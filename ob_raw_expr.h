#ifndef OCEANBASE_SQL_RAWEXPR_H_
#define OCEANBASE_SQL_RAWEXPR_H_

//#include "common/ob_vector.h"
#include <string>
//#include "common/ob_string_buf.h"
#include <vector>
//#include "ob_bit_set.h"
#include "ob_obj_type.h"
//#include "ob_sql_expression.h"
#include "ob_define.h"
#include "sql_item_type.h"
#include "ob_object.h"
#include "utility.h"
#include "parse_node.h"

using namespace oceanbase::common;


namespace oceanbase
{
    namespace sql
    {
        //class ObTransformer;
        //class ObLogicalPlan;
        //class ObPhysicalPlan;

        class ObRawExpr
        {
        public:

            explicit ObRawExpr(SqlItemType expr_type = T_INVALID)
            : type_(expr_type)
            {
                result_type_ = ObMinType;
            }

            virtual ~ObRawExpr()
            {
            }
            //virtual void trace(FILE *stream, int indentNum = 0);

            const SqlItemType get_expr_type() const
            {
                return type_;
            }

            const common::ObObjType & get_result_type() const
            {
                return result_type_;
            }

            void set_expr_type(SqlItemType type)
            {
                type_ = type;
            }

            void set_result_type(const common::ObObjType & type)
            {
                result_type_ = type;
            }

            bool is_const() const;
            bool is_column() const;
            /**************************************************
            Funtion     :   is_or_expr
            Author      :   qinbo
            Date        :   2013.9.25
            Description :   this expr is linked by OR
            Input       :   
            Output      :   
             **************************************************/
            bool is_or_expr() const;

            /**************************************************
            Funtion     :   is_and_expr
            Author      :   qinbo
            Date        :   2013.9.25
            Description :   this expr is linked by AND
            Input       :   
            Output      :   
             **************************************************/
            bool is_and_expr() const;

            /**************************************************
            Funtion     :   is_column_and_sharding_key
            Author      :   qinbo
            Date        :   2013.9.25
            Description :   this expr is sharding column
            Input       :   
            Output      :   
             **************************************************/
            bool is_column_and_sharding_key() const;

            /**************************************************
            Funtion     :   get_table_name_in_sharding_column
            Author      :   qinbo
            Date        :   2013.10.29
            Description :   get expr's related table name
            Input       :   
            Output      :   
             **************************************************/
            bool get_table_name_in_sharding_column(string &table_name) const;

            /**************************************************
            Funtion     :   get_column_and_sharding_key
            Author      :   qinbo
            Date        :   2013.9.25
            Description :   get this expr's column name when this is sharding column
            Input       :   
            Output      :   
             **************************************************/
            bool get_column_and_sharding_key(string &column_name) const;

            /**************************************************
            Funtion     :   is_contain_filter
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   is T_OP_IN/T_OP_NOT_IN or not
            Input       :   
            Output      :   
             **************************************************/
            // Format like "C1 IN "5, 6,7"
            bool is_contain_filter() const;

            /**************************************************
            Funtion     :   is_contain_filter_need_route
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   this expr is need to get route or not
            Input       :   
            Output      :   
             **************************************************/
            // Format like "C1 IN "5, 6,7"
            bool is_contain_filter_need_route() const;


            /**************************************************
            Funtion     :   is_need_to_get_route
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   this expr is need to get route or not
            Input       :   
            Output      :   
             **************************************************/
            bool is_need_to_get_route() const;
            // Format like "C1 = 5"
            bool is_equal_filter() const;

            /**************************************************
            Funtion     :   is_equal_filter_need_route
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   this expr is need to get route or not
            Input       :   
            Output      :   
             **************************************************/
            // Format like "C1 IN "5, 6,7"
            bool is_equal_filter_need_route() const;

            // Format like "C1 between 5 and 10"
            bool is_range_filter() const;

            /**************************************************
            Funtion     :   is_range_filter_need_route
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   this expr is need to get route or not
            Input       :   
            Output      :   
             **************************************************/
            // Format like "C1 IN "5, 6,7"
            bool is_range_filter_need_route() const;


            // Only format like "T1.c1 = T2.c1", not "T1.c1 - T2.c1 = 0"
            bool is_join_cond() const;
            bool is_aggr_fun() const;

            /**************************************************
            Funtion     :   set_db_name
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   store current db name
            Input       :   
            Output      :   
             **************************************************/
            void set_db_name(string db_name);

            /**************************************************
            Funtion     :   get_db_name
            Author      :   qinbo
            Date        :   2013.9.11
            Description :   get current db name
            Input       :   
            Output      :   
             **************************************************/
            string get_db_name() const;

            /**************************************************
            Funtion     :   try_get_table_name
            Author      :   qinbo
            Date        :   2013.10.29
            Description :   try get table name
            Input       :   
            Output      :   
             **************************************************/
            bool try_get_table_name(string &table_name) const;
            
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            /**************************************************
            Funtion     :   convert_ob_expr_to_route
            Author      :   qinbo
            Date        :   2013.10.14
            Description :   convert ob style expr to route used key relation
            Input       :   key_data& key_relation
            Output      :   
             **************************************************/
            bool convert_ob_expr_to_route(key_data& key_relation) const;
            virtual void print(FILE* fp, int32_t level) const = 0;
            /*added by qinbo*/
            virtual int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const = 0;

        private:
            SqlItemType type_;
            common::ObObjType result_type_;
            string current_db_name; //added by qinbo, store current db name
        };

        class ObConstRawExpr : public ObRawExpr
        {
        public:

            ObConstRawExpr()
            {
            }

            ObConstRawExpr(oceanbase::common::ObObj& val, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), value_(val)
            {
            }

            virtual ~ObConstRawExpr()
            {
            }

            const oceanbase::common::ObObj& get_value() const
            {
                return value_;
            }

            void set_value(const oceanbase::common::ObObj& val)
            {
                value_ = val;
            }
            int set_value_and_type(const common::ObObj& val);
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;
            /**************************************************
            Funtion     :   get_ob_const_expr_to_key_data
            Author      :   qinbo
            Date        :   2013.10.14
            Description :   get const expr value
            Input       :   ObConstRawExpr *const_expr
                            key_data& key_relation
                            uint32_t seq
            Output      :   
             **************************************************/
            void get_ob_const_expr_to_key_data(key_data& key_relation,
                    uint32_t seq) const;
        private:
            oceanbase::common::ObObj value_;
        };

        class ObUnaryRefRawExpr : public ObRawExpr
        {
        public:

            ObUnaryRefRawExpr()
            {
                id_ = OB_INVALID_ID;
            }

            ObUnaryRefRawExpr(uint64_t id, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), id_(id)
            {
            }

            virtual ~ObUnaryRefRawExpr()
            {
            }

            uint64_t get_ref_id() const
            {
                return id_;
            }

            void set_ref_id(uint64_t id)
            {
                id_ = id;
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

            int get_name(string& name) const;

        private:
            uint64_t id_;
        };

        class ObBinaryRefRawExpr : public ObRawExpr
        {
        public:

            ObBinaryRefRawExpr()
            {
                first_id_ = OB_INVALID_ID;
                second_id_ = OB_INVALID_ID;
                related_sql_raw_id = OB_INVALID_ID;
                is_op_name_field = false;
            }

            ObBinaryRefRawExpr(uint64_t first_id, uint64_t second_id, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), first_id_(first_id), second_id_(second_id)
            {
            }

            virtual ~ObBinaryRefRawExpr()
            {
            }

            uint64_t get_first_ref_id() const
            {
                return first_id_;
            }

            uint64_t get_second_ref_id() const
            {
                return second_id_;
            }

            void set_first_ref_id(uint64_t id)
            {
                first_id_ = id;
            }

            void set_second_ref_id(uint64_t id)
            {
                second_id_ = id;
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

            void set_op_name_field()
            {
                is_op_name_field = true;
            }

            bool get_op_name_field()
            {
                return is_op_name_field;
            }

            void set_related_sql_raw_id(uint64_t sql_raw_id)
            {
                related_sql_raw_id = sql_raw_id;
            }

            uint64_t get_related_sql_raw_id()
            {
                return related_sql_raw_id;
            }
        private:
            uint64_t first_id_;
            uint64_t second_id_;
            uint64_t related_sql_raw_id;
            bool is_op_name_field;
        };

        class ObUnaryOpRawExpr : public ObRawExpr
        {
        public:

            ObUnaryOpRawExpr()
            {
                expr_ = NULL;
            }

            ObUnaryOpRawExpr(ObRawExpr *expr, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), expr_(expr)
            {
            }

            virtual ~ObUnaryOpRawExpr()
            {
            }

            ObRawExpr* get_op_expr() const
            {
                return expr_;
            }

            void set_op_expr(ObRawExpr *expr)
            {
                expr_ = expr;
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

        private:
            ObRawExpr *expr_;
        };

        class ObBinaryOpRawExpr : public ObRawExpr
        {
        public:

            ObBinaryOpRawExpr()
            {
            }

            ObBinaryOpRawExpr(
                    ObRawExpr *first_expr, ObRawExpr *second_expr, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), first_expr_(first_expr), second_expr_(second_expr)
            {
            }

            virtual ~ObBinaryOpRawExpr()
            {
            }

            ObRawExpr* get_first_op_expr() const
            {
                return first_expr_;
            }

            ObRawExpr* get_second_op_expr() const
            {
                return second_expr_;
            }
            void set_op_exprs(ObRawExpr *first_expr, ObRawExpr *second_expr);
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

        private:
            ObRawExpr *first_expr_;
            ObRawExpr *second_expr_;
        };

        class ObTripleOpRawExpr : public ObRawExpr
        {
        public:

            ObTripleOpRawExpr()
            {
                first_expr_ = NULL;
                second_expr_ = NULL;
                third_expr_ = NULL;
            }

            ObTripleOpRawExpr(
                    ObRawExpr *first_expr, ObRawExpr *second_expr,
                    ObRawExpr *third_expr, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type),
            first_expr_(first_expr), second_expr_(second_expr),
            third_expr_(third_expr)
            {
            }

            virtual ~ObTripleOpRawExpr()
            {
            }

            ObRawExpr* get_first_op_expr() const
            {
                return first_expr_;
            }

            ObRawExpr* get_second_op_expr() const
            {
                return second_expr_;
            }

            ObRawExpr* get_third_op_expr() const
            {
                return third_expr_;
            }
            void set_op_exprs(ObRawExpr *first_expr, ObRawExpr *second_expr, ObRawExpr *third_expr);
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

        private:
            ObRawExpr *first_expr_;
            ObRawExpr *second_expr_;
            ObRawExpr *third_expr_;
        };

        class ObMultiOpRawExpr : public ObRawExpr
        {
        public:

            ObMultiOpRawExpr()
            {
            }

            virtual ~ObMultiOpRawExpr()
            {
            }

            ObRawExpr* get_op_expr(int32_t index) const
            {
                ObRawExpr* expr = NULL;
                if (index >= 0 && index < exprs_.size())
                    expr = exprs_.at(index);
                return expr;
            }

            int add_op_expr(ObRawExpr *expr)
            {
                exprs_.push_back(expr);
                return OB_SUCCESS;
            }

            int32_t get_expr_size() const
            {
                return exprs_.size();
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

        private:
            vector<ObRawExpr*> exprs_;
        };

#if 0

        class ObCaseOpRawExpr : public ObRawExpr
        {
        public:

            ObCaseOpRawExpr()
            {
                arg_expr_ = NULL;
                default_expr_ = NULL;
            }

            virtual ~ObCaseOpRawExpr()
            {
            }

            ObRawExpr* get_arg_op_expr() const
            {
                return arg_expr_;
            }

            ObRawExpr* get_default_op_expr() const
            {
                return default_expr_;
            }

            ObRawExpr* get_when_op_expr(int32_t index) const
            {
                ObRawExpr* expr = NULL;
                if (index >= 0 && index < when_exprs_.size())
                    expr = when_exprs_[index];
                return expr;
            }

            ObRawExpr* get_then_op_expr(int32_t index) const
            {
                ObRawExpr* expr = NULL;
                if (index >= 0 || index < then_exprs_.size())
                    expr = then_exprs_[index];
                return expr;
            }

            void set_arg_op_expr(ObRawExpr *expr)
            {
                arg_expr_ = expr;
            }

            void set_default_op_expr(ObRawExpr *expr)
            {
                default_expr_ = expr;
            }

            int add_when_op_expr(ObRawExpr *expr)
            {
                when_exprs_.push_back(expr);
                return OB_SUCCESS;
            }

            int add_then_op_expr(ObRawExpr *expr)
            {
                then_exprs_.push_back(expr);
                return OB_SUCCESS;
            }

            int32_t get_when_expr_size() const
            {
                return when_exprs_.size();
            }

            int32_t get_then_expr_size() const
            {
                return then_exprs_.size();
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;

        private:
            ObRawExpr *arg_expr_;
            vector<ObRawExpr*> when_exprs_;
            vector<ObRawExpr*> then_exprs_;
            ObRawExpr *default_expr_;
        };
#endif

        class ObAggFunRawExpr : public ObRawExpr
        {
        public:

            ObAggFunRawExpr()
            {
                param_expr_ = NULL;
                distinct_ = false;
            }

            ObAggFunRawExpr(ObRawExpr *param_expr, bool is_distinct, SqlItemType expr_type = T_INVALID)
            : ObRawExpr(expr_type), param_expr_(param_expr), distinct_(is_distinct)
            {
            }

            virtual ~ObAggFunRawExpr()
            {
            }

            ObRawExpr* get_param_expr() const
            {
                return param_expr_;
            }

            void set_param_expr(ObRawExpr *expr)
            {
                param_expr_ = expr;
            }

            bool is_param_distinct() const
            {
                return distinct_;
            }

            void set_param_distinct()
            {
                distinct_ = true;
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;
            /*added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;

        private:
            // NULL means '*'
            ObRawExpr* param_expr_;
            bool distinct_;
        };

#if 0

        class ObSysFunRawExpr : public ObRawExpr
        {
        public:

            ObSysFunRawExpr()
            {
            }

            virtual ~ObSysFunRawExpr()
            {
            }

            ObRawExpr* get_param_expr(int32_t index) const
            {
                ObRawExpr* expr = NULL;
                if (index >= 0 || index < exprs_.size())
                    expr = exprs_[index];
                return expr;
            }

            int add_param_expr(ObRawExpr *expr)
            {
                exprs_.push_back(expr);
                return OB_SUCCESS;
            }

            void set_func_name(const string& name)
            {
                func_name_ = name;
            }

            const string& get_func_name()
            {
                return func_name_;
            }

            int32_t get_param_size() const
            {
                return exprs_.size();
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level) const;

        private:
            string func_name_;
            vector<ObRawExpr*> exprs_;
        };
#endif

        class ObSqlRawExpr
        {
        public:
            ObSqlRawExpr();
            ObSqlRawExpr(
                    uint64_t expr_id,
                    uint64_t table_id = oceanbase::common::OB_INVALID_ID,
                    uint64_t column_id = oceanbase::common::OB_INVALID_ID,
                    ObRawExpr* expr = NULL);

            virtual ~ObSqlRawExpr()
            {
            }

            uint64_t get_expr_id() const
            {
                return expr_id_;
            }

            uint64_t get_column_id() const
            {
                return column_id_;
            }

            uint64_t get_table_id() const
            {
                return table_id_;
            }

            void set_expr_id(uint64_t expr_id)
            {
                expr_id_ = expr_id;
            }

            void set_column_id(uint64_t column_id)
            {
                column_id_ = column_id;
            }

            void set_table_id(uint64_t table_id)
            {
                table_id_ = table_id;
            }

            void set_expr(ObRawExpr* expr)
            {
                expr_ = expr;
            }
            //void set_tables_set(const common::ObBitSet<> tables_set) { tables_set_ = tables_set; }

            void set_applied(bool is_applied)
            {
                is_apply_ = is_applied;
            }

            void set_contain_aggr(bool contain_aggr)
            {
                contain_aggr_ = contain_aggr;
            }

            void set_contain_alias(bool contain_alias)
            {
                contain_alias_ = contain_alias;
            }

            void set_columnlized(bool is_columnlized)
            {
                is_columnlized_ = is_columnlized;
            }

            /*BEGIN: added by qinbo*/
            void set_contain_aggr_type(SqlItemType aggr_type)
            {
                contain_aggr_type_ = aggr_type;
            }

            SqlItemType get_contain_aggr_type()
            {
                return contain_aggr_type_;
            }

            /*END: added by qinbo*/
            bool is_apply() const
            {
                return is_apply_;
            }

            bool is_contain_aggr() const
            {
                return contain_aggr_;
            }

            bool is_contain_alias() const
            {
                return contain_alias_;
            }

            bool is_columnlized() const
            {
                return is_columnlized_;
            }

            ObRawExpr* get_expr() const
            {
                return expr_;
            }
            //const common::ObBitSet<>& get_tables_set() const { return tables_set_; }
            //common::ObBitSet<>& get_tables_set() { return tables_set_; }

            const common::ObObjType get_result_type() const
            {
                return expr_->get_result_type();
            }
            /*virtual int fill_sql_expression(
                ObSqlExpression& inter_expr,
                ObTransformer *transformer = NULL,
                ObLogicalPlan *logical_plan = NULL,
                ObPhysicalPlan *physical_plan = NULL) const = 0;*//*deleted by qinbo*/
            void print(FILE* fp, int32_t level, int32_t index = 0) const;
            /*BEGIN: added by qinbo*/
            int64_t to_string(ResultPlan& result_plan, string& assembled_sql) const;
            /*END: added by qinbo*/
        private:
            uint64_t expr_id_;
            uint64_t table_id_;
            uint64_t column_id_;
            SqlItemType contain_aggr_type_;
            bool is_apply_;
            bool contain_aggr_;
            bool contain_alias_;
            bool is_columnlized_;

            //common::ObBitSet<>  tables_set_;
            ObRawExpr* expr_;
        };
    }

}

#endif //OCEANBASE_SQL_RAWEXPR_H_
