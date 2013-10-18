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

#include <stdint.h>
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
#include <map>  

#include "parse_malloc.h"
#include "parse_node.h"
#include "utility.h"
#include "ob_define.h"
#include "ob_obj_type.h"
#include "ob_expr_obj.h"

#include "ob_logical_plan.h"
#include "ob_select_stmt.h"
#include "ob_delete_stmt.h"
#include "ob_insert_stmt.h"
#include "ob_update_stmt.h"
#include "dml_build_plan.h"
#include "ob_logical_plan.h"


using namespace oceanbase::common;
using namespace oceanbase::sql;

/*对执行单元的封装*/
class  ExecPlanUnit
{
    private:
        string sql;
        schema_shard* shard_info;
    public:
        void set_exec_unit_sql(string sql);
        void set_exec_uint_shard_info(schema_shard* shard_info);
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
        void    add_exec_plan_unit(ExecPlanUnit* exec_plan_unit);
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
        /**************************************************
        Funtion     :   get_stmt_instance
        Author      :   qinbo
        Date        :   2013.10.9
        Description :   generate exec plan
        Input       :   ResultPlan& result_plan,
                        T *& stmt
        Output      :   
        **************************************************/
        template <class T>
        bool get_stmt_instance(
            ResultPlan& result_plan,
            T *& stmt)
        {
            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
            
            /* get statement */
            stmt = dynamic_cast<T*>(logical_plan->get_main_stmt());
            
            if (stmt == NULL)
            {
                return false;
            }
            return true;
        }
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
        
        /**************************************************
        Funtion     :   reparse_where_items_with_route
        Author      :   qinbo
        Date        :   2013.10.17
        Description :   reparse distributed where conditions items
        Input       :   ResultPlan& result_plan,
                        schema_table table_info,
                        vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                        vector<vector<ObRawExpr*> > opted_raw_exprs
        Output      :   
        **************************************************/
        bool reparse_where_items_with_route( 
                                ResultPlan& result_plan,
                                schema_table* table_info,
                                vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                                multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs);
        
        /**************************************************
        Funtion     :   search_partition_sql_exprs_for_one_table
        Author      :   qinbo
        Date        :   2013.10.18
        Description :   find all expr that need to be partitioned
        Input       :   vector<ObRawExpr*>  atomic_exprs,
                        vector<ObRawExpr*>  &partition_sql_exprs
        Output      :   
        **************************************************/
        int search_partition_sql_exprs_for_one_table(
                                vector<ObRawExpr*>  atomic_exprs,
                                vector<ObRawExpr*>  &partition_sql_exprs);

        /**************************************************
        Funtion     :   build_shard_exprs_array_with_route
        Author      :   qinbo
        Date        :   2013.10.17
        Description :   generate distributed where conditions items
        Input       :   ResultPlan& result_plan,
                        string &sql
                        vector<vector<ObRawExpr*> > partition_sql_exprs
                        vector<vector<ObRawExpr*> > atomic_exprs,
                        multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs
        Output      :   
        **************************************************/
        int build_shard_exprs_array_with_route( 
                                ResultPlan& result_plan,
                                schema_table* table_info,
                                vector<ObRawExpr*>  partition_sql_exprs,
                                vector<ObRawExpr*>  atomic_exprs,
                                multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs);
        
        /**************************************************
        Funtion     :   generate_distributed_where_items
        Author      :   qinbo
        Date        :   2013.10.17
        Description :   generate distributed where conditions items
        Input       :   ObRawExpr* sql_expr
        Output      :   
        **************************************************/
        vector<vector<ObRawExpr*> > decompose_where_items(ObRawExpr* sql_expr);
        /**************************************************
        Funtion     :   append_distributed_where_items
        Author      :   qinbo
        Date        :   2013.10.17
        Description :   generate distributed where conditions items
        Input       :   ResultPlan& result_plan,
                        string &sql
                        vector<vector<ObRawExpr*> > &atomic_exprs_array
        Output      :   
        **************************************************/
        void append_distributed_where_items(ResultPlan& result_plan,
                                           string &sql, 
                                           vector<vector<ObRawExpr*> > &atomic_exprs_array);
};


#endif /* _JD_EXEC_PLAN_H */

