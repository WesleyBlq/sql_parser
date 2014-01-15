#ifndef SQL_UPDATESTMT_H_
#define SQL_UPDATESTMT_H_
#include "ob_stmt.h"
#include <stdio.h>
#include <vector>
#include <string>
#include "sql_raw_expr.h"

namespace jdbd
{
    namespace sql
    {

        class ObUpdateStmt : public ObStmt
        {
        public:
            ObUpdateStmt();
            virtual ~ObUpdateStmt();

            uint64_t set_update_table(uint64_t id)
            {
                if (id == jdbd::common::OB_INVALID_ID)
                    return jdbd::common::OB_INVALID_ID;
                table_id_ = id;
                return id;
            }

            uint64_t get_update_table_id(void)
            {
                return table_id_;
            }

            int add_update_column(uint64_t column_id)
            {
                int ret = common::OB_SUCCESS;
                if (column_id != jdbd::common::OB_INVALID_ID)
                    update_columns_.push_back(column_id);
                return ret;
            }

            int get_update_column_id(uint32_t idx, uint64_t &column_id)
            {
                int ret = common::OB_SUCCESS;
                if (idx < update_columns_.size())
                {
                    column_id = update_columns_.at(idx);
                }
                else
                {
                    ret = JD_INVALID_ARGUMENT;
                }
                return ret;
            }

            int add_update_expr(uint64_t expr_id)
            {
                int ret = common::OB_SUCCESS;
                if (expr_id == jdbd::common::OB_INVALID_ID)
                    ret = common::OB_ERROR;
                else
                    update_exprs_.push_back(expr_id);
                return ret;
            }

            int get_update_expr_id(uint32_t idx, uint64_t &expr_id)
            {
                int ret = common::OB_SUCCESS;
                if (idx < update_exprs_.size())
                {
                    expr_id = update_exprs_.at(idx);
                }
                else
                {
                    ret = JD_INVALID_ARGUMENT;
                }
                return ret;
            }

            uint32_t get_update_column_count(void)
            {
                return update_columns_.size();
            }

            void print(FILE* fp, int32_t level, int32_t index);
            int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, vector<schema_shard*> shard_info,string &assembled_sql);
            int64_t make_update_table_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_update_column_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_update_where_string(ResultPlan& result_plan, string &assembled_sql);
            
            /**************************************************
            Funtion     :   decompose_where_items
            Author      :   qinbo
            Date        :   2013.9.24
            Description :   generate distributed where conditions items
            Input       :   ObRawExpr* sql_expr
            Output      :   vector<vector<ObRawExpr*> > &atomic_exprs_array
            return      :   
             **************************************************/
            int decompose_where_items(ObRawExpr* sql_expr, vector<vector<ObRawExpr*> > &atomic_exprs_array);

        private:
            uint64_t table_id_;
            vector<uint64_t> update_columns_;
            vector<uint64_t> update_exprs_;
        };
    }
}

#endif //SQL_UPDATESTMT_H_

