#include <stdio.h>
#include <stdlib.h>
#include "parse_malloc.h"
#include "ob_logical_plan.h"
#include "utility.h"
#include "ob_delete_stmt.h"

namespace oceanbase
{
  namespace sql
  {
    using namespace oceanbase::common;

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
                    char* buf, 
                    const int64_t buf_len
    Output      :   
    **************************************************/
    int64_t ObDeleteStmt::make_stmt_string( ResultPlan& result_plan,
                                            char* buf, 
                                            const int64_t buf_len)
    {
        int32_t i = 0;
        int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
        int64_t pos = 0;
        char tmp_str[STMT_BUF_SIZE] = {0};
        ObSqlRawExpr* sql_expr = NULL;
        
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
        if (logical_plan == NULL)
        {
          ret = OB_ERR_LOGICAL_PLAN_FAILD;
          snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "logical_plan must exist!!!");
        }

        databuff_printf(buf, buf_len, pos, "DELETE FROM ");
        databuff_printf(buf, buf_len, pos, ObStmt::get_table_item_by_id(table_id_)->table_name_.data());
        databuff_printf(buf, buf_len, pos, " ");

        vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

        if (where_exprs.size()>0 )
        {
            databuff_printf(buf, buf_len, pos, "WHERE ");
            for (i = 0; i < where_exprs.size(); i++)
            {
                sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
                if (NULL == sql_expr)
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "where expr error!!!");
                    return ret;
                }

                memset(tmp_str, 0,STMT_BUF_SIZE);
                sql_expr->to_string(result_plan, tmp_str, STMT_BUF_SIZE);
                databuff_printf(buf, buf_len, pos, tmp_str);
                if (i != where_exprs.size()-1 )
                {
                    databuff_printf(buf, buf_len, pos, " AND ");
                }
                else
                {
                    databuff_printf(buf, buf_len, pos, " ");
                }
            }
        }
        
    }

  }
}
