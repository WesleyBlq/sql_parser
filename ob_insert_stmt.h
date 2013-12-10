#ifndef OCEANBASE_SQL_INSERTSTMT_H_
#define OCEANBASE_SQL_INSERTSTMT_H_
#include "ob_stmt.h"
#include <stdio.h>
#include <vector>
//#include "common/ob_string.h"
#include <string>
//#include "common/ob_string_buf.h"

namespace oceanbase
{
    namespace sql
    {

        class ObInsertStmt : public ObStmt
        {
        public:
            ObInsertStmt();
            virtual ~ObInsertStmt();

            void set_insert_table(uint64_t id);
            void set_insert_query(uint64_t id);
            void set_replace(bool is_replace);
            int add_value_row(vector<uint64_t>& value_row);
            bool is_replace() const;
            uint64_t get_table_id() const;
            uint64_t get_insert_query_id() const;
            int64_t get_value_row_size() const;
            const vector<uint64_t>& get_value_row(uint32_t idx) const;
            /**************************************************
            Funtion     :   get_all_value_rows
            Author      :   qinbo
            Date        :   2013.10.30
            Description :   get all value rows
            Input       :   
            Output      :   vector<vector<uint64_t> > all_value_rows
             **************************************************/
            const vector<vector<uint64_t> >& get_all_value_rows() const;
            void print(FILE* fp, int32_t level, int32_t index);
            int64_t make_stmt_string(ResultPlan& result_plan, string& assembled_sql_tmp);
            int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, schema_shard *shard_info,string &assembled_sql);

        private:
            uint64_t table_id_;
            uint64_t sub_query_id_;
            bool is_replace_; // replace semantic
            vector<vector<uint64_t> > value_vectors_;
        };

        inline void ObInsertStmt::set_insert_table(uint64_t id)
        {
            table_id_ = id;
        }

        inline void ObInsertStmt::set_insert_query(uint64_t id)
        {
            sub_query_id_ = id;
        }

        inline void ObInsertStmt::set_replace(bool is_replace)
        {
            is_replace_ = is_replace;
            if (is_replace_)
            {
                set_stmt_type(ObBasicStmt::T_REPLACE);
            }
            else
            {
                set_stmt_type(ObBasicStmt::T_INSERT);
            }
        }

        inline bool ObInsertStmt::is_replace() const
        {
            return is_replace_;
        }

        inline int ObInsertStmt::add_value_row(vector<uint64_t>& value_row)
        {
            value_vectors_.push_back(value_row);
            return common::OB_SUCCESS;
        }

        inline uint64_t ObInsertStmt::get_table_id() const
        {
            return table_id_;
        }

        inline uint64_t ObInsertStmt::get_insert_query_id() const
        {
            return sub_query_id_;
        }

        inline int64_t ObInsertStmt::get_value_row_size() const
        {
            return value_vectors_.size();
        }

        inline const vector<uint64_t>& ObInsertStmt::get_value_row(uint32_t idx) const
        {
            OB_ASSERT(idx >= 0 && idx < value_vectors_.size());
            return value_vectors_.at(idx);
        }
        
        /**************************************************
        Funtion     :   get_all_value_rows
        Author      :   qinbo
        Date        :   2013.10.30
        Description :   get all value rows
        Input       :   
        Output      :   vector<vector<uint64_t> > all_value_rows
         **************************************************/
        inline const vector<vector<uint64_t> >& ObInsertStmt::get_all_value_rows() const
        {
            return value_vectors_;
        }
    }
}

#endif //OCEANBASE_SQL_INSERTSTMT_H_
