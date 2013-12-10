#ifndef OCEANBASE_SQL_STMT_H_
#define OCEANBASE_SQL_STMT_H_
//#include "ob_row_desc.h"
#include <string>
#include <stdlib.h>
//#include "common/ob_string_buf.h"
//#include "common/ob_vector.h"
#include <vector>
#include "ob_obj_type.h"
#include "ob_basic_stmt.h"
#include "parse_node.h"

using std::vector;
using std::string;

namespace oceanbase
{
    namespace sql
    {

        struct ObQueryHint
        {

            ObQueryHint()
            {
                read_static_ = false;
            }

            bool read_static_;
        };

        struct TableItem
        {

            TableItem()
            {
                table_id_ = common::OB_INVALID_ID;
                ref_id_ = common::OB_INVALID_ID;
                has_scan_columns_ = false;
            }

            enum TableType
            {
                BASE_TABLE,
                ALIAS_TABLE,
                GENERATED_TABLE,
            };

            // if real table id, it is valid for all threads,
            // else if generated id, it is unique just during the thread session
            uint64_t table_id_;
            string table_name_;
            string alias_name_;
            TableType type_;
            // type == BASE_TABLE? ref_id_ is the real Id of the schema
            // type == ALIAS_TABLE? ref_id_ is the real Id of the schema, while table_id_ new generated
            // type == GENERATED_TABLE? ref_id_ is the reference of the sub-query.
            uint64_t ref_id_;
            bool has_scan_columns_;
        };

        struct ColumnItem
        {
            uint64_t column_id_;
            string column_name_;
            uint64_t table_id_;
            uint64_t query_id_;
            // This attribute is used by resolver, to mark if the column name is unique of all from tables
            bool is_name_unique_;
            bool is_group_based_;
            // TBD, we can not calculate resulte type now.
            common::ObObjType data_type_;
        };
    }

#if 0
    namespace common
    {

        template <>
        struct ob_vector_traits<oceanbase::sql::TableItem>
        {
            typedef oceanbase::sql::TableItem* pointee_type;
            typedef oceanbase::sql::TableItem value_type;
            typedef const oceanbase::sql::TableItem const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };

        template <>
        struct ob_vector_traits<oceanbase::sql::ColumnItem>
        {
            typedef oceanbase::sql::ColumnItem* pointee_type;
            typedef oceanbase::sql::ColumnItem value_type;
            typedef const oceanbase::sql::ColumnItem const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };

        template <>
        struct ob_vector_traits<uint64_t>
        {
            typedef uint64_t* pointee_type;
            typedef uint64_t value_type;
            typedef const uint64_t const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };
    }
#endif

    namespace sql
    {
        class ObLogicalPlan;

        class ObStmt : public ObBasicStmt
        {
        public:
            ObStmt(StmtType type);
            virtual ~ObStmt();

            int32_t get_table_size() const
            {
                return table_items_.size();
            }

            int32_t get_column_size() const
            {
                return column_items_.size();
            }

            int32_t get_condition_size() const
            {
                return where_expr_ids_.size();
            }
            int add_table_item(
                    ResultPlan& result_plan,
                    const string& table_name,
                    const string& alias_name,
                    uint64_t& table_id,
                    const TableItem::TableType type,
                    const uint64_t ref_id = common::OB_INVALID_ID);
            int check_table_column(
                    ResultPlan& result_plan,
                    const string& column_name,
                    const TableItem& table_item,
                    uint64_t& column_id,
                    common::ObObjType& column_type);
            int add_column_item(
                    ResultPlan& result_plan,
                    const string& column_name,
                    const string* table_name = NULL,
                    ColumnItem** col_item = NULL);

            int add_column_item(const ColumnItem& column_item);
            ColumnItem* get_column_item(
                    const string* table_name,
                    const string& column_name);
            ColumnItem* get_column_item_by_id(uint64_t table_id, uint64_t column_id);

            const ColumnItem* get_column_item(int32_t index)
            {
                const ColumnItem *column_item = NULL;
                if (0 <= index && index < column_items_.size())
                {
                    column_item = &column_items_[index];
                }
                return column_item;
            }
            TableItem* get_table_item_by_id(uint64_t table_id);

            TableItem& get_table_item(int32_t index)
            {
                OB_ASSERT(0 <= index && index < table_items_.size());
                return table_items_[index];
            }

            uint64_t get_condition_id(int32_t index)
            {
                OB_ASSERT(0 <= index && index < where_expr_ids_.size());
                return where_expr_ids_[index];
            }
            uint64_t get_table_item(
                    const string& table_name,
                    TableItem** table_item = NULL);

            //int32_t get_table_bit_index(uint64_t table_id) const ;

            vector<uint64_t>& get_where_exprs()
            {
                return where_expr_ids_;
            }

#if 0

            stringBuf* get_name_pool() const
            {
                return name_pool_;
            }
#endif

            ObQueryHint& get_query_hint()
            {
                return query_hint_;
            }

            virtual void print(FILE* fp, int32_t level, int32_t index = 0);
            virtual int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
            virtual int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, schema_shard *shard_info,string &assembled_sql);

        protected:
            //stringBuf* name_pool_;
            vector<TableItem> table_items_;
            vector<ColumnItem> column_items_;

        private:
            //uint64_t  where_expr_id_;
            vector<uint64_t> where_expr_ids_;
            ObQueryHint query_hint_;

            // it is only used to record the table_id--bit_index map
            // although it is a little weird, but it is high-performance than ObHashMap
            //common::ObRowDesc tables_hash_;
        };
    }
}

#endif //OCEANBASE_SQL_STMT_H_
