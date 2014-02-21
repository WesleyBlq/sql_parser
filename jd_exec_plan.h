/************************************************************
  Copyright (C), 2013-2015
  FileName:     jd_exec_plan.h
  Author:       qinbo      
  Version :          
  Date:         
  Description:  exec plan generator
  History: 
      <author>  <time>   <version >     <desc>
      qinbo    2013/9/15     1.0       build this moudle  
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
#include "ob_obj_type.h"
#include "ob_expr_obj.h"

#include "sql_logical_plan.h"
#include "sql_select_stmt.h"
#include "sql_delete_stmt.h"
#include "sql_insert_stmt.h"
#include "sql_update_stmt.h"
#include "dml_build_plan.h"
#include "crud_build_plan.h"
#include "sql_logical_plan.h"
#include "query_reduce.h"

using namespace jdbd::common;
using namespace jdbd::sql;

#define MAX_SQL_EXEC_PLAN_SHARD_NUM   200

#define SEND_SQL_TO_CONFIG_SERVER   0
#define SEND_SQL_TO_DATA_NODE       1

#define SHARD_NOT_FOUND             0xffffffff
/*��ִ�е�Ԫ�ķ�װ*/
class ExecPlanUnit
{
private:
    string sql;
    schema_shard* shard_info;
public:
    ExecPlanUnit();
    virtual ~ExecPlanUnit();
    
    void set_exec_unit_sql(string sql_)
    {
        sql = sql_;
    }
    
    string get_exec_unit_sql()
    {
        return sql;
    }
    
    void set_exec_uint_shard_info(schema_shard* shard_info_)
    {
        shard_info = shard_info_;
    }
    
    schema_shard* get_exec_unit_shard_info()
    {
        return shard_info;
    }
};

/*��ִ�мƻ��ķ�װ*/
class SameLevelExecPlan
{
private:
    vector<ExecPlanUnit*> exec_plan_units;
    QueryPostReduce*    query_post_reduce_info;     //record sql post process info
    bool                is_1st_plan;
    char                parent_sql_type;            //if need to be reparsed
    uint8_t             sql_sent_goal;              //where this sql should be sent
    
public:
    SameLevelExecPlan();
    virtual ~SameLevelExecPlan();
    bool get_parent_sql_type();
    void set_parent_sql_type(uint8_t parent_sql_type);
    void set_first_plan_true();
    bool is_first_plan();
    void add_exec_plan_unit(ExecPlanUnit* exec_plan_unit);
    vector<ExecPlanUnit*> get_all_exec_plan_units();
    void set_query_post_reduce_info(QueryPostReduce* query_post_reduce_info_)
    {
        query_post_reduce_info = query_post_reduce_info_;
    }

    QueryPostReduce*  get_query_post_reduce_info()
    {
        return query_post_reduce_info;
    }
    
    void set_sql_sent_goal(uint8_t sql_sent_goal_)
    {
        sql_sent_goal = sql_sent_goal_;
    }
    
    uint8_t get_sql_sent_goal()
    {
        return sql_sent_goal;
    }
};

/*ִ�мƻ������class*/
class FinalExecPlan
{
private:
    vector<SameLevelExecPlan*> same_level_exec_plans;
    bool    union_is_distinct;
    int     to_do_exec_plan_sequ;

public:
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
    void release_exec_plan();
    
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
            uint32_t* index = NULL);
    
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
    
    //BEGIN: add by tangchao 20131225
    ObBasicStmt::StmtType get_query_type()
    {
        return query_type;
    }
    //END: add by tangchao 20131225
private:
    // types and constants
    bool is_plan_done;
    bool is_next_plan_reparsed;
    ParseResult result;
    ResultPlan result_plan;
    FinalExecPlan* final_exec_plan;
    
    /*BEGIN: add by tangchao 20131225 */
    ObBasicStmt::StmtType query_type;
    /*END: add by tangchao 20131225 */
    
    //internal functions
    int generate_select_plan_single_table(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int generate_select_plan_multi_table(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int gen_exec_plan_update(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int gen_exec_plan_replace(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int gen_exec_plan_delete(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int gen_exec_plan_select(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);
    int gen_exec_plan_insert(
            ResultPlan& result_plan,
            FinalExecPlan* physical_plan,
            ErrStat& err_stat,
            const uint64_t& query_id,
            uint32_t* index);

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
                    multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
                    vector<schema_shard*>  &all_table_shards
    Output      :   
     **************************************************/
    int reparse_where_with_route_for_one_table(
            ResultPlan& result_plan,
            schema_table* table_info,
            vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
            multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
            vector<schema_shard*>  &all_table_shards);

    /**************************************************
    Funtion     :   reparse_where_with_route_for_multi_tables
    Author      :   qinbo
    Date        :   2013.10.29
    Description :   reparse distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    ObSelectStmt *select_stmt,
                    vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
                    multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
                    vector<vector<schema_shard*> > &all_binding_tables_shards
    Output      :   
     **************************************************/
    int reparse_where_with_route_for_multi_tables(
                ResultPlan& result_plan,
                ObSelectStmt *select_stmt,
                vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
                multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
                vector<vector<schema_shard*> > &all_binding_tables_shards);

    /**************************************************
    Funtion     :   reparse_insert_stmt_rows_value
    Author      :   qinbo
    Date        :   2014.1.6
    Description :   reparse insert rows info
    Input       :   ResultPlan& result_plan,
                    ObInsertStmt* insert_stmt,
                    schema_table* table_schema,
                    multimap<uint32_t, uint32_t > &sorted_insert_rows_value,
                    vector<schema_shard*>  &all_table_shards
    Output      :   
     **************************************************/
    int reparse_insert_stmt_rows_value(
                        ResultPlan& result_plan,
                        ObInsertStmt* insert_stmt,
                        schema_table* table_schema,
                        multimap<uint32_t, uint32_t > &sorted_insert_rows_value,
                        vector<schema_shard*>  &all_table_shards,
                        bool &has_auto_incr_sharding_key);

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
                    vector<schema_shard*>  &all_table_shards
    Output      :   
     **************************************************/
    int build_shard_exprs_array_with_route_one_table(
            ResultPlan& result_plan,
            schema_table* table_info,
            vector<ObRawExpr*> partition_sql_exprs,
            vector<ObRawExpr*> atomic_exprs,
            multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
            vector<schema_shard*>  &all_table_shards);

    /**************************************************
    Funtion     :   search_shard_from_one_table_shards
    Author      :   qinbo
    Date        :   2013.12.24
    Description :   search one shard from one table's shards and return 
                    index
    Input       :   vector<schema_shard*> &table_all_shards
                    schema_shard* goal_shard
    Output      :   index
     **************************************************/
    int search_shard_from_one_table_shards( vector<schema_shard*> &table_all_shards,
                                            schema_shard* goal_shard);

    /**************************************************
    Funtion     :   build_shard_exprs_array_with_route_multi_table
    Author      :   qinbo
    Date        :   2013.10.17
    Description :   generate distributed where conditions items
    Input       :   ResultPlan& result_plan,
                    ObSelectStmt *select_stmt,
                    vector<ObRawExpr*> partition_sql_exprs,
                    vector<ObRawExpr*> atomic_exprs,
                    multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs
                    vector<vector<schema_shard*> > &all_binding_tables_shards
    Output      :   
     **************************************************/
    int build_shard_exprs_array_with_route_multi_table(
            ResultPlan& result_plan,
            vector<ObRawExpr*> partition_sql_exprs,
            vector<ObRawExpr*> atomic_exprs,
            multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs,
            vector<vector<schema_shard*> > &all_binding_tables_shards);


    /**************************************************
    Funtion     :   search_partition_sql_exprs
    Author      :   qinbo
    Date        :   2013.10.18
    Description :   find all expr that need to be partitioned
    Input       :   ResultPlan& result_plan, 
                    vector<ObRawExpr*>  atomic_exprs,
                    vector<ObRawExpr*>  &partition_sql_exprs
    Output      :   
     **************************************************/
    int search_partition_sql_exprs( ResultPlan& result_plan,
                                    vector<ObRawExpr*> &atomic_exprs,
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
                    vector<FromItem> &from_items,
                    vector<vector<schema_shard*> > &all_tables_shards
    Output      :   
     **************************************************/
    void generate_all_table_shards( ResultPlan& result_plan,
                                    vector<FromItem> &from_items,
                                    vector<vector<schema_shard*> > &all_tables_shards);

    
    /**************************************************
    Funtion     :   search_shard_from_multi_tables_shards
    Author      :   qinbo
    Date        :   2013.12.24
    Description :   search one shard from all_binding_tables_shards and return 
                    all_binding_tables_shards index
    Input       :   vector<vector<schema_shard*> > &all_binding_tables_shards,
                    schema_shard* goal_shard
    Output      :   index
     **************************************************/
    int search_shard_from_multi_tables_shards(vector<vector<schema_shard*> > &all_binding_tables_shards,
                                       schema_shard* goal_shard);
    
    
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

    /**************************************************
    Funtion     :   send_sql_to_config_server
    Author      :   qinbo
    Date        :   2013.12.11
    Description :   send sql(show/set command) to config server
    Input       :   ResultPlan& result_plan,
                    FinalExecPlan* physical_plan,
                    string sql
    Output      :   
    return      :   
     **************************************************/
    int send_sql_to_config_server( 
                            ResultPlan& result_plan,
                            FinalExecPlan* physical_plan,
                            string sql);
    /**************************************************
    Funtion     :   is_from_tables_binding
    Author      :   qinbo
    Date        :   2013.12.24
    Description :   whether all from tables are binding(shard with the same COLUMN KEY)
    Input       :   ResultPlan& result_plan,
                    vector<FromItem> &from_items
    Output      :   
    return      :   bool
     **************************************************/
    bool is_from_tables_binding(ResultPlan& result_plan,
                                vector<FromItem> &from_items);
    
    
    /**************************************************
    Funtion     :   set_sql_dispatched_info
    Author      :   qinbo
    Date        :   2013.12.24
    Description :   set "select_stmt" "is_sql_dispatched_multi_shards"
    Input       :   ObSelectStmt *select_stmt, 
                    multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs
    Output      :   
    return      :   
     **************************************************/
    void set_sql_dispatched_info(ObSelectStmt *select_stmt, 
                                multimap<uint32_t, vector<ObRawExpr*> > &opted_raw_exprs);
};


#endif /* _JD_EXEC_PLAN_H */

