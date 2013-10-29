#include "ob_select_stmt.h"
#include "parse_malloc.h"
#include "ob_logical_plan.h"
//#include "sql_parser.tab.h"
#include "utility.h"

extern meta_reader *g_metareader;

using namespace oceanbase::sql;
using namespace oceanbase::common;

ObSelectStmt::ObSelectStmt()
: ObStmt(ObStmt::T_SELECT)
{
    //if (m_columnMap.create(MAX_MAP_BUCKET_NUM) == -1)
    //  throw new ParseException(name_pool_, "Create m_columnMap error!");
    left_query_id_ = OB_INVALID_ID;
    right_query_id_ = OB_INVALID_ID;
    limit_count_id_ = OB_INVALID_ID;
    limit_offset_id_ = OB_INVALID_ID;
    for_update_ = false;
    gen_joined_tid_ = UINT64_MAX - 2;
}

ObSelectStmt::~ObSelectStmt()
{
    // m_columnMap.destroy();
    for (int32_t i = 0; i < joined_tables_.size(); i++)
    {
        //ob_free(reinterpret_cast<char *>(joined_tables_[i]));
        joined_tables_[i]->~JoinedTable();
        parse_free(joined_tables_[i]);
    }
    select_items_.clear();
    select_items_.clear();
    joined_tables_.clear();
    group_expr_ids_.clear();
    order_items_.clear();
}

int ObSelectStmt::check_alias_name(
        ResultPlan& result_plan,
        const string& alias_name)
{
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObLogicalPlan *logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);

    for (int32_t i = 0; ret == OB_SUCCESS && i < table_items_.size(); i++)
    {
        /* check if it is column of base-table */
        TableItem& item = table_items_[i];
        if (item.type_ == TableItem::BASE_TABLE
                || item.type_ == TableItem::ALIAS_TABLE)
        {
            string db_name_tmp;
            db_name_tmp.assign(result_plan.db_name);
            schema_column* schema_column = g_metareader->get_column_schema(db_name_tmp, item.table_name_, alias_name);
            if (NULL == schema_column)
            {
                ret = OB_ERR_COLUMN_DUPLICATE;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "alias name %.*s is ambiguous", alias_name.size(), alias_name.data());
                break;
            }
        }
        else if (item.type_ == TableItem::GENERATED_TABLE)
        {
            /* check if it is column of generated-table */
            ObSelectStmt* sub_query = static_cast<ObSelectStmt*> (logical_plan->get_query(item.ref_id_));
            for (int32_t j = 0; ret == OB_SUCCESS && j < sub_query->get_select_item_size(); j++)
            {
                const SelectItem& select_item = sub_query->get_select_item(j);
                if (select_item.alias_name_ == alias_name)
                {
                    ret = OB_ERR_COLUMN_DUPLICATE;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "alias name %.*s is ambiguous", alias_name.size(), alias_name.data());
                    break;
                }
            }
        }
    }

    /* check if it is alias name of self-select */
    for (int32_t i = 0; ret == OB_SUCCESS && i < select_items_.size(); i++)
    {
        const SelectItem& select_item = get_select_item(i);
        if (select_item.alias_name_ == alias_name)
        {
            ret = OB_ERR_COLUMN_DUPLICATE;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "alias name %.*s is ambiguous", alias_name.size(), alias_name.data());
            break;
        }
    }

    return ret;
}

int ObSelectStmt::add_select_item(
        uint64_t eid,
        bool is_real_alias,
        const string& alias_name,
        const string& expr_name,
        const ObObjType& type)
{
    int ret = OB_SUCCESS;
    if (eid != OB_INVALID_ID)
    {
        SelectItem item;
        item.expr_id_ = eid;
        item.is_real_alias_ = is_real_alias;
        ret = ob_write_string(alias_name, item.alias_name_);
        if (ret == OB_SUCCESS)
            ret = ob_write_string(expr_name, item.expr_name_);
        if (ret == OB_SUCCESS)
        {
            item.type_ = type;
            select_items_.push_back(item);
        }
    }
    else
    {
        ret = OB_ERR_ILLEGAL_ID;
    }
    return ret;
}

// return the first expr with name alias_name

uint64_t ObSelectStmt::get_alias_expr_id(string& alias_name)
{
    uint64_t expr_id = OB_INVALID_ID;
    for (int32_t i = 0; i < select_items_.size(); i++)
    {
        SelectItem& item = select_items_[i];
        if (alias_name == item.alias_name_)
        {
            expr_id = item.expr_id_;
            break;
        }
    }
    return expr_id;
}

JoinedTable* ObSelectStmt::get_joined_table(uint64_t table_id)
{
    JoinedTable *joined_table = NULL;
    int32_t num = get_joined_table_size();
    for (int32_t i = 0; i < num; i++)
    {
        if (joined_tables_[i]->joined_table_id_ == table_id)
        {
            joined_table = joined_tables_[i];
            break;
        }
    }
    return joined_table;
}

int ObSelectStmt::check_having_ident(
        ResultPlan& result_plan,
        string& column_name,
        TableItem* table_item,
        ObRawExpr*& ret_expr)
{
    ObSqlRawExpr *sql_expr;
    ObRawExpr *expr;
    ret_expr = NULL;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }


    for (int32_t i = 0; ret == OB_SUCCESS && i < select_items_.size(); i++)
    {
        const SelectItem& select_item = get_select_item(i);
        // for single column expression, we already set it as alias name
        if (column_name == select_item.alias_name_)
        {
            sql_expr = logical_plan->get_expr(select_item.expr_id_);
            expr = sql_expr->get_expr();
            if (table_item)
            {
                if (expr->get_expr_type() == T_REF_COLUMN)
                {
                    ObBinaryRefRawExpr* col_expr = dynamic_cast<ObBinaryRefRawExpr *> (expr);
                    if (col_expr && col_expr->get_first_ref_id() == table_item->table_id_)
                    {
                        ColumnItem* column_item = get_column_item_by_id(col_expr->get_first_ref_id(), col_expr->get_second_ref_id());
                        if (column_item && column_item->column_name_ == column_name)
                        {
                            ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                            b_expr = new(b_expr) ObBinaryRefRawExpr();
                            b_expr->set_expr_type(T_REF_COLUMN);
                            b_expr->set_first_ref_id(col_expr->get_first_ref_id());
                            b_expr->set_second_ref_id(col_expr->get_second_ref_id());
                            ret_expr = b_expr;
                            break;
                        }
                    }
                }
            }
            else
            {
                if (ret_expr)
                {
                    ret = OB_ERR_COLUMN_AMBIGOUS;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "column %.*s of having clause is ambiguous", column_name.size(), column_name.data());
                    parse_free(ret_expr);
                    ret_expr = NULL;
                    break;
                }
                // for having clause: having cc > 0
                // type 1: select t1.cc
                if (expr->get_expr_type() == T_REF_COLUMN && !select_item.is_real_alias_)
                {
                    ObBinaryRefRawExpr *col_expr = dynamic_cast<ObBinaryRefRawExpr *> (expr);
                    ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                    b_expr = new(b_expr) ObBinaryRefRawExpr();
                    b_expr->set_expr_type(T_REF_COLUMN);
                    b_expr->set_first_ref_id(col_expr->get_first_ref_id());
                    b_expr->set_second_ref_id(col_expr->get_second_ref_id());
                    ret_expr = b_expr;
                }
                    // type 2: select t1.cc as cc
                    // type 3: select t1.c1 as cc
                    // type 4: select t1.c1 + t2.c1 as cc
                else
                {
                    ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                    b_expr = new(b_expr) ObBinaryRefRawExpr();
                    b_expr->set_expr_type(T_REF_COLUMN);
                    b_expr->set_first_ref_id(OB_INVALID_ID);
                    b_expr->set_second_ref_id(sql_expr->get_column_id());
                    ret_expr = b_expr;
                }
            }
        }
    }

    // No non-duplicated ident found
    if (ret == OB_SUCCESS && ret_expr == NULL)
    {
        for (int32_t i = 0; ret == OB_SUCCESS && i < group_expr_ids_.size(); i++)
        {
            sql_expr = logical_plan->get_expr(group_expr_ids_[i]);
            expr = sql_expr->get_expr();
            //ObRawExpr* expr = logical_plan->get_expr(group_expr_ids_[i])->get_expr();
            if (expr->get_expr_type() != T_REF_COLUMN)
                continue;

            ObBinaryRefRawExpr* col_expr = dynamic_cast<ObBinaryRefRawExpr *> (expr);
            // Only need to check original columns, alias columns are already checked before
            if (table_item == NULL || table_item->table_id_ == col_expr->get_first_ref_id())
            {
                ColumnItem* column_item = get_column_item_by_id(
                        col_expr->get_first_ref_id(),
                        col_expr->get_second_ref_id());
                if (column_item && column_name == column_item->column_name_)
                {
                    ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                    b_expr = new(b_expr) ObBinaryRefRawExpr();
                    b_expr->set_expr_type(T_REF_COLUMN);
                    b_expr->set_first_ref_id(column_item->table_id_);
                    b_expr->set_second_ref_id(column_item->column_id_);
                    ret_expr = b_expr;
                    break;
                }
            }
        }
    }

    if (ret == OB_SUCCESS && ret_expr == NULL)
    {
        ret = OB_ERR_COLUMN_UNKNOWN;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Unknown %.*s in having clause", column_name.size(), column_name.data());
    }
    return ret;
}

int ObSelectStmt::copy_select_items(ObSelectStmt* select_stmt)
{
    int ret = OB_SUCCESS;
    int32_t num = select_stmt->get_select_item_size();
    SelectItem new_select_item;
    for (int32_t i = 0; ret == OB_SUCCESS && i < num; i++)
    {
        const SelectItem& select_item = select_stmt->get_select_item(i);
        new_select_item.expr_id_ = select_item.expr_id_;
        new_select_item.type_ = select_item.type_;
        ret = ob_write_string(select_item.alias_name_, new_select_item.alias_name_);
        if (ret == OB_SUCCESS)
            ret = ob_write_string(select_item.expr_name_, new_select_item.expr_name_);
        if (ret == OB_SUCCESS)
            select_items_.push_back(new_select_item);
    }
    return ret;
}

void ObSelectStmt::print(FILE* fp, int32_t level, int32_t index)
{
    int32_t i;

    print_indentation(fp, level);
    fprintf(fp, "ObSelectStmt %d Begin\n", index);
    ObStmt::print(fp, level);

    if (set_op_ == NONE)
    {
        print_indentation(fp, level);
        if (is_distinct_)
            fprintf(fp, "SELECT ::= DISTINCT ");
        else
            fprintf(fp, "SELECT ::= ");
        for (i = 0; i < select_items_.size(); i++)
        {
            if (i > 0)
                fprintf(fp, ", ");
            SelectItem& item = select_items_[i];
            if (item.alias_name_.size() > 0)
                fprintf(fp, "<%lu, %.*s>", item.expr_id_,
                    item.alias_name_.size(), item.alias_name_.data());
            else
                fprintf(fp, "<%ld>", item.expr_id_);
        }
        fprintf(fp, "\n");

        print_indentation(fp, level);
        fprintf(fp, "FROM ::= ");
        for (i = 0; i < from_items_.size(); i++)
        {
            if (i > 0)
                fprintf(fp, ", ");
            FromItem& item = from_items_[i];
            if (item.is_joined_)
            {
                JoinedTable* joined_table = get_joined_table(item.table_id_);
                for (int32_t j = 1; j < joined_table->table_ids_.size(); j++)
                {
                    if (j == 1)
                        fprintf(fp, "<%lu> ", joined_table->table_ids_.at(j - 1));

                    switch (joined_table->join_types_.at(j - 1))
                    {
                        case JoinedTable::T_FULL:
                            fprintf(fp, "FULL JOIN ");
                            break;
                        case JoinedTable::T_LEFT:
                            fprintf(fp, "LEFT JOIN ");
                            break;
                        case JoinedTable::T_RIGHT:
                            fprintf(fp, "RIGHT JOIN ");
                            break;
                        case JoinedTable::T_INNER:
                            fprintf(fp, "INNER JOIN ");
                            break;
                        default:
                            break;
                    }
                    fprintf(fp, "<%lu> ", joined_table->table_ids_.at(j));
                    fprintf(fp, "ON <%lu>", joined_table->expr_ids_.at(j - 1));
                }
            }
            else
            {
                fprintf(fp, "<%lu>", item.table_id_);
            }
        }
        fprintf(fp, "\n");

        if (group_expr_ids_.size() > 0)
        {
            print_indentation(fp, level);
            fprintf(fp, "GROUP BY ::= ");
            for (i = 0; i < group_expr_ids_.size(); i++)
            {
                if (i > 0)
                    fprintf(fp, ", ");
                fprintf(fp, "<%lu>", group_expr_ids_[i]);
            }
            fprintf(fp, "\n");
        }

        if (having_expr_ids_.size() > 0)
        {
            print_indentation(fp, level);
            fprintf(fp, "HAVING ::= ");
            for (i = 0; i < having_expr_ids_.size(); i++)
            {
                if (i > 0)
                    fprintf(fp, ", ");
                fprintf(fp, "<%lu>", having_expr_ids_[i]);
            }
            fprintf(fp, "\n");
        }
    }
    else
    {
        print_indentation(fp, level);
        fprintf(fp, "LEFTQUERY ::= <%lu>\n", left_query_id_);
        print_indentation(fp, level);

        switch (set_op_)
        {
            case UNION:
                fprintf(fp, "<UNION ");
                break;
            case INTERSECT:
                fprintf(fp, "<INTERSECT ");
                break;
            case EXCEPT:
                fprintf(fp, "<EXCEPT ");
                break;
            default:
                break;
        }

        if (is_set_distinct_)
            fprintf(fp, "DISTINCT>\n");
        else
            fprintf(fp, "ALL>\n");

        print_indentation(fp, level);
        fprintf(fp, "RIGHTQUERY ::= <%lu>\n", right_query_id_);
    }

    for (i = 0; i < order_items_.size(); i++)
    {
        if (i == 0)
        {
            print_indentation(fp, level);
            fprintf(fp, "ORDER BY ::= ");
        }
        else
            fprintf(fp, ", ");
        OrderItem& item = order_items_[i];
        fprintf(fp, "<%lu, %s>", item.expr_id_,
                item.order_type_ == OrderItem::ASC ? "ASC" : "DESC");
        if (i == order_items_.size() - 1)
            fprintf(fp, "\n");
    }

    if (has_limit())
    {
        print_indentation(fp, level);
        fprintf(fp, "LIMIT ::= <");
        if (limit_count_id_ == OB_INVALID_ID)
            fprintf(fp, "NULL, ");
        else
            fprintf(fp, "%lu, ", limit_count_id_);
        if (limit_offset_id_ == OB_INVALID_ID)
            fprintf(fp, "NULL>\n");
        else
            fprintf(fp, "%lu>\n", limit_offset_id_);
    }

    print_indentation(fp, level);
    fprintf(fp, "ObSelectStmt %d End\n", index);
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
int64_t ObSelectStmt::make_stmt_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (set_op_ == NONE)
    {
        make_select_item_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        databuff_printf(buf, buf_len, pos, tmp_str);

        databuff_printf(buf, buf_len, pos, "FROM ");
        for (i = 0; i < from_items_.size(); i++)
        {
            FromItem& item = from_items_[i];
            if (item.is_joined_)
            {
                JoinedTable* joined_table = get_joined_table(item.table_id_);
                for (int32_t j = 1; j < joined_table->table_ids_.size(); j++)
                {
                    if (j == 1)
                    {
                        databuff_printf(buf, buf_len, pos, ObStmt::get_table_item_by_id(joined_table->table_ids_.at(j - 1))->table_name_.data());
                    }

                    switch (joined_table->join_types_.at(j - 1))
                    {
                        case JoinedTable::T_FULL:
                            databuff_printf(buf, buf_len, pos, " FULL JOIN ");
                            break;
                        case JoinedTable::T_LEFT:
                            databuff_printf(buf, buf_len, pos, " LEFT JOIN ");
                            break;
                        case JoinedTable::T_RIGHT:
                            databuff_printf(buf, buf_len, pos, " RIGHT JOIN ");
                            break;
                        case JoinedTable::T_INNER:
                            databuff_printf(buf, buf_len, pos, " JOIN ");
                            break;
                        default:
                            break;
                    }

                    databuff_printf(buf, buf_len, pos, ObStmt::get_table_item_by_id(joined_table->table_ids_.at(j))->table_name_.data());
                    databuff_printf(buf, buf_len, pos, " ON ");

                    sql_expr = logical_plan->get_expr_by_id(joined_table->expr_ids_.at(j - 1));
                    if (NULL == sql_expr)
                    {
                        ret = OB_ERR_LOGICAL_PLAN_FAILD;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "join table expr name error!!!");
                        return ret;
                    }
                    memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
                    sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
                    databuff_printf(buf, buf_len, pos, tmp_str);
                    databuff_printf(buf, buf_len, pos, " ");
                }
            }
            else
            {
                databuff_printf(buf, buf_len, pos, ObStmt::get_table_item_by_id(item.table_id_)->table_name_.data());
                if (i == from_items_.size() - 1)
                {
                    databuff_printf(buf, buf_len, pos, " ");
                }
                else
                {
                    databuff_printf(buf, buf_len, pos, ", ");
                }
            }
        }


        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        make_where_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        databuff_printf(buf, buf_len, pos, tmp_str);

        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        make_group_by_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        databuff_printf(buf, buf_len, pos, tmp_str);

        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        make_having_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        databuff_printf(buf, buf_len, pos, tmp_str);
    }
    else
    {
        fprintf(stderr, "LEFTQUERY ::= <%lu>\n", left_query_id_);

        switch (set_op_)
        {
            case UNION:
                fprintf(stderr, "<UNION ");
                break;
#if 0  /*mysql does not support*/
            case INTERSECT:
                fprintf(fp, "<INTERSECT ");
                break;
            case EXCEPT:
                fprintf(fp, "<EXCEPT ");
                break;
#endif  
            default:
                break;
        }

        if (is_set_distinct_)
            fprintf(stderr, "DISTINCT>\n");
        else
            fprintf(stderr, "ALL>\n");

        fprintf(stderr, "RIGHTQUERY ::= <%lu>\n", right_query_id_);
    }

    memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
    make_order_by_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
    databuff_printf(buf, buf_len, pos, tmp_str);
    memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
    make_limit_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
    databuff_printf(buf, buf_len, pos, tmp_str);

    return ret;
}

/**************************************************
Funtion     :   make_select_item_string
Author      :   qinbo
Date        :   2013.9.10
Description :   make select sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_select_item_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    ObSqlRawExpr* sql_expr = NULL;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (is_distinct_)
        databuff_printf(buf, buf_len, pos, "SELECT DISTINCT ");
    else
        databuff_printf(buf, buf_len, pos, "SELECT ");


    for (i = 0; i < select_items_.size(); i++)
    {
        SelectItem& item = select_items_[i];

        if (item.is_real_alias_)
        {
            databuff_printf(buf, buf_len, pos, item.expr_name_.data());
            databuff_printf(buf, buf_len, pos, " AS ");
            databuff_printf(buf, buf_len, pos, item.alias_name_.data());
            databuff_printf(buf, buf_len, pos, " ");

            if (i < select_items_.size() - 1)
            {
                databuff_printf(buf, buf_len, pos, ", ");
            }
            else
            {
                databuff_printf(buf, buf_len, pos, " ");
            }
        }
        else
        {
            sql_expr = logical_plan->get_expr_by_id(item.expr_id_);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "select expr error!!!");
                return ret;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);

            //databuff_printf(buf, buf_len, pos, item.expr_name_.data());

            if (i < select_items_.size() - 1)
            {
                databuff_printf(buf, buf_len, pos, ", ");
            }
            else
            {
                databuff_printf(buf, buf_len, pos, " ");
            }
        }
    }
    return ret;
}

/**************************************************
Funtion     :   make_group_by_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make select sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_group_by_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (group_expr_ids_.size() > 0)
    {
        databuff_printf(buf, buf_len, pos, "GROUP BY ");
        for (i = 0; i < group_expr_ids_.size(); i++)
        {
            sql_expr = logical_plan->get_expr_by_id(group_expr_ids_[i]);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "group by expr name error!!!");
                return ret;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);
            databuff_printf(buf, buf_len, pos, " ");
        }
    }

    return ret;
}

/**************************************************
Funtion     :   make_order_by_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make select sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_order_by_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }


    for (i = 0; i < order_items_.size(); i++)
    {
        if (i == 0)
        {
            databuff_printf(buf, buf_len, pos, "ORDER BY ");
        }

        OrderItem& item = order_items_[i];

        sql_expr = logical_plan->get_expr_by_id(item.expr_id_);
        if (NULL == sql_expr)
        {
            ret = OB_ERR_LOGICAL_PLAN_FAILD;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "order by expr name error!!!");
            return ret;
        }

        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        databuff_printf(buf, buf_len, pos, tmp_str);
        databuff_printf(buf, buf_len, pos, " ");
        databuff_printf(buf, buf_len, pos, item.order_type_ == OrderItem::ASC ? "ASC " : "DESC ");
    }

    return ret;
}

/**************************************************
Funtion     :   make_having_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make select sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_having_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }


    if (having_expr_ids_.size() > 0)
    {
        databuff_printf(buf, buf_len, pos, "HAVING ");
        for (i = 0; i < having_expr_ids_.size(); i++)
        {
            sql_expr = logical_plan->get_expr_by_id(having_expr_ids_[i]);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "having expr name error!!!");
                return ret;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);
            databuff_printf(buf, buf_len, pos, " ");
        }
    }

    return ret;
}

/**************************************************
Funtion     :   make_limit_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make select sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_limit_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }


    if (has_limit())
    {
        databuff_printf(buf, buf_len, pos, "LIMIT ");

        if (limit_offset_id_ == OB_INVALID_ID)
        {
            //fprintf(stderr, "NULL>\n");
        }
        else
        {
            sql_expr = logical_plan->get_expr_by_id(limit_offset_id_);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "limit offset expr name error!!!");
                return ret;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);
        }

        if (limit_count_id_ == OB_INVALID_ID)
        {
            //fprintf(stderr, "NULL, ");
        }
        else
        {
            sql_expr = logical_plan->get_expr_by_id(limit_count_id_);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "limit count expr name error!!!");
                return ret;
            }

            if (limit_offset_id_ != OB_INVALID_ID)
            {
                databuff_printf(buf, buf_len, pos, ", ");
            }
            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);
        }
    }

    return ret;
}

/**************************************************
Funtion     :   make_where_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make where sql
Input       :   ResultPlan& result_plan,
                char* buf, 
                const int64_t buf_len
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_where_string(ResultPlan& result_plan,
        char* buf,
        const int64_t buf_len)
{
    int32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

    if (where_exprs.size() > 0)
    {
        databuff_printf(buf, buf_len, pos, "WHERE ");
        for (i = 0; i < where_exprs.size(); i++)
        {
            sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "where expr name error!!!");
                return ret;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            databuff_printf(buf, buf_len, pos, tmp_str);
            if (i != where_exprs.size() - 1)
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

/**************************************************
Funtion     :   fetch_tables_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch table names from tree
Input       :   ResultPlan& result_plan,
Output      :   
 **************************************************/
vector<string> ObSelectStmt::fetch_tables_from_tree(ResultPlan& result_plan)
{
    int32_t i = 0;
    vector<string> table_names;

    if (is_from_item_with_join())
    {
        return table_names;
    }

    for (i = 0; i < from_items_.size(); i++)
    {
        FromItem& item = from_items_[i];
        string table_item = ObStmt::get_table_item_by_id(item.table_id_)->table_name_;
        table_names.push_back(table_item);
    }

    return table_names;
}

/**************************************************
Funtion     :   fetch_select_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch select items from tree
Input       :   ResultPlan& result_plan,
                string table_name
Output      :   
 **************************************************/
vector<SelectItem> ObSelectStmt::fetch_select_from_tree(ResultPlan& result_plan, string table_name)
{
    int32_t i = 0;
    int64_t pos = 0;
    ObSqlRawExpr* sql_expr = NULL;
    vector<SelectItem> select_items;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    for (i = 0; i < select_items_.size(); i++)
    {
        SelectItem& item = select_items_[i];

        sql_expr = logical_plan->get_expr_by_id(item.expr_id_);

        if (NULL == sql_expr)
        {
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "select item error!!!");
            return select_items;
        }

        ObBinaryRefRawExpr *select_expr = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));

        if (select_expr->get_first_ref_id() == OB_INVALID_ID)
        {
            sql_expr = logical_plan->get_expr_by_ref_sql_expr_raw_id(select_expr->get_related_sql_raw_id());
            if (NULL == sql_expr)
            {
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "ref column error!!!");
                return select_items;
            }

            if (sql_expr->get_expr()->is_aggr_fun())
            {
                ObAggFunRawExpr *agg_fun_raw_expr = dynamic_cast<ObAggFunRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));

                if (NULL != agg_fun_raw_expr->get_param_expr())
                {
                    if (!agg_fun_raw_expr->get_param_expr()->is_column())
                    {
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "select item error!!!");
                        return select_items;
                    }

                    memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
                    agg_fun_raw_expr->get_param_expr()->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
                    item.raw_select_item_name.assign(tmp_str, RAW_EXPR_BUF_SIZE);
                }
            }
        }
        else if (sql_expr->get_expr()->is_column())
        {
            item.raw_select_item_name.assign(item.expr_name_);
        }
        else
        {
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "select item error!!!");
            return select_items;
        }

        if (sql_expr->is_contain_aggr())
        {
            item.aggr_fun_type = sql_expr->get_contain_aggr_type();
        }
        else
        {
            item.aggr_fun_type = T_INVALID;
        }

        select_items.push_back(item);
    }

    return select_items;
}

/**************************************************
Funtion     :   fetch_where_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch where items from tree
Input       :   ResultPlan& result_plan,
                string table_name
Output      :   
 **************************************************/
vector<string> ObSelectStmt::fetch_where_from_tree(ResultPlan& result_plan, string table_name)
{
    int32_t i = 0;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;
    vector<string> where_items;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

    for (i = 0; i < where_exprs.size(); i++)
    {
        sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
        if (NULL == sql_expr)
        {
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "where expr name error!!!");
            return where_items;
        }

        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);

        where_items.push_back(tmp_str);
    }

    return where_items;
}

/**************************************************
Funtion     :   fetch_group_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch group by items from tree
Input       :   ResultPlan& result_plan,
                string table_name
Output      :   
 **************************************************/
vector<GroupItem> ObSelectStmt::fetch_group_from_tree(ResultPlan& result_plan, string table_name)
{
    int32_t i = 0;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;
    vector<GroupItem> group_items;
    GroupItem item = {0};
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (group_expr_ids_.size() > 0)
    {
        for (i = 0; i < group_expr_ids_.size(); i++)
        {
            sql_expr = logical_plan->get_expr_by_id(group_expr_ids_[i]);
            if (NULL == sql_expr)
            {
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "group by expr name error!!!");
                return group_items;
            }

            memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
            sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);

            item.group_type_ = GroupItem::ASC;
            item.group_column_.assign(tmp_str);
            group_items.push_back(item);
        }
    }

    return group_items;
}

/**************************************************
Funtion     :   fetch_order_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch order by items from tree
Input       :   ResultPlan& result_plan,
                string table_name
Output      :   
 **************************************************/
vector<OrderItem> ObSelectStmt::fetch_order_from_tree(ResultPlan& result_plan, string table_name)
{
    int32_t i = 0;
    int64_t pos = 0;
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    ObSqlRawExpr* sql_expr = NULL;
    vector<OrderItem> order_items;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    for (i = 0; i < order_items_.size(); i++)
    {
        OrderItem& item = order_items_[i];

        sql_expr = logical_plan->get_expr_by_id(item.expr_id_);
        if (NULL == sql_expr)
        {
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "order by expr name error!!!");
            return order_items;
        }

        memset(tmp_str, 0, RAW_EXPR_BUF_SIZE);
        sql_expr->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
        item.order_column.assign(tmp_str);


        order_items.push_back(item);
    }

    return order_items;
}

/**************************************************
Funtion     :   fetch_group_from_tree
Author      :   qinbo
Date        :   2013.9.24
Description :   fetch group by items from tree
Input       :   ResultPlan& result_plan,
                string table_name
Output      :   
 **************************************************/
LimitItem
ObSelectStmt::fetch_limit_from_tree(ResultPlan& result_plan)
{
    LimitItem limit_item;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    int64_t pos = 0;
    ObSqlRawExpr* sql_expr = NULL;
    ObConstRawExpr *const_raw_expr = NULL;
    bool is_add = false;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!!");
    }

    if (has_limit())
    {
        if (limit_offset_id_ != OB_INVALID_ID)
        {
            sql_expr = logical_plan->get_expr_by_id(limit_offset_id_);
            if (NULL != sql_expr)
            {
                if (sql_expr->get_expr()->is_const())
                {
                    const_raw_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
                    if (ObIntType == const_raw_expr->get_value().get_type())
                    {
                        const_raw_expr->get_value().get_int(limit_item.start, is_add);
                    }
                    else
                    {
                        ret = OB_ERR_LOGICAL_PLAN_FAILD;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "limit_offset set error!!!");
                    }
                }
                else
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                            "limit_offset set error!!!");
                }
            }
        }

        if (ret != OB_SUCCESS)
        {
            return limit_item;
        }

        if (limit_count_id_ != OB_INVALID_ID)
        {
            sql_expr = logical_plan->get_expr_by_id(limit_count_id_);
            if (NULL != sql_expr)
            {
                if (limit_offset_id_ != OB_INVALID_ID)
                {
                    if (sql_expr->get_expr()->is_const())
                    {
                        const_raw_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
                        if (ObIntType == const_raw_expr->get_value().get_type())
                        {
                            const_raw_expr->get_value().get_int(limit_item.end, is_add);
                        }
                        else
                        {
                            ret = OB_ERR_LOGICAL_PLAN_FAILD;
                            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                    "limit_count set error!!!");
                        }
                    }
                    else
                    {
                        ret = OB_ERR_LOGICAL_PLAN_FAILD;
                        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                                "limit_count set error!!!");
                    }
                }
            }
        }
    }
    return limit_item;
}


