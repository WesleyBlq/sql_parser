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
    int ret = 0;
    QueryActuator *query_actuator = new QueryActuator(current_db_name);
            
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql)))
    {
        fprintf(stderr, "generate_exec_plan: %s\n", query_actuator->get_result_plan().err_stat_.err_msg_);
        ret = OB_ERR_GEN_PLAN;
        return ret;
    }

    delete query_actuator;
}


int main(void)
{
    string sql1 = "INSERT INTO persons (lastname, address) VALUES ('Wilson', 'Champs-Elysees')";
    string sql2 = "SELECT * FROM persons";
    string sql3 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE id IN (select id from order_list) GROUP BY lastname";

    string sql4 = "SELECT lastname, address FROM persons \
WHERE lastname='Bush' OR address='Adams' AND id = 10\
GROUP BY lastname HAVING(count(lastname) > 10) ORDER BY lastname desc limit 100, 10";

    string sql7 = "select lastname,address FROM persons \
WHERE id=(select id from persons where lastname='NEW YORK')";

    string sql5 = "SELECT persons.lastname, persons.address, order_list.order_desc \
FROM persons \
JOIN order_list \
ON persons.id = order_list.id \
ORDER BY persons.lastname";

    string sql6 = "select id, order_desc from (select * from order_list) ooxx where id > 50";

    string sql9 = "SELECT id FROM persons WHERE lastname = 'Attendee' AND address = 'beijing'  AND (id = 147 OR id = 155)";

    string sql10 = "UPDATE persons SET address = 'BEIJING' WHERE lastname = 'Wilson'";
    string sql11 = "SELECT COUNT(lastname), address AS addr FROM persons";

    string sql12 = "INSERT INTO persons VALUES ('Gates', 'Bill', 100), ('qinbo', 'qin', 101)";

    string sql13 = "INSERT INTO persons (address, lastname)  \
SELECT address,lastname FROM persons";

    string sql14 = "DELETE FROM persons  WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";

    string sql15 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";
    string sqls = "select t.id, s.lastname from persons t join persons s on t.id = s.id";
    string sql_multi_table = "select * from persons, order_list \
        WHERE persons.lastname = 'Attendee' AND persons.address = 'beijing'  AND (persons.id = 147 OR persons.id = 155)";

    string sql_test1 = "SELECT id, name, age from tt where id = 147 OR id = 155";
    string sql_test2 = "SELECT id from pp where id>5  AND id<20 AND (id = 6 OR id = 10) AND name = 'beijing'";
    string sql_test3 = "SELECT id FROM pp";
    
    //string sql_test4 = "SELECT id from pp where id>5  AND id<20 AND (id = 6 OR id = 10) AND name = 'beijing' UNION distinct SELECT id FROM tt";
    
    string sql_test4 = "select * from t1 order by id";
    //sql_parser(sql3, "qinbo");
    //sql_parser(sql6);
    //sql_parser(sql10);
    sql_parser(sql_test4, "oxwf");
    //sql_parser(sql14);
    //sql_parser(sql9);
    //sql_parser(sql8, "qinbo");
    return 1;
}

