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
#include <signal.h>

#include "parse_malloc.h"
#include "parse_node.h"
#include "utility.h"
#include "ob_define.h"
#include "sql_logical_plan.h"
#include "sql_select_stmt.h"
#include "sql_delete_stmt.h"
#include "sql_insert_stmt.h"
#include "sql_update_stmt.h"
#include "dml_build_plan.h"
#include "jd_exec_plan.h"


using namespace std;
using namespace jdbd;
using namespace jdbd::common;
using namespace jdbd::sql;


/**************************************************
Funtion		:	process_segment_default
Author		:	qinbo
Date		:	2014.1.9
Description	:   process_segment_default
Input		:	
Output		:	
return      :
**************************************************/
void process_segment_default(int sig)
{
    sig = sig;
    BACKTRACE();
    exit(0);
}

/**************************************************
Funtion		:	init_signal_handlers
Author		:	qinbo
Date		:	2014.1.9
Description	:   init signal process handler
Input		:	
Output		:	
return      :
**************************************************/
void init_signal_handlers() 
{
    signal(SIGSEGV, process_segment_default);
}

int
sql_parser(string sql, string current_db_name)
{

}


int main(void)
{
    int ret = 0;
    QueryActuator *query_actuator = new QueryActuator("oxwf");
    meta_reader::get_instance().init();
    router::get_instance().init();
    init_signal_handlers();

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

    string sql11 = "SELECT COUNT(lastname), address AS addr FROM persons";

    string sql13 = "INSERT INTO persons (address, lastname)  \
SELECT address,lastname FROM persons";

    string sql15 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";
    string sqls = "select t.id, s.lastname from persons t join persons s on t.id = s.id";
    string sql_multi_table = "select * from tt AS ttt, pp WHERE tt.id > 10";

    string sql_test1 = "SELECT id, name, age from pp where id = 1 OR id = 150";
    string sql_test2 = "SELECT id from pp where id>5  AND id<20 AND (id = 6 OR id = 10) AND name = 'beijing'";
    string sql_test3 = "SELECT * FROM pp";
    
    string sql_test40 = "select max(id) as id, name, avg(age) as age from tt";
    
    // UNION distinct SELECT id FROM tt
    string sql_test5 = "SELECT MAX(id) from pp where id>5  AND id<20 AND name = 'beijing' GROUP BY name, id Having SUM(age)>100 ORDER BY age";
    string sql_test4 = "select max(id), name, avg(age) as cao  from tt  group by age HAVING cao>1 order by id LIMIT 10,100"; //
    string sql_test6 = "show databases"; //
    string sql_test7 = "INSERT INTO t (age) VALUES (26)";
    string sql_test8 = "UPDATE tt SET age = 26 WHERE id = 100";
    string sql12 = "INSERT INTO pp VALUES (10, 'Bill', 26), (201, 'qin', 26)"; //id, name, age 
    string sql_test9 = "replace into tt set id=8,name='name8'";
    string sql_test10= "select concat(name,age) from tt";
    string sql_test11 = "SELECT tt.id, tt.name, pp.age \
    FROM tt \
    JOIN pp \
    ON tt.id = pp.id \
    ORDER BY tt.name";
    
    string sql_test12 = "select count(*) from tt where id is null";
    string sql_test13 = "select create_time+0 from tt";
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test13)))
    {
        ret = OB_ERR_GEN_PLAN;
    }
    #if 0
    query_actuator->release_exec_plan();
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test13)))
    {
        ret = OB_ERR_GEN_PLAN;
    }
    #endif
    
    delete query_actuator;
    //sql_parser(sql14);
    //sql_parser(sql9);
    //sql_parser(sql8, "qinbo");
    return 1;
}

