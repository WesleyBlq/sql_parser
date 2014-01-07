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


int
sql_parser(string sql, string current_db_name)
{

}


int main(void)
{
    int ret = 0;
    QueryActuator *query_actuator = new QueryActuator("oxwf");
            

    string sql1 = "INSERT INTO persons (lastname, address) VALUES ('Wilson', 'Champs-Elysees')";
    string sql2 = "SELECT * FROM persons";
    string sql3 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE id IN (select id from order_list) GROUP BY lastname";

    string sql4 = "SELECT lastname, address FROM persons \
WHERE lastname='Bush' OR address='Adams' AND id = 10\
GROUP BY lastname HAVING(count(lastname) > 10) ORDER BY lastname desc limit 100, 10";

    string sql7 = "select id,name FROM tt \
WHERE id=(select id from pp)";

    string sql5 = "SELECT tt.id, tt.name, pp.age \
FROM tt \
JOIN pp \
ON tt.id = pp.id \
ORDER BY tt.name";

    string sql6 = "select id, name, age from (select * from tt) ooxx where id > 50";

    string sql9 = "SELECT id FROM tt WHERE name = 'Attendee' AND age = 10  AND (id = 147 OR id = 155)";

    string sql10 = "UPDATE persons SET address = 'BEIJING' WHERE lastname = 'Wilson'";
    string sql11 = "SELECT COUNT(lastname), address AS addr FROM persons";


    string sql13 = "INSERT INTO persons (address, lastname)  \
SELECT address,lastname FROM persons";

    string sql14 = "DELETE FROM persons  WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";

    string sql15 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";
    string sqls = "select t.id, s.lastname from persons t join persons s on t.id = s.id";
    string sql_multi_table = "select * from tt AS ttt, pp WHERE tt.id > 10";

    string sql_test1 = "SELECT id, name, age from pp where id = 1 OR id = 150";
    string sql_test2 = "SELECT id from pp where id>5  AND id<20 AND (id = 6 OR id = 10) AND name = 'beijing'";
    string sql_test3 = "SELECT * FROM pp";
    
    string sql_test40 = "select max(id) as id, name, avg(age) as age from tt";
    
    // UNION distinct SELECT id FROM tt
    string sql_test5 = "SELECT MAX(id) from pp where id>5  AND id<20 AND name = 'beijing' GROUP BY name Having SUM(age)>100 ORDER BY age";
    string sql_test4 = "select max(id), name, avg(age) as cao  from tt  group by age HAVING cao>1 order by id LIMIT 10,100"; //
    string sql_test6 = "show databases"; //
    string sql_test7 = "INSERT INTO pp (name, age) VALUES ('Bill',26)";
    
    string sql12 = "INSERT INTO pp VALUES (10, 'Bill', 26), (201, 'qin', 26)"; //id, name, age 
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test1)))
    {
        fprintf(stderr, "generate_exec_plan: %s\n", query_actuator->get_result_plan().err_stat_.err_msg_);
        ret = OB_ERR_GEN_PLAN;
        return ret;
    }
    #if 0
    query_actuator->release_exec_plan();
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test5)))
    {
        fprintf(stderr, "generate_exec_plan: %s\n", query_actuator->get_result_plan().err_stat_.err_msg_);
        ret = OB_ERR_GEN_PLAN;
        return ret;
    }
    #endif
    
    delete query_actuator;
    //sql_parser(sql14);
    //sql_parser(sql9);
    //sql_parser(sql8, "qinbo");
    return 1;
}

