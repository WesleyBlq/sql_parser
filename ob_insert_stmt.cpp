#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "parse_malloc.h"
#include "ob_logical_plan.h"
#include "utility.h"
#include "ob_insert_stmt.h"

using namespace std;
using namespace oceanbase::common;
using namespace oceanbase::sql;

ObInsertStmt::ObInsertStmt()
: ObStmt(T_INSERT)
{
    sub_query_id_ = OB_INVALID_ID;
    is_replace_ = false;
}

ObInsertStmt::~ObInsertStmt()
{
    for (int64_t i = 0; i < value_vectors_.size(); i++)
    {
        vector<uint64_t>& value_row = value_vectors_.at(i);
        value_row.clear();
    }
}

void ObInsertStmt::print(FILE* fp, int32_t level, int32_t index)
{
    print_indentation(fp, level);
    fprintf(fp, "<ObInsertStmt %d Begin>\n", index);
    ObStmt::print(fp, level + 1);
    print_indentation(fp, level + 1);
    fprintf(fp, "INTO ::= <%ld>\n", table_id_);
    if (sub_query_id_ == OB_INVALID_ID)
    {
        print_indentation(fp, level + 1);
        fprintf(fp, "VALUES ::= ");
        for (int64_t i = 0; i < value_vectors_.size(); i++)
        {
            if (i == 0)
                fprintf(fp, "<");
            else
                fprintf(fp, ", <");
            vector<uint64_t>& value_row = value_vectors_.at(i);
            for (int j = 0; j < value_row.size(); j++)
            {
                if (j == 0)
                    fprintf(fp, "%ld", value_row.at(j));
                else
                    fprintf(fp, ", %ld", value_row.at(j));
            }
            fprintf(fp, ">");
        }
        fprintf(fp, "\n");
    }
    else
    {
        print_indentation(fp, level + 1);
        fprintf(fp, "SUBQUERY ::= <%ld>\n", sub_query_id_);
    }
    print_indentation(fp, level);
    fprintf(fp, "<ObInsertStmt %d End>\n", index);
}

/**************************************************
Funtion     :   make_stmt_string
Author      :   qinbo
Date        :   2013.9.10
Description :   make select sql
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObInsertStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    string assembled_sql_tmp;
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (is_replace_)
    {
        assembled_sql.append("REPLACE INTO ");
    }
    else
    {
        assembled_sql.append("INSERT INTO ");
    }

    assembled_sql.append(ObStmt::get_table_item_by_id(table_id_)->table_name_);
        
    for (int64_t i = 0; i < ObStmt::get_column_size(); i++)
    {
        if (0 == i)
        {
            assembled_sql.append(" (");
        }

        assembled_sql.append(ObStmt::get_column_item(i)->column_name_);
            
        if (i != ObStmt::get_column_size() - 1)
        {
            assembled_sql.append(", ");
        }
        else
        {
            assembled_sql.append(") ");
        }
    }

    if (sub_query_id_ == OB_INVALID_ID)
    {
        assembled_sql.append("VALUES ");
            
        for (int64_t i = 0; i < value_vectors_.size(); i++)
        {
            vector<uint64_t>& value_row = value_vectors_.at(i);
            for (int j = 0; j < value_row.size(); j++)
            {
                if (j == 0)
                {
                    assembled_sql.append("(");
                }

                sql_expr = logical_plan->get_expr_by_id(value_row.at(j));

                if (NULL == sql_expr)
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "insert value expr error!!!");
                    return ret;
                }

                sql_expr->to_string(result_plan, assembled_sql_tmp);
                assembled_sql.append(assembled_sql_tmp);
                    
                if (j == value_row.size() - 1)
                {
                    assembled_sql.append(")");
                }
                else
                {
                    assembled_sql.append(",");
                }

            }

            if (i != value_vectors_.size() - 1)
            {
                assembled_sql.append(",");
            }
        }
    }
    else
    {
        string assembled_sql_tmp;
        ObBasicStmt* query_stmt = logical_plan->get_query(sub_query_id_);

        if (NULL == query_stmt)
        {
            ret = OB_ERR_LOGICAL_PLAN_FAILD;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "can not get query stmt by query id!!!");
            return ret;
        }

        query_stmt->make_stmt_string(result_plan, assembled_sql_tmp);
        assembled_sql.append(assembled_sql_tmp);
    }
}

/**************************************************
Funtion     :   make_exec_plan_unit_string
Author      :   qinbo
Date        :   2013.12.9
Description :   make select sql
Input       :   ResultPlan& result_plan, 
                string where_conditions, 
                schema_shard *shard_info,
                string &assembled_sql
                
Output      :   
 **************************************************/
int64_t ObInsertStmt::make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, schema_shard *shard_info,string &assembled_sql)
{
    return OB_SUCCESS;
}


