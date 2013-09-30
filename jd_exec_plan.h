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

#include <string>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "utility.h"
#include "ob_define.h"

using namespace oceanbase::common;
using namespace oceanbase::sql;

/*对执行单元的封装*/
class  ExecPlanUnit
{
    private:
        string sql;
        //TABLET_INFO *db_info;
    public:
        void set_exec_unit_sql(string &sql);
        //void set_exec_uint_db_info(TABLET_INFO *db_info)
};

/*对执行计划的封装*/
class SameLevelExecPlan
{
    private:
        vector<ExecPlanUnit*> exec_plan_units;
        bool    is_1st_plan;
        char    parent_sql_type;        /**if need to be reparsed*/
    public:
        bool    get_parent_sql_type();
        void    set_parent_sql_type(uint8_t parent_sql_type);
        void    set_first_plan_true();
        void    is_first_plan();
};


/*执行计划本身的class*/
class FinalExecPlan
{
    private:
        vector<SameLevelExecPlan*> exec_plan;

    public:
       //friend class Optimizor;
};


/*用于操作执行计划的动作的class*/
class QueryActuator
{    
    public:
        QueryActuator();
        virtual ~QueryActuator();
        FinalExecPlan* popActuator();
        void pushActuator(FinalExecPlan* exec_plan);
        
        bool is_all_plan_done();
        void set_all_plan_done();
        void set_next_plan_reparsed();
        bool get_next_plan_reparsed();
        void reparse_next_plan();

        int generate_exec_plan(
                ResultPlan& result_plan,
                FinalExecPlan*&  physical_plan,
                ErrStat& err_stat,
                const uint64_t& query_id = oceanbase::common::OB_INVALID_ID,
                int32_t* index = NULL);
  private:
        // types and constants
        bool is_plan_done;
        bool is_next_plan_reparsed;



        /*internal functions*/
        int generate_select_plan_single_table(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int generate_select_plan_multi_table(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int gen_exec_plan_update(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int gen_exec_plan_replace(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int gen_exec_plan_delete(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int gen_exec_plan_select(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);
        int gen_exec_plan_insert(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            int32_t* index);

        template <class T>
        int get_stmt(
            ObLogicalPlan *logical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            T *& stmt);
};


#endif /* _JD_EXEC_PLAN_H */

