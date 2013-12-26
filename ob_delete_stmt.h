#ifndef OCEANBASE_SQL_DELETESTMT_H_
#define OCEANBASE_SQL_DELETESTMT_H_
#include "ob_stmt.h"
#include <string>
//#include "common/ob_string_buf.h"

namespace oceanbase
{
    namespace sql
    {

        class ObDeleteStmt : public ObStmt
        {
        public:
            ObDeleteStmt();
            virtual ~ObDeleteStmt();

            uint64_t set_delete_table(uint64_t id);
            uint64_t get_delete_table_id(void);

            void print(FILE* fp, int32_t level, int32_t index);
            int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, vector<schema_shard*> shard_info,string &assembled_sql);
            int64_t make_delete_table_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_delete_where_string(ResultPlan& result_plan, string &assembled_sql);

        private:
            uint64_t table_id_;
        };

        inline uint64_t ObDeleteStmt::set_delete_table(uint64_t id)
        {
            table_id_ = id;
            return id;
        }

        inline uint64_t ObDeleteStmt::get_delete_table_id(void)
        {
            return table_id_;
        }
    }
}

#endif //OCEANBASE_SQL_DELETESTMT_H_

