#ifndef OCEANBASE_SQL_SELECTSTMT_H_
#define OCEANBASE_SQL_SELECTSTMT_H_

#include "ob_stmt.h"
#include "ob_raw_expr.h"
//#include "common/ob_string.h"
//#include "common/ob_string_buf.h"
//#include "common/ob_array.h"
#include <vector>
#include <map>
#include <string>

#define OP_SELECT       2
#define OP_FROM         4
#define OP_TABLE        8
#define OP_ON           16
#define OP_WHERE        32
#define OP_GROUP        64
#define OP_HAVING       128
#define OP_ORDER        256
#define OP_LIMIT        512
#define OP_SUBSELECT    1024

#define OP_SELECT_ALL (OP_SELECT + OP_FROM + OP_TABLE + OP_ON + OP_WHERE + \
                        OP_GROUP + OP_HAVING + OP_ORDER + OP_LIMIT + OP_SUBSELECT)

namespace oceanbase
{
    namespace sql
    {

        struct SelectItem
        {
            uint64_t expr_id_;
            bool is_real_alias_;
            string alias_name_;
            string expr_name_;
            common::ObObjType type_;

            string raw_select_item_name;
            SqlItemType aggr_fun_type; /*added by qinbo*/
        };

        struct LimitItem
        {
            int64_t start;
            int64_t end;
            uint32_t pos;
            bool end_of_query;
        };

        struct OrderItem
        {

            enum OrderType
            {
                ASC,
                DESC
            };

            uint64_t expr_id_;
            OrderType order_type_;
            string order_column;
        };

        struct GroupItem
        {

            enum GroupType
            {
                ASC,
                DESC
            };

            uint64_t expr_id_;
            GroupType group_type_;
            string group_column_;
        };

        /*END: added by qinbo*/

        struct JoinedTable
        {

            enum JoinType
            {
                T_FULL,
                T_LEFT,
                T_RIGHT,
                T_INNER,
            };

            int add_table_id(uint64_t tid)
            {
                table_ids_.push_back(tid);
                return common::OB_SUCCESS;
            }

            int add_join_type(JoinType type)
            {
                join_types_.push_back(type);
                return common::OB_SUCCESS;
            }

            int add_expr_id(uint64_t eid)
            {
                expr_ids_.push_back(eid);
                return common::OB_SUCCESS;
            }

            void set_joined_tid(uint64_t tid)
            {
                joined_table_id_ = tid;
            }

            uint64_t joined_table_id_;
            vector<uint64_t> table_ids_;
            vector<uint64_t> join_types_;
            vector<uint64_t> expr_ids_;
        };

        struct FromItem
        {
            uint64_t table_id_;
            // false: it is the real table id
            // true: it is the joined table id
            bool is_joined_;
        };

        typedef struct st_select_tpl
        {
            string str;
            string table_name;
            string real_table_name;
            bool fill;
            ulong op;
        } select_tpl;
    }
#if 0
    namespace common
    {

        template <>
        struct ob_vector_traits<oceanbase::sql::SelectItem>
        {
            typedef oceanbase::sql::SelectItem* pointee_type;
            typedef oceanbase::sql::SelectItem value_type;
            typedef const oceanbase::sql::SelectItem const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };

        template <>
        struct ob_vector_traits<oceanbase::sql::OrderItem>
        {
            typedef oceanbase::sql::OrderItem* pointee_type;
            typedef oceanbase::sql::OrderItem value_type;
            typedef const oceanbase::sql::OrderItem const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };

        template <>
        struct ob_vector_traits<oceanbase::sql::FromItem>
        {
            typedef oceanbase::sql::FromItem* pointee_type;
            typedef oceanbase::sql::FromItem value_type;
            typedef const oceanbase::sql::FromItem const_value_type;
            typedef value_type* iterator;
            typedef const value_type* const_iterator;
            typedef int32_t difference_type;
        };
    }
#endif
    namespace sql
    {

        class ObSelectStmt : public ObStmt
        {
        public:

            enum SetOperator
            {
                UNION,
                INTERSECT,
                EXCEPT,
                NONE,
            };

            ObSelectStmt();
            virtual ~ObSelectStmt();

            int32_t get_select_item_size() const
            {
                return select_items_.size();
            }

            int32_t get_from_item_size() const
            {
                return from_items_.size();
            }

            int32_t get_joined_table_size() const
            {
                return joined_tables_.size();
            }

            int32_t get_group_expr_size() const
            {
                return group_expr_ids_.size();
            }

            int32_t get_agg_fun_size() const
            {
                return agg_func_ids_.size();
            }

            int32_t get_having_expr_size() const
            {
                return having_expr_ids_.size();
            }

            int32_t get_order_item_size() const
            {
                return order_items_.size();
            }

            void assign_distinct()
            {
                is_distinct_ = true;
            }

            void assign_all()
            {
                is_distinct_ = false;
            }

            void assign_set_op(SetOperator op)
            {
                set_op_ = op;
            }

            void assign_set_distinct()
            {
                is_set_distinct_ = true;
            }

            void assign_set_all()
            {
                is_set_distinct_ = false;
            }

            void assign_left_query_id(uint64_t lid)
            {
                left_query_id_ = lid;
            }

            void assign_right_query_id(uint64_t rid)
            {
                right_query_id_ = rid;
            }
            int check_alias_name(ResultPlan& result_plan, const string& sAlias);
            uint64_t get_alias_expr_id(string& alias_name);

            uint64_t generate_joined_tid()
            {
                return gen_joined_tid_--;
            }

            uint64_t get_left_query_id()
            {
                return left_query_id_;
            }

            uint64_t get_right_query_id()
            {
                return right_query_id_;
            }

            uint64_t get_limit_expr_id() const
            {
                return limit_count_id_;
            }

            uint64_t get_offset_expr_id() const
            {
                return limit_offset_id_;
            }

            bool is_distinct()
            {
                return is_distinct_;
            }

            bool is_set_distinct()
            {
                return is_set_distinct_;
            }

            bool is_for_update()
            {
                return for_update_;
            }

            bool has_limit()
            {
                return (limit_count_id_ != common::OB_INVALID_ID || limit_offset_id_ != common::OB_INVALID_ID);
            }

            SetOperator get_set_op()
            {
                return set_op_;
            }
            JoinedTable* get_joined_table(uint64_t table_id);

            const SelectItem& get_select_item(int32_t index)
            {
                OB_ASSERT(0 <= index && index < select_items_.size());
                return select_items_[index];
            }

            const FromItem& get_from_item(int32_t index)
            {
                OB_ASSERT(0 <= index && index < from_items_.size());
                return from_items_[index];
            }

            //BEGIN: Added by qinbo

            const vector<FromItem> &get_all_from_items()
            {
                return from_items_;
            }
            //END: Added by qinbo

            const OrderItem& get_order_item(int32_t index)
            {
                OB_ASSERT(0 <= index && index < order_items_.size());
                return order_items_[index];
            }

            uint64_t get_group_expr_id(int32_t index)
            {
                OB_ASSERT(0 <= index && index < group_expr_ids_.size());
                return group_expr_ids_[index];
            }

            uint64_t get_agg_expr_id(int32_t index)
            {
                OB_ASSERT(0 <= index && index < agg_func_ids_.size());
                return agg_func_ids_[index];
            }

            uint64_t get_having_expr_id(int32_t index)
            {
                OB_ASSERT(0 <= index && index < having_expr_ids_.size());
                return having_expr_ids_[index];
            }

            vector<uint64_t>& get_having_exprs()
            {
                return having_expr_ids_;
            }

            int add_group_expr(uint64_t expr_id)
            {
                group_expr_ids_.push_back(expr_id);
                return common::OB_SUCCESS;
            }

            int add_agg_func(uint64_t expr_id)
            {
                agg_func_ids_.push_back(expr_id);
                return common::OB_SUCCESS;
            }

            int add_from_item(uint64_t tid, bool is_joined = false)
            {
                int ret = OB_SUCCESS;
                if (tid != OB_INVALID_ID)
                {
                    FromItem item;
                    item.table_id_ = tid;
                    item.is_joined_ = is_joined;
                    from_items_.push_back(item);
                    return common::OB_SUCCESS;
                }
                else
                {
                    ret = OB_ERR_ILLEGAL_ID;
                }
                return ret;
            }

            /*BEGIN: added by qinbo*/
            bool is_from_item_with_join()
            {
                for (int32_t i = 0; i < from_items_.size(); i++)
                {
                    FromItem& item = from_items_[i];
                    if (item.is_joined_)
                    {
                        return true;
                    }
                }
                return false;
            }

            /*END: added by qinbo*/

            int add_order_item(OrderItem& order_item)
            {
                order_items_.push_back(order_item);
                return common::OB_SUCCESS;
            }

            int add_joined_table(JoinedTable* pJoinedTable)
            {
                joined_tables_.push_back(pJoinedTable);
                return common::OB_SUCCESS;
            }

            int add_having_expr(uint64_t expr_id)
            {
                having_expr_ids_.push_back(expr_id);
                return common::OB_SUCCESS;
            }

            void set_limit_offset(const uint64_t& limit, const uint64_t& offset)
            {
                limit_count_id_ = limit;
                limit_offset_id_ = offset;
            }

            void set_for_update(bool for_update)
            {
                for_update_ = for_update;
            }

            int check_having_ident(
                    ResultPlan& result_plan,
                    string& column_name,
                    TableItem* table_item,
                    ObRawExpr*& ret_expr);

            int add_select_item(
                    uint64_t eid,
                    bool is_real_alias,
                    const string& alias_name,
                    const string& expr_name,
                    const common::ObObjType& type);

            int copy_select_items(ObSelectStmt* select_stmt);
            void print(FILE* fp, int32_t level, int32_t index = 0);

            /*BEGIN: added by qinbo*/
            int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_select_item_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_from_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_where_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_group_by_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_order_by_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_having_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_limit_string(ResultPlan& result_plan, string &assembled_sql);
            /*END: added by qinbo*/
        private:
            /* These fields are only used by normal select */
            bool is_distinct_;
            vector<SelectItem> select_items_;
            vector<FromItem> from_items_;
            vector<JoinedTable*> joined_tables_;
            vector<uint64_t> group_expr_ids_;
            vector<uint64_t> having_expr_ids_;
            vector<uint64_t> agg_func_ids_;

            /* These fields are only used by set select */
            SetOperator set_op_;
            bool is_set_distinct_;
            uint64_t left_query_id_;
            uint64_t right_query_id_;

            /* These fields are used by both normal select and set select */
            vector<OrderItem> order_items_;

            /* -1 means no limit */
            uint64_t limit_count_id_;
            uint64_t limit_offset_id_;

            /* FOR UPDATE clause */
            bool for_update_;

            uint64_t gen_joined_tid_;

            /* for tangchao@jd.com, optimize select */
        public:
            vector<string> fetch_tables_from_tree(ResultPlan& result_plan);
            vector<SelectItem> fetch_select_from_tree(ResultPlan& result_plan, string table_name);
            vector<string> fetch_where_from_tree(ResultPlan& result_plan, string table_name);
            vector<GroupItem> fetch_group_from_tree(ResultPlan& result_plan, string table_name);
            vector<OrderItem> fetch_order_from_tree(ResultPlan& result_plan, string table_name);
            LimitItem fetch_limit_from_tree(ResultPlan& result_plan);

            void set_follow_order(bool f)
            {
                follow_order = f;
            }

            void set_follow_group(bool f)
            {
                follow_group = f;
            }

            void set_follow_agg(bool f)
            {
                follow_aggregate = f;
            }

            void set_order_by_primary(bool f)
            {
                order_by_primary = f;
            }

            void set_limit(long f)
            {
                limit = f;
            }

        private:
            /* follow down */
            bool follow_order; /* true need do order by secondary. */
            bool follow_group; /* true need do group secondary. */
            bool follow_aggregate; /* true need do function. */
            bool order_by_primary; /* order by */
            long limit; /* */
        };
    }
}

#endif //OCEANBASE_SQL_SELECTSTMT_H_
