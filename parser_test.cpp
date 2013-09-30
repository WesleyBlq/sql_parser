
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <map>
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>


#include "parse_malloc.h"
#include "parse_node.h"
#include "utility.h"
#include "ob_define.h"
#include "ob_logical_plan.h"
#include "ob_select_stmt.h"
#include "ob_delete_stmt.h"
#include "ob_insert_stmt.h"
#include "ob_update_stmt.h"
#include "dml_build_plan.h"
#include "jd_exec_plan.h"


using namespace std;
using namespace oceanbase;
using namespace oceanbase::common;
using namespace oceanbase::sql;

meta_reader *g_metareader = NULL;

int
sql_parser(char * sql)
{
    int32_t ret = 0;
    ParseResult result;

    g_metareader = new meta_reader;

    #if 0
    if(g_metareader->DBMetaReader_init())
    {
        cout << "init success" << endl;
    }
    #endif

    g_metareader->add_DB_schema("qinbo");
    g_metareader->add_table_schema("qinbo","persons", 100);
    g_metareader->add_column_schema("qinbo","persons", "lastname", 1111, CHAR, 0);
    g_metareader->add_column_schema("qinbo","persons", "address", 1112, CHAR, 0);
    g_metareader->add_column_schema("qinbo","persons", "id", 1113, INT, 0);

    g_metareader->add_table_schema("qinbo","order_list", 101);
    g_metareader->add_column_schema("qinbo","order_list", "id", 1211, INT, 0);
    g_metareader->add_column_schema("qinbo","order_list", "item_id", 1212, INT, 0);
    g_metareader->add_column_schema("qinbo","order_list", "order_desc", 1213, CHAR, 0);    

    schema_table* schema_table = g_metareader->get_table_schema("qinbo",  "persons");
     if (schema_table) {
         cout << "get_table_id:" << schema_table->get_table_id() << endl;
     }
    
     schema_column* schema_column = g_metareader->get_column_schema("qinbo","persons", "address");
     if (schema_column) {
         cout << "address: get_column_id:" << schema_column->get_column_id() << endl;
     }
    
     schema_column = g_metareader->get_column_schema("qinbo","persons", "lastname");
     if (schema_column) {
         cout << "lastName: get_column_id:" << schema_column->get_column_id() << endl;
     }
    
     int a =  g_metareader->get_all_column_schemas("qinbo","persons").size();
     //cout << "persons: column_num:" << a << endl;
     
     a =  g_metareader->get_all_column_schemas("qinbo","order_list").size();
     //cout << "order_list: column_num:" << a << endl;


    router *route_info = new router;
    route_info->route_init(g_metareader);

    
    ResultPlan result_plan;
    result_plan.name_pool_  = NULL;
    result_plan.route_info  = (void*)route_info;
    result_plan.plan_tree_  = NULL;
    result_plan.db_name     = "qinbo"; 

    route_info->test();


    uint64_t query_id = OB_INVALID_ID;


    if(parse_init(&result))
    {
        printf("parse_init error!!!\n");
        return 1;
    }

    fprintf(stderr,"<<Part 1 : SQL STRING>>\n%s\n",sql);
    parse_sql(&result,sql,strlen(sql));


    fflush(stderr);
    if(result.result_tree_ == 0)
    {
        fprintf(stderr,"parse_sql error!\n");
        fprintf(stderr,"%s at %d:%d\n",result.error_msg_,result.line_,result.start_col_);
    }
    else
    {
        fprintf(stderr,"\n<<Part 2 : PARSE TREE>>\n");
        print_tree(result.result_tree_,0);
    }


    if(result.result_tree_ != NULL)
    {
        switch(result.result_tree_->children_[0]->type_)
        {
            fprintf(stderr,"\n<<result.result_tree_>>\n");
            case T_SELECT:
            {
                ret = resolve_select_stmt(&result_plan,result.result_tree_->children_[0],query_id);
                break;
            }
            case T_DELETE:
            {
                ret = resolve_delete_stmt(&result_plan,result.result_tree_->children_[0],query_id);
                break;
            }
            case T_INSERT:
            {
                fprintf(stderr,"\n<<resolve_insert_stmt>>\n");
                ret = resolve_insert_stmt(&result_plan,result.result_tree_->children_[0],query_id);
                break;
            }
            case T_UPDATE:
            {
                fprintf(stderr,"\n<<resolve_update_stmt>>\n");
                ret = resolve_update_stmt(&result_plan,result.result_tree_->children_[0],query_id);
                break;
            }
            default:
                break;
        }
    }

    if(NULL == result_plan.plan_tree_)
    {
        fprintf(stderr,"\n<<result_plan.plan_tree_ is NULL>>\n");
        fprintf(stderr, "RESULT_PLAN: %s\n", result_plan.err_stat_.err_msg_);
        return 1;
    }

    //if (OB_SUCCESS != ret)
    fprintf(stderr, "RESULT_PLAN: %s\n", result_plan.err_stat_.err_msg_);

    ObLogicalPlan* logic_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    fflush(stderr);
    fprintf(stderr,"\n<<Part 3 : LOGICAL PLAN>>\n");
    logic_plan->print();
    char str[2048] = {0};
    logic_plan->make_stmt_string(result_plan, str, 2048);
    fprintf(stderr, "\nstmt_string: %s\n", str);

#if 1
    QueryActuator query_actuator;
    FinalExecPlan* final_exec_plan = NULL;
    ErrStat err_stat;
    if (OB_SUCCESS != (ret = query_actuator.generate_exec_plan(result_plan, final_exec_plan, err_stat)))
    {
      TBSYS_LOG(WARN, "failed to transform to physical plan");
      ret = OB_ERR_GEN_PLAN;
    }
#endif

    if(result_plan.plan_tree_ != NULL)
    {
        //delete (static_cast<logic_plan*>(result_plan->plan_tree_));
        parse_free(result_plan.plan_tree_);

        result_plan.plan_tree_ = NULL;
        result_plan.name_pool_ = NULL;
    }

    if(result.result_tree_)
    {
        destroy_tree(result.result_tree_);
        result.result_tree_ = NULL;
    }

    printf("\n");
}


int main(void)
{
    char *sql1 = "INSERT INTO persons (lastname, address) VALUES ('Wilson', 'Champs-Elysees')";
    char *sql2 = "SELECT * FROM persons";
    char *sql3 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE id IN (select id from order_list) GROUP BY lastname";

    char *sql4 = "SELECT lastname, address FROM persons \
WHERE lastname='Bush' OR address='Adams' AND id = 10\
GROUP BY lastname HAVING(count(lastname) > 10) ORDER BY lastname desc limit 100, 10";

    char *sql7 = "select lastname,address FROM persons \
WHERE id=(select id from persons where lastname='NEW YORK')";


    char *sql5 = "SELECT persons.lastname, persons.address, order_list.order_desc \
FROM persons \
JOIN order_list \
ON persons.id = order_list.id \
ORDER BY persons.lastname";

    char *sql6 = "select id, order_desc from (select * from order_list) ooxx where id > 50";

    char *sql9 = "SELECT id FROM persons WHERE lastname = 'Attendee' AND address = 'beijing'  AND (id = 147 OR id = 155)";

    char *sql8 = "SELECT id FROM persons    \
UNION ALL   \
SELECT id FROM order_list";

    char *sql10 = "UPDATE persons SET address = 'BEIJING' WHERE lastname = 'Wilson'";
    char *sql11 = "INSERT INTO persons (address, lastname) VALUES ('BEIJING', 'Champs-Elysees')";

    char *sql12 = "INSERT INTO persons VALUES ('Gates', 'Bill', 100), ('qinbo', 'qin', 101)";

    char *sql13 = "INSERT INTO persons (address, lastname)  \
SELECT address,lastname FROM persons";

    char *sql14 = "DELETE FROM persons  WHERE address = 'beijing'";

    char *sql15 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE id IN (10,11,12)";

    //sql_parser(sql4);
    //sql_parser(sql6);
    sql_parser(sql15);
    //sql_parser(sql14);
    //sql_parser(sql9);
    //sql_parser(sql8);
    return 1;
}
