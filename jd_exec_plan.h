/************************************************************
  Copyright (C), 2013-2015
  FileName:     jd_exec_plan.h
  Author:       qinbo(gqinbo@gmail.com)      
  Version :          
  Date:         
  Description:  sql语句生成执行计划模块   
  History: 
      <author>  <time>   <version >     <desc>
      qinbo    2013/8/5     1.0         build this moudle  
***********************************************************/
#ifndef _JD_EXEC_PLAN_H
#define _JD_EXEC_PLAN_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdexcept>
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


#if 0

using std::vector;
using std::string;

class SqlParser
{
    private:
        uint32_t sql_length;
        
    public:
        ParseNode* parse(char *sql);
        uint32_t get_sql_length();
};


/*对执行单元的封装*/
class  ExecPlanUnit
{
    private:
        string sql;
        //TABLET_INFO *db_info;
    public:
        void set_exec_unit_sql(string &sql);
        //void set_exec_uint_db_info(TABLET_INFO *db_info)
}

/*对执行计划的封装*/
class ExecPlan
{
    private:
        vector<ExecPlanUnit*> exec_plan;
        bool    is_first_plan;
        char    parent_sql_type;        /**if need to be reparsed*/
    public:
        bool    get_parent_sql_type();
        void    set_parent_sql_type(uint8 parent_sql_type);
        void    set_first_plan_true();
        void    is_first_plan();
}


/*执行计划本身的class*/
class QueryPlan
{
    private:
        vector<ExecPlan*> exec_plan;

    public:
       //friend class Optimizor;
}


/*用于操作执行计划的动作的class*/
class QueryActuator
{
  public:
    /**
     * execute the SQL statement directly
     *
     * @param stmt [in]
     * @param result [out]
     *
     * @return oceanbase error code defined in ob_define.h
     */
    static int direct_execute(const string &stmt);
    /**
     * prepare the SQL statement for later execution
     * @see stmt_execute()
     * @param stmt [in]
     * @param result [out]
     * @param context [out]
     *
     * @return oceanbase error code defined in ob_define.h
     */
    static int stmt_prepare(const string &stmt);
  private:
    // types and constants
    bool is_all_plan_done;
    bool is_next_plan_list_reparsed;
  private:
    QueryActuator(){}
    QueryActuator(){}
    // disallow copy
    QueryActuator(const QueryActuator &other);
    //static int generate_logical_plan(const string &stmt, ResultPlan  &logical_plan);
    void generate_exec_plans(string &sql);       /*generate the whole exec_plan*/
    void release_exec_plans();
    
    ExecPlan* popActuator();
    void pushActuator(ExecPlan* exec_plan);
    
    bool is_all_plan_done();
    void set_all_plan_done();
    void set_next_plan_reparsed();
    bool is_next_plan_reparsed();
    void reparse_next_plan(QueryPlan* exec_query_plan);
  private:
    // data members
};
#endif
#endif /* _JD_EXEC_PLAN_H */

