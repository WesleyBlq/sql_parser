#include "dml_build_plan.h"
#include "sql_raw_expr.h"
#include "sql_select_stmt.h"
#include "sql_insert_stmt.h"
#include "sql_delete_stmt.h"
#include "sql_update_stmt.h"
#include "sql_logical_plan.h"
#include "parse_malloc.h"
#include <vector>
#include "utility.h"
#include <stdint.h>
#include "ob_obj_type.h"
#include "ob_expr_obj.h"

using namespace jdbd::common;
using namespace jdbd::sql;
using namespace std;


int resolve_expr(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node,
        ObSqlRawExpr *sql_expr,
        ObRawExpr*& expr,
        int32_t expr_scope_type = T_NONE_LIMIT,
        bool sub_query_results_scalar = true);
int resolve_agg_func(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node,
        ObSqlRawExpr*& ret_sql_expr,
        int32_t expr_scope_type);
int resolve_joined_table(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node,
        JoinedTable& joined_table);
int resolve_from_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_star(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_select_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_where_clause(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node);
int resolve_group_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_having_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_order_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_limit_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_for_update_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node);
int resolve_insert_columns(
        ResultPlan * result_plan,
        ObInsertStmt* insert_stmt,
        ParseNode* node);
int resolve_insert_values(
        ResultPlan * result_plan,
        ObInsertStmt* insert_stmt,
        ParseNode* node);
int resolve_hints(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node);


static bool int_value_check(const char *str, uint length)
{
    bool neg=0;

    if (*str == '+')
    {
        str++;
        length--;
    }
    else if (*str == '-')
    {
        neg=1;
    }

    if (neg)
    {
        if (length < SIGNED_UINT64_MIN_LEN)
        {
            return true;
        }
        else if (length > SIGNED_UINT64_MIN_LEN)
        {
            return false;
        } 
        else if (strcmp(str, SIGNED_UINT64_MIN_STR) > 0)
        {
            return false;
        }
    } 
    else
    {
        if (length < SIGNED_UINT64_MAX_LEN)
        {
            return true;
        }
        else if (length > SIGNED_UINT64_MAX_LEN)
        {
            return false;
        } 
        else if (strcmp(str, SIGNED_UINT64_MAX_STR) > 0)
        {
            return false;
        }
    }
    return true;
}


static int add_all_rowkey_columns_to_stmt(ResultPlan* result_plan, uint64_t table_id, ObStmt *stmt)
{
    return OB_SUCCESS;
}

int resolve_independ_expr(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node,
        uint64_t& expr_id,
        int32_t expr_scope_type)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        ObRawExpr* expr = NULL;
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        ObSqlRawExpr* sql_expr = (ObSqlRawExpr*) parse_malloc(sizeof (ObSqlRawExpr), NULL);
        if (sql_expr == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc space for ObSqlRawExpr");
        }
        if (ret == OB_SUCCESS)
        {
            sql_expr = new(sql_expr) ObSqlRawExpr();
            ret = logical_plan->add_expr(sql_expr);
            if (ret != OB_SUCCESS)
                jlog(WARNING, "Add ObSqlRawExpr error");
        }
        if (ret == OB_SUCCESS)
        {
            expr_id = logical_plan->generate_expr_id();
            sql_expr->set_expr_id(expr_id);
            ret = resolve_expr(result_plan, stmt, node, sql_expr, expr, expr_scope_type);
        }
        if (ret == OB_SUCCESS)
        {
            if (expr->get_expr_type() == T_REF_COLUMN)
            {
                ObBinaryRefRawExpr *col_expr = dynamic_cast<ObBinaryRefRawExpr*> (expr);
                sql_expr->set_table_id(col_expr->get_first_ref_id());
                sql_expr->set_column_id(col_expr->get_second_ref_id());
            }
            else
            {
                sql_expr->set_table_id(OB_INVALID_ID);
                sql_expr->set_column_id(logical_plan->generate_column_id());
            }
            sql_expr->set_expr(expr);
            //sql_expr->print(stderr, 0, 0);
        }
    }
    return ret;
}

int resolve_and_exprs(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node,
        vector<uint64_t>& and_exprs,
        int32_t expr_scope_type)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        /*BEGIN:Modified by qinbo, No matter OP is AND or not,  left and right expr is both uniquely stored*/
        /*when OP is AND, left and right expr is both uniquely stored, else stored as whole*/
        //if (node->type_ != T_OP_AND)
        {
            uint64_t expr_id = OB_INVALID_ID;
            ret = resolve_independ_expr(result_plan, stmt, node, expr_id, expr_scope_type);
            if (ret == OB_SUCCESS)
            {
                and_exprs.push_back(expr_id);
            }
        }
#if 0 /*deleted by qinbo*/
        else
        {
            ret = resolve_and_exprs(result_plan, stmt, node->children_[0], and_exprs, expr_scope_type);
            if (ret == OB_SUCCESS)
                ret = resolve_and_exprs(result_plan, stmt, node->children_[1], and_exprs, expr_scope_type);
        }
#endif
        /*END:Modified by qinbo, No matter OP is AND or not,  left and right expr is both uniquely stored*/
    }
    return ret;
}

#define CREATE_RAW_EXPR(expr, type_name, result_plan)    \
({    \
  ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan->plan_tree_); \
  expr = (type_name*)parse_malloc(sizeof(type_name), NULL);   \
  if (expr != NULL) \
  { \
    expr = new(expr) type_name();   \
    if (OB_SUCCESS != logical_plan->add_raw_expr(expr))    \
    { \
      expr = NULL;  /* no memory leak, bulk dealloc */ \
    } \
  } \
  if (expr == NULL)  \
  { \
    result_plan->err_stat_.err_code_ = JD_ERR_PARSER_MALLOC_FAILED; \
    jlog(WARNING, "Fail to malloc new raw expression"); \
  } \
  expr; \
})


int resolve_expr(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node,
        ObSqlRawExpr *sql_expr,
        ObRawExpr*& expr,
        int32_t expr_scope_type,
        bool sub_query_results_scalar)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    expr = NULL;
    if (node == NULL)
        return ret;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    //stringBuf* name_pool = static_cast<stringBuf*>(result_plan->name_pool_);

    switch (node->type_)
    {
        case T_BINARY:
        {
            string str;
            string str_val;
            str_val.assign(const_cast<char*> (node->str_value_), static_cast<int32_t> (node->value_));
            str = str_val;
            ObObj val;
            val.set_varchar(str);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(node->type_);
            c_expr->set_result_type(ObVarcharType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_STRING:
        case T_SYSTEM_VARIABLE:
        case T_TEMP_VARIABLE:
        {
            string str = make_string(node->str_value_);
            ObObj val;
            val.set_varchar(str);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(node->type_);
            c_expr->set_result_type(ObVarcharType);
            c_expr->set_value(val);
            expr = c_expr;
            if (node->type_ == T_TEMP_VARIABLE)
            {
                jlog(WARNING, "resolve tmp variable, name=%.*s", (int)str.size(), str.data());
            }
            break;
        }
        case T_FLOAT:
        {
            ObObj val;
            val.set_float(static_cast<float> (atof(node->str_value_)));
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_FLOAT);
            c_expr->set_result_type(ObFloatType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_DOUBLE:
        {
            ObObj val;
            val.set_double(atof(node->str_value_));
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_DOUBLE);
            c_expr->set_result_type(ObDoubleType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_DECIMAL: // set as string
        {
            string str = make_string(node->str_value_);
            ObObj val;
            val.set_varchar(str);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_DECIMAL);
            c_expr->set_result_type(ObDecimalType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_INT:
        {
            if ((sub_query_results_scalar)&&(!int_value_check(node->str_value_, strlen(node->str_value_))))
            {
                ret = JD_ERR_INT_VALUE_EXCEED_MAX_LIMIT;
                break;
            }
            ObObj val;
            val.set_int(node->value_);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_INT);
            c_expr->set_result_type(ObIntType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_BOOL:
        {
            ObObj val;
            val.set_bool(node->value_ == 1 ? true : false);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_BOOL);
            c_expr->set_result_type(ObBoolType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_DATE:
        {
            ObObj val;
            val.set_precise_datetime(node->value_);
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_DATE);
            c_expr->set_result_type(ObPreciseDateTimeType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_NULL:
        {
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_NULL);
            c_expr->set_result_type(ObNullType);
            expr = c_expr;
            break;
        }
        case T_QUESTIONMARK:
        {
            ObObj val;
            val.set_int(logical_plan->inc_question_mark());
            ObConstRawExpr *c_expr = NULL;
            if (CREATE_RAW_EXPR(c_expr, ObConstRawExpr, result_plan) == NULL)
                break;
            c_expr->set_expr_type(T_QUESTIONMARK);
            c_expr->set_result_type(ObIntType);
            c_expr->set_value(val);
            expr = c_expr;
            break;
        }
        case T_OP_NAME_FIELD:
        {
            OB_ASSERT(node->children_[0]->type_ == T_IDENT);
            // star has been expand before
            // T_IDENT.* can't has alias name here, which is illeagal
            if (node->children_[1]->type_ != T_IDENT)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "%s.* is illeagal", node->children_[0]->str_value_);
                break;
            }

            const char* table_str = node->children_[0]->str_value_;
            const char* column_str = node->children_[1]->str_value_;
            if (expr_scope_type == T_INSERT_LIMIT)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Illegal usage %s.%s", table_str, column_str);
                break;
            }

            string table_name;
            string column_name;
            table_name.assign((char*) table_str, static_cast<int32_t> (strlen(table_str)));
            column_name.assign((char*) column_str, static_cast<int32_t> (strlen(column_str)));
            
            // Column name with table name, it can't be alias name, so we don't need to check select item list
            if (expr_scope_type == T_HAVING_LIMIT)
            {
                OB_ASSERT(stmt->get_stmt_type() == ObStmt::T_SELECT);
                ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                TableItem* table_item;
                if ((select_stmt->get_table_item(table_name, &table_item)) == OB_INVALID_ID)
                {
                    ret = JD_ERR_TABLE_UNKNOWN;
                    jlog(WARNING, "Unknown table %s in having clause");
                    break;
                }
                ret = select_stmt->check_having_ident(*result_plan, column_name, table_item, expr);
                // table_set is of no use in having clause, because all tables have been joined to one table
                // when having condition is calculated
                //sql_expr->get_tables_set().add_member(select_stmt->get_table_bit_index(table_item->table_id_));
            }
            else
            {
                OB_ASSERT(stmt->get_stmt_type() == ObStmt::T_SELECT);
                ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                TableItem* table_item;
                ColumnItem *column_item = stmt->get_column_item(&table_name, column_name);
                if (!column_item)
                {
                    ret = stmt->add_column_item(*result_plan, column_name, &table_name, &column_item);
                    if (ret != OB_SUCCESS)
                    {
                        break;
                    }
                }
                ObBinaryRefRawExpr *b_expr = NULL;
                if (CREATE_RAW_EXPR(b_expr, ObBinaryRefRawExpr, result_plan) == NULL)
                    break;

                //BEGIN: added by qinbo
                if ((select_stmt->get_table_item(table_name, &table_item)) == OB_INVALID_ID)
                {
                    ret = JD_ERR_TABLE_UNKNOWN;
                    jlog(WARNING, "Unknown table %s in having clause");
                    break;
                }
                
                if (table_item->type_ == TableItem::ALIAS_TABLE)
                {
                    b_expr->set_alias_table_name(table_item->alias_name_);
                }
                else
                {
                    table_item->need_display_table_name = true;
                }
                //END: added by qinbo
                
                b_expr->set_expr_type(T_REF_COLUMN);
                b_expr->set_result_type(column_item->data_type_);
                b_expr->set_first_ref_id(column_item->table_id_);
                b_expr->set_second_ref_id(column_item->column_id_);
                b_expr->set_op_name_field(); //added by qinbo
                expr = b_expr;
                //sql_expr->get_tables_set().add_member(stmt->get_table_bit_index(column_item->table_id_));
            }
            break;
        }
        case T_IDENT:
        {
            if (expr_scope_type == T_INSERT_LIMIT)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Unknown value %s", node->str_value_);
                break;
            }
            else if (expr_scope_type == T_VARIABLE_VALUE_LIMIT)
            {
                /* TBD */
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Unknown value %s", node->str_value_);
                break;
            }

            string column_name;
            column_name.assign(
                    (char*) (node->str_value_),
                    static_cast<int32_t> (strlen(node->str_value_))
                    );

            if (expr_scope_type == T_HAVING_LIMIT)
            {
                OB_ASSERT(stmt->get_stmt_type() == ObStmt::T_SELECT);
                ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                ret = select_stmt->check_having_ident(*result_plan, column_name, NULL, expr);
                // table_set is of no use in having clause, because all tables have been joined to one table
                // when having condition is calculated
                // sql_expr->get_tables_set().add_member(select_stmt->get_table_bit_index(table_item->table_id_));
            }
            else
            {
                // the checking rule is follow mysql, although not reasonable
                // 1. select user_id user_id, item_id user_id from order_list where user_id>0;
                //     syntax correct, you can try
                // 2. select item_id as user_id, user_id from order_list  where user_id>0;
                //     real order_list.user_id is used, so real column first.
                // 3. select item_id as user_id from order_list  where user_id>0;
                //     real order_list.user_id is used, so real column first.
                if (expr == NULL)
                {
                    ColumnItem *column_item = stmt->get_column_item(NULL, column_name);
                    if (column_item)
                    {
                        ObBinaryRefRawExpr *b_expr = NULL;
                        if (CREATE_RAW_EXPR(b_expr, ObBinaryRefRawExpr, result_plan) == NULL)
                            break;
                        b_expr->set_expr_type(T_REF_COLUMN);
                        b_expr->set_result_type(column_item->data_type_);
                        b_expr->set_first_ref_id(column_item->table_id_);
                        b_expr->set_second_ref_id(column_item->column_id_);
                        expr = b_expr;
                        //sql_expr->get_tables_set().add_member(stmt->get_table_bit_index(column_item->table_id_));
                    }
                }
                if (expr == NULL)
                {
                    ColumnItem *column_item = NULL;
                    ret = stmt->add_column_item(*result_plan, column_name, NULL, &column_item);
                    if (ret == OB_SUCCESS)
                    {
                        ObBinaryRefRawExpr *b_expr = NULL;
                        if (CREATE_RAW_EXPR(b_expr, ObBinaryRefRawExpr, result_plan) == NULL)
                            break;
                        b_expr->set_expr_type(T_REF_COLUMN);
                        b_expr->set_result_type(column_item->data_type_);
                        b_expr->set_first_ref_id(column_item->table_id_);
                        b_expr->set_second_ref_id(column_item->column_id_);
                        expr = b_expr;
                        //sql_expr->get_tables_set().add_member(stmt->get_table_bit_index(column_item->table_id_));
                    }
                    else if (ret == JD_ERR_COLUMN_UNKNOWN)
                    {
                        ret = OB_SUCCESS;
                    }
                    else
                    {
                        break;
                    }
                }
                if (!expr && stmt->get_stmt_type() == ObStmt::T_SELECT)
                {
                    ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                    uint64_t expr_id = select_stmt->get_alias_expr_id(column_name);
                    
                    if (expr_id != OB_INVALID_ID)
                    {
                        ObSqlRawExpr* alias_expr = logical_plan->get_expr(expr_id);
                        if (alias_expr == NULL)
                        {
                            ret = JD_ERR_ILLEGAL_ID;
                            jlog(WARNING, "Wrong expr_id %lu", expr_id);
                            break;
                        }
                        if (alias_expr->is_contain_aggr()
                                && (expr_scope_type == T_INSERT_LIMIT
                                || expr_scope_type == T_UPDATE_LIMIT
                                || expr_scope_type == T_AGG_LIMIT
                                || expr_scope_type == T_WHERE_LIMIT
                                || expr_scope_type == T_GROUP_LIMIT))
                        {
                            ret = JD_ERR_PARSER_SYNTAX;
                            jlog(WARNING, "Invalid use of alias which contains group function");
                            break;
                        }
                        else
                        {
                            ObBinaryRefRawExpr *b_expr = NULL;
                            if (CREATE_RAW_EXPR(b_expr, ObBinaryRefRawExpr, result_plan) == NULL)
                                break;
                            b_expr->set_expr_type(T_REF_COLUMN);
                            b_expr->set_result_type(alias_expr->get_result_type());
                            b_expr->set_first_ref_id(alias_expr->get_table_id());
                            b_expr->set_second_ref_id(alias_expr->get_column_id());
                            expr = b_expr;
                            sql_expr->set_contain_alias(true);
                        }
                    }
                }
                if (expr == NULL)
                {
                    ret = JD_ERR_COLUMN_UNKNOWN;
                    jlog(WARNING, "Unkown column name %.*s", (int)column_name.size(), column_name.data());
                }
            }
            break;
        }
        case T_OP_EXISTS:
            if (expr_scope_type == T_INSERT_LIMIT || expr_scope_type == T_UPDATE)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "EXISTS expression can not appear in INSERT/UPDATE statement");
                break;
            }
        case T_OP_POS:
        case T_OP_NEG:
        case T_OP_NOT:
        {
            ObRawExpr* sub_expr = NULL;
            bool       is_min_int = false;
            if ((node->type_ == T_OP_NEG)&&(node->children_[0]->type_ == T_INT))
            {
                JD_DEBUG;
                char neg_int[100];
                memset(neg_int, 0, 100);
                neg_int[0] = '-';
                strncpy(neg_int+1, node->children_[0]->str_value_, strlen(node->children_[0]->str_value_));
                
                if (!int_value_check(neg_int, strlen(neg_int)))
                {
                    ret = JD_ERR_INT_VALUE_EXCEED_MIN_LIMIT;
                    break;
                }

                if (strcmp(neg_int, SIGNED_UINT64_MIN_STR) == 0)
                {
                    is_min_int = true;
                }
                ret = resolve_expr(result_plan, stmt, node->children_[0], sql_expr, sub_expr, expr_scope_type, false);
            }
            else
            {
                ret = resolve_expr(result_plan, stmt, node->children_[0], sql_expr, sub_expr, expr_scope_type, true);
            }
            
            if (ret != OB_SUCCESS)
                break;
            // only INT/FLOAT/DOUBLE are in consideration
            if (sub_expr->is_const()
                    && (sub_expr->get_expr_type() == T_INT
                    || sub_expr->get_expr_type() == T_FLOAT
                    || sub_expr->get_expr_type() == T_DOUBLE))
            {
                ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr*> (sub_expr);
                if (const_expr == NULL)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "Wrong internal status of const expression");
                    break;
                }
                switch (sub_expr->get_expr_type())
                {
                    case T_INT:
                    {
                        int64_t val = OB_INVALID_ID;
                        if ((ret = const_expr->get_value().get_int(val)) == OB_SUCCESS)
                        {
                            ObObj new_val;
                            if (is_min_int)
                            {
                                new_val.set_int(SIGNED_UINT64_MIN_VALUE);
                            }
                            else
                            {
                                new_val.set_int(-val);
                            }
                            const_expr->set_value(new_val);
                        }
                        break;
                    }
                    case T_FLOAT:
                    {
                        float val = static_cast<float> (OB_INVALID_ID);
                        if ((ret = const_expr->get_value().get_float(val)) == OB_SUCCESS)
                        {
                            ObObj new_val;
                            new_val.set_float(-val);
                            const_expr->set_value(new_val);
                        }
                        break;
                    }
                    case T_DOUBLE:
                    {
                        double val = static_cast<double> (OB_INVALID_ID);
                        if ((ret = const_expr->get_value().get_double(val)) == OB_SUCCESS)
                        {
                            ObObj new_val;
                            new_val.set_double(-val);
                            const_expr->set_value(new_val);
                        }
                        break;
                    }
                    default:
                    {
                        /* won't be here */
                        ret = JD_ERR_PARSER_SYNTAX;
                    }
                }
                if (ret == OB_SUCCESS)
                {
                    expr = sub_expr;
                }
                else
                {
                    jlog(WARNING, "Wrong internal status of const expression");
                    break;
                }
            }
            else
            {
                ObUnaryOpRawExpr *u_expr = NULL;
                if (CREATE_RAW_EXPR(u_expr, ObUnaryOpRawExpr, result_plan) == NULL)
                    break;
                u_expr->set_expr_type(node->type_);
                if (node->type_ == T_OP_POS)
                {
                    u_expr->set_result_type(sub_expr->get_result_type());
                }
                else if (node->type_ == T_OP_NEG)
                {
                    ObObj in_type;
                    in_type.set_type(sub_expr->get_result_type());
                    u_expr->set_result_type(ObExprObj::type_negate(in_type).get_type());
                }
                else if (node->type_ == T_OP_EXISTS || node->type_ == T_OP_NOT)
                {
                    u_expr->set_result_type(ObBoolType);
                }
                else
                {
                    /* won't be here */
                    u_expr->set_result_type(ObMinType);
                }
                u_expr->set_op_expr(sub_expr);
                expr = u_expr;
            }
            break;
        }
        case T_OP_ADD:
        case T_OP_MINUS:
        case T_OP_MUL:
        case T_OP_DIV:
        case T_OP_REM:
        case T_OP_POW:
        case T_OP_MOD:
        case T_OP_LE:
        case T_OP_LT:
        case T_OP_EQ:
        case T_OP_GE:
        case T_OP_GT:
        case T_OP_NE:
        case T_OP_LIKE:
        case T_OP_NOT_LIKE:
        case T_OP_AND:
        case T_OP_OR:
        case T_OP_IS:
        case T_OP_IS_NOT:
        case T_OP_CNN:
        {
            ObRawExpr* sub_expr1 = NULL;
            ret = resolve_expr(result_plan, stmt, node->children_[0], sql_expr, sub_expr1, expr_scope_type, true);
            if (ret != OB_SUCCESS)
                break;
            ObRawExpr* sub_expr2 = NULL;
            ret = resolve_expr(result_plan, stmt, node->children_[1], sql_expr, sub_expr2, expr_scope_type, true);
            if (ret != OB_SUCCESS)
                break;

            if ((T_FUN_SYS == sub_expr1->get_expr_type())||(T_FUN_SYS == sub_expr2->get_expr_type()))
            {
                ret = JD_ERR_NOT_SUPPORT_FUNC_CALC;
                break;
            }
            
            ObBinaryOpRawExpr *b_expr = NULL;
            if (CREATE_RAW_EXPR(b_expr, ObBinaryOpRawExpr, result_plan) == NULL)
                break;
            b_expr->set_expr_type(node->type_);
            ObObj in_type1;
            in_type1.set_type(sub_expr1->get_result_type());
            ObObj in_type2;
            in_type2.set_type(sub_expr2->get_result_type());
            if (node->type_ == T_OP_ADD)
            {
                b_expr->set_result_type(ObExprObj::type_add(in_type1, in_type2).get_type());
            }
            else if (node->type_ == T_OP_MINUS)
            {
                b_expr->set_result_type(ObExprObj::type_sub(in_type1, in_type2).get_type());
            }
            else if (node->type_ == T_OP_MUL)
            {
                b_expr->set_result_type(ObExprObj::type_mul(in_type1, in_type2).get_type());
            }
            else if (node->type_ == T_OP_DIV)
            {
                if (in_type1.get_type() == ObDoubleType || in_type2.get_type() == ObDoubleType)
                    b_expr->set_result_type(ObExprObj::type_div(in_type1, in_type2, true).get_type());
                else
                    b_expr->set_result_type(ObExprObj::type_div(in_type1, in_type2, false).get_type());
            }
            else if (node->type_ == T_OP_REM || node->type_ == T_OP_MOD)
            {
                b_expr->set_result_type(ObExprObj::type_mod(in_type1, in_type2).get_type());
            }
            else if (node->type_ == T_OP_POW)
            {
                b_expr->set_result_type(sub_expr1->get_result_type());
            }
            else if (node->type_ == T_OP_LE || node->type_ == T_OP_LT || node->type_ == T_OP_EQ
                    || node->type_ == T_OP_GE || node->type_ == T_OP_GT || node->type_ == T_OP_NE
                    || node->type_ == T_OP_LIKE || node->type_ == T_OP_NOT_LIKE || node->type_ == T_OP_AND
                    || node->type_ == T_OP_OR || node->type_ == T_OP_IS || node->type_ == T_OP_IS_NOT)
            {
                b_expr->set_result_type(ObBoolType);
            }
            else if (node->type_ == T_OP_CNN)
            {
                b_expr->set_result_type(ObVarcharType);
            }
            else
            {
                /* won't be here */
                b_expr->set_result_type(ObMinType);
            }
            b_expr->set_op_exprs(sub_expr1, sub_expr2);
            expr = b_expr;
            break;
        }
        case T_OP_BTW:
            /* pass through */
        case T_OP_NOT_BTW:
        {
            ObRawExpr* sub_expr1 = NULL;
            ObRawExpr* sub_expr2 = NULL;
            ObRawExpr* sub_expr3 = NULL;
            ret = resolve_expr(result_plan, stmt, node->children_[0], sql_expr, sub_expr1, expr_scope_type);
            if (ret != OB_SUCCESS)
                break;
            ret = resolve_expr(result_plan, stmt, node->children_[1], sql_expr, sub_expr2, expr_scope_type);
            if (ret != OB_SUCCESS)
                break;
            ret = resolve_expr(result_plan, stmt, node->children_[2], sql_expr, sub_expr3, expr_scope_type);
            if (ret != OB_SUCCESS)
                break;

            ObTripleOpRawExpr *t_expr = NULL;
            if (CREATE_RAW_EXPR(t_expr, ObTripleOpRawExpr, result_plan) == NULL)
                break;
            t_expr->set_expr_type(node->type_);
            t_expr->set_result_type(ObBoolType);
            t_expr->set_op_exprs(sub_expr1, sub_expr2, sub_expr3);
            expr = t_expr;
            break;
        }
        case T_OP_IN:
            // get through
        case T_OP_NOT_IN:
        {
            ObRawExpr* sub_expr1 = NULL;
            if (node->children_[0]->type_ == T_SELECT)
                ret = resolve_expr(
                    result_plan,
                    stmt,
                    node->children_[0],
                    sql_expr, sub_expr1,
                    expr_scope_type,
                    false
                    );
            else
                ret = resolve_expr(
                    result_plan,
                    stmt,
                    node->children_[0],
                    sql_expr,
                    sub_expr1,
                    expr_scope_type,
                    true);
            if (ret != OB_SUCCESS)
                break;
            ObRawExpr* sub_expr2 = NULL;
            ret = resolve_expr(
                    result_plan,
                    stmt,
                    node->children_[1],
                    sql_expr,
                    sub_expr2,
                    expr_scope_type,
                    false
                    );
            if (ret != OB_SUCCESS)
                break;
            ObBinaryOpRawExpr *in_expr = NULL;
            if (CREATE_RAW_EXPR(in_expr, ObBinaryOpRawExpr, result_plan) == NULL)
                break;
            in_expr->set_expr_type(node->type_ == T_OP_IN ? T_OP_IN : T_OP_NOT_IN);
            in_expr->set_result_type(ObBoolType);
            in_expr->set_op_exprs(sub_expr1, sub_expr2);

            /* 1. get the the column num of left operand */
            int32_t num_left_param = 1;
            switch (in_expr->get_first_op_expr()->get_expr_type())
            {
                case T_OP_ROW:
                {
                    ObMultiOpRawExpr *left_expr = dynamic_cast<ObMultiOpRawExpr *> (in_expr->get_first_op_expr());
                    num_left_param = left_expr->get_expr_size();
                    break;
                }
                case T_REF_QUERY:
                {
                    result_plan->has_sub_query = true; //added by qinbo
                    ObUnaryRefRawExpr *left_expr = dynamic_cast<ObUnaryRefRawExpr *> (in_expr->get_first_op_expr());
                    ObSelectStmt *sub_select = dynamic_cast<ObSelectStmt *> (logical_plan->get_query(left_expr->get_ref_id()));
                    if (!sub_select)
                    {
                        ret = JD_ERR_PARSER_SYNTAX;
                        jlog(WARNING, "Sub-query of In operator is not select statment");
                        break;
                    }
                    num_left_param = sub_select->get_select_item_size();
                    break;
                }
                default:
                    num_left_param = 1;
                    break;
            }

            /* 2. get the the column num of right operand(s) */
            int32_t num_right_param = 0;
            switch (in_expr->get_second_op_expr()->get_expr_type())
            {
                case T_OP_ROW:
                {
                    ObMultiOpRawExpr *row_expr = dynamic_cast<ObMultiOpRawExpr *> (in_expr->get_second_op_expr());
                    int32_t num = row_expr->get_expr_size();
                    ObRawExpr *sub_expr = NULL;
                    for (int32_t i = 0; i < num; i++)
                    {
                        sub_expr = row_expr->get_op_expr(i);
                        switch (sub_expr->get_expr_type())
                        {
                            case T_OP_ROW:
                            {
                                num_right_param = (dynamic_cast<ObMultiOpRawExpr *> (sub_expr))->get_expr_size();
                                break;
                            }
                            case T_REF_QUERY:
                            {
                                result_plan->has_sub_query = true; //added by qinbo
                                uint64_t query_id = (dynamic_cast<ObUnaryRefRawExpr *> (sub_expr))->get_ref_id();
                                ObSelectStmt *sub_query = dynamic_cast<ObSelectStmt*> (logical_plan->get_query(query_id));
                                if (sub_query)
                                    num_right_param = sub_query->get_select_item_size();
                                else
                                    num_right_param = 0;
                                break;
                            }
                            default:
                                num_right_param = 1;
                                break;
                        }
                        if (num_left_param != num_right_param)
                        {
                            break;
                        }
                    }
                    break;
                }
                case T_REF_QUERY:
                {
                    result_plan->has_sub_query = true; //added by qinbo
                    uint64_t query_id = (dynamic_cast<ObUnaryRefRawExpr *> (in_expr->get_second_op_expr()))->get_ref_id();
                    ObSelectStmt *sub_query = dynamic_cast<ObSelectStmt*> (logical_plan->get_query(query_id));
                    if (sub_query)
                        num_right_param = sub_query->get_select_item_size();
                    else
                        num_right_param = 0;
                    break;
                }
                default:
                    /* won't be here */
                    OB_ASSERT(0);
                    break;
            }

            /* 3. to check if the nums of two sides are equal */
            if (num_left_param != num_right_param)
            {
                ret = JD_ERR_COLUMN_SIZE;
                jlog(WARNING, "In operands contain different column(s)");
                break;
            }

            expr = in_expr;
            break;
        }
#if 0
        case T_CASE:
        {
            ObCaseOpRawExpr *case_expr = NULL;
            ObObjType tmp_type = ObMinType;
            if (CREATE_RAW_EXPR(case_expr, ObCaseOpRawExpr, result_plan) == NULL)
                break;
            if (node->children_[0])
            {
                ObRawExpr *arg_expr = NULL;
                ret = resolve_expr(result_plan, stmt, node->children_[0], sql_expr, arg_expr, expr_scope_type);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                case_expr->set_arg_op_expr(arg_expr);
                case_expr->set_expr_type(T_OP_ARG_CASE);
            }
            else
            {
                case_expr->set_expr_type(T_OP_CASE);
            }

            OB_ASSERT(node->children_[1]->type_ == T_WHEN_LIST);
            ParseNode *when_node;
            ObRawExpr *when_expr = NULL;
            ObRawExpr *then_expr = NULL;
            for (int32_t i = 0; ret == OB_SUCCESS && i < node->children_[1]->num_child_; i++)
            {
                when_node = node->children_[1]->children_[i];
                ret = resolve_expr(result_plan, stmt, when_node->children_[0], sql_expr, when_expr, expr_scope_type);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                ret = resolve_expr(result_plan, stmt, when_node->children_[1], sql_expr, then_expr, expr_scope_type);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                ret = case_expr->add_when_op_expr(when_expr);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                ret = case_expr->add_then_op_expr(then_expr);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                const ObObjType then_type = then_expr->get_result_type();
                if (then_type == ObNullType)
                {
                    continue;
                }
                else if (then_type > ObMinType && then_type < ObMaxType
                        && (then_type == tmp_type || tmp_type == ObMinType))
                {
                    tmp_type = then_type;
                }
                else
                {
                    ret = JD_ERR_ILLEGAL_TYPE;
                    jlog(WARNING, 
                            "Return types of then clause are not compatible");
                    break;
                }
            }
            if (ret != OB_SUCCESS)
            {
                break;
            }
            // @bug FIXME
            if (tmp_type == ObMinType) tmp_type = ObVarcharType;

            case_expr->set_result_type(tmp_type);
            if (case_expr->get_when_expr_size() != case_expr->get_then_expr_size())
            {
                ret = JD_ERR_COLUMN_SIZE;
                jlog(WARNING, 
                        "Error size of when expressions");
                break;
            }
            if (node->children_[2])
            {
                ObRawExpr *default_expr = NULL;
                ret = resolve_expr(result_plan, stmt, node->children_[2], sql_expr, default_expr, expr_scope_type);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                case_expr->set_default_op_expr(default_expr);
            }
            expr = case_expr;
            break;
        }
#endif
        case T_EXPR_LIST:
        {
            ObMultiOpRawExpr *multi_expr = NULL;
            if (CREATE_RAW_EXPR(multi_expr, ObMultiOpRawExpr, result_plan) == NULL)
                break;
            multi_expr->set_expr_type(T_OP_ROW);
            // not mathematic expression, result type is of no use.
            // should be ObRowType
            multi_expr->set_result_type(ObMinType);

            ObRawExpr *sub_query = NULL;
            uint64_t num = node->num_child_;
            for (uint64_t i = 0; ret == OB_SUCCESS && i < num; i++)
            {
                if (node->children_[i]->type_ == T_SELECT && !sub_query_results_scalar)
                    ret = resolve_expr(
                        result_plan,
                        stmt,
                        node->children_[i],
                        sql_expr,
                        sub_query,
                        expr_scope_type,
                        false);
                else
                    ret = resolve_expr(
                        result_plan,
                        stmt,
                        node->children_[i],
                        sql_expr,
                        sub_query,
                        expr_scope_type,
                        true);
                if (ret != OB_SUCCESS)
                {
                    break;
                }
                ret = multi_expr->add_op_expr(sub_query);
            }
            if (ret == OB_SUCCESS)
                expr = multi_expr;
            break;
        }
        case T_SELECT:
        {
            if (expr_scope_type == T_INSERT_LIMIT
                    || expr_scope_type == T_UPDATE_LIMIT
                    || expr_scope_type == T_AGG_LIMIT)
            {
                ret = JD_ERR_SQL_NO_SUBQUERY;
                jlog(WARNING, "Sub-query is illeagal in INSERT/UPDATE statement or AGGREGATION function");
                break;
            }

            uint64_t query_id = OB_INVALID_ID;
            if ((ret = resolve_select_stmt(result_plan, node, query_id)) != OB_SUCCESS)
                break;
            if (sub_query_results_scalar)
            {
                ObBasicStmt *sub_stmt = logical_plan->get_query(query_id);
                ObSelectStmt *sub_select = dynamic_cast<ObSelectStmt*> (sub_stmt);
                if (sub_select->get_select_item_size() != 1)
                {
                    ret = JD_ERR_COLUMN_SIZE;
                    jlog(WARNING, "Operand should contain 1 column(s)");
                    break;
                }
            }
            ObUnaryRefRawExpr *sub_query_expr = NULL;
            if (CREATE_RAW_EXPR(sub_query_expr, ObUnaryRefRawExpr, result_plan) == NULL)
                break;
            result_plan->has_sub_query = true; //added by qinbo
            sub_query_expr->set_expr_type(T_REF_QUERY);
            // not mathematic expression, result type is of no use.
            // should be ObRowType
            sub_query_expr->set_result_type(ObMinType);
            sub_query_expr->set_ref_id(query_id);
            expr = sub_query_expr;
            break;
        }
        case T_FUN_COUNT:
        case T_FUN_MAX:
        case T_FUN_MIN:
        case T_FUN_SUM:
        case T_FUN_AVG:
        {
            if (expr_scope_type == T_INSERT_LIMIT
                    || expr_scope_type == T_UPDATE_LIMIT
                    || expr_scope_type == T_AGG_LIMIT
                    || expr_scope_type == T_WHERE_LIMIT
                    || expr_scope_type == T_GROUP_LIMIT)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Invalid use of group function");
                break;
            }
            ObSelectStmt* select_stmt = dynamic_cast<ObSelectStmt*> (stmt);
            ObSqlRawExpr *ret_sql_expr = NULL;
            if ((ret = resolve_agg_func(result_plan, select_stmt, node, ret_sql_expr, expr_scope_type)) != OB_SUCCESS)
                break;
            ObBinaryRefRawExpr *col_expr = NULL;
            if (CREATE_RAW_EXPR(col_expr, ObBinaryRefRawExpr, result_plan) == NULL)
                break;
            col_expr->set_expr_type(T_REF_COLUMN);
            col_expr->set_result_type(ret_sql_expr->get_result_type());

            col_expr->set_first_ref_id(ret_sql_expr->get_table_id());
            col_expr->set_second_ref_id(ret_sql_expr->get_column_id());
            col_expr->set_related_sql_raw_id(ret_sql_expr->get_expr_id());
            // add invalid table bit index, avoid aggregate function expressions are used as filter
            //sql_expr->get_tables_set().add_member(0);
            sql_expr->set_contain_aggr(true);
            sql_expr->set_contain_aggr_type(node->type_);
            expr = col_expr;
            break;
        }
        case T_FUN_SYS:
        {
            ObSysFunRawExpr *func_expr = NULL;
            if (CREATE_RAW_EXPR(func_expr, ObSysFunRawExpr, result_plan) == NULL)
                break;
            func_expr->set_expr_type(T_FUN_SYS);
            string func_name = make_string(node->children_[0]->str_value_);
            func_expr->set_func_name(func_name);
            func_expr->set_result_type(ObIntType);
            
#if 0    
            if (ret == OB_SUCCESS)
            {
                int32_t param_num = 0;
                if ((ret = oceanbase::sql::ObPostfixExpression::get_sys_func_param_num(func_name, param_num)) != OB_SUCCESS)
                {
                    jlog(WARNING, "Unknown function '%.*s', ret=%d", func_name.size(), func_name.data());
                }
                else
                {
                    switch (param_num)
                    {
                        case TWO_OR_THREE:
                        {
                            if (func_expr->get_param_size() < 2 || func_expr->get_param_size() > 3)
                            {
                                ret = JD_ERR_PARAM_SIZE;
                                jlog(WARNING, "Param num of function '%.*s' can not be less than 2 or more than 3, ret=%d",
                                        func_name.size(), func_name.data(), ret);
                            }
                            break;
                        }
                        case OCCUR_AS_PAIR:
                        {
                            /* Won't be here */
                            /* No function of this type now */
                            ret = JD_ERR_PARAM_SIZE;
                            jlog(WARNING, "Wrong num of function param(s), function='%.*s', num=%d, ret=%d",
                                    func_name.size(), func_name.data(), OCCUR_AS_PAIR, ret);
                            break;
                        }
                        case MORE_THAN_ZERO:
                        {
                            if (func_expr->get_param_size() <= 0)
                            {
                                ret = JD_ERR_PARAM_SIZE;
                                jlog(WARNING, "Param num of function '%.*s' can not be less than 2 or more than 3, ret=%d",
                                        func_name.size(), func_name.data(), ret);
                            }
                            break;
                        }
                        default:
                        {
                            if (func_expr->get_param_size() != param_num)
                            {
                                ret = JD_ERR_PARAM_SIZE;
                                jlog(WARNING, "Param num of function '%.*s' must be %d, ret=%d",
                                        func_name.size(), func_name.data(), ret);
                            }
                            break;
                        }
                    }
                }
            }
            if (ret == OB_SUCCESS)
            {
                if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_LENGTH), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObIntType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_SUBSTR), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_CAST), func_name.data(), func_name.size()))
                {
                    int32_t num = node->children_[1]->num_child_;
                    if (num == 2)
                    {
                        ObObj obj;
                        int64_t item_type;
                        ObConstRawExpr *param_expr = dynamic_cast<ObConstRawExpr *> (func_expr->get_param_expr(1));
                        if (NULL != param_expr)
                        {
                            obj = param_expr->get_value();
                            if (OB_SUCCESS == (ret = obj.get_int(item_type)))
                            {
                                ObObjType dest_type = convert_item_type_to_obj_type(static_cast<SqlItemType> (item_type));
                                func_expr->set_result_type(dest_type);
                            }
                            else
                            {
                                jlog(WARNING, "fail to get int val. obj.get_type()=%d", obj.get_type());
                                break;
                            }
                        }
                        else
                        {
                            jlog(WARNING, "fail to get param expression");
                            break;
                        }
                    }
                    else
                    {
                        jlog(WARNING, "CAST function must only take 2 params");
                    }
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_CUR_TIME), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObDateTimeType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_CUR_DATE), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObDateTimeType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_CUR_TIMESTAMP), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObPreciseDateTimeType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_CUR_USER), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_TRIM), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_LOWER), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_UPPER), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_COALESCE), func_name.data(), func_name.size()))
                {
                    // always cast to varchar as it is an all-mighty type
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_HEX), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_UNHEX), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_IP_TO_INT), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObIntType);
                }
                else if (0 == strncasecmp(oceanbase::sql::ObPostfixExpression::get_sys_func_name(SYS_FUNC_INT_TO_IP), func_name.data(), func_name.size()))
                {
                    func_expr->set_result_type(ObVarcharType);
                }
                else
                {
                    ret = JD_ERR_UNKNOWN_SYS_FUNC;
                    jlog(WARNING, "system function `%.*s' not supported", func_name.size(), func_name.data());
                }
            }
#endif
            if (ret == OB_SUCCESS)
            {
                expr = func_expr;
            }
            break;
        }
        default:
            ret = JD_ERR_PARSER_SYNTAX;
            jlog(WARNING, "Wrong type in expression");
            break;
    }
    return ret;
}

int resolve_agg_func(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node,
        ObSqlRawExpr*& ret_sql_expr,
        int32_t expr_scope_type)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t expr_id = OB_INVALID_ID;
    ObSqlRawExpr* sql_expr = NULL;

    if (node != NULL)
    {
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        sql_expr = (ObSqlRawExpr*) parse_malloc(sizeof (ObSqlRawExpr), NULL);
        if (sql_expr == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc space for ObSqlRawExpr");
        }
        if (ret == OB_SUCCESS)
        {
            sql_expr = new(sql_expr) ObSqlRawExpr();
            ret = logical_plan->add_expr(sql_expr);
            if (ret != OB_SUCCESS)
                jlog(WARNING, "Add ObSqlRawExpr error");
        }
        if (ret == OB_SUCCESS)
        {
            expr_id = logical_plan->generate_expr_id();
            sql_expr->set_expr_id(expr_id);
            sql_expr->set_table_id(OB_INVALID_ID);
            sql_expr->set_column_id(logical_plan->generate_range_column_id());
            ret = select_stmt->add_agg_func(expr_id);
            if (ret != OB_SUCCESS)
                jlog(WARNING, "Add aggregate function error");
        }

        // When '*', do not set parameter
        ObRawExpr* sub_expr = NULL;
        if (ret == OB_SUCCESS)
        {
            if (node->type_ != T_FUN_COUNT || node->num_child_ > 1)
                ret = resolve_expr(result_plan, select_stmt, node->children_[1], sql_expr, sub_expr, T_AGG_LIMIT);
        }

        ObAggFunRawExpr *agg_expr = NULL;
        if (ret == OB_SUCCESS && CREATE_RAW_EXPR(agg_expr, ObAggFunRawExpr, result_plan) != NULL)
        {
            agg_expr->set_param_expr(sub_expr);
            if (node->children_[0] && node->children_[0]->type_ == T_DISTINCT)
            {
                agg_expr->set_param_distinct();
                ret = JD_ERR_NOT_SUPPORT_DISTINCT;
            }

            if (ret == OB_SUCCESS)
            {
                agg_expr->set_expr_type(node->type_);
                if (node->type_ == T_FUN_COUNT)
                    agg_expr->set_expr_type(T_FUN_COUNT);
                else if (node->type_ == T_FUN_MAX)
                    agg_expr->set_expr_type(T_FUN_MAX);
                else if (node->type_ == T_FUN_MIN)
                    agg_expr->set_expr_type(T_FUN_MIN);
                else if (node->type_ == T_FUN_SUM)
                    agg_expr->set_expr_type(T_FUN_SUM);
                else if (node->type_ == T_FUN_AVG)
                {
                    if (expr_scope_type == T_HAVING_LIMIT)
                    {
                        select_stmt->set_has_avg_in_having(true);
                    }
                    agg_expr->set_expr_type(T_FUN_AVG);
                }
                else
                {
                    /* Won't be here */

                }
                if (node->type_ == T_FUN_COUNT)
                {
                    agg_expr->set_result_type(ObIntType);
                }
                else if (node->type_ == T_FUN_MAX || node->type_ == T_FUN_MIN || node->type_ == T_FUN_SUM)
                {
                    agg_expr->set_result_type(sub_expr->get_result_type());
                }
                else if (node->type_ == T_FUN_AVG)
                {
                    ObObj in_type1;
                    ObObj in_type2;
                    in_type1.set_type(sub_expr->get_result_type());
                    in_type2.set_type(ObIntType);
                    if (in_type1.get_type() == ObDoubleType)
                        agg_expr->set_result_type(ObExprObj::type_div(in_type1, in_type2, true).get_type());
                    else
                        agg_expr->set_result_type(ObExprObj::type_div(in_type1, in_type2, false).get_type());
                }
                else
                {
                    /* won't be here */
                    agg_expr->set_result_type(ObMinType);
                    OB_ASSERT(false);
                }

                sql_expr->set_expr(agg_expr);
                sql_expr->set_contain_aggr(true);
                sql_expr->set_contain_aggr_type(node->type_);
                // add invalid table bit index, avoid aggregate function expressions are used as filters
                //sql_expr->get_tables_set().add_member(0);
            }
        }
    }
    else
    {
        ret = JD_ERR_PARSER_SYNTAX;
        jlog(WARNING, "Wrong usage of aggregate function");
    }
    if (ret == OB_SUCCESS)
        ret_sql_expr = sql_expr;
    return ret;
}

int resolve_joined_table(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node,
        JoinedTable& joined_table)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    OB_ASSERT(node->type_ == T_JOINED_TABLE);

    uint64_t tid = OB_INVALID_ID;
    uint64_t expr_id = OB_INVALID_ID;
    ParseNode* table_node = NULL;

    /* resolve table */
    for (uint64_t i = 1; ret == OB_SUCCESS && i < 3; i++)
    {
        table_node = node->children_[i];
        switch (table_node->type_)
        {
            case T_IDENT:
            case T_SELECT:
            case T_ALIAS:
                ret = resolve_table(result_plan, select_stmt, table_node, tid);
                if (ret == OB_SUCCESS && (ret = joined_table.add_table_id(tid)) != OB_SUCCESS)
                    jlog(WARNING, "Add table_id to outer joined table failed");
                break;
            case T_JOINED_TABLE:
                ret = resolve_joined_table(result_plan, select_stmt, table_node, joined_table);
                break;
            default:
                /* won't be here */
                ret = JD_ERR_PARSER_MALLOC_FAILED;
                jlog(WARNING, "Unknown table type in outer join");
                break;
        }
    }

    /* resolve join type */
    if (ret == OB_SUCCESS)
    {
        switch (node->children_[0]->type_)
        {
            case T_JOIN_FULL:
                ret = joined_table.add_join_type(JoinedTable::T_FULL);
                break;
            case T_JOIN_LEFT:
                ret = joined_table.add_join_type(JoinedTable::T_LEFT);
                break;
            case T_JOIN_RIGHT:
                ret = joined_table.add_join_type(JoinedTable::T_RIGHT);
                break;
            case T_JOIN_INNER:
                ret = joined_table.add_join_type(JoinedTable::T_INNER);
                break;
            default:
                /* won't be here */
                ret = JD_ERR_PARSER_MALLOC_FAILED;
                jlog(WARNING, "Unknown outer join type");
                break;
        }
    }

    /* resolve expression */
    if (ret == OB_SUCCESS)
    {
        ret = resolve_independ_expr(result_plan, select_stmt, node->children_[3], expr_id);
    }
    if (ret == OB_SUCCESS)
    {
        if ((ret = joined_table.add_expr_id(expr_id)) != OB_SUCCESS)
            jlog(WARNING, "Add outer join condition error");
    }

    return ret;
}

int resolve_table(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node,
        uint64_t& table_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        table_id = OB_INVALID_ID;
        ParseNode* table_node = node;
        ParseNode* alias_node = NULL;
        if (node->type_ == T_ALIAS)
        {
            OB_ASSERT(node->num_child_ == 2);
            OB_ASSERT(node->children_[0]);
            OB_ASSERT(node->children_[1]);

            table_node = node->children_[0];
            alias_node = node->children_[1];
        }

        switch (table_node->type_)
        {
            case T_IDENT:
            {
                string table_name;
                string alias_name;
                table_name.assign(
                        (char*) (table_node->str_value_),
                        static_cast<int32_t> (strlen(table_node->str_value_))
                        );
                if (alias_node)
                {
                    alias_name.assign(
                            (char*) (alias_node->str_value_),
                            static_cast<int32_t> (strlen(alias_node->str_value_))
                            );
                    ret = stmt->add_table_item(*result_plan, table_name, alias_name, table_id, TableItem::ALIAS_TABLE);
                }
                else
                    ret = stmt->add_table_item(*result_plan, table_name, alias_name, table_id, TableItem::BASE_TABLE);
                break;
            }
            case T_SELECT:
            {
                /* It must be select statement.
                 * For other statements, if the target is a view, it need to be expanded before this step
                 */
                OB_ASSERT(stmt->get_stmt_type() == ObStmt::T_SELECT);
                ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                if (alias_node == NULL)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "generated table must have alias name");
                    break;
                }

                uint64_t query_id = OB_INVALID_ID;
                ret = resolve_select_stmt(result_plan, table_node, query_id);
                if (ret == OB_SUCCESS)
                {
                    string table_name;
                    string alias_name;
                    table_name.assign(
                            (char*) (alias_node->str_value_),
                            static_cast<int32_t> (strlen(alias_node->str_value_))
                            );
                    ret = select_stmt->add_table_item(
                            *result_plan,
                            table_name,
                            alias_name,
                            table_id,
                            TableItem::GENERATED_TABLE,
                            query_id
                            );
                }
                break;
            }
            case T_JOINED_TABLE:
            {
                /* only select statement has this type */
                OB_ASSERT(stmt->get_stmt_type() == ObStmt::T_SELECT);
                ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                table_id = select_stmt->generate_joined_tid();
                JoinedTable* joined_table = (JoinedTable*) parse_malloc(sizeof (JoinedTable), NULL);
                if (joined_table == NULL)
                {
                    ret = JD_ERR_PARSER_MALLOC_FAILED;
                    jlog(WARNING, "Can not malloc space for JoinedTable");
                    break;
                }
                joined_table = new(joined_table) JoinedTable;
                joined_table->set_joined_tid(table_id);
                ret = resolve_joined_table(result_plan, select_stmt, table_node, *joined_table);
                if (ret != OB_SUCCESS)
                    break;
                ret = select_stmt->add_joined_table(joined_table);
                if (ret != OB_SUCCESS)
                    jlog(WARNING, "Can not add JoinedTable");
                break;
            }
            //BEGIN: Added by qinbo
            //only support meta database query
            case T_OP_NAME_FIELD:
            {
                OB_ASSERT(node->children_[0]->type_ == T_IDENT);
                // star has been expand before
                // T_IDENT.* can't has alias name here, which is illeagal
                if (node->children_[1]->type_ != T_IDENT)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "%s.* is illeagal", node->children_[0]->str_value_);
                    break;
                }
                
                const char* db_str = node->children_[0]->str_value_;
                const char* table_str = node->children_[1]->str_value_;
                string db_name;
                string table_name;
                db_name.assign((char*) db_str, static_cast<int32_t> (strlen(db_str)));
                table_name.assign((char*) table_str, static_cast<int32_t> (strlen(table_str)));
                //transfer to lower string
                std::transform(db_name.begin(), db_name.end(), db_name.begin(), ::tolower);
                std::transform(table_name.begin(), table_name.end(), table_name.begin(), ::tolower);
                if ((0 != db_name.compare("information_schema"))
                 && (0 != db_name.compare("mysql"))
                 && (0 != db_name.compare("performance_schema")))
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "Unknown db name");
                }
                else
                {
                    result_plan->meta_db_name = db_name;
                    result_plan->is_show_sys_var = true;
                    jlog(INFO, "Current meta dic query database is: %s", db_name.c_str());
                }
                break;
            }
            //END: Added by qinbo
            default:
                /* won't be here */
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Unknown table type");
                break;
        }
    }
    else
    {
        ret = JD_ERR_PARSER_SYNTAX;
        jlog(WARNING, "No table in from clause");
    }

    return ret;
}

int resolve_from_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        OB_ASSERT(node->type_ == T_FROM_LIST);
        OB_ASSERT(node->num_child_ >= 1);

        uint64_t tid = OB_INVALID_ID;
        for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
        {
            ParseNode* child_node = node->children_[i];
            ret = resolve_table(result_plan, select_stmt, child_node, tid);
            if (ret != OB_SUCCESS)
                break;

            if (child_node->type_ == T_OP_NAME_FIELD)
            {
                break;
            }
            if (child_node->type_ == T_JOINED_TABLE)
                ret = select_stmt->add_from_item(tid, true);
            else
                ret = select_stmt->add_from_item(tid);
            if (ret != OB_SUCCESS)
            {
                jlog(WARNING, "Add from table failed");
                break;
            }
        }
    }
    return ret;
}

int resolve_table_columns(
        ResultPlan * result_plan,
        ObStmt* stmt,
        TableItem& table_item,
        int64_t num_columns)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    ColumnItem *column_item = NULL;
    ColumnItem new_column_item;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    OB_ASSERT(NULL != logical_plan);

    if (ret == OB_SUCCESS)
    {
        if (table_item.type_ == TableItem::GENERATED_TABLE)
        {
            ObSelectStmt* sub_select = static_cast<ObSelectStmt*> (logical_plan->get_query(table_item.ref_id_));
            if (sub_select == NULL)
            {
                ret = JD_ERR_ILLEGAL_ID;
                jlog(WARNING, "Can not get sub-query whose id = %lu", table_item.ref_id_);
            }
            else
            {
                int32_t num = sub_select->get_select_item_size();
                for (int32_t i = 0; ret == OB_SUCCESS && i < num && (num_columns <= 0 || i < num_columns); i++)
                {
                    const SelectItem& select_item = sub_select->get_select_item(i);
                    column_item = stmt->get_column_item_by_id(table_item.table_id_, OB_APP_MIN_COLUMN_ID + i);
                    if (column_item == NULL)
                    {
                        new_column_item.column_id_  = OB_APP_MIN_COLUMN_ID + i;
                        new_column_item.column_name_= select_item.alias_name_;
                        new_column_item.table_id_ = table_item.table_id_;
                        new_column_item.query_id_ = 0; // no use now, because we don't support correlated subquery
                        new_column_item.is_name_unique_ = false;
                        new_column_item.is_group_based_ = false;
                        new_column_item.data_type_ = select_item.type_;
                        ret = stmt->add_column_item(new_column_item);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Add column error");
                            break;
                        }
                        column_item = &new_column_item;
                    }

                    if (stmt->get_stmt_type() == ObStmt::T_SELECT && num_columns <= 0)
                    {
                        ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                        ObBinaryRefRawExpr* expr = NULL;
                        if (CREATE_RAW_EXPR(expr, ObBinaryRefRawExpr, result_plan) == NULL)
                            break;
                        expr->set_expr_type(T_REF_COLUMN);
                        expr->set_first_ref_id(column_item->table_id_);
                        expr->set_second_ref_id(column_item->column_id_);
                        expr->set_result_type(column_item->data_type_);

                        //BEGIN: added by qinbo
                        //singal table                          | multi tables
                        if ((table_item.need_display_table_name)||(select_stmt->get_from_item_size() > 1))
                        {
                            expr->set_op_name_field();
                        }
                        //END: added by qinbo
                        
                        ObSqlRawExpr* sql_expr = (ObSqlRawExpr*) parse_malloc(sizeof (ObSqlRawExpr), NULL);
                        if (sql_expr == NULL)
                        {
                            ret = JD_ERR_PARSER_MALLOC_FAILED;
                            jlog(WARNING, "Can not malloc space for ObSqlRawExpr");
                            break;
                        }
                        sql_expr = new(sql_expr) ObSqlRawExpr();
                        sql_expr->set_expr_id(logical_plan->generate_expr_id());
                        sql_expr->set_table_id(OB_INVALID_ID);
                        sql_expr->set_column_id(logical_plan->generate_column_id());
                        sql_expr->set_expr(expr);
                        //ObBitSet<> tables_set;
                        //tables_set.add_member(stmt->get_table_bit_index(table_item.table_id_));
                        //sql_expr->set_tables_set(tables_set);
                        ret = logical_plan->add_expr(sql_expr);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Can not add ObSqlRawExpr to logical plan");
                            break;
                        }

                        //ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                        ret = select_stmt->add_select_item(
                                result_plan,
                                sql_expr->get_expr_id(),
                                false,
                                column_item->column_name_,
                                select_item.expr_name_,
                                select_item.type_);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Can not add select item");
                            break;
                        }
                    }
                }
            }
        }
        //BASE_TABLE OR alias table
        else
        {
            /*get table columns qinbo*/
#if 0
            const ObColumnSchemaV2* column = NULL;
#endif
            string db_name_tmp;
            db_name_tmp.assign(result_plan->db_name);
            vector<class schema_column*> schema_columns = meta_reader::get_instance().get_all_column_schemas_with_lock(db_name_tmp, table_item.table_name_);

            int32_t column_size = schema_columns.size();

            if (column_size > 0)
            {
                if (table_item.ref_id_ == OB_TABLES_SHOW_TID) // @FIXME !!!
                {
                    column_size = 1;
                }

                //for (unsigned i = 0; i < schema_columns.size(); i++)
                for (int32_t i = 0; ret == OB_SUCCESS && i < column_size && (num_columns <= 0 || i < num_columns); i++)
                {
                    schema_column *schema_column_ = schema_columns.at(i);
                    new_column_item.column_id_ = schema_column_->get_column_id();
                    column_item = stmt->get_column_item_by_id(table_item.table_id_, new_column_item.column_id_);
                    if (column_item == NULL)
                    {
                        new_column_item.column_name_ = schema_column_->get_column_name();
                        new_column_item.table_id_ = table_item.table_id_;
                        new_column_item.query_id_ = 0; // no use now, because we don't support correlated subquery
                        new_column_item.is_name_unique_ = false;
                        new_column_item.is_group_based_ = false;
                        new_column_item.data_type_ = trans_int_type2obj_type(schema_column_->get_column_type());
                        ret = stmt->add_column_item(new_column_item);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Add column error");
                            break;
                        }
                        column_item = &new_column_item;
                    }

                    if (stmt->get_stmt_type() == ObStmt::T_SELECT && num_columns <= 0)
                    {
                        ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (stmt);
                        ObBinaryRefRawExpr* expr = NULL;
                        if (CREATE_RAW_EXPR(expr, ObBinaryRefRawExpr, result_plan) == NULL)
                            break;
                        expr->set_expr_type(T_REF_COLUMN);
                        expr->set_first_ref_id(column_item->table_id_);
                        expr->set_second_ref_id(column_item->column_id_);
                        expr->set_result_type(column_item->data_type_);
                        
                        //BEGIN: added by qinbo
                        if ((table_item.need_display_table_name)||(select_stmt->get_from_item_size() > 1))
                        {
                            expr->set_op_name_field();
                            if (table_item.type_ == TableItem::ALIAS_TABLE)
                            {
                                expr->set_alias_table_name(table_item.alias_name_);
                            }
                        }
                        //END: added by qinbo
                        
                        ObSqlRawExpr* sql_expr = (ObSqlRawExpr*) parse_malloc(sizeof (ObSqlRawExpr), NULL);
                        if (sql_expr == NULL)
                        {
                            ret = JD_ERR_PARSER_MALLOC_FAILED;
                            jlog(WARNING, "Can not malloc space for ObSqlRawExpr");
                            break;
                        }
                        sql_expr = new(sql_expr) ObSqlRawExpr();
                        sql_expr->set_expr_id(logical_plan->generate_expr_id());
                        sql_expr->set_table_id(OB_INVALID_ID);
                        sql_expr->set_column_id(logical_plan->generate_column_id());
                        sql_expr->set_expr(expr);
                        //ObBitSet<> tables_set;
                        //tables_set.add_member(stmt->get_table_bit_index(table_item.table_id_));
                        //sql_expr->set_tables_set(tables_set);

                        ret = logical_plan->add_expr(sql_expr);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Can not add ObSqlRawExpr to logical plan");
                            break;
                        }

                        ret = select_stmt->add_select_item(
                                result_plan,
                                sql_expr->get_expr_id(),
                                false,
                                column_item->column_name_,
                                column_item->column_name_,
                                column_item->data_type_);
                        if (ret != OB_SUCCESS)
                        {
                            jlog(WARNING, "Can not add select item");
                            break;
                        }
                    }
                }
            }
        }
    }
    return ret;
}

int resolve_star(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    OB_ASSERT(result_plan);
    OB_ASSERT(select_stmt);
    OB_ASSERT(node);
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;

    if (node->type_ == T_STAR)
    {
        int32_t num = select_stmt->get_table_size();
        for (int32_t i = 0; ret == OB_SUCCESS && i < num; i++)
        {
            //even join exist, join tables also in table_items.
            TableItem& table_item = select_stmt->get_table_item(i);
            if (num > 1)
            {
                table_item.need_display_table_name = true;
            }
            ret = resolve_table_columns(result_plan, select_stmt, table_item);
        }
    }
    else if (node->type_ == T_OP_NAME_FIELD)
    {
        OB_ASSERT(node->children_[0]->type_ == T_IDENT);
        OB_ASSERT(node->children_[1]->type_ == T_STAR);

        TableItem* table_item;
        ParseNode* table_node = node->children_[0];
        string table_name;
        table_name.assign(
                (char*) (table_node->str_value_),
                static_cast<int32_t> (strlen(table_node->str_value_))
                );

        if ((select_stmt->get_table_item(table_name, &table_item)) == OB_INVALID_ID)
        {
            ret = JD_ERR_TABLE_UNKNOWN;
            jlog(WARNING, "Unknown table %s", table_node->str_value_);
        }
        if (ret == OB_SUCCESS)
        {
            table_item->need_display_table_name = true;
            ret = resolve_table_columns(result_plan, select_stmt, *table_item);
        }
    }
    else
    {
        /* won't be here */
    }

    return ret;
}

int resolve_select_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    OB_ASSERT(node->type_ == T_PROJECT_LIST);
    OB_ASSERT(node->num_child_ >= 1);

    ParseNode* project_node = NULL;
    ParseNode* alias_node = NULL;
    string alias_name;
    string expr_name;
    bool is_bald_star = false;
    bool is_real_alias;
    for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
    {
        is_real_alias = false;
        expr_name.assign(
                (char*) (node->children_[i]->str_value_),
                static_cast<int32_t> (strlen(node->children_[i]->str_value_))
                );
        project_node = node->children_[i]->children_[0];
        if (project_node->type_ == T_STAR
                || (project_node->type_ == T_OP_NAME_FIELD
                && project_node->children_[1]->type_ == T_STAR))
        {
            if (project_node->type_ == T_STAR)
            {
                if (is_bald_star)
                {
                    ret = JD_ERR_STAR_DUPLICATE;
                    jlog(WARNING, "Wrong usage of '*'");
                    break;
                }
                else
                    is_bald_star = true;
            }

            ret = resolve_star(result_plan, select_stmt, project_node);
            continue;
        }

        if (project_node->type_ == T_ALIAS)
        {
            OB_ASSERT(project_node->num_child_ == 2);
            expr_name.assign(
                         const_cast<char*>(project_node->str_value_),
                         static_cast<int32_t>(strlen(project_node->str_value_))
                         );

            alias_node = project_node->children_[1];
            project_node = project_node->children_[0];
            is_real_alias = true;

            /* check if the alias name is legal */
            OB_ASSERT(alias_node->type_ == T_IDENT);
            alias_name.assign(
                (char*)(alias_node->str_value_),
                static_cast<int32_t>(strlen(alias_node->str_value_))
                );
            // Same as mysql, we do not check alias name
            // if (!(select_stmt->check_alias_name(logical_plan, sAlias)))
            // {
            //   TBSYS_LOG(ERROR, "alias name %.s is ambiguous", alias_node->str_value_);
            //   return false;
            // }
        }
        /* it is not real alias name, we just record them for convenience */
        else
        {
            if (project_node->type_ == T_IDENT)
                alias_node = project_node;
            else if (project_node->type_ == T_OP_NAME_FIELD)
            {
                expr_name.assign(
                           const_cast<char*>(project_node->str_value_),
                           static_cast<int32_t>(strlen(project_node->str_value_))
                           );
                alias_node = project_node->children_[1];
                OB_ASSERT(alias_node->type_ == T_IDENT);
            }

            /* original column name of based table, it has been checked in expression resolve */
            if (alias_node)
                alias_name.assign(
                  (char*)(alias_node->str_value_),
                  static_cast<int32_t>(strlen(alias_node->str_value_))
                  );
        }

        if (project_node->type_ == T_EXPR_LIST && project_node->num_child_ != 1)
        {
            ret = JD_ERR_RESOLVE_SQL;
            jlog(WARNING, "Operand should contain 1 column(s)");
            break;
        }

        uint64_t expr_id = OB_INVALID_ID;
        if ((ret = resolve_independ_expr(result_plan, select_stmt, project_node, expr_id)) != OB_SUCCESS)
            break;

        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        OB_ASSERT(NULL != logical_plan);
        ObSqlRawExpr *select_expr = NULL;
        if ((select_expr = logical_plan->get_expr(expr_id)) == NULL)
        {
            ret = JD_ERR_ILLEGAL_ID;
            jlog(WARNING, "Wrong expr_id");
            break;
        }

        //sql like "select @@version_comment limit 1" or "select @version_comment limit 1"
        //should be processed 
        if ((NULL != select_expr->get_expr())
            &&((select_expr->get_expr()->get_expr_type() == T_SYSTEM_VARIABLE)
            ||(select_expr->get_expr()->get_expr_type() == T_TEMP_VARIABLE)))
        {
            result_plan->is_show_sys_var = true;
            break;
        }

        
        if ((NULL != select_expr->get_expr())
            &&(select_expr->get_expr()->get_expr_type() == T_FUN_SYS))
        {
            if (select_stmt->is_sys_func_query())
            {
                result_plan->is_show_sys_var = true;
                break;
            }
            else
            {
                result_plan->is_show_sys_var = false;
                ret = JD_ERR_NOT_SUPPORT_FUNCTION;
                jlog(WARNING, "do not support query with function which sent to data node.");
                break;
            }
        }

        /* if IDENT, we need to assign new id for it to avoid same (table_id, column_id) in ObRowDesc */
        /* 1. select price + off new_price, new_price from tbl; */
        /* 2. select price, price from tbl; */
        /* new_price from 1 and two price from 2 will have new column id after top project operator,
         * so, before this project any operator use none-aliased base column must get its real table id
         * and column id not the ids of the expression
         */
        if (project_node->type_ == T_IDENT || project_node->type_ == T_OP_NAME_FIELD)
        {
            select_expr->set_table_id(OB_INVALID_ID);
            select_expr->set_column_id(logical_plan->generate_column_id());
        }

        /* get table name and column name here*/
        const ObObjType type = select_expr->get_result_type();
        ret = select_stmt->add_select_item(result_plan, expr_id, is_real_alias, alias_name, expr_name, type);
        if (ret != OB_SUCCESS)
        {
            break;
        }

        alias_node = NULL;
        alias_name.assign("");
    }

    return ret;
}

int resolve_where_clause(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        ret = resolve_and_exprs(
                result_plan,
                stmt,
                node,
                stmt->get_where_exprs(),
                T_WHERE_LIMIT
                );
    }
    return ret;
}

int resolve_group_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;

    /*****************************************************************************
     * The non-aggregate expression of select clause must be expression of group items,
     * but we don't check it here, which is in accordance with mysql.
     * Although there are different values of one group, but the executor only pick the first one
     * E.g.
     * select c1, c2, sum(c3)
     * from tbl
     * group by c1;
     * c2 in select clause is leagal, which is not in standard.
     *****************************************************************************/

    if (ret == OB_SUCCESS && node != NULL)
    {
        OB_ASSERT(node->type_ == T_EXPR_LIST);
        OB_ASSERT(node->num_child_ >= 1);
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        uint64_t expr_id;
        ParseNode* group_node;
        for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
        {
            GroupItem group_item;
            group_item.group_type_ = T_SORT_ASC;
        
            group_node = node->children_[i];
            if (group_node->type_ == T_INT && group_node->value_ >= 0)
            {
                uint32_t pos = static_cast<uint32_t> (group_node->value_);
                if (pos <= 0 || pos > select_stmt->get_select_item_size())
                {
                    ret = JD_ERR_WRONG_POS;
                    jlog(WARNING, "Unknown column '%d' in 'group clause'", pos);
                    break;
                }
                expr_id = select_stmt->get_select_item(pos - 1).expr_id_;
                ObSqlRawExpr *sql_expr = logical_plan->get_expr(expr_id);
                if (!sql_expr)
                {
                    ret = JD_ERR_ILLEGAL_ID;
                    jlog(WARNING, "Can not find expression, expr_id = %lu", expr_id);
                    break;
                }
                if (sql_expr->is_contain_aggr())
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "Invalid use of expression which contains group function");
                    break;
                }

                //BEGIN: modified by qinbo
                group_item.expr_id_     = expr_id;
                group_item.column_type_ = select_stmt->get_select_item(pos - 1).type_;
                group_item.group_column_= select_stmt->get_select_item(pos - 1).select_column_name_;
                //END: modified by qinbo
            }
            else
            {
                ret = resolve_independ_expr(
                        result_plan,
                        select_stmt,
                        group_node,
                        expr_id,
                        T_GROUP_LIMIT
                        );
                //BEGIN: modified by qinbo
                group_item.expr_id_     = expr_id;
                //END: modified by qinbo
            }
            if (ret == OB_SUCCESS)
            {
                //BEGIN:Added by qinbo
                SqlItemType not_unsed_aggr_type;
                ret = select_stmt->get_column_info_by_expr_id(
                                    result_plan,
                                    group_item.expr_id_,
                                    group_item.column_type_,
                                    not_unsed_aggr_type,
                                    group_item.group_column_);
                if (ret == OB_SUCCESS)
                {
                    select_stmt->add_group_item(group_item);
                    if ((ret = select_stmt->add_group_expr(expr_id)) != OB_SUCCESS)
                        jlog(WARNING, "Add group expression error");
                }
                //END:Added by qinbo
            }
        }
    }
    return ret;
}

int resolve_having_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int&        ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint32_t    having_expr_size;
    if (node)
    {
        ret = resolve_and_exprs(
                result_plan,
                select_stmt,
                node,
                select_stmt->get_having_exprs(),
                T_HAVING_LIMIT
                );
        //BEGIN: Added by qinbo
        if (OB_SUCCESS == ret) 
        {
            having_expr_size = select_stmt->get_having_exprs().size();
            if (having_expr_size > 0)
            {
                for (uint32_t i = 0; i< having_expr_size; i++)
                {
                    uint64_t   having_expr_id = select_stmt->get_having_exprs().at(i);
                    HavingItem having_item;
                    having_item.expr_id_    = having_expr_id;
                    ret = select_stmt->get_having_column_by_expr_id(
                                                result_plan, 
                                                having_item.expr_id_,
                                                having_item.column_type_,
                                                having_item.aggr_fun_type,
                                                having_item.aggr_fun_operate,
                                                having_item.aggr_fun_value,
                                                having_item.having_column_name
                                                );
                    if (OB_SUCCESS != ret)
                    {
                        break;
                    }
                    select_stmt->add_having_item(having_item);
                }
            }
                        
        }
        //END: Added by qinbo
    }
    return ret;
}

int resolve_order_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        OB_ASSERT(node->type_ == T_SORT_LIST);

        for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
        {
            ParseNode* sort_node = node->children_[i];
            OB_ASSERT(sort_node->type_ == T_SORT_KEY);

            OrderItem order_item;
            order_item.order_type_ = T_SORT_ASC;
            if (sort_node->children_[1]->type_ == T_SORT_ASC)
                order_item.order_type_ = T_SORT_ASC;
            else if (sort_node->children_[1]->type_ == T_SORT_DESC)
                order_item.order_type_ = T_SORT_DESC;
            else
            {
                OB_ASSERT(false); /* Won't be here */
            }

            if (sort_node->children_[0]->type_ == T_INT && sort_node->children_[0]->value_ >= 0)
            {
                uint32_t pos = static_cast<uint32_t> (sort_node->children_[0]->value_);
                if (pos <= 0 || pos > select_stmt->get_select_item_size())
                {
                    ret = JD_ERR_WRONG_POS;
                    jlog(WARNING, "Unknown column '%d' in 'order clause'");
                    break;
                }
                order_item.expr_id_     = select_stmt->get_select_item(pos - 1).expr_id_;
                //BEGIN: modified by qinbo
                order_item.column_type_ = select_stmt->get_select_item(pos - 1).type_;
                order_item.order_column_= select_stmt->get_select_item(pos - 1).select_column_name_;
                //END: modified by qinbo
            }
            else
            {
                ret = resolve_independ_expr(result_plan, select_stmt, sort_node->children_[0], order_item.expr_id_);
            }
            
            if (ret == OB_SUCCESS)
            {
                //BEGIN:Added by qinbo
                SqlItemType not_unsed_aggr_type;
                ret = select_stmt->get_column_info_by_expr_id(
                                result_plan,
                                order_item.expr_id_,
                                order_item.column_type_,
                                not_unsed_aggr_type,
                                order_item.order_column_);

                if (ret == OB_SUCCESS)
                {
                    if ((ret = select_stmt->add_order_item(order_item)) != OB_SUCCESS)
                        jlog(WARNING, "Add order expression error");
                }
                //END:Added by qinbo
            }
        }
    }
    return ret;
}

int resolve_limit_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{

    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t limit_count = OB_INVALID_ID;
    uint64_t limit_offset = OB_INVALID_ID;
    
    if (node)
    {
        OB_ASSERT(result_plan != NULL);
        OB_ASSERT(node->type_ == T_LIMIT_CLAUSE);

        ParseNode* limit_node = node->children_[0];
        ParseNode* offset_node = node->children_[1];
        OB_ASSERT(limit_node != NULL || offset_node != NULL);

        // resolve the question mark with less value first
        if (limit_node != NULL && limit_node->type_ == T_QUESTIONMARK
                && offset_node != NULL && offset_node->type_ == T_QUESTIONMARK
                && limit_node->value_ > offset_node->value_)
        {
            if ((ret = resolve_independ_expr(result_plan, select_stmt, offset_node, limit_offset)) != OB_SUCCESS
                    || (ret = resolve_independ_expr(result_plan, select_stmt, limit_node, limit_count)) != OB_SUCCESS)
            {
                jlog(WARNING, "Resolve limit/offset error, ret=%d", ret);
            }
        }
        else
        {
            if (ret == OB_SUCCESS && limit_node != NULL)
            {
                if (limit_node->type_ != T_INT && limit_node->type_ != T_QUESTIONMARK)
                {
                    jlog(WARNING, "Wrong type of limit value");
                }
                else if ((ret = resolve_independ_expr(result_plan, select_stmt, limit_node, limit_count)) != OB_SUCCESS)
                {
                    jlog(WARNING, "Resolve limit error, ret=%d", ret);
                }
            }
            if (ret == OB_SUCCESS && offset_node != NULL)
            {
                if (offset_node->type_ != T_INT && offset_node->type_ != T_QUESTIONMARK)
                {
                    jlog(WARNING,"Wrong type of limit value");
                }
                else if ((ret = resolve_independ_expr(result_plan, select_stmt, offset_node, limit_offset)) != OB_SUCCESS)
                {
                    jlog(WARNING, "Resolve offset error, ret=%d", ret);
                }
            }
        }
    }
    
    if (ret == OB_SUCCESS)
    {
        ret = select_stmt->set_limit_offset(result_plan, limit_offset, limit_count);
    }
    
    return ret;
}

int resolve_for_update_clause(
        ResultPlan * result_plan,
        ObSelectStmt* select_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        OB_ASSERT(node->type_ == T_BOOL);
        if (node->value_ == 1)
            select_stmt->set_for_update(true);
    }
    return ret;
}

int resolve_select_stmt(
        ResultPlan* result_plan,
        ParseNode* node,
        uint64_t& query_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    OB_ASSERT(node && node->num_child_ >= 12);
    query_id = OB_INVALID_ID;

    //stringBuf* name_pool = static_cast<stringBuf*>(result_plan->name_pool_);
    ObLogicalPlan* logical_plan = NULL;
    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*) parse_malloc(sizeof (ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObLogicalPlan");
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    }

    ObSelectStmt* select_stmt = NULL;
    if (ret == OB_SUCCESS)
    {
        select_stmt = (ObSelectStmt*) parse_malloc(sizeof (ObSelectStmt), NULL);
        if (select_stmt == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObSelectStmt");
        }
    }

    if (ret == OB_SUCCESS)
    {
        select_stmt = new(select_stmt) ObSelectStmt();
        query_id = logical_plan->generate_query_id();
        select_stmt->set_query_id(query_id);
        ret = logical_plan->add_query(select_stmt);
        if (ret != OB_SUCCESS)
        {
            jlog(WARNING,"Can not add ObSelectStmt to logical plan");
        }
    }

    /* -----------------------------------------------------------------
     * The later resolve may need some infomation resolved by the former one,
     * so please follow the resolving orders:
     *
     * 1. set clause
     * 2. from clause
     * 3. select clause
     * 4. where clause
     * 5. group by clause
     * 6. having clause
     * 7. order by clause
     * 8. limit clause
     * -----------------------------------------------------------------
     */

    /* resolve set clause */
    if (node->children_[6] != NULL)
    {
        OB_ASSERT(node->children_[8] != NULL);
        OB_ASSERT(node->children_[9] != NULL);

        if (node->children_[12] && node->children_[12]->value_ == 1)
        {
            ret = JD_ERR_ILLEGAL_ID;
            jlog(WARNING,"Select for update statement can not process set query");
        }

        // assign set type
        if (ret == OB_SUCCESS)
        {
            switch (node->children_[6]->type_)
            {
                case T_SET_UNION:
                    select_stmt->assign_set_op(ObSelectStmt::UNION);
                    break;
                case T_SET_INTERSECT:
                    select_stmt->assign_set_op(ObSelectStmt::INTERSECT);
                    break;
                case T_SET_EXCEPT:
                    select_stmt->assign_set_op(ObSelectStmt::EXCEPT);
                    break;
                default:
                    ret = JD_ERR_OPERATOR_UNKNOWN;
                    jlog(WARNING, "unknown set operator of set clause");
                    break;
            }
        }

        // assign first query
        uint64_t sub_query_id = OB_INVALID_ID;
        if (ret == OB_SUCCESS)
        {
            if (node->children_[7] == NULL || node->children_[7]->type_ == T_DISTINCT)
            {
                select_stmt->assign_set_distinct();
                ret = JD_ERR_NOT_SUPPORT_DISTINCT;
            }
            else
            {
                select_stmt->assign_set_all();
            }
            ret = resolve_select_stmt(result_plan, node->children_[8], sub_query_id);
            if (ret == OB_SUCCESS)
                select_stmt->assign_left_query_id(sub_query_id);
        }
        // assign second query
        if (ret == OB_SUCCESS)
        {
            ret = resolve_select_stmt(result_plan, node->children_[9], sub_query_id);
            if (ret == OB_SUCCESS)
                select_stmt->assign_right_query_id(sub_query_id);
        }

        // check if columns number ars match
        if (ret == OB_SUCCESS)
        {
            ObSelectStmt* left_select = logical_plan->get_select_query(select_stmt->get_left_query_id());
            ObSelectStmt* right_select = logical_plan->get_select_query(select_stmt->get_right_query_id());
            if (!left_select || !right_select)
            {
                ret = JD_ERR_ILLEGAL_ID;
                jlog(WARNING, "resolve set clause error");
            }
            else if (left_select->get_select_item_size() != right_select->get_select_item_size())
            {
                ret = JD_ERR_COLUMN_SIZE;
                jlog(WARNING, "The used SELECT statements have a different number of columns");
            }
            else
                ret = select_stmt->copy_select_items(left_select);
        }
    }
    else
    {
        /* normal select */
        select_stmt->assign_set_op(ObSelectStmt::NONE);

        if ((NULL == node->children_[0])
            &&(NULL == node->children_[2])
            &&(NULL == node->children_[3])
            &&(NULL == node->children_[4])
            &&(NULL == node->children_[5])
            &&(NULL == node->children_[6])
            &&(NULL == node->children_[7])
            &&(NULL == node->children_[8])
            &&(NULL == node->children_[9])
            &&(NULL == node->children_[10])
            &&(NULL == node->children_[11])
            &&(NULL == node->children_[12])
            &&(NULL == node->children_[13]))
        {
            select_stmt->set_sys_func_query(true);
        }
        else
        {
            select_stmt->set_sys_func_query(false);
        }

        if (node->children_[0] == NULL || node->children_[0]->type_ == T_ALL)
        {
            select_stmt->assign_all();
        }
        else
        {
            select_stmt->assign_distinct();
            ret = JD_ERR_NOT_SUPPORT_DISTINCT;
        }

        /* resolve from clause */
        if (ret == OB_SUCCESS)
        {
            ret = resolve_from_clause(result_plan, select_stmt, node->children_[2]);
        }
        
        if (ret == OB_SUCCESS && node->children_[12] && node->children_[12]->value_ == 1)
        {
            if (select_stmt->get_table_size() != 1)
            {
                ret = JD_ERR_ILLEGAL_ID;
                jlog(WARNING, "Select for update statement can only process one table");
            }
            else
            {
                TableItem& table_item = select_stmt->get_table_item(0);
                uint64_t table_id = table_item.table_id_;
                ret = add_all_rowkey_columns_to_stmt(result_plan, table_id, select_stmt);
            }
        }
        /* resolve select clause */
        /* resolve where clause */
        /* resolve group by clause */
        /* resolve having clause */
        if (ret == OB_SUCCESS
            && (ret = resolve_select_clause(result_plan, select_stmt, node->children_[1]))
            == OB_SUCCESS
            && (ret = resolve_where_clause(result_plan, select_stmt, node->children_[3]))
            == OB_SUCCESS
            && (ret = resolve_group_clause(result_plan, select_stmt, node->children_[4]))
            == OB_SUCCESS
            && (ret = resolve_having_clause(result_plan, select_stmt, node->children_[5]))
            == OB_SUCCESS
            )
        {
            ;
        }
    }

    /* resolve order by clause */
    /* resolve limit clause */
    if (ret == OB_SUCCESS
        && (ret = resolve_order_clause(result_plan, select_stmt, node->children_[10]))
        == OB_SUCCESS
        && (ret = resolve_limit_clause(result_plan, select_stmt, node->children_[11]))
        == OB_SUCCESS
        && (ret = resolve_for_update_clause(result_plan, select_stmt, node->children_[12]))
        == OB_SUCCESS
        )
    {
        ;
    }

    // In some cases, some table(s) may have none column mentioned,
    // considerating the optimization, not all columns needed, we only need to scan out one of its columns
    // Example:
    // 1. select count(*) from t1;
    // 2. select t1.c1 from t1, t2;
    if (ret == OB_SUCCESS && select_stmt->get_table_size() > 0)
    {
        for (uint32_t i = 0; ret == OB_SUCCESS && i < select_stmt->get_table_size(); i++)
        {
            TableItem& table_item = select_stmt->get_table_item(i);
            if (!table_item.has_scan_columns_)
                ret = resolve_table_columns(result_plan, select_stmt, table_item, 1);
        }
    }

    if (ret == OB_SUCCESS && node->children_[13])
    {
        ret = resolve_hints(result_plan, select_stmt, node->children_[13]);
    }

    return ret;
}

int resolve_hints(
        ResultPlan * result_plan,
        ObStmt* stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        ObQueryHint& query_hint = stmt->get_query_hint();
        OB_ASSERT(node->type_ == T_HINT_OPTION_LIST && node->num_child_ > 0);
        for (int32_t i = 0; i < node->num_child_; i++)
        {
            ParseNode* hint_node = node->children_[i];
            assert(hint_node);
            switch (hint_node->type_)
            {
                case T_READ_STATIC:
                    query_hint.read_static_ = true;
                    break;
                default:
                    ret = JD_ERR_HINT_UNKNOWN;
                    jlog(WARNING, "Unknown hint '%s'", get_type_name(hint_node->type_));
                    break;
            }
        }
    }
    return ret;
}

int resolve_delete_stmt(
        ResultPlan* result_plan,
        ParseNode* node,
        uint64_t& query_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t table_id = OB_INVALID_ID;
    OB_ASSERT(node && node->type_ == T_DELETE && node->num_child_ >= 2);
    query_id = OB_INVALID_ID;

    ObLogicalPlan* logical_plan = NULL;
    //stringBuf* name_pool = static_cast<stringBuf*>(result_plan->name_pool_);
    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*) parse_malloc(sizeof (ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObLogicalPlan");
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    }

    if (ret == OB_SUCCESS)
    {
        ObDeleteStmt* delete_stmt = (ObDeleteStmt*) parse_malloc(sizeof (ObDeleteStmt), NULL);
        if (delete_stmt == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObDeleteStmt");
        }
        else
        {
            delete_stmt = new(delete_stmt) ObDeleteStmt();
            query_id = logical_plan->generate_query_id();
            delete_stmt->set_query_id(query_id);
            ret = logical_plan->add_query(delete_stmt);
            if (ret != OB_SUCCESS)
            {
                jlog(WARNING, "Can not add ObDeleteStmt to logical plan");
            }
            else
            {
                ParseNode* table_node = node->children_[0];
                if (table_node->type_ != T_IDENT)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING,  "Only single base table is supported for delete");
                }
                if (ret == OB_SUCCESS)
                {
                    ret = resolve_table(result_plan, delete_stmt, table_node, table_id);
                }
                if (ret == OB_SUCCESS)
                {
                    ret = add_all_rowkey_columns_to_stmt(result_plan, table_id, delete_stmt);
                }
                if (ret == OB_SUCCESS)
                {
                    delete_stmt->set_delete_table(table_id);
                    ret = resolve_where_clause(result_plan, delete_stmt, node->children_[1]);
                }
            }
        }
    }
    return ret;
}

int resolve_insert_columns(
        ResultPlan * result_plan,
        ObInsertStmt* insert_stmt,
        ParseNode* node)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    if (node)
    {
        OB_ASSERT(node->type_ == T_COLUMN_LIST);
        ColumnItem* column_item = NULL;
        ParseNode* column_node = NULL;


        for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
        {
            column_node = node->children_[i];
            OB_ASSERT(column_node->type_ == T_IDENT);

            string column_name;
            column_name.assign((char*) (column_node->str_value_), static_cast<int32_t> (strlen(column_node->str_value_)));
            column_item = insert_stmt->get_column_item(NULL, column_name);
            if (column_item == NULL)
            {
                if ((ret = insert_stmt->add_column_item(*result_plan, column_name)) != OB_SUCCESS)
                {
                    break;
                }
            }
            else
            {
                ret = JD_ERR_COLUMN_DUPLICATE;
                jlog(WARNING, "Column %s are duplicate", column_node->str_value_);
                break;
            }
        }
    }
    else
    {
        if (insert_stmt->get_table_size() != 1)
        {
            ret = JD_ERR_PARSER_SYNTAX;
            jlog(WARNING, "Insert statement only support one table");
        }
        if (ret == OB_SUCCESS)
        {
            TableItem& table_item = insert_stmt->get_table_item(0);
            if (table_item.type_ != TableItem::BASE_TABLE)
            {
                ret = JD_ERR_PARSER_SYNTAX;
                jlog(WARNING, "Only base table can be inserted");
            }
            else
                ret = resolve_table_columns(result_plan, insert_stmt, table_item);
        }
    }

    if (OB_SUCCESS == ret)
    {
        for (uint32_t i = 0; OB_SUCCESS == ret && i < insert_stmt->get_column_size(); i++)
        {
            const ColumnItem* column_item = insert_stmt->get_column_item(i);
            if (NULL != column_item && column_item->table_id_ != OB_INVALID_ID)
            {
#if 0      
                DBMetaReader* g_metareader = static_cast<DBMetaReader*> (result_plan->meta_reader_);
                if (g_metareader == NULL)
                {
                    ret = JD_ERR_SCHEMA_UNSET;
                    jlog(WARNING,"Schema(s) are not set");
                    break;
                }

                if (g_metareader->is_join_column(column_item->table_id_, column_item->column_id_))
                {
                    ret = JD_ERR_INSERT_INNER_JOIN_COLUMN;
                    jlog(WARNING, "Cannot insert inner join column: %.*s", column_item->column_name_.size(), column_item->column_name_.data());
                    break;
                }
#endif        
            }
        }
    }
    return ret;
}

int resolve_insert_values(
        ResultPlan * result_plan,
        ObInsertStmt* insert_stmt,
        ParseNode* node)
{
    OB_ASSERT(node->type_ == T_VALUE_LIST);
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    ObLogicalPlan* logical_plan = NULL;
    logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);

    vector<uint64_t> value_row;
    for (int32_t i = 0; ret == OB_SUCCESS && i < node->num_child_; i++)
    {
        ParseNode* vector_node = node->children_[i];
        uint64_t expr_id;
        for (int32_t j = 0; ret == OB_SUCCESS && j < vector_node->num_child_; j++)
        {
            ret = resolve_independ_expr(result_plan, insert_stmt, vector_node->children_[j],
                    expr_id, T_INSERT_LIMIT);
            if (ret != OB_SUCCESS)
            {
                jlog(WARNING, "Can not add expr_id to vector");
                break;
            }
            value_row.push_back(expr_id);
        }

        if (ret == OB_SUCCESS &&
                insert_stmt->get_column_size() != value_row.size())
        {
            ret = JD_ERR_COLUMN_SIZE;
            jlog(WARNING, "Column count doesn't match value count");
        }
        
        if (ret == OB_SUCCESS)
        {
            if ((ret = insert_stmt->add_value_row(value_row)) != OB_SUCCESS)
                jlog(WARNING, "Add value-row to ObInsertStmt error");
        }
        value_row.clear();
    }

    return ret;
}

int resolve_insert_stmt(
        ResultPlan* result_plan,
        ParseNode* node,
        uint64_t& query_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t table_id = OB_INVALID_ID;
    OB_ASSERT(node && node->type_ == T_INSERT && node->num_child_ >= 5);
    query_id = OB_INVALID_ID;

    ObLogicalPlan* logical_plan = NULL;
    //stringBuf* name_pool = static_cast<stringBuf*>(result_plan->name_pool_);
    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*) parse_malloc(sizeof (ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObLogicalPlan");
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    }


    if (ret == OB_SUCCESS)
    {

        ObInsertStmt* insert_stmt = (ObInsertStmt*) parse_malloc(sizeof (ObInsertStmt), NULL);
        if (insert_stmt == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObInsertStmt");
        }
        else
        {
            insert_stmt = new(insert_stmt) ObInsertStmt();
            query_id = logical_plan->generate_query_id();
            insert_stmt->set_query_id(query_id);
            ret = logical_plan->add_query(insert_stmt);

            if (ret != OB_SUCCESS)
            {
                jlog(WARNING, "Can not add ObInsertStmt to logical plan");
            }
            else
            {
                ParseNode* table_node = node->children_[0];
                if (table_node->type_ != T_IDENT)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "Only single base table is supported for insert");
                }
                if (ret == OB_SUCCESS)
                    ret = resolve_table(result_plan, insert_stmt, table_node, table_id);

                if (ret == OB_SUCCESS)
                {
                    insert_stmt->set_insert_table(table_id);
                    ret = resolve_insert_columns(result_plan, insert_stmt, node->children_[1]);
                }
                if (ret == OB_SUCCESS)
                {
                    // value list
                    if (node->children_[2])
                    {
                        ret = resolve_insert_values(result_plan, insert_stmt, node->children_[2]);
                    }
                    else
                    {
                        // value from sub-query(insert into table select ..)
                        OB_ASSERT(node->children_[3] && node->children_[3]->type_ == T_SELECT);
                        uint64_t ref_id = OB_INVALID_ID;
                        ret = JD_ERR_SQL_NO_SUBQUERY;
                        jlog(WARNING, "Now we DO NOT support sub-query in insert");
                        
                        if (ret == OB_SUCCESS)
                        {
                            ret = resolve_select_stmt(result_plan, node->children_[3], ref_id);
                        }
                        if (ret == OB_SUCCESS)
                        {
                            insert_stmt->set_insert_query(ref_id);
                            ObSelectStmt* select_stmt = static_cast<ObSelectStmt*> (logical_plan->get_query(ref_id));
                            if (select_stmt == NULL)
                            {
                                ret = JD_ERR_ILLEGAL_ID;
                                jlog(WARNING, "Invalid query id of sub-query");
                            }
                            if (ret == OB_SUCCESS &&
                                    insert_stmt->get_column_size() != select_stmt->get_select_item_size())
                            {
                                ret = JD_ERR_COLUMN_SIZE;
                                jlog(WARNING, "select values are not match insert columns");
                            }
                        }
                    }
                }
                if (ret == OB_SUCCESS)
                {
                    OB_ASSERT(node->children_[4] && node->children_[4]->type_ == T_BOOL);
                    if (node->children_[4]->value_ == 1)
                        insert_stmt->set_replace(true);
                    else
                        insert_stmt->set_replace(false);
                }
            }
        }
    }
    return ret;
}

int resolve_update_stmt(
        ResultPlan* result_plan,
        ParseNode* node,
        uint64_t& query_id)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    uint64_t table_id = OB_INVALID_ID;
    OB_ASSERT(node && node->type_ == T_UPDATE && node->num_child_ >= 3);
    query_id = OB_INVALID_ID;

    ObLogicalPlan* logical_plan = NULL;
    //stringBuf* name_pool = static_cast<stringBuf*>(result_plan->name_pool_);
    if (result_plan->plan_tree_ == NULL)
    {
        logical_plan = (ObLogicalPlan*) parse_malloc(sizeof (ObLogicalPlan), NULL);
        if (logical_plan == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObLogicalPlan");
        }
        else
        {
            logical_plan = new(logical_plan) ObLogicalPlan();
            result_plan->plan_tree_ = logical_plan;
        }
    }
    else
    {
        logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    }

    if (ret == OB_SUCCESS)
    {
        ObUpdateStmt* update_stmt = (ObUpdateStmt*) parse_malloc(sizeof (ObUpdateStmt), NULL);
        if (update_stmt == NULL)
        {
            ret = JD_ERR_PARSER_MALLOC_FAILED;
            jlog(WARNING, "Can not malloc ObUpdateStmt");
        }
        else
        {
            update_stmt = new(update_stmt) ObUpdateStmt();
            query_id = logical_plan->generate_query_id();
            update_stmt->set_query_id(query_id);
            ret = logical_plan->add_query(update_stmt);
            if (ret != OB_SUCCESS)
            {
                jlog(WARNING, "Can not add ObUpdateStmt to logical plan");
            }
            else
            {
                ParseNode* table_node = node->children_[0];
                if (table_node->type_ != T_IDENT)
                {
                    ret = JD_ERR_PARSER_SYNTAX;
                    jlog(WARNING, "Only single base table is supported for Update");
                }
                if (ret == OB_SUCCESS)
                {
                    ret = resolve_table(result_plan, update_stmt, table_node, table_id);
                }
                if (ret == OB_SUCCESS)
                {
                    ret = add_all_rowkey_columns_to_stmt(result_plan, table_id, update_stmt);
                }
                if (ret == OB_SUCCESS)
                {
                    update_stmt->set_update_table(table_id);
                    ParseNode* assign_list = node->children_[1];
                    OB_ASSERT(assign_list && assign_list->type_ == T_ASSIGN_LIST);
                    uint64_t ref_id;
                    ColumnItem *column_item = NULL;
                    for (int32_t i = 0; ret == OB_SUCCESS && i < assign_list->num_child_; i++)
                    {
                        ParseNode* assgin_node = assign_list->children_[i];
                        OB_ASSERT(assgin_node && assgin_node->type_ == T_ASSIGN_ITEM && assgin_node->num_child_ >= 2);

                        /* resolve target column */
                        ParseNode* column_node = assgin_node->children_[0];
                        OB_ASSERT(column_node && column_node->type_ == T_IDENT);
                        string column_name;
                        column_name.assign(
                                (char*) (column_node->str_value_),
                                static_cast<int32_t> (strlen(column_node->str_value_))
                                );
                        column_item = update_stmt->get_column_item(NULL, column_name);
                        if (column_item == NULL)
                        {
                            ret = update_stmt->add_column_item(*result_plan, column_name, NULL, &column_item);
                        }
                        if (ret == OB_SUCCESS)
                        {
                            ret = update_stmt->add_update_column(column_item->column_id_);
                        }
                        /* resolve new value expression */
                        if (ret == OB_SUCCESS)
                        {
                            ParseNode* expr = assgin_node->children_[1];
                            ret = resolve_independ_expr(result_plan, update_stmt, expr, ref_id, T_UPDATE_LIMIT);
                        }
                        if (ret == OB_SUCCESS)
                        {
                            if ((ret = update_stmt->add_update_expr(ref_id)) != OB_SUCCESS)
                            {
                                jlog(WARNING, "Add update value error");
                            }
                        }
                    }
                }
                if (ret == OB_SUCCESS)
                    ret = resolve_where_clause(result_plan, update_stmt, node->children_[2]);
            }
        }
    }
    return ret;
}



////////////////////////////////////////////////////////////////

int resolve(ResultPlan* result_plan, ParseNode* node)
{
    if (!result_plan)
    {
        jlog(ERROR, "null result_plan");
        return JD_ERR_RESOLVE_SQL;
    }
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;


    uint64_t query_id = OB_INVALID_ID;
    if (ret == OB_SUCCESS && node != NULL)
    {
        switch (node->type_)
        {
            case T_STMT_LIST:
            {
                //ret = resolve_multi_stmt(result_plan, node);
                break;
            }
            case T_SELECT:
            {
                ret = resolve_select_stmt(result_plan, node, query_id);
                break;
            }
            case T_DELETE:
            {
                ret = resolve_delete_stmt(result_plan, node, query_id);
                break;
            }
            case T_INSERT:
            {
                ret = resolve_insert_stmt(result_plan, node, query_id);
                break;
            }
            case T_UPDATE:
            {
                ret = resolve_update_stmt(result_plan, node, query_id);
                break;
            }
            default:
                jlog(WARNING, "unknown top node type=%d", node->type_);
                ret = JD_ERR_UNEXPECTED;
                break;
        };
    }

#if 0
    if (ret == OB_SUCCESS && node->type_ != T_STMT_LIST && node->type_ != T_PREPARE)
    {
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        if (logical_plan != NULL && logical_plan->get_question_mark_size() > 0)
        {
            ret = JD_ERR_PARSE_SQL;
            jlog(ERROR, "Uknown column '?'");
        }
    }
#endif
    if (ret != OB_SUCCESS && result_plan->plan_tree_ != NULL)
    {
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
        logical_plan->~ObLogicalPlan();
        parse_free(result_plan->plan_tree_);
        result_plan->plan_tree_ = NULL;
    }
    return ret;
}


