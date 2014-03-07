#ifndef SQL_SELECTSTMT_H_
#define SQL_SELECTSTMT_H_

#include "ob_stmt.h"
#include "sql_raw_expr.h"
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

//sql sent to shard should have max rows num MAX_LIMIT_ROWS
#define MAX_LIMIT_ROWS  100000000

using namespace jdbd::common;

namespace jdbd
{
    namespace sql
    {

        struct SelectItem
        {
            uint64_t expr_id_;
            string expr_name_;
            common::ObObjType type_;
            bool is_real_alias_;        //whether or not is real alias
            string alias_name_;         //alias name
            string select_column_name_; //original field name
            SqlItemType aggr_fun_type;
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
            uint64_t expr_id_;
            SqlItemType order_type_;
            common::ObObjType column_type_;
            string order_column_;
        };

        struct GroupItem
        {
            uint64_t expr_id_;
            SqlItemType group_type_;
            common::ObObjType column_type_;
            string group_column_;
        };

        struct HavingItem
        {
            uint64_t expr_id_;
            common::ObObjType column_type_;
            string having_column_name;
            SqlItemType aggr_fun_type;
            uint32_t    aggr_fun_operate;
            double      aggr_fun_value;
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
            string   table_name_;
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

            uint32_t get_select_item_size() const
            {
                return select_items_.size();
            }

            uint32_t get_from_item_size() const
            {
                return from_items_.size();
            }

            uint32_t get_joined_table_size() const
            {
                return joined_tables_.size();
            }

            uint32_t get_group_expr_size() const
            {
                return group_expr_ids_.size();
            }

            uint32_t get_agg_fun_size() const
            {
                return agg_func_ids_.size();
            }

            uint32_t get_having_expr_size() const
            {
                return having_expr_ids_.size();
            }

            uint32_t get_order_item_size() const
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

            const SelectItem& get_select_item(uint32_t index)
            {
                OB_ASSERT(0 <= index && index < select_items_.size());
                return select_items_[index];
            }

            const FromItem& get_from_item(uint32_t index)
            {
                OB_ASSERT(0 <= index && index < from_items_.size());
                return from_items_[index];
            }

            //BEGIN: Added by qinbo
            const bool try_fetch_select_item_by_column_name(
                    const vector<SelectItem> &select_items, string column_name,
                    uint32_t &offset)
            {
                for (uint32_t i = 0; i < select_items.size(); i++)
                {
                    if (select_items[i].select_column_name_ == column_name)
                        
                    {
                        offset = i;
                        return true;
                    }
                }

                return false;
            }

            //BEGIN: add by tangchao at 20140106
            const bool try_fetch_select_item_by_group(
                    const vector<SelectItem> &select_items, string column_name,
                    uint32_t &offset)
            {
                for (uint32_t i = 0; i < select_items.size(); i++)
                {
                    if (select_items[i].select_column_name_ == column_name
                            && select_items[i].aggr_fun_type == T_INVALID)
                    {
                        offset = i;
                        return true;
                    }
                }
                
                return false;
            }

            const bool try_fetch_select_item_by_having(
                    const vector<SelectItem> &select_items, HavingItem& having,
                    uint32_t & offset)
            {
                for (uint32_t i = 0; i < select_items.size(); i++)
                {
                    if (select_items[i].select_column_name_ ==
                            having.having_column_name
                            && select_items[i].aggr_fun_type ==
                            having.aggr_fun_type)

                    {
                        offset = i;
                        return true;
                    }
                }

                return false;
            }
            //END: add by tangchao at 20140106

            const bool try_fetch_group_item_from_order_by_items(
                    const vector<OrderItem> &order_items, const GroupItem &group_item)
            {
                for (uint32_t i = 0; i< order_items.size(); i++)
                {
                    if ((order_items[i].order_column_ == group_item.group_column_)
                        &&(order_items[i].order_type_ == group_item.group_type_)
                        &&(order_items[i].column_type_== group_item.column_type_))
                    {
                        return true;
                    }
                }

                return false;
            }

            
            const bool is_group_by_order_by_same(ResultPlan& result_plan)
            {
                const vector<GroupItem> &group_items = get_all_group_items();
                const vector<OrderItem> &order_items = get_all_order_items();
                
                if (group_items.size() == order_items.size())
                {
                    for (uint32_t i=0; i< group_items.size(); i++)
                    {
                        if (!try_fetch_group_item_from_order_by_items(order_items, group_items.at(i)))
                        {
                            return false;
                        }
                    }
                    return true;
                }

                return false;
            }
            //END: Added by qinbo

            const OrderItem& get_order_item(uint32_t index)
            {
                OB_ASSERT(0 <= index && index < order_items_.size());
                return order_items_[index];
            }

            uint64_t get_group_expr_id(uint32_t index)
            {
                OB_ASSERT(0 <= index && index < group_expr_ids_.size());
                return group_expr_ids_[index];
            }

            uint64_t get_agg_expr_id(uint32_t index)
            {
                OB_ASSERT(0 <= index && index < agg_func_ids_.size());
                return agg_func_ids_[index];
            }

            uint64_t get_having_expr_id(uint32_t index)
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
                    if (!is_joined)
                    {
                        if (NULL != ObStmt::get_table_item_by_id(tid))
                        {
                            item.table_name_ = ObStmt::get_table_item_by_id(tid)->table_name_;
                        }
                    }
                    from_items_.push_back(item);
                    return common::OB_SUCCESS;
                }
                else
                {
                    ret = JD_ERR_ILLEGAL_ID;
                }
                return ret;
            }

            //BEGIN: added by qinbo
            bool is_from_item_with_join()
            {
                for (uint32_t i = 0; i < from_items_.size(); i++)
                {
                    FromItem& item = from_items_[i];
                    if (item.is_joined_)
                    {
                        return true;
                    }
                }
                return false;
            }

            int add_group_item(GroupItem& group_item)
            {
                group_items_.push_back(group_item);
                return common::OB_SUCCESS;
            }

            int add_having_item(HavingItem& having_item)
            {
                having_items_.push_back(having_item);
                return common::OB_SUCCESS;
            }

            const vector<SelectItem> &get_all_select_items()
            {
                return select_items_;
            }

            const vector<GroupItem> &get_all_group_items()
            {
                return group_items_;
            }
            
            const vector<OrderItem> &get_all_order_items()
            {
                return order_items_;
            }
            
            const vector<HavingItem> &get_all_having_items()
            {
                return having_items_;
            }
            
            const vector<FromItem> &get_all_from_items()
            {
                return from_items_;
            }

            const LimitItem& get_limit_item()
            {
                return limit_item_;
            }

            bool is_sys_func_query()
            {
                return is_sys_func_query_;
            }

            void set_sys_func_query(bool is_sys_func_query)
            {
                is_sys_func_query_ = is_sys_func_query;
            }
            //END: added by qinbo

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

            int set_limit_offset(ResultPlan * result_plan, const uint64_t& offset, const uint64_t& count);

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
                    ResultPlan * result_plan,
                    uint64_t eid,
                    bool is_real_alias,
                    const string& alias_name,
                    const string& expr_name,
                    const common::ObObjType& type);

            int copy_select_items(ObSelectStmt* select_stmt);
            void print(FILE* fp, int32_t level, int32_t index = 0);

            int64_t make_stmt_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, vector<schema_shard*> &shard_info,string &assembled_sql);
            int64_t make_select_item_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t append_select_items_reduce_used(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_from_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_where_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_group_by_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_order_by_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_having_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t make_limit_string(ResultPlan& result_plan, string &assembled_sql);
            int64_t get_column_info_by_expr_id(
                                ResultPlan *result_plan,
                                uint64_t expr_id,
                                ObObjType &column_type,
                                SqlItemType &aggr_fun_type,
                                string& column_name);
            int64_t get_having_column_by_expr_id( 
                                ResultPlan *result_plan,
                                uint64_t expr_id,
                                ObObjType &column_type,
                                SqlItemType &aggr_fun_type,
                                uint32_t    &aggr_fun_operate,
                                double      &aggr_fun_value,
                                string      &column_name);
            
            void set_sql_dispatched_multi_shards(bool is_dispatched)
            {
                is_sql_relate_multi_shards = is_dispatched;
            }
            bool is_sql_dispatched_multi_shards()
            {
                return is_sql_relate_multi_shards;
            }
            bool is_join_tables_binded(ResultPlan& result_plan, ObSelectStmt *select_stmt, string& first_join_table);
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

            /**************************************************
            Funtion     :   decompose_join_on_items
            Author      :   qinbo
            Date        :   2013.9.24
            Description :   generate distributed where conditions items
            Input       :   ObRawExpr* sql_expr
            Output      :   vector<vector<ObRawExpr*> > &atomic_exprs_array
            return      :   
             **************************************************/
            int decompose_join_on_items(ObRawExpr* sql_expr, vector<vector<ObRawExpr*> > &atomic_exprs_array);
            void set_has_avg_in_having(bool has_avg_in_having_ )
            {
                has_avg_in_having = has_avg_in_having_;
            }
            bool is_has_avg_in_having()
            {
                return has_avg_in_having;
            }
            int append_avg_content(ResultPlan& result_plan, ObSqlRawExpr* sql_expr, SelectItem& item, string &assembled_sql);
            
        private:
            // These fields are only used by normal select
            bool is_distinct_;
            vector<SelectItem> select_items_;
            vector<FromItem> from_items_;
            vector<JoinedTable*> joined_tables_;
            LimitItem        limit_item_;
            vector<uint64_t> group_expr_ids_;
            vector<uint64_t> having_expr_ids_;
            vector<uint64_t> agg_func_ids_;

            // These fields are only used by set select
            SetOperator set_op_;
            bool is_set_distinct_;
            uint64_t left_query_id_;
            uint64_t right_query_id_;

            // These fields are used by both normal select and set select
            vector<GroupItem> group_items_;
            vector<OrderItem> order_items_;
            vector<HavingItem> having_items_;

            // -1 means no limit
            uint64_t limit_count_id_;
            uint64_t limit_offset_id_;

            // FOR UPDATE clause
            bool for_update_;

            uint64_t gen_joined_tid_;

            // this sql is exec on multi shard(>1)
            bool is_sql_relate_multi_shards;
            bool is_sys_func_query_;
            bool has_avg_in_having;
        };
    }
}

#endif //SQL_SELECTSTMT_H_
