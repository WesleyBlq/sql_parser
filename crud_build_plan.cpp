/**
 * (C) 2010-2012 Alibaba Group Holding Limited.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Version: $Id$
 *
 * dml_build_plan.cpp
 *
 * Authors:
 *   Guibin Du <tianguan.dgb@taobao.com>
 *
 */
#include "crud_build_plan.h"
#include "ob_raw_expr.h"
#include "ob_show_stmt.h"
#include "ob_variable_set_stmt.h"
#include "ob_logical_plan.h"
#include "parse_malloc.h"
#include "dml_build_plan.h"
#include <vector>
#include "ob_define.h"
#include "utility.h"
#include <stdint.h>
#include "ob_obj_type.h"
#include "ob_expr_obj.h"

using namespace oceanbase::common;
using namespace oceanbase::sql;
using namespace std;


template <class T>
T* create_stmt(ResultPlan* result_plan)
{
    T* stmt = NULL;
    void *ptr = NULL;
    if (NULL == (ptr = parse_malloc(sizeof(T), result_plan->name_pool_)))
    {
        jlog(WARNING, "Can not allocate memory for stmt");
    }
    else
    {
        stmt = new(ptr) T();
    }
    return stmt;
}

template <class T>
int prepare_resolve_stmt(ResultPlan* result_plan,
                         uint64_t& query_id,
                         T* &stmt)
{
    OB_ASSERT(result_plan);
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    query_id = OB_INVALID_ID;
    oceanbase::sql::ObLogicalPlan *logical_plan = NULL;
    stmt = NULL;

    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*) parse_malloc(sizeof (ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "out of memory");
            snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG,
                  "Can not malloc ObLogicalPlan");
            return ret;
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    }
  
    if (NULL == (stmt = create_stmt<T>(result_plan)))
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        jlog(WARNING, "Failed to allocate memory");
    }
    else
    {
        query_id = logical_plan->generate_query_id();
        stmt->set_query_id(query_id);
        if (OB_SUCCESS != (ret = logical_plan->add_query(stmt)))
        {
            jlog(WARNING, "Can not add stmt to logical plan");
            stmt->~T();
            stmt = NULL;
        }
    }
    return ret;
}


int resolve_variable_set_stmt(
    ResultPlan* result_plan,
    ParseNode* node,
    uint64_t& query_id)
{
    OB_ASSERT(result_plan);
    OB_ASSERT(node && node->type_ == T_VARIABLE_SET);
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    ObVariableSetStmt *stmt = NULL;
    if (OB_SUCCESS != (ret = prepare_resolve_stmt(result_plan, query_id, stmt)))
    {
    }
    else
    {
        ParseNode* set_node = NULL;
        ObVariableSetStmt::VariableSetNode var_node;
        for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
        {
          set_node = node->children_[i];
          OB_ASSERT(set_node->type_ == T_VAR_VAL);
          switch (set_node->value_)
          {
            case 1:
                var_node.scope_type_ = ObVariableSetStmt::GLOBAL;
                break;
            case 2:
                var_node.scope_type_ = ObVariableSetStmt::SESSION;
                break;
            case 3:
                var_node.scope_type_ = ObVariableSetStmt::LOCAL;
                break;
            default:
                var_node.scope_type_ = ObVariableSetStmt::NONE_SCOPE;
                break;
          }

          ParseNode* var = set_node->children_[0];
          OB_ASSERT(var);
          var_node.is_system_variable_ = (var->type_ == T_SYSTEM_VARIABLE) ? true : false;
          if ((ret = ob_write_string(make_string(var->str_value_),
                                      var_node.variable_name_)) != OB_SUCCESS)
          {
            jlog(WARNING, "Can not malloc space for variable name");
            break;
          }

          OB_ASSERT(node->children_[1]);
          if ((ret = resolve_independ_expr(result_plan, NULL, set_node->children_[1], var_node.value_expr_id_,
                                            T_VARIABLE_VALUE_LIMIT)) != OB_SUCCESS)
          {
            jlog(WARNING, "Resolve set value error");
            break;
          }

          stmt->add_variable_node(var_node);
        }
    }
    return ret;
}


int resolve_show_stmt(
    ResultPlan* result_plan,
    ParseNode* node,
    uint64_t& query_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t  sys_table_id = OB_INVALID_ID;
    ParseNode *show_table_node = NULL;
    ParseNode *condition_node = NULL;
    OB_ASSERT(node && node->type_ >= T_SHOW_TABLES && node->type_ <= T_SHOW_PROCESSLIST);
    query_id = OB_INVALID_ID;

    ObLogicalPlan* logical_plan = NULL;
    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*)parse_malloc(sizeof(ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc ObLogicalPlan");
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*>(result_plan->plan_tree_);
    }

    if (ret == OB_SUCCESS)
    {
        ObShowStmt* show_stmt = (ObShowStmt*)parse_malloc(sizeof(ObShowStmt), NULL);
        if (show_stmt == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc ObShowStmt");
        }
        else
        {
            ParseNode sys_table_name;
            sys_table_name.type_ = T_IDENT;
            switch (node->type_)
            {
                case T_SHOW_TABLES:
                  OB_ASSERT(node->num_child_ == 1);
                  condition_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_TABLES);
                  sys_table_name.str_value_ = OB_TABLES_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_VARIABLES:
                  OB_ASSERT(node->num_child_ == 1);
                  condition_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_VARIABLES);
                  show_stmt->set_global_scope(node->value_ == 1 ? true : false);
                  sys_table_name.str_value_ = OB_VARIABLES_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_COLUMNS:
                  OB_ASSERT(node->num_child_ == 2);
                  show_table_node = node->children_[0];
                  condition_node = node->children_[1];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_COLUMNS);
                  sys_table_name.str_value_ = OB_COLUMNS_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_SCHEMA:
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_SCHEMA);
                  sys_table_name.str_value_ = OB_SCHEMA_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_CREATE_TABLE:
                  OB_ASSERT(node->num_child_ == 1);
                  show_table_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_CREATE_TABLE);
                  sys_table_name.str_value_ = OB_CREATE_TABLE_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_TABLE_STATUS:
                  OB_ASSERT(node->num_child_ == 1);
                  condition_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_TABLE_STATUS);
                  sys_table_name.str_value_ = OB_TABLE_STATUS_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_SERVER_STATUS:
                  OB_ASSERT(node->num_child_ == 1);
                  condition_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_SERVER_STATUS);
                  sys_table_name.str_value_ = OB_SERVER_STATUS_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_WARNINGS:
                  OB_ASSERT(node->num_child_ == 0 || node->num_child_ == 1);
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_WARNINGS);
                  break;
                case T_SHOW_GRANTS:
                  OB_ASSERT(node->num_child_ == 1);
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_GRANTS);
                  break;
                case T_SHOW_PARAMETERS:
                  OB_ASSERT(node->num_child_ == 1);
                  condition_node = node->children_[0];
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_PARAMETERS);
                  sys_table_name.str_value_ = OB_PARAMETERS_SHOW_TABLE_NAME;
                  break;
                case T_SHOW_PROCESSLIST:
                  show_stmt = new(show_stmt) ObShowStmt(ObBasicStmt::T_SHOW_PROCESSLIST);
                  show_stmt->set_full_process(node->value_ == 1? true: false);
                  show_stmt->set_show_table(OB_ALL_SERVER_SESSION_TID);
                  break;
                default:
                  /* won't be here */
                  break;
            }
            
            if (node->type_ >= T_SHOW_TABLES && node->type_ <= T_SHOW_SERVER_STATUS
                && (ret = resolve_table(result_plan, show_stmt, &sys_table_name, sys_table_id)) == OB_SUCCESS)
            {
                show_stmt->set_sys_table(sys_table_id);
                query_id = logical_plan->generate_query_id();
                show_stmt->set_query_id(query_id);
            }
            
            if (ret == OB_SUCCESS && (ret = logical_plan->add_query(show_stmt)) != OB_SUCCESS)
            {
                snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not add ObShowStmt to logical plan");
            }
            if (ret != OB_SUCCESS && show_stmt != NULL)
            {
                show_stmt->~ObShowStmt();
            }
        }

        if (ret == OB_SUCCESS && sys_table_id != OB_INVALID_ID)
        {
            TableItem *table_item = show_stmt->get_table_item_by_id(sys_table_id);
            ret = resolve_table_columns(result_plan, show_stmt, *table_item);
        }

        if (ret == OB_SUCCESS && (node->type_ == T_SHOW_COLUMNS || node->type_ == T_SHOW_CREATE_TABLE))
        {
            OB_ASSERT(show_table_node);

            #if 0
            ObSchemaChecker *schema_checker = static_cast<ObSchemaChecker*>(result_plan->schema_checker_);
            if (schema_checker == NULL)
            {
            ret = OB_ERR_SCHEMA_UNSET;
            snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG, "Schema(s) are not set");
            }
            int32_t len = static_cast<int32_t>(strlen(show_table_node->str_value_));
            ObString table_name(len, len, show_table_node->str_value_);
            uint64_t show_table_id = schema_checker->get_table_id(table_name);
            if (show_table_id == OB_INVALID_ID)
            {
            ret = OB_ERR_TABLE_UNKNOWN;
            snprintf(result_plan->err_stat_.err_msg_, MAX_ERROR_MSG,
                "Unknown table \"%s\"", show_table_node->str_value_);
            }
            else
            {
            show_stmt->set_show_table(show_table_id);
            }
            #endif
        }

    if (ret == OB_SUCCESS && condition_node
      && (node->type_ == T_SHOW_TABLES || node->type_ == T_SHOW_VARIABLES || node->type_ == T_SHOW_COLUMNS
      || node->type_ == T_SHOW_TABLE_STATUS || node->type_ == T_SHOW_SERVER_STATUS
      || node->type_ == T_SHOW_PARAMETERS))
    {
      if (condition_node->type_ == T_OP_LIKE && condition_node->num_child_ == 1)
      {
        OB_ASSERT(condition_node->children_[0]->type_ == T_STRING);
        string  like_pattern;
        like_pattern.assign( (char*)(condition_node->children_[0]->str_value_),
                static_cast<int32_t>(strlen(condition_node->children_[0]->str_value_))
            );
        show_stmt->set_like_pattern(like_pattern);
      }
      else
      {
        ret = resolve_and_exprs(
                  result_plan,
                  show_stmt,
                  condition_node->children_[0],
                  show_stmt->get_where_exprs(),
                  T_WHERE_LIMIT
                  );
      }
    }

    if (ret == OB_SUCCESS && node->type_ == T_SHOW_WARNINGS)
    {
      show_stmt->set_count_warnings(node->value_ == 1 ? true : false);
      if (node->num_child_ == 1 && node->children_[0] != NULL)
      {
        ParseNode *limit = node->children_[0];
        OB_ASSERT(limit->num_child_ == 2);
        int64_t offset = limit->children_[0] == NULL ? 0 : limit->children_[0]->value_;
        int64_t count = limit->children_[1] == NULL ? -1 : limit->children_[1]->value_;
        show_stmt->set_warnings_limit(offset, count);
      }
    }

    if (ret == OB_SUCCESS && node->type_ == T_SHOW_GRANTS)
    {
      if (node->children_[0] != NULL)
      {
        string name;
        if ((ret = ob_write_string(make_string(node->children_[0]->str_value_), name)) != OB_SUCCESS)
        {
            //PARSER_LOG("Can not malloc space for user name");
        }
        else
        {
            show_stmt->set_user_name(name);
        }
      }
    }
  }
  return ret;
}

