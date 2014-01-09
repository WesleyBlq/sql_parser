#include <stdio.h>
#include <stdlib.h>
#include "parse_malloc.h"
#include "sql_logical_plan.h"
#include "utility.h"
#include "sql_delete_stmt.h"

namespace jdbd
{
    namespace sql
    {
        using namespace jdbd::common;

        ObDeleteStmt::ObDeleteStmt()
        : ObStmt(ObStmt::T_DELETE)
        {
        }

        ObDeleteStmt::~ObDeleteStmt()
        {
        }

        void ObDeleteStmt::print(FILE* fp, int32_t level, int32_t index)
        {
            print_indentation(fp, level);
            fprintf(fp, "ObDeleteStmt %d Begin\n", index);
            ObStmt::print(fp, level + 1);
            print_indentation(fp, level + 1);
            fprintf(fp, "FROM ::= <%ld>\n", table_id_);
            print_indentation(fp, level);
            fprintf(fp, "ObDeleteStmt %d End\n", index);
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
        int64_t ObDeleteStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ret = make_delete_table_string(result_plan, assembled_sql);

            if (OB_SUCCESS == ret)
            {
                ret = make_delete_where_string(result_plan, assembled_sql);
            }
            
            return ret;
        }

        /**************************************************
        Funtion     :   make_exec_plan_unit_string
        Author      :   qinbo
        Date        :   2013.12.9
        Description :   make select sql
        Input       :   ResultPlan& result_plan, 
                        string &where_conditions, 
                        vector<schema_shard*> shard_info,
                        string &assembled_sql
                        
        Output      :   
         **************************************************/
        int64_t ObDeleteStmt::make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, vector<schema_shard*> shard_info,string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);

            assembled_sql.append("DELETE FROM ");
            string table_name = ObStmt::get_table_item_by_id(table_id_)->table_name_ ;
            if (table_name != shard_info.at(0)->get_table_name())
            {
                assembled_sql.append(shard_info.at(0)->get_shard_name());
            }
            else
            {
                assembled_sql.append(table_name);
            }

            if (where_conditions.empty())
            {
                make_delete_where_string(result_plan, assembled_sql);
            }
            else
            {
                assembled_sql.append(where_conditions);
                assembled_sql.append(" ");
            }
            return ret;
        }

        
        /**************************************************
        Funtion     :   make_delete_table_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make select sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObDeleteStmt::make_delete_table_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            string assembled_sql_tmp;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);

            assembled_sql.append("DELETE FROM ");
            assembled_sql.append(ObStmt::get_table_item_by_id(table_id_)->table_name_);

            return ret;
        }
        
        /**************************************************
        Funtion     :   make_delete_where_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make select sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObDeleteStmt::make_delete_where_string(ResultPlan& result_plan, string &assembled_sql)
        {
            uint32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            string assembled_sql_tmp;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);
            
            vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

            if (where_exprs.size() > 0)
            {
                assembled_sql.append(" WHERE ");
                for (i = 0; i < where_exprs.size(); i++)
                {
                    sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
                    if (NULL == sql_expr)
                    {
                        ret = OB_ERR_LOGICAL_PLAN_FAILD;
                        jlog(WARNING, "where expr error!!!");
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