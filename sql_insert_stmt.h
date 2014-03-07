#ifndef SQL_INSERTSTMT_H_
#define SQL_INSERTSTMT_H_
#include "ob_stmt.h"
#include <stdio.h>
#include <vector>
#include <string>

#define AUTO_INCR_MAX_INDEX     1000

namespace jdbd
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
            int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string insert_rows, vector<schema_shard*> &shard_info,string &assembled_sql);
            /**************************************************
            Funtion     :   append_distributed_insert_items
            Author      :   qinbo
            Date        :   2014.1.6
            Description :   append insert rows
            Input       :   ResultPlan& result_plan,
                            vector<uint32_t> &insert_rows_index,
                            string &assembled_sql
            Output      :   
             **************************************************/
            int append_distributed_insert_items(ResultPlan& result_plan,
                                                vector<uint32_t> &insert_rows_index,
                                                string &assembled_sql);
            
            /**************************************************
            Funtion     :   set_auto_incr_sharding_key
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   has_auto_incr_sharding_key
            Input       :   bool has_auto_incr_
            Output      :   
             **************************************************/
            void set_auto_incr_sharding_key(bool has_auto_incr_)
            {
                has_auto_incr = has_auto_incr_;
            }

            /**************************************************
            Funtion     :   has_auto_incr_sharding_key
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   has_auto_incr_sharding_key
            Input       :   bool has_auto_incr_
            Output      :   
             **************************************************/
            bool has_auto_incr_sharding_key()
            {
                return has_auto_incr;
            }
            
            /**************************************************
            Funtion     :   set_auto_incr_column_name
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   has_auto_incr_sharding_key
            Input       :   bool has_auto_incr_
            Output      :   
             **************************************************/
            void set_auto_incr_column_name(string column_name) 
            {
                auto_incr_column_name = column_name;
            }
            
            /**************************************************
            Funtion     :   get_auto_incr_column_name
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   has_auto_incr_sharding_key
            Input       :   bool has_auto_incr_
            Output      :   
             **************************************************/
            string get_auto_incr_column_name() 
            {
                return auto_incr_column_name;
            }

            /**************************************************
            Funtion     :   set_auto_incr_id_value
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   set_auto_incr_id_value
            Input       :   uint64_t index
            Output      :   
             **************************************************/
            void set_auto_incr_id_value(uint32_t index, uint64_t value)
            {
                OB_ASSERT((index >= 0)&&(index < AUTO_INCR_MAX_INDEX));
                auto_incr_ids[index] = value;
            }

            /**************************************************
            Funtion     :   get_auto_incr_id_value
            Author      :   qinbo
            Date        :   2014.1.23
            Description :   set_auto_incr_id_value
            Input       :   uint64_t index
            Output      :   
             **************************************************/
            uint64_t get_auto_incr_id_value(uint32_t index)
            {
                OB_ASSERT((index >= 0)&&(index < AUTO_INCR_MAX_INDEX));
                return auto_incr_ids[index];
            }
        private:
            uint64_t table_id_;
            uint64_t sub_query_id_;
            bool is_replace_; // replace semantic
            vector<vector<uint64_t> > value_vectors_;
            bool    has_auto_incr;
            string  auto_incr_column_name;
            uint64_t auto_incr_ids[AUTO_INCR_MAX_INDEX];
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

#endif //SQL_INSERTSTMT_H_
