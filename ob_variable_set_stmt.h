/**
 * (C) 2010-2012 Alibaba Group Holding Limited.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Version: $Id$
 *
 * ob_variable_set_stmt.h
 *
 * Authors:
 *   Guibin Du <tianguan.dgb@taobao.com>
 *
 */

#ifndef OCEANBASE_SQL_OB_VARIABLE_STMT_H_
#define OCEANBASE_SQL_OB_VARIABLE_STMT_H_

#include "ob_basic_stmt.h"
#include <string>
#include <vector>
 
namespace oceanbase
{
  namespace sql
  {
    class ObVariableSetStmt : public ObBasicStmt
    {
    public:
        enum ScopeType
    	{
    	    NONE_SCOPE = 0,
    	    GLOBAL,
            SESSION,
            LOCAL,
    	};

        struct VariableSetNode
        {
            VariableSetNode()
            {
                is_system_variable_ = false;
                scope_type_ = NONE_SCOPE;
                value_expr_id_ = common::OB_INVALID_ID;
            }
            string variable_name_;
            bool is_system_variable_;
            ScopeType scope_type_;
            uint64_t value_expr_id_;
        };
              
        ObVariableSetStmt();
        virtual ~ObVariableSetStmt();

        int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
        int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, schema_shard *shard_info,string &assembled_sql);
        void add_variable_node(const VariableSetNode& node);
        int64_t get_variables_size() const;
        const VariableSetNode& get_variable_node(int32_t index) const;

        virtual void print(FILE* fp, int32_t level, int32_t index);

    private:
        vector<VariableSetNode> variable_nodes_;
    };

    inline void ObVariableSetStmt::add_variable_node(const VariableSetNode& node)
    {
        variable_nodes_.push_back(node);
    }
    
    inline const ObVariableSetStmt::VariableSetNode& ObVariableSetStmt::get_variable_node(int32_t index) const
    {
        OB_ASSERT(0 <= index && index < variable_nodes_.size());
        return variable_nodes_.at(index);
    }
    
    inline int64_t ObVariableSetStmt::get_variables_size() const
    {
        return variable_nodes_.size();
    }
  }
}

#endif //OCEANBASE_SQL_OB_VARIABLE_STMT_H_


