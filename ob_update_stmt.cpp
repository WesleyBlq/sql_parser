
#include <stdio.h>
#include <stdlib.h>
#include "ob_update_stmt.h"
#include "parse_malloc.h"
#include "ob_logical_plan.h"
#include "utility.h"

namespace oceanbase
{
    namespace sql
    {
        using namespace oceanbase::common;

        ObUpdateStmt::ObUpdateStmt()
        : ObStmt(T_UPDATE)
        {
        }

        ObUpdateStmt::~ObUpdateStmt()
        {
        }

        void ObUpdateStmt::print(FILE* fp, int32_t level, int32_t index)
        {
            print_indentation(fp, level);
            fprintf(fp, "ObUpdateStmt %d Begin\n", index);
            ObStmt::print(fp, level + 1);
            print_indentation(fp, level + 1);
            fprintf(fp, "UPDATE ::= <%ld>\n", table_id_);
            print_indentation(fp, level + 1);
            fprintf(fp, "SET ::= ");
            for (int64_t i = 0; i < update_columns_.size(); i++)
            {
                if (i > 0)
                    fprintf(fp, ", <%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
                else
                    fprintf(fp, "<%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
            }
            fprintf(fp, "\n");
            print_indentation(fp, level);
            fprintf(fp, "ObUpdateStmt %d End\n", index);
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
        int64_t ObUpdateStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
        {
            make_update_table_string(result_plan, assembled_sql);
            make_update_column_string(result_plan, assembled_sql);
            make_update_where_string(result_plan, assembled_sql);
        }
        
        /**************************************************
        Funtion     :   make_update_table_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update table sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_table_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            if (logical_plan == NULL)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "logical_plan must exist!!!");
            }

            assembled_sql.append("UPDATE ");
            assembled_sql.append(ObStmt::get_table_item_by_id(table_id_)->table_name_);
            assembled_sql.append(" SET ");
        }

        /**************************************************
        Funtion     :   make_update_column_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update column name sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_column_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            if (logical_plan == NULL)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "logical_plan must exist!!!");
            }
            
            for (i = 0; i < update_columns_.size(); i++)
            {
                string assembled_sql_tmp;
                assembled_sql.append(ObStmt::get_column_item(i)->column_name_);
                assembled_sql.append(" = ");

                sql_expr = logical_plan->get_expr_by_id(update_exprs_.at(i));

                if (NULL == sql_expr)
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG, "update expr name error");
                    return ret;
                }

                sql_expr->to_string(result_plan, assembled_sql_tmp);
                assembled_sql.append(assembled_sql_tmp);

                if (i != update_columns_.size() - 1)
                {
                    assembled_sql.append(" , ");
                }
                else
                {
                    assembled_sql.append(" ");
                }
            }
        }

        
        /**************************************************
        Funtion     :   make_update_where_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update where item sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_where_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            if (logical_plan == NULL)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "logical_plan must exist!!!");
            }
            
            vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

            if (where_exprs.size() > 0)
            {
                assembled_sql.append("WHERE ");
                for (i = 0; i < where_exprs.size(); i++)
                {
                    string assembled_sql_tmp;
                    sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
                    if (NULL == sql_expr)
                    {
                        ret = OB_ERR_LOGICAL_PLAN_FAILD;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "where expr name error!!!");
                        return ret;
                    }

                    sql_expr->to_string(result_plan, assembled_sql_tmp);
                    assembled_sql.append(assembled_sql_tmp);
                    if (i != where_exprs.size() - 1)
                    {
                        assembled_sql.append(" AND ");
                    }
                    else
                    {
                        assembled_sql.append(" ");
                    }
                }
            }
            return ret;
        }

    }
}
