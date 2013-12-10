/**
 * (C) 2010-2012 Alibaba Group Holding Limited.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * Version: $Id$
 *
 * ob_variable_set_stmt.cpp
 *
 * Authors:
 *   Guibin Du <tianguan.dgb@taobao.com>
 *
 */
#include "ob_variable_set_stmt.h"

using namespace oceanbase::common;
using namespace oceanbase::sql;
using namespace std;



ObVariableSetStmt::ObVariableSetStmt(): ObBasicStmt(T_VARIABLE_SET)
{

}

ObVariableSetStmt::~ObVariableSetStmt()
{

}

void ObVariableSetStmt::print(FILE* fp, int32_t level, int32_t index)
{
    UNUSED(index);
    print_indentation(fp, level);
    fprintf(fp, "<ObVariableSetStmt %d Begin>\n", index);
    for (int64_t i = 0; i < variable_nodes_.size(); i++)
    {
        print_indentation(fp, level + 1);
        fprintf(fp, "<Variable %ld Begin>\n", i);
        print_indentation(fp, level + 2);
        fprintf(fp, "Variable name ::= %.*s\n", variable_nodes_.at(i).variable_name_.size(), 
            variable_nodes_.at(i).variable_name_.data());
        print_indentation(fp, level + 2);
        
        switch (variable_nodes_.at(i).scope_type_)
        {
        case GLOBAL:
            fprintf(fp, "Scopy ::= GLOBAL\n");
            break;
        case SESSION:
            fprintf(fp, "Scopy ::= SESSION\n");
            break;
        case LOCAL:
            fprintf(fp, "Scopy ::= LOCAL\n");
            break;
        default:
            fprintf(fp, "Scopy ::= NONE\n");
            break;
        }
        print_indentation(fp, level + 2);
        fprintf(fp, "Is system vairable ::= %s\n", variable_nodes_.at(i).is_system_variable_ ? "TRUE" : "FALSE");
        print_indentation(fp, level + 2);
        fprintf(fp, "Value Expression Id ::= <%ld>\n", variable_nodes_.at(i).value_expr_id_);
        print_indentation(fp, level + 1);
        fprintf(fp, "<Variable %ld End>\n", i);
    }
    
    print_indentation(fp, level);
    fprintf(fp, "<ObVariableSetStmt %d End>\n", index);
}



int64_t ObVariableSetStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
{

}

int64_t ObVariableSetStmt::make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, schema_shard *shard_info,string &assembled_sql)
{
    return OB_SUCCESS;
}


