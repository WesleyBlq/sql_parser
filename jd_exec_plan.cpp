
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
#include "jd_exec_plan.h"

extern meta_reader *g_metareader;

using namespace oceanbase::common;
using namespace oceanbase::sql;


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
    stmt = dynamic_cast<T*>(logical_plan->get_main_stmt());
  else
    stmt = dynamic_cast<T*>(logical_plan->get_query(query_id));
  if (stmt == NULL)
  {
    err_stat.err_code_ = OB_ERR_PARSER_SYNTAX;
  }
  return ret;
}


QueryActuator::QueryActuator()
{

}

QueryActuator::~QueryActuator()
{


}

FinalExecPlan* QueryActuator::popActuator()
{


}

void QueryActuator::pushActuator(FinalExecPlan* exec_plan)
{



}


bool QueryActuator::is_all_plan_done()
{



}


void QueryActuator::set_all_plan_done()
{



}


void QueryActuator::set_next_plan_reparsed()
{



}


bool QueryActuator::get_next_plan_reparsed()
{


}

void QueryActuator::reparse_next_plan()
{


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
    ResultPlan& result_plan,
    FinalExecPlan*& final_exec_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    
    int& ret = err_stat.err_code_ = OB_SUCCESS;
    bool new_generated = false;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);

    
    if (logical_plan)
    {
      if (OB_LIKELY(NULL == final_exec_plan))
      {
        if ((final_exec_plan = (FinalExecPlan*)parse_malloc(sizeof(FinalExecPlan), NULL)) == NULL)
        {
          ret = OB_ERR_PARSER_MALLOC_FAILED;
          TBSYS_LOG(DEBUG, "Can not malloc space for FinalExecPlan");
        }
        else
        {
          final_exec_plan = new(final_exec_plan) FinalExecPlan();
          TBSYS_LOG(DEBUG, "new physical plan, addr=%p", final_exec_plan);
          new_generated = true;
        }
      }
      
      ObBasicStmt *stmt = NULL;
      if (ret == OB_SUCCESS)
      {
        if (query_id == OB_INVALID_ID)
          stmt = logical_plan->get_main_stmt();
        else
          stmt = logical_plan->get_query(query_id);
        if (stmt == NULL)
        {
          ret = OB_ERR_ILLEGAL_ID;
          TBSYS_LOG(DEBUG, "Wrong query id to find query statement");
        }
      }
      TBSYS_LOG(DEBUG, "generate physical plan for query_id=%lu stmt_type=%d",
                query_id, stmt->get_stmt_type());
      if (OB_LIKELY(ret == OB_SUCCESS))
      {
        switch (stmt->get_stmt_type())
        {
          case ObBasicStmt::T_SELECT:
            ret = gen_exec_plan_select(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_DELETE:
            ret = gen_exec_plan_delete(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_INSERT:
            ret = gen_exec_plan_insert(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_REPLACE:
            ret = gen_exec_plan_replace(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_UPDATE:
            ret = gen_exec_plan_update(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          default:
            ret = OB_NOT_SUPPORTED;
            TBSYS_LOG(DEBUG, "Unknown logical plan, stmt_type=%d", stmt->get_stmt_type());
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
**************************************************/
int QueryActuator::gen_exec_plan_select(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }

    if (select_stmt->is_from_item_with_join())
    {
        ret = OB_ERR_GEN_PLAN;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not support stmt with JOIN now");
        return ret;
    }
    else
    {
        /*related to 1 table*/
        if (select_stmt->get_from_item_size() == 1)
        {
            generate_select_plan_single_table(result_plan, physical_plan, err_stat, query_id, index);
        }
        /*related to >1 tables*/
        else
        {
            generate_select_plan_multi_table(result_plan, physical_plan, err_stat, query_id, index);
        }
    }


    
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
**************************************************/
int QueryActuator::generate_select_plan_single_table(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);
    vector<string>      table_names;
    string              table_name;
    
    
    vector<SelectItem>  select_items;
    SelectItem          select_item;

    vector<string>      where_items;
    string              where_item;
    string              db_name;
    
    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }


    table_names = select_stmt->fetch_tables_from_tree(result_plan);
    if (table_names.size() > 1)
    {
        ret = JD_ERR_LOGICAL_TREE_WRONG;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Select stmt size is not right");
        return ret;
    }
    
    table_name = table_names.at(0);
    select_items = select_stmt->fetch_select_from_tree(result_plan, table_name);
    where_items = select_stmt->fetch_where_from_tree(result_plan, table_name);
        
    db_name.assign(result_plan.db_name);

    cout << "db name get " << db_name << endl;
    
    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    schema_table* table_schema = db_schema->get_table_from_db(table_name);


    int get_replicas_num();
    vector<string> get_relation_table();
    void set_sharding_key(map<string, int> sharding_key);
    map<string, int> get_sharding_key();
    string get_partition_by();
    string get_primary_key();

    /*this table is not distributed table*/
    if (table_schema->get_is_distributed_table())
    {

    }
    /*this table is distributed table*/
    else
    {
        
    }
    
#if 0

    if ( ! a_table_info->is_distributed) {
        tablet_t *tablet = a_table_info->single_tablet;

        sql_decomposer_elem_t *elem = (sql_decomposer_elem_t *)calloc(1,
                sizeof(sql_decomposer_elem_t));
        if (elem == NULL) {
            log_error(logger, "calloc() for elem failed!");

            return -1;
        }

        elem->a_cluster = (cluster *)g_hash_table_lookup(sd->nsc->clusters,
                tablet->master_tablet_server);
        if (elem->a_cluster == NULL) {
            log_error(logger, "Can't find cluster instance by cluster name: %s",
                    tablet->master_tablet_server);

            goto free_elem;
        }

        if (clone_tablets(a_table_info->tablet_array, &elem->tablets) < 0) {
            log_error(logger, "clone_tablets() failed!");

            goto free_elem;
        }

        if (tablet->alias != NULL && strlen(tablet->alias) > 0) {
            table_factor->table_name = tablet->alias;
        }
        int generated_sql_size = original_sql_size * SQL_DECOMPOSE_EXTEND_ROTIO;
        elem->sql = (char *)calloc(1, generated_sql_size);
        if (elem->sql == NULL) {
            log_error(logger, "calloc() for elem->sql failed!");

            goto free_elem;
        }
        if (sql_cmd_select->to_string(elem->sql, generated_sql_size,
                    (sql_command_t *)sql_cmd_select) == 0) {
            log_error(logger, "to_string() failed!");

            goto free_elem;
        }

        g_ptr_array_add(result, elem);
        return 0;
    } else {
        sql_item_t *where_condition = from->where_condition;
        sql_item_linked_t *group_by_item = from->group_by_list;
        sql_item_t *having_item = from->having;
        sql_item_linked_t *order_by_item = from->order_by_list;
        sql_item_limit_t *limit_item = from->limit;
        if (from->where_condition == NULL) {
            GPtrArray *tablets = a_table_info->tablet_array;
            guint i = 0;
            for (; i < tablets->len; i++) {
                tablet_t *tablet = ((tablet_t *)tablets->pdata[i]);

                if (tablet->is_truncated) {
                    log_debug(logger, "Has truncated!");

                    continue;
                }
                if ( ! tablet->is_open || ! tablet->allow_to_read) {
                    log_error(logger, "Not allowed to read!");

                    return -1;
                }

                sql_decomposer_elem_t *elem = (sql_decomposer_elem_t *)calloc(1,
                        sizeof(sql_decomposer_elem_t));
                if (elem == NULL) {
                    log_error(logger, "calloc() for elem failed!");

                    return -1;
                }

                elem->a_cluster = (cluster *)g_hash_table_lookup(sd->nsc->clusters,
                        tablet->master_tablet_server);
                if (elem->a_cluster == NULL) {
                    log_error(logger, "Can't find cluster instance by cluster name: %s",
                            tablet->master_tablet_server);

                    goto free_elem_2;
                }

                elem->tablets = g_ptr_array_new();
                if (tablets == NULL) {
                    log_error(logger, "g_ptr_array_new() for elem->tablets failed!");

                    goto free_elem_2;
                }
                g_ptr_array_add(elem->tablets, tablet);

                if (tablet->alias != NULL && strlen(tablet->alias) > 0) {
                    table_factor->table_name = tablet->alias;
                } else {
                    table_factor->table_name = table_name;
                }
                int generated_sql_size = original_sql_size * SQL_DECOMPOSE_EXTEND_ROTIO;
                elem->sql = (char *)calloc(1, generated_sql_size);
                if (elem->sql == NULL) {
                    log_error(logger, "calloc() for elem->sql failed!");

                    goto free_elem_2;
                }
                if (sql_cmd_select->to_string(elem->sql, generated_sql_size,
                            (sql_command_t *)sql_cmd_select) == 0) {
                    log_error(logger, "to_string() failed!");

                    goto free_elem_2;
                }

                g_ptr_array_add(result, elem);

                continue;

free_elem_2:
                sql_decomposer_elem_destroy(elem);

                return -1;
            }

            if (result->len == 0) {
                log_error(logger, "Not found any tablet!");

                return -1;
            }

            return 0;
        } else {
            if (from->where_condition->item_type != ITEM_EXPR) {
                log_error(logger, "where condition is not sql_expr_t, not support now!");
                return -1;
            }  

            GPtrArray *atomic_exprs_array = create_atomic_exprs_array(
                    (sql_expr_t *)from->where_condition);
            if (atomic_exprs_array == NULL) {
                log_error(logger, "create_atomic_exprs_array() failed!");

                return -1;
            }

            // Container type: <tablet_t *, GPtrArray *>
            GHashTable *tablet_exprs_array_mappings = g_hash_table_new_full(
                    g_direct_hash, g_direct_equal, NULL, g_destroy_notify_for_hash_value);
            if (tablet_exprs_array_mappings == NULL) {
                log_error(logger, "g_hash_table_new() for tablet_exprs_array_mappings failed!");

                goto free_exprs_array;
            }
            if (build_tablet_exprs_array_mappings(sd, a_table_info, atomic_exprs_array,
                    tablet_exprs_array_mappings) < 0) {
                log_error(logger, "build_tablet_exprs_array_mappings() failed!");

                goto free_mappings;
            }

            from->where_condition = NULL;
            from->group_by_list = NULL;
            from->having = NULL;
            from->order_by_list = NULL;
            from->limit = NULL;

            GHashTableIter iter;
            gpointer key;
            gpointer value;
            g_hash_table_iter_init(&iter, tablet_exprs_array_mappings);
            while (g_hash_table_iter_next(&iter, &key, &value)) {
                tablet_t *tablet = (tablet_t *)key;

                if (tablet->is_truncated) {
                    log_debug(logger, "Has truncated!");

                    continue;
                }
                if ( ! tablet->is_open || ! tablet->allow_to_read) {
                    log_error(logger, "Not allowed to read!");

                    goto free_mappings;
                }

                GPtrArray *atomic_exprs_array = (GPtrArray *)value;

                sql_decomposer_elem_t *elem = (sql_decomposer_elem_t *)calloc(1,
                        sizeof(sql_decomposer_elem_t));
                if (elem == NULL) {
                    log_error(logger, "calloc() for elem failed!");

                    goto free_mappings;
                }

                elem->a_cluster = (cluster *)g_hash_table_lookup(sd->nsc->clusters,
                        tablet->master_tablet_server);
                if (elem->a_cluster == NULL) {
                    log_error(logger, "Can't find cluster instance by cluster name: %s",
                            tablet->master_tablet_server);

                    goto free_elem_3;
                }

                elem->tablets = g_ptr_array_new();
                if (elem->tablets == NULL) {
                    log_error(logger, "g_ptr_array_new() for elem->tablets failed!");

                    goto free_elem_3;
                }
                g_ptr_array_add(elem->tablets, tablet);

                if (tablet->alias != NULL && strlen(tablet->alias) > 0) {
                    table_factor->table_name = tablet->alias;
                } else {
                    table_factor->table_name = table_name;
                }
                int size = original_sql_size * 2;
                elem->sql = (char *)calloc(1, size);
                if (elem->sql == NULL) {
                    log_error(logger, "calloc() for elem->sql failed!");

                    goto free_elem_3;
                }
                if (sql_cmd_select->to_string(elem->sql, size, (sql_command_t *)sql_cmd_select)
                        == 0) {
                    log_error(logger, "to_string() failed!");

                    goto free_elem_3;
                }
                elem->sql[strlen(elem->sql)-1] = '\0';
                if (append_where_clause(elem->sql, size, atomic_exprs_array) < 0) {
                    log_error(logger, "append_where_clause() failed!");

                    goto free_elem_3;
                }
                if (append_group_by_clause(elem->sql, size, group_by_item) < 0) {
                    log_error(logger, "append_group_by_clause() failed!");

                    goto free_elem_3;
                }
                if (append_having_clause(elem->sql, size, having_item) < 0) {
                    log_error(logger, "append_having_clause() failed!");

                    goto free_elem_3;
                }
                if (append_order_by_clause(elem->sql, size, order_by_item) < 0) {
                    log_error(logger, "append_order_by_clause() failed!");

                    goto free_elem_3;
                }
                if (append_limit_clause(elem->sql, size, limit_item) < 0) {
                    log_error(logger, "append_limit_clause() failed!");

                    goto free_elem_3;
                }

                g_ptr_array_add(result, elem);

                continue;
free_elem_3:
                sql_decomposer_elem_destroy(elem);

                goto free_mappings;
            }

            if (result->len == 0) {
                log_error(logger, "Not found any tablet!");

                goto free_mappings;
            }

            g_hash_table_destroy(tablet_exprs_array_mappings);
            g_ptr_array_set_free_func(atomic_exprs_array, g_destroy_notify_for_array);
            g_ptr_array_free(atomic_exprs_array, TRUE);

            from->where_condition = where_condition;
            from->group_by_list = group_by_item;
            from->having = having_item;
            from->order_by_list = order_by_item;
            from->limit = limit_item;

            return 0;

free_mappings:
            g_hash_table_destroy(tablet_exprs_array_mappings);
free_exprs_array:
            g_ptr_array_set_free_func(atomic_exprs_array, g_destroy_notify_for_array);
            g_ptr_array_free(atomic_exprs_array, TRUE);
            
            from->where_condition = where_condition;
            from->group_by_list = group_by_item;
            from->having = having_item;
            from->order_by_list = order_by_item;
            from->limit = limit_item;

            return -1;
        }
    }
#endif
    return 0;
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
    int32_t* index)
{


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
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObUpdateStmt *update_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, update_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }

    
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
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObInsertStmt *replace_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, replace_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
    
    
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
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObDeleteStmt *delete_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, delete_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
    
    
    
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
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObInsertStmt *insert_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, insert_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
}


