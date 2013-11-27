/************************************************************
  Copyright (C), 2013-2015
  FileName:     jd_exec_plan.cpp
  Author:       qinbo      
  Version :          
  Date:         
  Description:  exec plan generator
  History: 
      <author>  <time>   <version >     <desc>
      qinbo    2013/9/15     1.0       build this moudle  
***********************************************************/

#include <algorithm>
#include "jd_exec_plan.h"

extern meta_reader *g_metareader;

using namespace oceanbase::common;
using namespace oceanbase::sql;

/**************************************************
Funtion     :   set_exec_unit_sql
Author      :   qinbo
Date        :   2013.10.18
Description :   set exec plan unit sql 
Input       :   string sql_
Output      :   
 **************************************************/
void ExecPlanUnit::set_exec_unit_sql(string sql_)
{
    sql.assign(sql_);
}

/**************************************************
Funtion     :   set_exec_unit_sql
Author      :   qinbo
Date        :   2013.10.18
Description :   set exec plan unit shard info 
Input       :   schema_shard* shard_info_
Output      :   
 **************************************************/
void ExecPlanUnit::set_exec_uint_shard_info(schema_shard* shard_info_)
{
    shard_info = shard_info_;
}

string ExecPlanUnit::get_exec_unit_sql()
{
    return sql;
}


schema_shard* ExecPlanUnit::get_exec_unit_shard_info()
{
    return shard_info;

}

/**************************************************
Funtion     :   SameLevelExecPlan
Author      :   qinbo
Date        :   2013.11.1
Description :   
Input       :   
Output      :   
 **************************************************/
SameLevelExecPlan::SameLevelExecPlan()
{

}

/**************************************************
Funtion     :   ~SameLevelExecPlan
Author      :   qinbo
Date        :   2013.11.1
Description :   
Input       :   
Output      :   
 **************************************************/
SameLevelExecPlan::~SameLevelExecPlan()
{
    for(uint32_t i = 0; i < exec_plan_units.size(); i++)
    {
        parse_free(exec_plan_units.at(i));
    }
    exec_plan_units.clear();
}

bool SameLevelExecPlan::get_parent_sql_type()
{
    return false;
}

void SameLevelExecPlan::set_parent_sql_type(uint8_t parent_sql_type)
{

}

void SameLevelExecPlan::set_first_plan_true()
{

}

void SameLevelExecPlan::is_first_plan()
{

}

void SameLevelExecPlan::add_exec_plan_unit(ExecPlanUnit* exec_plan_unit)
{
    exec_plan_units.push_back(exec_plan_unit);

}

/**************************************************
Funtion     :   get_all_same_level_exec_plans
Author      :   qinbo
Date        :   2013.11.
Description :   get all same level exec plans
Input       :   
Output      :   
return      :
 **************************************************/
vector<ExecPlanUnit*> SameLevelExecPlan::get_all_exec_plan_units()
{
    return exec_plan_units;
}

/**************************************************
Funtion     :   FinalExecPlan
Author      :   qinbo
Date        :   2013.11.1
Description :   
Input       :   
Output      :   
return      :
 **************************************************/
FinalExecPlan::FinalExecPlan()
{
    set_union_is_distinct(false);
}

/**************************************************
Funtion     :   ~FinalExecPlan
Author      :   qinbo
Date        :   2013.11.1
Description :   
Input       :   
Output      :   
return      :
 **************************************************/
FinalExecPlan::~FinalExecPlan()
{
    for(uint32_t i = 0; i < same_level_exec_plans.size(); i++)
    {
        same_level_exec_plans[i]->~SameLevelExecPlan();
        parse_free(same_level_exec_plans.at(i));
    }
    same_level_exec_plans.clear();
}

/**************************************************
Funtion     :   set_union_is_distinct
Author      :   qinbo
Date        :   2013.11.7
Description :   set union is distinct
Input       :   
Output      :   
return      :
 **************************************************/
void FinalExecPlan::set_union_is_distinct(bool union_is_distinct_)
{
    union_is_distinct = union_is_distinct_;
}


/**************************************************
Funtion     :   get_union_is_distinct
Author      :   qinbo
Date        :   2013.11.7
Description :   check whether union is distinct
Input       :   
Output      :   
return      :
 **************************************************/
bool FinalExecPlan::get_union_is_distinct()
{
    return union_is_distinct;
}



/**************************************************
Funtion     :   add_same_level_exec_plan
Author      :   qinbo
Date        :   2013.11.7
Description :   add same_level_exec_plan into fanal_exec_plan
Input       :   
Output      :   
return      :
 **************************************************/
void FinalExecPlan::add_same_level_exec_plan(SameLevelExecPlan* same_level_exec_plan)
{
    same_level_exec_plans.push_back(same_level_exec_plan);
}


/**************************************************
Funtion     :   get_all_same_level_exec_plans
Author      :   qinbo
Date        :   2013.11.
Description :   get all same level exec plans
Input       :   
Output      :   
return      :
 **************************************************/
vector<SameLevelExecPlan*> FinalExecPlan::get_all_same_level_exec_plans()
{
    return same_level_exec_plans;
}

template <class T>
int QueryActuator::get_stmt(
        ObLogicalPlan *logical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        T *& stmt)
{
    int& ret = err_stat.err_code_ = OB_SUCCESS;
    /* get statement */
    if (query_id == OB_INVALID_ID)
        stmt = dynamic_cast<T*> (logical_plan->get_main_stmt());
    else
        stmt = dynamic_cast<T*> (logical_plan->get_query(query_id));
    if (stmt == NULL)
    {
        err_stat.err_code_ = OB_ERR_PARSER_SYNTAX;
    }
    return ret;
}

QueryActuator::QueryActuator(string current_db_name)
{
    init_exec_plan(current_db_name);
}

QueryActuator::~QueryActuator()
{
    release_exec_plan();
}

FinalExecPlan* QueryActuator::popActuator()
{
    return NULL;;

}

void QueryActuator::pushActuator(FinalExecPlan* exec_plan)
{



}

bool QueryActuator::is_all_plan_done()
{

    return false;;

}

void QueryActuator::set_all_plan_done()
{



}

void QueryActuator::set_next_plan_reparsed()
{



}

bool QueryActuator::get_next_plan_reparsed()
{
    return false;;
}

void QueryActuator::reparse_next_plan()
{


}

/**************************************************
Funtion     :   init_exec_plan
Author      :   qinbo
Date        :   2013.10.28
Description :   generate exec plan
Input       :   string current_db_name
Output      :   
 **************************************************/
int QueryActuator::init_exec_plan(string current_db_name)
{
#if 0
    g_metareader->add_DB_schema("qinbo");
    g_metareader->add_table_schema("qinbo", "persons", 100);
    g_metareader->add_column_schema("qinbo", "persons", "lastname", 1111, T_STRING, 0);
    g_metareader->add_column_schema("qinbo", "persons", "address", 1112, T_STRING, 0);
    g_metareader->add_column_schema("qinbo", "persons", "id", 1113, T_INT, 0);

    g_metareader->add_table_schema("qinbo", "order_list", 101);
    g_metareader->add_column_schema("qinbo", "order_list", "id", 1211, T_INT, 0);
    g_metareader->add_column_schema("qinbo", "order_list", "item_id", 1212, T_INT, 0);
    g_metareader->add_column_schema("qinbo", "order_list", "order_desc", 1213, T_STRING, 0);

    schema_table* schema_table = g_metareader->get_table_schema("qinbo", "persons");
    if (schema_table)
    {
        cout << "get_table_id:" << schema_table->get_table_id() << endl;
    }

    schema_shard *shard_info1 = new schema_shard("person1");
    schema_shard *shard_info2 = new schema_shard("person2");
    schema_table->add_shard_to_table(shard_info1);
    schema_table->add_shard_to_table(shard_info2);
    schema_table->set_is_distributed_table(true);


    schema_column* schema_column = g_metareader->get_column_schema("qinbo", "persons", "id");
    if (schema_column)
    {
        cout << "address: get_column_id:" << schema_column->get_column_id() << endl;
    }

    schema_column->set_sharding_key_status(true);

    schema_column = g_metareader->get_column_schema("qinbo", "persons", "lastname");
    if (schema_column)
    {
        cout << "lastName: get_column_id:" << schema_column->get_column_id() << endl;
    }

    schema_column->set_sharding_key_status(false);
#endif
    result_plan.name_pool_ = NULL;
    result_plan.route_info = (void*) route;
    result_plan.plan_tree_ = NULL;
    result_plan.db_name    = current_db_name;

    return 0;

}

/**************************************************
Funtion     :   release_exec_plan
Author      :   qinbo
Date        :   2013.10.28
Description :   generate exec plan
Input       :   
Output      :   
 **************************************************/
void QueryActuator::release_exec_plan()
{
    if (result_plan.plan_tree_ != NULL)
    {
        //delete (static_cast<logic_plan*>(result_plan->plan_tree_));
        parse_free(result_plan.plan_tree_);

        result_plan.plan_tree_ = NULL;
        result_plan.name_pool_ = NULL;
    }

    if (result.result_tree_)
    {
        destroy_tree(result.result_tree_);
        result.result_tree_ = NULL;
    }

    if (NULL != final_exec_plan)
    {
        final_exec_plan->~FinalExecPlan();
        parse_free(final_exec_plan);
        final_exec_plan = NULL;
    }

    memset(&result, 0, sizeof(ParseResult));
}

/**************************************************
Funtion     :   set_final_exec_plan
Author      :   qinbo
Date        :   2013.11.1
Description :   set QueryActuator exec plans
Input       :   
Output      :   
 **************************************************/
void QueryActuator::set_final_exec_plan(FinalExecPlan* final_exec_plan_)
{
    final_exec_plan = final_exec_plan_;
}


/**************************************************
Funtion     :   get_final_exec_plan
Author      :   qinbo
Date        :   2013.11.1
Description :   set QueryActuator exec plans
Input       :   
Output      :   
 **************************************************/
FinalExecPlan*  QueryActuator::get_final_exec_plan( )
{
    return final_exec_plan;
}


/**************************************************
Funtion     :   generate_exec_plan
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::generate_exec_plan(
        string sql,
        uint32_t* index)
{
    int&        ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    bool        new_generated = false;
    uint64_t    query_id = OB_INVALID_ID;
    string      assemble_sql;
    FinalExecPlan* final_exec_plan = NULL;

    if (parse_init(&result))
    {
        ret = JD_ERR_SQL_PARSER_WRONG;
        cout << "parse_init error!!!" << endl;
        return ret;
    }

    cout << "<<Part 1 : SQL STRING>>" << endl << sql << endl;
    parse_sql(&result, sql.data(), sql.size());

    if (result.result_tree_ == NULL)
    {
        ret = JD_ERR_SQL_PARSER_WRONG;
        cout << "parse_sql error!!!" << endl;
        fprintf(stderr, "%s at %d:%d\n", result.error_msg_, result.line_, result.start_col_);
        destroy_tree(result.result_tree_);
        result.result_tree_ = NULL;
        return ret;
    }
    else
    {
        cout << "<<Part 2 : PARSE TREE>>" << endl;
        print_tree(result.result_tree_, 0);
    }

    if (result.result_tree_ != NULL)
    {
        switch (result.result_tree_->children_[0]->type_)
        {
            case T_SELECT:
            {
                ret = resolve_select_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            case T_DELETE:
            {
                ret = resolve_delete_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            case T_INSERT:
            {
                ret = resolve_insert_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            case T_UPDATE:
            {
                ret = resolve_update_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            case T_SHOW_TABLES:
            case T_SHOW_VARIABLES:
            case T_SHOW_COLUMNS:
            case T_SHOW_SCHEMA:
            case T_SHOW_CREATE_TABLE:
            case T_SHOW_TABLE_STATUS:
            case T_SHOW_SERVER_STATUS:
            case T_SHOW_WARNINGS:
            case T_SHOW_GRANTS:
            case T_SHOW_PARAMETERS:
            case T_SHOW_PROCESSLIST :
            {
                ret = resolve_show_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            
            case T_VARIABLE_SET:
            {
                ret = resolve_variable_set_stmt(&result_plan, result.result_tree_->children_[0], query_id);
                break;
            }
            default:
                break;
        }
    }

    if ((!result_plan.plan_tree_)||(OB_SUCCESS != ret))
    {
        return ret;
    }
    
    fprintf(stderr, "\n=======================================\n");

    ObLogicalPlan* logic_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    fflush(stderr);
    fprintf(stderr, "\n<<Part 2 : LOGICAL PLAN>>\n");
    logic_plan->print();
    logic_plan->make_stmt_string(result_plan);

    if (logic_plan)
    {
        if (OB_LIKELY(NULL == final_exec_plan))
        {
            if ((final_exec_plan = (FinalExecPlan*) parse_malloc(sizeof (FinalExecPlan), NULL)) == NULL)
            {
                ret = OB_ERR_PARSER_MALLOC_FAILED;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Can not malloc space for FinalExecPlan at %s:%d", __FILE__,__LINE__);
            }
            else
            {
                final_exec_plan = new(final_exec_plan) FinalExecPlan();
                jlog(INFO, "new physical plan, addr=%p", final_exec_plan);
                new_generated = true;
            }
        }

        set_final_exec_plan(final_exec_plan);
        
        ObBasicStmt *stmt = NULL;
        if (ret == OB_SUCCESS)
        {
            stmt = logic_plan->get_main_stmt();
            if (stmt == NULL)
            {
                ret = OB_ERR_ILLEGAL_ID;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Wrong query id to find query statement at %s:%d", __FILE__,__LINE__);
            }
        }


        if (OB_LIKELY(ret == OB_SUCCESS))
        {
            switch (stmt->get_stmt_type())
            {
                case ObBasicStmt::T_SELECT:
                    ret = gen_exec_plan_select(result_plan, final_exec_plan, result_plan.err_stat_, query_id, index);
                    break;
                case ObBasicStmt::T_DELETE:
                    ret = gen_exec_plan_delete(result_plan, final_exec_plan, result_plan.err_stat_, query_id, index);
                    break;
                case ObBasicStmt::T_INSERT:
                case ObBasicStmt::T_REPLACE:
                    ret = gen_exec_plan_insert(result_plan, final_exec_plan, result_plan.err_stat_, query_id, index);
                    break;
                case ObBasicStmt::T_UPDATE:
                    ret = gen_exec_plan_update(result_plan, final_exec_plan, result_plan.err_stat_, query_id, index);
                    break;
                default:
                    ret = OB_NOT_SUPPORTED;
                    jlog(INFO, "Unknown logical plan, stmt_type=%d", stmt->get_stmt_type());
                    break;
            }
        }

        if (ret != OB_SUCCESS && new_generated && final_exec_plan != NULL)
        {
            final_exec_plan->~FinalExecPlan();
            parse_free(final_exec_plan);
            final_exec_plan = NULL;
        }
    }
    return ret;
}

/**************************************************
Funtion     :   gen_exec_plan_select
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   

 SELECT
     [ALL | DISTINCT | DISTINCTROW ]
       [HIGH_PRIORITY]
       [STRAIGHT_JOIN]
       [SQL_SMALL_RESULT] [SQL_BIG_RESULT] [SQL_BUFFER_RESULT]
       [SQL_CACHE | SQL_NO_CACHE] [SQL_CALC_FOUND_ROWS]
     select_expr [, select_expr ...]
     [FROM table_references
       [PARTITION partition_list]
     [WHERE where_condition]
     [GROUP BY {col_name | expr | position}
       [ASC | DESC], ... [WITH ROLLUP]]
     [HAVING where_condition]
     [ORDER BY {col_name | expr | position}
       [ASC | DESC], ...]
     [LIMIT {[offset,] row_count | row_count OFFSET offset}]
     [PROCEDURE procedure_name(argument_list)]
     [INTO OUTFILE 'file_name'
         [CHARACTER SET charset_name]
         export_options
       | INTO DUMPFILE 'file_name'
       | INTO var_name [, var_name]]
     [FOR UPDATE | LOCK IN SHARE MODE]]
 **************************************************/
int QueryActuator::gen_exec_plan_select(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    //router *route_info = static_cast<router*> (result_plan.route_info);

    //get statement
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    if (ObSelectStmt::UNION == select_stmt->get_set_op())
    {
        if (select_stmt->is_set_distinct())
        {
            physical_plan->set_union_is_distinct(true);
        }
        
        ret = gen_exec_plan_select(result_plan, physical_plan, err_stat, select_stmt->get_left_query_id(), index);
        if (OB_SUCCESS == ret)
        {
            ret = gen_exec_plan_select(result_plan, physical_plan, err_stat, select_stmt->get_right_query_id(), index);
        }
    }
    else if (ObSelectStmt::NONE == select_stmt->get_set_op())
    {
        if (select_stmt->is_from_item_with_join())
        {
            ret = OB_ERR_GEN_PLAN;
            snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                    "Can not support stmt with JOIN now at %s:%d", __FILE__,__LINE__);
        }
        else
        {
            /*related to 1 table*/
            if (1 == select_stmt->get_from_item_size())
            {
                ret = generate_select_plan_single_table(result_plan, physical_plan, err_stat, query_id, index);
            }
            /*related to >1 tables*/
            else
            {
                ret = generate_select_plan_multi_table(result_plan, physical_plan, err_stat, query_id, index);
            }
        }
    }
    else
    {
        ret = JD_ERR_SQL_NOT_SUPPORT;
        jlog(WARNING, "Now we DO NOT support 'union distinct' query");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Now we DO NOT support 'union distinct' query at %s:%d", __FILE__,__LINE__);
    }

    return ret;
}

/**************************************************
Funtion     :   generate_select_plan_single_table
Author      :   qinbo
Date        :   2013.9.27
Description :   generate select exec plan with single table
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
return      :
 **************************************************/
int QueryActuator::generate_select_plan_single_table(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    int where_ret = WHERE_IS_OR_AND;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    vector<string> table_names;
    string table_name;

    string db_name;
    string sql_exec_plan_unit;
    ObSqlRawExpr* sql_expr = NULL;

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    table_names = select_stmt->fetch_tables_from_tree(result_plan);
    if (table_names.size() > 1)
    {
        ret = JD_ERR_LOGICAL_TREE_WRONG;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "From table size is not right at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    table_name = table_names.at(0);
    db_name.assign(result_plan.db_name);

    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    schema_table* table_schema = db_schema->get_table_from_db(table_name);

    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*) parse_malloc(sizeof (SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for SameLevelExecPlan at %s:%d", __FILE__,__LINE__);
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
        physical_plan->add_same_level_exec_plan(exec_plan);
    }

    /*this table is not distributed table*/
    if (!table_schema->get_is_distributed_table())
    {
        if (1 != table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
        return ret;
    }
    //this table is distributed table
    else
    {
        vector<uint64_t> expr_ids = select_stmt->get_where_exprs();
        /*if there is no where conditions*/
        if (0 == expr_ids.size())
        {
            ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
            return ret;
        }
        else
        {
            /*decompose where conditions into seperate sql which is linked by AND*/
            sql_expr = logical_plan->get_expr_by_id(expr_ids.at(0));
            vector<vector<ObRawExpr*> > atomic_exprs_array;

            where_ret = decompose_where_items(sql_expr->get_expr(), atomic_exprs_array);
            
            if (WHERE_IS_OR_AND == where_ret)
            {
                multimap<schema_shard*, vector<ObRawExpr*> > opted_raw_exprs;
                schema_shard* shard_key = NULL;

                cout << "atomic_exprs_array num: " << atomic_exprs_array.size() << endl;

                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map1;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map_tmp;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map2;
                pair<multimap<schema_shard*, vector<ObRawExpr*> >::iterator, multimap<schema_shard*, vector<ObRawExpr*> >::iterator> raw_exprs_same_shard;

                reparse_where_with_route_for_one_table(result_plan,
                        table_schema,
                        atomic_exprs_array,
                        opted_raw_exprs);
                for (p_map1 = opted_raw_exprs.begin(); p_map1 != opted_raw_exprs.end();)
                {
                    vector<vector<ObRawExpr*> > final_exprs_array;
                    string assembled_sql;
                    shard_key = p_map1->first;
                    raw_exprs_same_shard = opted_raw_exprs.equal_range(p_map1->first);
                    for (p_map2 = raw_exprs_same_shard.first; p_map2 != raw_exprs_same_shard.second; p_map2++)
                    {
                        final_exprs_array.push_back((*p_map2).second);
                    }

                    for (uint32_t i = 0; i < opted_raw_exprs.count(p_map1->first); i++)
                    {
                        p_map1++;
                    }

                    select_stmt->make_select_item_string(result_plan, assembled_sql);
                    select_stmt->make_from_string(result_plan, assembled_sql);
                    append_distributed_where_items(result_plan, assembled_sql, final_exprs_array);
                    select_stmt->make_group_by_string(result_plan, assembled_sql);
                    select_stmt->make_order_by_string(result_plan, assembled_sql);
                    select_stmt->make_having_string(result_plan, assembled_sql);
                    select_stmt->make_limit_string(result_plan, assembled_sql);

                    ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
                    if (exec_plan_unit == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                        return ret;
                    }
                    else
                    {
                        exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                    }

                    exec_plan_unit->set_exec_unit_sql(assembled_sql);
                    cout << "exec_plan_unit shard name: " << shard_key->get_shard_name() << endl;
                    cout << "exec_plan_unit SQL name  : " << assembled_sql << endl;
                    exec_plan_unit->set_exec_uint_shard_info(shard_key);

                    /*add exec_plan_unit*/
                    exec_plan->add_exec_plan_unit(exec_plan_unit);
                }
            }
            else if (WHERE_IS_SUBQUERY == where_ret)
            {
                ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
                return ret;
            }
        }
    }

    return ret;
}

/**************************************************
Funtion     :   reparse_where_with_route_for_one_table
Author      :   qinbo
Date        :   2013.10.17
Description :   reparse distributed where conditions items
Input       :   ResultPlan& result_plan,
                schema_table table_schema,
                vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                vector<vector<ObRawExpr*> > opted_raw_exprs
Output      :   
 **************************************************/
bool QueryActuator::reparse_where_with_route_for_one_table(
        ResultPlan& result_plan,
        schema_table* table_schema,
        vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
        multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs)
{
    bool ret = false;
    vector<schema_shard*> all_table_shards = table_schema->get_all_shards();

    if (un_opt_raw_exprs.size() == 0)
    {
        return ret;
    }

    for (uint32_t i = 0; i < un_opt_raw_exprs.size(); i++)
    {
        vector<ObRawExpr*> atomic_exprs = un_opt_raw_exprs.at(i);
        vector<ObRawExpr*> partition_sql_exprs;

        search_partition_sql_exprs(atomic_exprs, partition_sql_exprs);

        /*if there is no route sql, this sql should be sent to all shards*/
        if (partition_sql_exprs.size() == 0)
        {
            for (uint32_t j = 0; j < all_table_shards.size(); j++)
            {
                opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(all_table_shards.at(j), atomic_exprs));
            }
        }
            /*if there is route sql, this sql should be sent to related shards*/
        else
        {
            ret = build_shard_exprs_array_with_route_one_table(
                    result_plan,
                    table_schema,
                    partition_sql_exprs,
                    atomic_exprs,
                    opted_raw_exprs);
        }
    }
    return ret;

}

/**************************************************
Funtion     :   build_shard_exprs_array_with_route_one_table
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
bool QueryActuator::build_shard_exprs_array_with_route_one_table(
        ResultPlan& result_plan,
        schema_table* table_schema,
        vector<ObRawExpr*> partition_sql_exprs,
        vector<ObRawExpr*> atomic_exprs,
        multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs)
{
    ObRawExpr* raw_expr = NULL;
    vector<vector<schema_shard*> > all_related_shards;
    vector<schema_shard*> shard_tmp1(MAX_SQL_EXEC_PLAN_SHARD_NUM);
    vector<schema_shard*> shard_tmp2;
    uint32_t i = 0;

    for (i = 0; i < partition_sql_exprs.size(); i++)
    {
        raw_expr = partition_sql_exprs.at(i);

        string table_name = table_schema->get_table_name();
        map<string, SqlItemType> sharding_key_tmp = table_schema->get_sharding_key();
        vector<key_data> key_relations;
        vector<schema_shard*> shard_info;

        map<string, SqlItemType>::iterator it = sharding_key_tmp.begin();
        while (it != sharding_key_tmp.end())
        {
            key_data key_relation;
            key_relation.db_name        = result_plan.db_name;
            key_relation.table_name     = table_name;
            key_relation.sharding_key   = it->first;
            key_relation.key_type       = it->second;
            if (raw_expr->convert_ob_expr_to_route(key_relation))
            {
                key_relations.push_back(key_relation);
            }
            it++;
        }
        if (key_relations.size() > 0)
        {
            router *route_info = (router *) result_plan.route_info;
            if (!route_info->get_route_result(key_relations, &shard_info, NULL))
            {
                jlog(WARNING, "route info manage error");
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Route info manage error at %s:%d", __FILE__,__LINE__);
                return false;
            }
        }

        if (shard_info.size() > 0)
        {
            all_related_shards.push_back(shard_info);
        }
    }

    if (all_related_shards.size() == 0)
    {
        jlog(WARNING, "shard info manage error");
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Shard info manage error at %s:%d", __FILE__,__LINE__);
        return false;
    }

    if (all_related_shards.size() == 1)
    {
        shard_tmp1 = all_related_shards.at(0);
        for (i = 0; i < shard_tmp1.size(); i++)
        {
            opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(shard_tmp1.at(i), atomic_exprs));
        }
    }
    //get shards' intersection
    else if (all_related_shards.size() == 2)
    {
        set_intersection(all_related_shards.at(0).begin(), all_related_shards.at(0).end(),
                all_related_shards.at(1).begin(), all_related_shards.at(1).end(), shard_tmp1.begin());
    }
    else
    {
        set_intersection(all_related_shards.at(0).begin(), all_related_shards.at(0).end(),
                all_related_shards.at(1).begin(), all_related_shards.at(1).end(), shard_tmp1.begin());
        for (i = 2; i < all_related_shards.size(); i++)
        {
            vector<schema_shard*> shard_tmp3(MAX_SQL_EXEC_PLAN_SHARD_NUM);
            shard_tmp2 = all_related_shards.at(i);
            set_intersection(shard_tmp1.begin(), shard_tmp1.end(), shard_tmp2.begin(), shard_tmp2.end(), shard_tmp3.begin());
            shard_tmp1.clear();
            shard_tmp1.resize(MAX_SQL_EXEC_PLAN_SHARD_NUM, NULL);
            shard_tmp1 = shard_tmp3;
        }
    }

    for (i = 0; i < shard_tmp1.size(); i++)
    {
        if (NULL != shard_tmp1.at(i))
        {
            opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(shard_tmp1.at(i), atomic_exprs));
        }
    }

    return true;
}

/**************************************************
Funtion     :   generate_select_plan_multi_table
Author      :   qinbo
Date        :   2013.9.27
Description :   generate select exec plan with multi table
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::generate_select_plan_multi_table(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    int where_ret = WHERE_IS_OR_AND;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    vector<string> table_names;
    string table_name;

    string sql_exec_plan_unit;
    vector<schema_shard*> shards_info;
    schema_shard* shard_info = NULL;
    ObSqlRawExpr* sql_expr = NULL;
    vector<vector<schema_shard*> >all_tables_shards;
    uint32_t i = 0;
    uint32_t j = 0;

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt");
        return ret;
    }

    table_names = select_stmt->fetch_tables_from_tree(result_plan);
    if (table_names.size() <= 1)
    {
        ret = JD_ERR_LOGICAL_TREE_WRONG;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "From table size is not right at %s:%d", __FILE__,__LINE__);
        return ret;
    }


    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*) parse_malloc(sizeof (SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for SameLevelExecPlan at %s:%d", __FILE__,__LINE__);
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
        physical_plan->add_same_level_exec_plan(exec_plan);
    }

    vector<uint64_t> expr_ids = select_stmt->get_where_exprs();

    /*if there is no where conditions*/
    if (0 == expr_ids.size())
    {
        generate_all_table_shards(result_plan, table_names, all_tables_shards);
        if (0 == all_tables_shards.size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        for (i = 0; i < all_tables_shards.size(); i++)
        {
            shards_info = all_tables_shards.at(i);
            for (j = 0; j < shards_info.size(); j++)
            {
                string     assembled_sql;
                shard_info = shards_info.at(j);
                ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
                if (exec_plan_unit == NULL)
                {
                    ret = OB_ERR_PARSER_MALLOC_FAILED;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                    return ret;
                }
                else
                {
                    exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                }

                select_stmt->make_stmt_string(result_plan, assembled_sql);

                /*generate sql exec plan*/
                sql_exec_plan_unit.assign(assembled_sql);
                exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);

                cout << "exec_plan_unit SQL name: " << sql_exec_plan_unit << endl;
                exec_plan_unit->set_exec_uint_shard_info(shard_info);

                /*add exec_plan_unit*/
                exec_plan->add_exec_plan_unit(exec_plan_unit);
            }
        }
    }
    else
    {
        //decompose where conditions into seperate sql which is linked by AND
        sql_expr = logical_plan->get_expr_by_id(expr_ids.at(0));

        vector<vector<ObRawExpr*> > atomic_exprs_array;
        where_ret = decompose_where_items(sql_expr->get_expr(), atomic_exprs_array);

        if (WHERE_IS_OR_AND == where_ret)
        {
            multimap<schema_shard*, vector<ObRawExpr*> > opted_raw_exprs;
            schema_shard* shard_key = NULL;

            cout << "multi table atomic_exprs_array num: " << atomic_exprs_array.size() << endl;

            multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map1;
            multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map_tmp;
            multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map2;
            pair<multimap<schema_shard*, vector<ObRawExpr*> >::iterator, multimap<schema_shard*, vector<ObRawExpr*> >::iterator> raw_exprs_same_shard;

            reparse_where_with_route_for_multi_tables(result_plan,
                    select_stmt,
                    atomic_exprs_array,
                    opted_raw_exprs);
            
            for (p_map1 = opted_raw_exprs.begin(); p_map1 != opted_raw_exprs.end();)
            {
                vector<vector<ObRawExpr*> > final_exprs_array;
                string assembled_sql;
                shard_key = p_map1->first;
                raw_exprs_same_shard = opted_raw_exprs.equal_range(p_map1->first);
                for (p_map2 = raw_exprs_same_shard.first; p_map2 != raw_exprs_same_shard.second; p_map2++)
                {
                    final_exprs_array.push_back((*p_map2).second);
                }

                for (i = 0; i < opted_raw_exprs.count(p_map1->first); i++)
                {
                    p_map1++;
                }

                select_stmt->make_select_item_string(result_plan, assembled_sql);
                select_stmt->make_from_string(result_plan, assembled_sql);
                append_distributed_where_items(result_plan, assembled_sql, final_exprs_array);
                select_stmt->make_group_by_string(result_plan, assembled_sql);
                select_stmt->make_order_by_string(result_plan, assembled_sql);
                select_stmt->make_having_string(result_plan, assembled_sql);
                select_stmt->make_limit_string(result_plan, assembled_sql);

                ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
                if (exec_plan_unit == NULL)
                {
                    ret = OB_ERR_PARSER_MALLOC_FAILED;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                    return ret;
                }
                else
                {
                    exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                }

                exec_plan_unit->set_exec_unit_sql(assembled_sql);
                cout << "exec_plan_unit shard name: " << shard_key->get_shard_name() << endl;
                cout << "exec_plan_unit SQL name: " << assembled_sql << endl;
                exec_plan_unit->set_exec_uint_shard_info(shard_key);

                /*add exec_plan_unit*/
                exec_plan->add_exec_plan_unit(exec_plan_unit);
            }
        }
        else if (WHERE_IS_SUBQUERY == where_ret)
        {

        }
    }

    return ret;
}

/**************************************************
Funtion     :   reparse_where_with_route_for_multi_tables
Author      :   qinbo
Date        :   2013.10.29
Description :   reparse distributed where conditions items
Input       :   ResultPlan& result_plan,
                vector<schema_table*> table_schemas,
                vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                vector<vector<ObRawExpr*> > opted_raw_exprs
Output      :   
 **************************************************/
bool QueryActuator::reparse_where_with_route_for_multi_tables(
                        ResultPlan& result_plan,
                        ObSelectStmt *select_stmt,
                        vector<vector<ObRawExpr*> > &un_opt_raw_exprs,
                        multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs)
{
    int             ret = false;
    schema_shard*   shard_info = NULL;
    vector<schema_shard*>   shards_info;
    vector<string>          table_names;
    vector<vector<schema_shard*> >all_tables_shards;
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    
    if (un_opt_raw_exprs.size() == 0)
    {
        return ret;
    }

    for (i = 0; i < un_opt_raw_exprs.size(); i++)
    {
        vector<ObRawExpr*> atomic_exprs = un_opt_raw_exprs.at(i);
        vector<ObRawExpr*> partition_sql_exprs;

        search_partition_sql_exprs(atomic_exprs, partition_sql_exprs);

        //if there is no route sql, this sql should be sent to all shards
        if (partition_sql_exprs.size() == 0)
        {
            table_names = select_stmt->fetch_tables_from_tree(result_plan);
            if (table_names.size() <= 1)
            {
                ret = JD_ERR_LOGICAL_TREE_WRONG;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "From table size is not right at %s:%d", __FILE__,__LINE__);
                return ret;
            }
        
            generate_all_table_shards(result_plan, table_names, all_tables_shards);
            if (0 == all_tables_shards.size())
            {
                ret = JD_ERR_SHARD_NUM_WRONG;
                jlog(WARNING, "shard manage wrong");
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Shard manage wrong at %s:%d", __FILE__,__LINE__);
                return ret;
            }
            
            for (j = 0; j < all_tables_shards.size(); j++)
            {
                shards_info = all_tables_shards.at(j);
                for (k = 0; k < shards_info.size(); k++)
                {
                    shard_info = shards_info.at(k);
                    opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(shard_info, atomic_exprs));
                    
                }
            }
        }
        //if there is route sql, this sql should be sent to related shards
        else
        {
            ret = build_shard_exprs_array_with_route_multi_table(
                    result_plan,
                    partition_sql_exprs,
                    atomic_exprs,
                    opted_raw_exprs);
        }
    }
    
    return ret;
}

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
bool QueryActuator::build_shard_exprs_array_with_route_multi_table(
        ResultPlan& result_plan,
        vector<ObRawExpr*> partition_sql_exprs,
        vector<ObRawExpr*> atomic_exprs,
        multimap<schema_shard*, vector<ObRawExpr*> > &opted_raw_exprs)
{
    ObRawExpr* raw_expr = NULL;
    vector<vector<schema_shard*> > all_related_shards;
    vector<schema_shard*> shard_tmp1;
    vector<schema_shard*> shard_tmp2;
    vector<schema_shard*> shard_tmp3;
    schema_table*   table_schema = NULL;
    uint32_t i = 0;

    for (i = 0; i < partition_sql_exprs.size(); i++)
    {
        raw_expr = partition_sql_exprs.at(i);

        string table_name;
        
        if (!raw_expr->try_get_table_name(table_name))
        {
            continue;
        }
        
        table_schema = g_metareader->get_table_schema(result_plan.db_name, table_name);
        
        map<string, SqlItemType> sharding_key_tmp = table_schema->get_sharding_key();
        vector<key_data> key_relations;
        vector<schema_shard*> shard_info;

        map<string, SqlItemType>::iterator it = sharding_key_tmp.begin();

        while (it != sharding_key_tmp.end())
        {
            key_data key_relation;
            key_relation.db_name        = result_plan.db_name;
            key_relation.table_name     = table_name;
            key_relation.sharding_key   = it->first;
            key_relation.key_type       = it->second;

            if (raw_expr->convert_ob_expr_to_route(key_relation))
            {
                key_relations.push_back(key_relation);
            }

            it++;
        }

        if (key_relations.size() > 0)
        {
            router *route_info = (router *) result_plan.route_info;
            if (!route_info->get_route_result(key_relations, &shard_info, NULL))
            {
                jlog(WARNING, "route info manage error");
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Route info manage error at %s:%d", __FILE__,__LINE__);
                return false;
            }
        }

        if (shard_info.size() > 0)
        {
            all_related_shards.push_back(shard_info);
        }
    }

    if (all_related_shards.size() == 0)
    {
        jlog(WARNING, "shard info manage error");
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Shard info manage error at %s:%d", __FILE__,__LINE__);
        return false;
    }

    if (all_related_shards.size() == 1)
    {
        shard_tmp1 = all_related_shards.at(0);
        for (i = 0; i < shard_tmp1.size(); i++)
        {
            opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(shard_tmp1.at(i), atomic_exprs));
        }
    }
    //get shards' intersection
    else if (all_related_shards.size() == 2)
    {
        set_intersection(all_related_shards.at(0).begin(), all_related_shards.at(0).end(),
                all_related_shards.at(1).begin(), all_related_shards.at(1).end(), shard_tmp1.begin()); //����
    }
    else
    {
        set_intersection(all_related_shards.at(0).begin(), all_related_shards.at(0).end(),
                all_related_shards.at(1).begin(), all_related_shards.at(1).end(), shard_tmp1.begin()); //����
        for (i = 2; i < all_related_shards.size(); i++)
        {
            shard_tmp2 = all_related_shards.at(i);
            set_intersection(shard_tmp1.begin(), shard_tmp1.end(), shard_tmp2.begin(), shard_tmp2.end(), shard_tmp3.begin()); //����
            shard_tmp1 = shard_tmp3;
        }
    }

    for (i = 0; i < shard_tmp1.size(); i++)
    {
        opted_raw_exprs.insert(pair<schema_shard*, vector<ObRawExpr*> >(shard_tmp1.at(i), atomic_exprs));
    }

    return true;
}


/**************************************************
Funtion     :   generate_all_table_shards
Author      :   qinbo
Date        :   2013.10.24
Description :   generate all tables' shards
Input       :   ResultPlan& result_plan,
                vector<string> table_names,
                vector<schema_shard*> &all_tables_shards
Output      :   
 **************************************************/
void QueryActuator::generate_all_table_shards(ResultPlan& result_plan,
                                              vector<string> table_names,
                                              vector<vector<schema_shard*> > &all_tables_shards)
{
    string db_name;
    string table_name;
    uint32_t i = 0;
    uint32_t j = 0;
    db_name.assign(result_plan.db_name);
    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    schema_table* table_schema = NULL;
    vector<vector<schema_shard*> > all_tables_shards_tmp;
    vector<vector<schema_shard*> > all_tables_shards_tmp2;
    vector<schema_shard*> a_tables_shards_tmp;
    uint32_t combination_count = 1;

    for (i = 0; i < table_names.size(); i++)
    {
        table_name = table_names.at(i);
        table_schema = db_schema->get_table_from_db(table_name);
        all_tables_shards_tmp.push_back(table_schema->get_all_shards());
    }

    uint32_t indexes_len = all_tables_shards_tmp.size();
    uint32_t *indexes = new uint32_t[indexes_len];

    //all table's shards ȫ���
    for (i = 0; i < all_tables_shards_tmp.size(); i++)
    {
        combination_count *= all_tables_shards_tmp.at(i).size();
    }

    for (i = 0; i < combination_count; i++)
    {
        vector<schema_shard*> expanded_shards;

        for (j = 0; j < indexes_len; j++)
        {
            vector<schema_shard*> curr_shards = all_tables_shards_tmp.at(j);
            schema_shard *shard = curr_shards.at(indexes[j]);
            expanded_shards.push_back(shard);
        }

        all_tables_shards_tmp2.push_back(expanded_shards);

        uint32_t k = indexes_len - 1;
        for (; k >= 0; k--)
        {
            vector<schema_shard*> curr_shards = all_tables_shards_tmp.at(k);
            if ((indexes[k] + 1) == curr_shards.size())
            {
                indexes[k] = 0;
            }
            else
            {
                ++indexes[k];
                break;
            }
        }
    }
    delete []indexes;

    string server_name;

    //�ж����еķ�Ƭ������ͬһ��server�У�������Ч
    for (i = 0; i < all_tables_shards_tmp2.size(); i++)
    {
        vector<schema_shard*> expanded_shards_seq = all_tables_shards_tmp2.at(i);
        for (j = 0; j < expanded_shards_seq.size(); j++)
        {
            schema_shard* shard_tmp = expanded_shards_seq.at(j);
            if (server_name == "")
            {
                server_name = shard_tmp->get_master_server();
            }
            else if (server_name != shard_tmp->get_master_server())
            {
                break;
            }
            else if (j == expanded_shards_seq.size() - 1)
            {
                all_tables_shards.push_back(expanded_shards_seq);
            }
        }
    }


    return;
}

/**************************************************
Funtion     :   decompose_where_items
Author      :   qinbo
Date        :   2013.9.24
Description :   generate distributed where conditions items
Input       :   ObRawExpr* sql_expr
Output      :   vector<vector<ObRawExpr*> > &atomic_exprs_array
return      :   
 **************************************************/
int QueryActuator::decompose_where_items(ObRawExpr* sql_expr, vector<vector<ObRawExpr*> > &atomic_exprs_array)
{
    uint32_t i = 0;

    if (sql_expr->is_or_expr())
    {
        vector<vector<ObRawExpr*> > left_atomic_exprs_array;

        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (sql_expr));
        ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();

        if (left_sql_item->is_and_expr() || left_sql_item->is_or_expr())
        {
            (void)decompose_where_items(left_sql_item, left_atomic_exprs_array);
        }
        else
        {
            vector<ObRawExpr*> atomic_exprs1;
            atomic_exprs1.push_back(left_sql_item);
            left_atomic_exprs_array.push_back(atomic_exprs1);
        }

        ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
        vector<vector<ObRawExpr*> > right_atomic_exprs_array;

        if (right_sql_item->is_and_expr() || right_sql_item->is_or_expr())
        {
            (void)decompose_where_items(right_sql_item, right_atomic_exprs_array);
        }
        else
        {
            vector<ObRawExpr*> atomic_exprs2;
            atomic_exprs2.push_back(right_sql_item);
            right_atomic_exprs_array.push_back(atomic_exprs2);
        }

        /*add with each other*/
        for (i = 0; i < left_atomic_exprs_array.size(); i++)
        {
            atomic_exprs_array.push_back(left_atomic_exprs_array.at(i));
        }

        for (i = 0; i < right_atomic_exprs_array.size(); i++)
        {
            atomic_exprs_array.push_back(right_atomic_exprs_array.at(i));
        }

        return WHERE_IS_OR_AND;
    }
    else if (sql_expr->is_and_expr())
    {
        vector<vector<ObRawExpr*> > left_atomic_exprs_array;

        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (sql_expr));
        ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();

        if (left_sql_item->is_and_expr() || left_sql_item->is_or_expr())
        {
            (void)decompose_where_items(left_sql_item, left_atomic_exprs_array);
        }
        else
        {
            vector<ObRawExpr*> atomic_exprs1;
            atomic_exprs1.push_back(left_sql_item);
            left_atomic_exprs_array.push_back(atomic_exprs1);
        }

        ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
        vector<vector<ObRawExpr*> > right_atomic_exprs_array;

        if (right_sql_item->is_and_expr() || right_sql_item->is_or_expr())
        {
            (void)decompose_where_items(right_sql_item, right_atomic_exprs_array);
        }
        else
        {
            vector<ObRawExpr*> atomic_exprs2;
            atomic_exprs2.push_back(right_sql_item);
            right_atomic_exprs_array.push_back(atomic_exprs2);
        }

        /*X with each other*/
        for (i = 0; i < left_atomic_exprs_array.size(); i++)
        {
            uint32_t j;
            for (j = 0; j < right_atomic_exprs_array.size(); j++)
            {
                vector<ObRawExpr*> atomic_exprs;

                uint32_t k;
                vector<ObRawExpr*> left_atomic_exprs = left_atomic_exprs_array.at(i);
                for (k = 0; k < left_atomic_exprs.size(); k++)
                {
                    atomic_exprs.push_back(left_atomic_exprs.at(k));
                }
                vector<ObRawExpr*> right_atomic_exprs = right_atomic_exprs_array.at(j);
                for (k = 0; k < right_atomic_exprs.size(); k++)
                {
                    atomic_exprs.push_back(right_atomic_exprs.at(k));
                }

                atomic_exprs_array.push_back(atomic_exprs);
            }
        }

        return WHERE_IS_OR_AND;
    }
    else
    {
        return WHERE_IS_SUBQUERY;
    }
}


/**************************************************
Funtion     :   search_partition_sql_exprs
Author      :   qinbo
Date        :   2013.10.18
Description :   find all expr that need to be partitioned
Input       :   vector<ObRawExpr*>  atomic_exprs,
                vector<ObRawExpr*>  &partition_sql_exprs
Output      :   
 **************************************************/
int QueryActuator::search_partition_sql_exprs(
        vector<ObRawExpr*> atomic_exprs,
        vector<ObRawExpr*> &partition_sql_exprs)
{
    uint32_t i = 0;
    ObRawExpr* raw_expr = NULL;

    for (i = 0; i < atomic_exprs.size(); i++)
    {
        raw_expr = atomic_exprs.at(i);

        if (raw_expr->is_need_to_get_route())
        {
            partition_sql_exprs.push_back(raw_expr);
        }
    }

    return 0;
}

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
void QueryActuator::append_distributed_where_items(ResultPlan& result_plan,
                                                string &sql,
                                                vector<vector<ObRawExpr*> > &atomic_exprs_array)
{
    if (atomic_exprs_array.size() == 0)
    {
        return;
    }

    sql.append(" WHERE ");
    
    for (uint32_t i = 0; i < atomic_exprs_array.size(); i++)
    {
        if (i > 0)
        {
            sql.append(" OR ");
        }
        vector<ObRawExpr*> atomic_exprs = atomic_exprs_array.at(i);
        for (uint32_t j = 0; j < atomic_exprs.size(); j++)
        {
            string assembled_sql_tmp;
            
            if (j > 0)
            {
                sql.append(" AND ");
            }
            atomic_exprs.at(j)->to_string(result_plan, assembled_sql_tmp);
            sql.append(assembled_sql_tmp);
        }
    }

    return;
}

/**************************************************
Funtion     :   gen_exec_plan_update
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::gen_exec_plan_update(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    int where_ret = WHERE_IS_OR_AND;
    ObUpdateStmt *update_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);

    string db_name;
    string table_name;
    string sql_exec_plan_unit;
    vector<schema_shard*> all_related_shards;
    schema_column*  column_info = NULL;
    ObSqlRawExpr*   sql_expr = NULL;
    uint64_t        column_id= 0;
    uint64_t        i = 0;
    
    // get statement
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, update_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    db_name.assign(result_plan.db_name);
    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    table_name.assign(update_stmt->get_table_item_by_id(update_stmt->get_update_table_id())->table_name_);
    schema_table* table_schema = db_schema->get_table_from_db(table_name);

    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*) parse_malloc(sizeof (SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for SameLevelExecPlan at %s:%d", __FILE__,__LINE__);
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
        physical_plan->add_same_level_exec_plan(exec_plan);
    }

    //this table is not distributed table
    if (!table_schema->get_is_distributed_table())
    {
        if (1 != table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
        return ret;
    }
    //this table is distributed table
    else
    {
        if (0 == table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        if (0 == update_stmt->get_update_column_count())
        {
            ret = JD_ERR_SQL_NOT_SUPPORT;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "MUST set column name in UPDATE OPERATION at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        for (i = 0; i < update_stmt->get_update_column_count(); i++)
        {            
            if(OB_INVALID_ARGUMENT != update_stmt->get_update_column_id(i, column_id))
            {
                column_info = table_schema->get_column_from_table_by_id(column_id);
                if (column_info->is_sharding_key())
                {
                    ret = JD_ERR_SQL_NOT_SUPPORT;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "Can not update partition key column at %s:%d", __FILE__,__LINE__);
                    return ret;
                }
            }
        }

        vector<uint64_t> expr_ids = update_stmt->get_where_exprs();
        /*if there is no where conditions*/
        if (0 == expr_ids.size())
        {
            ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
            return ret;
        }
        else
        {
            /*decompose where conditions into seperate sql which is linked by AND*/
            sql_expr = logical_plan->get_expr_by_id(expr_ids.at(0));
            vector<vector<ObRawExpr*> > atomic_exprs_array;
            
            where_ret = decompose_where_items(sql_expr->get_expr(), atomic_exprs_array);

            if (WHERE_IS_OR_AND == where_ret)
            {
                multimap<schema_shard*, vector<ObRawExpr*> > opted_raw_exprs;
                schema_shard* shard_key = NULL;
            
                cout << "atomic_exprs_array num: " << atomic_exprs_array.size() << endl;
            
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map1;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map_tmp;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map2;
                pair<multimap<schema_shard*, vector<ObRawExpr*> >::iterator, multimap<schema_shard*, vector<ObRawExpr*> >::iterator> raw_exprs_same_shard;
            
                reparse_where_with_route_for_one_table(result_plan,
                        table_schema,
                        atomic_exprs_array,
                        opted_raw_exprs);
                for (p_map1 = opted_raw_exprs.begin(); p_map1 != opted_raw_exprs.end();)
                {
                    vector<vector<ObRawExpr*> > final_exprs_array;
                    string assembled_sql;
                    shard_key = p_map1->first;
                    raw_exprs_same_shard = opted_raw_exprs.equal_range(p_map1->first);
                    for (p_map2 = raw_exprs_same_shard.first; p_map2 != raw_exprs_same_shard.second; p_map2++)
                    {
                        final_exprs_array.push_back((*p_map2).second);
                    }
            
                    for (i = 0; i < opted_raw_exprs.count(p_map1->first); i++)
                    {
                        p_map1++;
                    }
                    
                    update_stmt->make_update_table_string(result_plan, assembled_sql);
                    update_stmt->make_update_column_string(result_plan, assembled_sql);
                    append_distributed_where_items(result_plan, assembled_sql, final_exprs_array);
            
                    ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
                    if (exec_plan_unit == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                        return ret;
                    }
                    else
                    {
                        exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                    }
            
                    exec_plan_unit->set_exec_unit_sql(assembled_sql);
                    cout << "exec_plan_unit shard name: " << shard_key->get_shard_name() << endl;
                    cout << "exec_plan_unit SQL name: " << assembled_sql << endl;
                    exec_plan_unit->set_exec_uint_shard_info(shard_key);
            
                    /*add exec_plan_unit*/
                    exec_plan->add_exec_plan_unit(exec_plan_unit);
                }
            }
            else if (WHERE_IS_SUBQUERY == where_ret)
            {
                ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
                return ret;
            }
        }
    }

    return ret;
}

/**************************************************
Funtion     :   gen_exec_plan_replace
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::gen_exec_plan_replace(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    return gen_exec_plan_insert(result_plan, physical_plan, result_plan.err_stat_, query_id, index);
}

/**************************************************
Funtion     :   gen_exec_plan_delete
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::gen_exec_plan_delete(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    int where_ret = WHERE_IS_OR_AND;
    ObDeleteStmt *delete_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    string table_name;

    string db_name;
    string sql_exec_plan_unit;
    ObSqlRawExpr* sql_expr = NULL;
    uint32_t    i = 0;

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, delete_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    db_name.assign(result_plan.db_name);
    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    schema_table* table_schema = db_schema->get_table_from_db_by_id(delete_stmt->get_delete_table_id());

    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*) parse_malloc(sizeof (SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for SameLevelExecPlan at %s:%d", __FILE__,__LINE__);
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
        physical_plan->add_same_level_exec_plan(exec_plan);
    }

    /*this table is not distributed table*/
    if (!table_schema->get_is_distributed_table())
    {
        if (1 != table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
        return ret;
    }
    //this table is distributed table
    else
    {
        vector<uint64_t> expr_ids = delete_stmt->get_where_exprs();
        /*if there is no where conditions*/
        if (0 == expr_ids.size())
        {
            ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
            return ret;
        }
        else
        {
            /*decompose where conditions into seperate sql which is linked by AND*/
            sql_expr = logical_plan->get_expr_by_id(expr_ids.at(0));
            vector<vector<ObRawExpr*> > atomic_exprs_array;
            
            where_ret = decompose_where_items(sql_expr->get_expr(), atomic_exprs_array);

            if (WHERE_IS_OR_AND == where_ret)
            {
                multimap<schema_shard*, vector<ObRawExpr*> > opted_raw_exprs;
                schema_shard* shard_key = NULL;

                cout << "atomic_exprs_array num: " << atomic_exprs_array.size() << endl;

                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map1;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map_tmp;
                multimap<schema_shard*, vector<ObRawExpr*> >::iterator p_map2;
                pair<multimap<schema_shard*, vector<ObRawExpr*> >::iterator, multimap<schema_shard*, vector<ObRawExpr*> >::iterator> raw_exprs_same_shard;

                reparse_where_with_route_for_one_table(result_plan,
                        table_schema,
                        atomic_exprs_array,
                        opted_raw_exprs);
                for (p_map1 = opted_raw_exprs.begin(); p_map1 != opted_raw_exprs.end();)
                {
                    vector<vector<ObRawExpr*> > final_exprs_array;
                    string assembled_sql;
                    shard_key = p_map1->first;
                    raw_exprs_same_shard = opted_raw_exprs.equal_range(p_map1->first);
                    for (p_map2 = raw_exprs_same_shard.first; p_map2 != raw_exprs_same_shard.second; p_map2++)
                    {
                        final_exprs_array.push_back((*p_map2).second);
                    }

                    for (i = 0; i < opted_raw_exprs.count(p_map1->first); i++)
                    {
                        p_map1++;
                    }

                    delete_stmt->make_delete_table_string(result_plan, assembled_sql);
                    append_distributed_where_items(result_plan, assembled_sql, final_exprs_array);

                    ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
                    if (exec_plan_unit == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                        return ret;
                    }
                    else
                    {
                        exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                    }

                    exec_plan_unit->set_exec_unit_sql(assembled_sql);
                    cout << "exec_plan_unit shard name: " << shard_key->get_shard_name() << endl;
                    cout << "exec_plan_unit SQL name: " << assembled_sql << endl;
                    exec_plan_unit->set_exec_uint_shard_info(shard_key);

                    /*add exec_plan_unit*/
                    exec_plan->add_exec_plan_unit(exec_plan_unit);
                }
            }
            else if (WHERE_IS_SUBQUERY == where_ret)
            {
                ret = distribute_sql_to_all_shards( result_plan, query_id, table_schema, exec_plan);
                return ret;
            }
        }
    }

    return ret;

}

/**************************************************
Funtion     :   gen_exec_plan_insert
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
 **************************************************/
int QueryActuator::gen_exec_plan_insert(
        ResultPlan& result_plan,
        FinalExecPlan* physical_plan,
        ErrStat& err_stat,
        const uint64_t& query_id,
        uint32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObInsertStmt *insert_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);

    string table_name;
    string sql_exec_plan_unit;
    vector<schema_shard*> all_related_shards;
    schema_shard*   shard_info = NULL;
    schema_column*  column_info = NULL;
    ObSqlRawExpr*   sql_expr = NULL;
    ObRawExpr*      raw_expr = NULL;
    bool            has_find_shard_column = false;
    uint32_t        i = 0;
    uint32_t        j = 0;
    
    // get statement
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, insert_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        jlog(WARNING, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
                "Can not get stmt at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    schema_db* db_schema = g_metareader->get_DB_schema(result_plan.db_name);
    table_name.assign(insert_stmt->get_table_item_by_id(insert_stmt->get_table_id())->table_name_);
    schema_table* table_schema = db_schema->get_table_from_db(table_name);

    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*) parse_malloc(sizeof (SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for SameLevelExecPlan at %s:%d", __FILE__,__LINE__);
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
        physical_plan->add_same_level_exec_plan(exec_plan);
    }

    //this table is not distributed table
    if (!table_schema->get_is_distributed_table())
    {
        if (1 != table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
        if (exec_plan == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
            return ret;
        }
        else
        {
            exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
        }

        string assembled_sql;
        insert_stmt->make_stmt_string(result_plan, assembled_sql);

        //generate sql exec plan
        sql_exec_plan_unit.assign(assembled_sql);
        exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);

        cout << "exec_plan_unit SQL name: " << sql_exec_plan_unit << endl;

        shard_info = table_schema->get_all_shards().at(0);
        exec_plan_unit->set_exec_uint_shard_info(shard_info);

        //add exec_plan_unit
        exec_plan->add_exec_plan_unit(exec_plan_unit);
    }
    //this table is distributed table
    else
    {
        if (0 == table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            jlog(WARNING, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        if (0 == insert_stmt->get_column_size())
        {
            ret = JD_ERR_SQL_NOT_SUPPORT;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "MUST set column name in INSERT OPERATION at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        for (i = 0; i < insert_stmt->get_column_size(); i++)
        {            
            column_info = table_schema->get_column_from_table(insert_stmt->get_column_item(i)->column_name_);
            if (column_info->is_sharding_key())
            {
                has_find_shard_column = true;
                break;
            }
            
        }

        if ( has_find_shard_column )
        {
            vector<vector<uint64_t> > all_value_rows = insert_stmt->get_all_value_rows();

            for (j = 0; j < all_value_rows.size(); j++)
            {
                vector<uint64_t>& value_row = all_value_rows.at(j);
                {
                    sql_expr = logical_plan->get_expr_by_id(value_row.at(i));
                    
                    if (!sql_expr->get_expr()->is_column_and_sharding_key())
                    {
                        ret = JD_ERR_COLUMN_NOT_MATCH;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "insert value does not match with config info!!! at %s:%d", __FILE__,__LINE__);
                        return ret;
                    }
                    
                    map<string, SqlItemType> sharding_key_tmp = table_schema->get_sharding_key();
                    vector<key_data> key_relations;
                    vector<schema_shard*> shard_info;
                    
                    map<string, SqlItemType>::iterator it = sharding_key_tmp.begin();
                    
                    while (it != sharding_key_tmp.end())
                    {
                        key_data key_relation;
                        key_relation.db_name        = result_plan.db_name;
                        key_relation.table_name     = table_name;
                        key_relation.sharding_key   = it->first;
                        key_relation.key_type       = it->second;
                    
                        if (raw_expr->convert_ob_expr_to_route(key_relation))
                        {
                            key_relations.push_back(key_relation);
                        }
                    
                        it++;
                    }
                    
                    if (key_relations.size() > 0)
                    {
                        router *route_info = (router *) result_plan.route_info;
                        if (!route_info->get_route_result(key_relations, &shard_info, NULL))
                        {
                            jlog(WARNING, "route info manage error");
                            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                    "Route info manage error at %s:%d", __FILE__,__LINE__);
                            return false;
                        }
                    }

                    for (uint32_t tmp = 0; tmp < shard_info.size(); tmp++ )
                    {
                        if(!vector_elem_exist_already(all_related_shards, shard_info.at(tmp)))
                        {
                            all_related_shards.push_back(shard_info.at(tmp));
                        }
                    }
                }
            }
        }
        else
        {
            all_related_shards = table_schema->get_all_shards();
        }

        for (i = 0; i < all_related_shards.size(); i++)
        {
            string assembled_sql;
            shard_info = all_related_shards.at(i);

            ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
            if (exec_plan_unit == NULL)
            {
                ret = OB_ERR_PARSER_MALLOC_FAILED;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
                return ret;
            }
            else
            {
                exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
            }

            insert_stmt->make_stmt_string(result_plan, assembled_sql);

            //generate sql exec plan
            sql_exec_plan_unit.assign(assembled_sql);
            exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);

            cout << "exec_plan_unit SQL name: " << sql_exec_plan_unit << endl;
            exec_plan_unit->set_exec_uint_shard_info(shard_info);

            //add exec_plan_unit
            exec_plan->add_exec_plan_unit(exec_plan_unit);
        }
    }
    
    return ret;
}


/**************************************************
Funtion     :   vector_elem_exist_already
Author      :   qinbo
Date        :   2013.10.30
Description :   vector elem is already existing
Input       :   vector<schema_shard*> vector_shards,
                schema_shard* single_shard
Output      :   
 **************************************************/
bool QueryActuator::vector_elem_exist_already( 
                            vector<schema_shard*> vector_shards,
                            schema_shard* single_shard)
{
    for (uint32_t i =0; i < vector_shards.size(); i++)
    {
        if (single_shard == vector_shards.at(i))
        {
            return true;
        }
    }
    return false;
}


/**************************************************
Funtion     :   distribute_sql_to_all_shards
Author      :   qinbo
Date        :   2013.11.6
Description :   vector elem is already existing
Input       :   ResultPlan& result_plan,
                schema_table* table_schema,
                SameLevelExecPlan* exec_plan
Output      :   
return      :
 **************************************************/
int QueryActuator::distribute_sql_to_all_shards( 
                    ResultPlan& result_plan,
                    const uint64_t& query_id,
                    schema_table* table_schema,
                    SameLevelExecPlan* exec_plan)
{
    uint32_t i   = 0;
    int ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    schema_shard*   shard_info  = NULL;
    ObBasicStmt*    stmt        = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    string  sql_exec_plan_unit;
    
    if (0 == table_schema->get_all_shards().size())
    {
        ret = JD_ERR_SHARD_NUM_WRONG;
        jlog(WARNING, "shard manage wrong");
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Shard manage wrong at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    stmt = logical_plan->get_query(query_id);
    
    for (i = 0; i < table_schema->get_all_shards().size(); i++)
    {
        string     assembled_sql;
        shard_info = table_schema->get_all_shards().at(i);
    
        ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*) parse_malloc(sizeof (ExecPlanUnit), NULL);
        if (exec_plan_unit == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Can not malloc space for ExecPlanUnit at %s:%d", __FILE__,__LINE__);
            return ret;
        }
        else
        {
            exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
        }
    
        stmt->make_stmt_string(result_plan, assembled_sql);
    
        /*generate sql exec plan*/
        sql_exec_plan_unit.assign(assembled_sql);
        exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);
    
        cout << "exec_plan_unit shard name: " << shard_info->get_shard_name() << endl;
        cout << "exec_plan_unit SQL name  : " << sql_exec_plan_unit << endl;
        exec_plan_unit->set_exec_uint_shard_info(shard_info);
    
        /*add exec_plan_unit*/
        exec_plan->add_exec_plan_unit(exec_plan_unit);
    }

    return ret;
}


