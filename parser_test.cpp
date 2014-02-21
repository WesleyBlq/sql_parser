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
void process_segment_default(int signo)
{
    signo = signo;
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
void init_signal_handler() 
{
    struct sigaction act;
    act.sa_handler = &process_segment_default ;
    act.sa_flags |= SA_RESETHAND;
    sigaction(SIGSEGV, &act, NULL);
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
    init_signal_handler();
    
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

    string sql13 = "select * from tt inner join pp on tt.id > pp.id and tt.id < 1000;";

    string sql15 = "SELECT COUNT(lastname), address AS addr FROM persons WHERE lastname > 'cao1' AND id = 10 AND (id = 15 OR id = 100)";
    string sqls = "select t.id, s.lastname from persons t join persons s on t.id = s.id";
    string sql_multi_table = "select * from tt AS ttt, pp WHERE tt.id > 10 AND pp.id>10";

    string sql_test1 = "SELECT id, name, age from pp where id = 1 OR id = 150";
    string sql_test2 = "SELECT id from pp where id>5  AND id<20 AND (id = 6 OR id = 10) AND name = 'beijing'";
    string sql_test3 = "SELECT * FROM pp";
    
    string sql_test40 = "select max(id) as id, name, avg(age) as age from tt";
    
    // UNION distinct SELECT id FROM tt
    string sql_test5 = "SELECT MAX(id) from pp where id>5  AND id<20 AND name = 'beijing' GROUP BY name, id Having SUM(age)>100 ORDER BY age";
    string sql_test4 = "select max(id), name, avg(age) as cao  from tt  group by age HAVING cao>1 order by id LIMIT 10,100"; //
    string sql_test6 = "show databases"; //
    string sql_test8 = "update tt set id=3 where id is null";
    string sql12 = "insert into tt(id,name) select id,name from tt"; //id, name, age 
    string sql_test9 = "replace into tt set id=8,name='name8'";
    string sql_test10= "select concat(name,age) from tt";
    string sql_test11 = "SELECT tt.id, tt.name, pp.age FROM tt JOIN pp ON (tt.id = pp.id AND tt.age = pp.age) where tt.id = 100 ORDER BY tt.name";
    string sql_test14 = "SELECT tt.id, tt.name, pp.age FROM tt JOIN pp ON tt.id = pp.id where tt.id > 1 ORDER BY tt.name";
    string sql_test15 = "SELECT * FROM tt JOIN pp ON tt.id = pp.id where tt.id = 100 ORDER BY tt.name";
    
    string sql_test12 = "insert into tt(id) values(null)";
    string sql_test13 = "select * from pp,tt where tt.id=pp.id;";
    string sql_test16 = "delete from tt where id=590076 limit 1";
    string sql_test17 = "insert into pp(id) values ('1000')";

    string sql_test7 = "insert into tt(name ,age) values \
        ('Human Resources', 100),\
        (2, 'Sales', 10), \
        (3, 'Finance', 20)";
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test13)))
    { 
        ret = JD_ERR_GEN_PLAN;
    }
    #if 0
    query_actuator->release_exec_plan();
    query_actuator->init_exec_plan("oxwf");
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_multi_table)))
    {
        ret = JD_ERR_GEN_PLAN;
    }
    query_actuator->release_exec_plan();
    #endif
    #if 0
    query_actuator->init_exec_plan("oxwf");
    if (OB_SUCCESS != (ret = query_actuator->generate_exec_plan(sql_test15)))
    {
        ret = JD_ERR_GEN_PLAN;
    }
    #endif
    
    delete query_actuator;
    //sql_parser(sql14);
    //sql_parser(sql9);
    //sql_parser(sql8, "qinbo");
    
    return 1;
}

