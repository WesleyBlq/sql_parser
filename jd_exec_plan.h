/************************************************************
  Copyright (C), 2013-2015
  FileName:     jd_exec_plan.h
  Author:       qinbo(gqinbo@gmail.com)      
  Version :          
  Date:         
  Description:  sql������ִ�мƻ�ģ��   
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
#include "crud_build_plan.h"
#include "ob_logical_plan.h"


using namespace oceanbase::common;
using namespace oceanbase::sql;

#define MAX_SQL_EXEC_PLAN_SHARD_NUM   200

#define WHERE_IS_OR_AND     0
#define WHERE_IS_SUBQUERY   1

/*��ִ�е�Ԫ�ķ�װ*/
class ExecPlanUnit
{
private:
    string sql;
    schema_shard* shard_info;
public:
    void set_exec_unit_sql(string sql);
    string get_exec_unit_sql();
    void set_exec_uint_shard_info(schema_shard* shard_info);
    schema_shard* get_exec_unit_shard_info();
};

/*��ִ�мƻ��ķ�װ*/
class SameLevelExecPlan
{
private:
    vector<ExecPlanUnit*> exec_plan_units;
    bool is_1st_plan;
    char parent_sql_type; /**if need to be reparsed*/
public:
    SameLevelExecPlan();
    virtual ~SameLevelExecPlan();
    bool get_parent_sql_type();
    void set_parent_sql_type(uint8_t parent_sql_type);
    void set_first_plan_true();
    void is_first_plan();
    void add_exec_plan_unit(ExecPlanUnit* exec_plan_unit);
    vector<ExecPlanUnit*> get_all_exec_plan_units();
};

/*ִ�мƻ������class*/
class FinalExecPlan
{
private:
    vector<SameLevelExecPlan*> same_level_exec_plans;
    bool    union_is_distinct;
    int     to_do_exec_plan_sequ;

public:
    //friend class Optimizor;
    FinalExecPlan();
    virtual ~FinalExecPlan();
    void set_union_is_distinct(bool union_is_distinct);
    bool get_union_is_distinct();

    int get_TODO_exec_plan_sequ()
    {
        return to_do_exec_plan_sequ;
    }

    void set_TODO_exec_plan_sequ(int to_do_exec_plan_sequ_)
    {
        to_do_exec_plan_sequ = to_do_exec_plan_sequ_;
    }
    
    void add_same_level_exec_plan(SameLevelExecPlan* same_level_exec_plan);
    vector<SameLevelExecPlan*> get_all_same_level_exec_plans();
};

/*���ڲ���ִ�мƻ��Ķ�����class*/
class QueryActuator
{
public:
    QueryActuator(string current_db_name);
    virtual ~QueryActuator();
    FinalExecPlan* popActuator();
    void pushActuator(FinalExecPlan* exec_plan);

    bool is_all_plan_done();
    void set_all_plan_done();
    void set_next_plan_reparsed();
    bool get_next_plan_reparsed();
    void reparse_next_plan();

    /**************************************************
    Funtion     :   init_exec_plan
    Author      :   qinbo
    Date        :   2013.10.28
    Description :   generate exec plan
    Input       :   string current_db_name
    Output      :   
     **************************************************/
    int init_exec_plan(string current_db_name);

    /**************************************************
    Funtion     :   release_exec_plan
    Author      :   qinbo
    Date        :   2013.10.28
    Description :   generate exec plan
    Input       :   
    Output      :   
     **************************************************/
    int release_exec_plan();
    
    /**************************************************
    Funtion     :   release_exec_plan
    Author      :   qinbo
    Date        :   2013.10.28
    Description :   generate exec plan
    Input       :   
    Output      :   
     **************************************************/
    int generate_exec_plan(
            string sql,
            int32_t* index = NULL);

    /**************************************************
    Funtion     :   set_final_exec_plan
    Author      :   qinbo
    Date        :   2013.11.1
    Description :   set QueryActuator exec plans
    Input       :   
    Output      :   
     **************************************************/
    void set_final_exec_plan(FinalExecPlan* final_exec_plan_);
    
    /**************************************************
    Funtion     :   get_final_exec_plan
    Author      :   qinbo
    Date        :   2013.11.1
    Description :   set QueryActuator exec plans
    Input       :   
    Output      :   
     **************************************************/
    FinalExecPlan*  get_final_exec_plan();

    /**************************************************
    Funtion     :   release_exec_plan
    Author      :   qinbo
    Date        :   2013.10.28
    Description :   generate exec plan
    Input       :   
    Output      :   
     **************************************************/
    ResultPlan get_result_plan()
    {
        return result_plan;
    }

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
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);

        // get statement
        stmt = dynamic_cast<T*> (logical_plan->get_main_stmt());

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
    ParseResult result;
    ResultPlan result_plan;
    FinalExecPlan* final_exec_plan;

    //internal functions
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
    Funtion     :   reparse_where_with_route_for_one_table
    Author      :   qinbo
    Date        :   2013.10.17
    Description :   reparse distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    schema_table table_info,
                    vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                    vector<vector<ObRawExpr*> > opted_raw_exprs
    Output      :   
     **************************************************/
    bool reparse_where_with_route_for_one_table(
            ResultPlan& result_plan,
            schema_table* table_info,
            vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
            multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs);

    /**************************************************
    Funtion     :   reparse_where_with_route_for_multi_tables
    Author      :   qinbo
    Date        :   2013.10.29
    Description :   reparse distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    vector<schema_table*> table_infos,
                    vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                    vector<vector<ObRawExpr*> > opted_raw_exprs
    Output      :   
     **************************************************/
    bool reparse_where_with_route_for_multi_tables(
            ResultPlan& result_plan,
            ObSelectStmt *select_stmt,
            vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
            multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs);

    /**************************************************
    Funtion     :   build_shard_exprs_array_with_route_one_table
    Author      :   qinbo
    Date        :   2013.10.17
    Description :   generate distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    schema_table* table_info,
                    vector<ObRawExpr*> partition_sql_exprs,
                    vector<ObRawExpr*> atomic_exprs,
                    multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs
    Output      :   
     **************************************************/
    bool build_shard_exprs_array_with_route_one_table(
            ResultPlan& result_plan,
            schema_table* table_info,
            vector<ObRawExpr*> partition_sql_exprs,
            vector<ObRawExpr*> atomic_exprs,
            multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs);

    /**************************************************
    Funtion     :   build_shard_exprs_array_with_route_multi_table
    Author      :   qinbo
    Date        :   2013.10.17
    Description :   generate distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    ObSelectStmt *select_stmt,
                    vector<ObRawExpr*> partition_sql_exprs,
                    vector<ObRawExpr*> atomic_exprs,
                    multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs
    Output      :   
     **************************************************/
    bool build_shard_exprs_array_with_route_multi_table(
            ResultPlan& result_plan,
            vector<ObRawExpr*> partition_sql_exprs,
            vector<ObRawExpr*> atomic_exprs,
            multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs);


    /**************************************************
    Funtion     :   decompose_where_items
    Author      :   qinbo
    Date        :   2013.9.24
    Description :   generate distributed where conditions items
    Input       :   ObRawExpr* sql_expr
    Output      :   vector<vector<ObRawExpr*> > &atomic_exprs_array
    return      :   
     **************************************************/
    int decompose_where_items(ObRawExpr* sql_expr, vector<vector<ObRawExpr*> > &atomic_exprs_array);

    /**************************************************
    Funtion     :   search_partition_sql_exprs
    Author      :   qinbo
    Date        :   2013.10.18
    Description :   find all expr that need to be partitioned
    Input       :   vector<ObRawExpr*>  atomic_exprs,
                    vector<ObRawExpr*>  &partition_sql_exprs
    Output      :   
     **************************************************/
    int search_partition_sql_exprs(
            vector<ObRawExpr*> atomic_exprs,
            vector<ObRawExpr*> &partition_sql_exprs);
    
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
    
    /**************************************************
    Funtion     :   generate_all_table_shards
    Author      :   qinbo
    Date        :   2013.10.24
    Description :   generate all tables' shards
    Input       :   ResultPlan& result_plan,
                    vector<schema_table*> table_infos,
                    vector<vector<schema_shard*> > &all_tables_shards
    Output      :   
     **************************************************/
    void generate_all_table_shards(ResultPlan& result_plan,
            vector<string> table_names,
            vector<vector<schema_shard*> > &all_tables_shards);
    /**************************************************
    Funtion     :   vector_elem_exist_already
    Author      :   qinbo
    Date        :   2013.10.30
    Description :   vector elem is already existing
    Input       :   vector<schema_shard*> vector_shards,
                    schema_shard* single_shard
    Output      :   
     **************************************************/
    bool vector_elem_exist_already( 
                            vector<schema_shard*> vector_shards,
                            schema_shard* single_shard);
    
    /**************************************************
    Funtion     :   distribute_sql_to_all_shards
    Author      :   qinbo
    Date        :   2013.11.6
    Description :   vector elem is already existing
    Input       :   ResultPlan& result_plan,
                    const uint64_t& query_id,
                    schema_table* table_schema,
                    SameLevelExecPlan* exec_plan
    Output      :   
    return      :
     **************************************************/
    int distribute_sql_to_all_shards( 
                    ResultPlan& result_plan,
                    const uint64_t& query_id,
                    schema_table* table_schema,
                    SameLevelExecPlan* exec_plan);
};


#endif /* _JD_EXEC_PLAN_H */

