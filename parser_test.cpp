
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
#include "ob_multi_logic_plan.h"


using namespace std;
using namespace oceanbase;
using namespace oceanbase::common;
using namespace oceanbase::sql;

int
sql_parser(char * sql)
{
    int32_t ret = 0;
    ParseResult result;

    DBMetaReader *metareader = new DBMetaReader;
    if(metareader->DBMetaReader_init())
    {
        cout << "init success" << endl;
    }

    ResultPlan result_plan;
    result_plan.name_pool_ = NULL;
    result_plan.meta_reader = metareader;
    result_plan.plan_tree_ = NULL;

    uint64_t query_id = OB_INVALID_ID;


    if(parse_init(&result))
    {
        printf("parse_init error!!!\n");
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
            default:
                break;
        }
    }

    if(NULL == result_plan.plan_tree_)
    {
        fprintf(stderr,"\n<<result_plan.plan_tree_ is NULL>>\n");
        return 1;
    }

    ObLogicalPlan* multi_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    fflush(stderr);
    fprintf(stderr,"\n<<Part 3 : LOGICAL PLAN>>\n");
    multi_plan->print();

    if(result_plan.plan_tree_ != NULL)
    {
        //delete (static_cast<multi_plan*>(result_plan->plan_tree_));
        parse_free(result_plan.plan_tree_);

        result_plan.plan_tree_ = NULL;
        result_plan.name_pool_ = NULL;
        result_plan.meta_reader = NULL;
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
    char *sql1 = "INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees')";
    char *sql2 = "INSERT INTO User (user_name, user_desc) VALUES ('dafenqi', 'aturtle')";
    char *sql4 = "SELECT Customer,SUM(OrderPrice) FROM Orders \
WHERE Customer='Bush' OR Customer='Adams' \
GROUP BY Customer \
HAVING SUM(OrderPrice)>1500";

    char *sql5 = "SELECT Persons.LastName, Persons.FirstName, Orders.OrderNo \
FROM Persons \
INNER JOIN Orders \
ON Persons.Id_P = Orders.Id_P \
ORDER BY Persons.LastName";

    sql_parser(sql1);
    //sql_parser(sql2);
    //sql_parser(sql4);
    //sql_parser(sql5);
    return 1;
}




