#include <string>
#include <sstream>
#include <iostream> 
#include "ob_select_stmt.h"
#include "parse_malloc.h"
#include "ob_logical_plan.h"
//#include "sql_parser.tab.h"
#include "utility.h"

using namespace oceanbase::sql;
using namespace oceanbase::common;
using namespace std;

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
    is_sql_relate_multi_shards = false;
}

ObSelectStmt::~ObSelectStmt()
{
    // m_columnMap.destroy();
    for (uint32_t i = 0; i < joined_tables_.size(); i++)
    {
        //ob_free(reinterpret_cast<char *>(joined_tables_[i]));
        joined_tables_[i]->~JoinedTable();
        parse_free(joined_tables_[i]);
    }
    select_items_.clear();
    from_items_.clear();
    joined_tables_.clear();
    group_expr_ids_.clear();
    having_expr_ids_.clear();
    agg_func_ids_.clear();
    group_items_.clear();
    order_items_.clear();
    having_items_.clear();
}

int ObSelectStmt::check_alias_name(
        ResultPlan& result_plan,
        const string& alias_name)
{
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObLogicalPlan *logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);

    for (uint32_t i = 0; ret == OB_SUCCESS && i < table_items_.size(); i++)
    {
        /* check if it is column of base-table */
        TableItem& item = table_items_[i];
        if (item.type_ == TableItem::BASE_TABLE
                || item.type_ == TableItem::ALIAS_TABLE)
        {
            string db_name_tmp;
            db_name_tmp.assign(result_plan.db_name);
            schema_column* schema_column = meta_reader::get_instance().get_column_schema(db_name_tmp, item.table_name_, alias_name);
            if (NULL == schema_column)
            {
                ret = OB_ERR_COLUMN_DUPLICATE;
                jlog(WARNING, "alias name %.*s is ambiguous", (int)alias_name.size(), alias_name.data());
                break;
            }
        }
        else if (item.type_ == TableItem::GENERATED_TABLE)
        {
            /* check if it is column of generated-table */
            ObSelectStmt* sub_query = static_cast<ObSelectStmt*> (logical_plan->get_query(item.ref_id_));
            for (uint32_t j = 0; ret == OB_SUCCESS && j < sub_query->get_select_item_size(); j++)
            {
                const SelectItem& select_item = sub_query->get_select_item(j);
                if (select_item.alias_name_ == alias_name)
                {
                    ret = OB_ERR_COLUMN_DUPLICATE;
                    jlog(WARNING, "alias name %.*s is ambiguous", (int)alias_name.size(), alias_name.data());
                    break;
                }
            }
        }
    }

    /* check if it is alias name of self-select */
    for (uint32_t i = 0; ret == OB_SUCCESS && i < select_items_.size(); i++)
    {
        const SelectItem& select_item = get_select_item(i);
        if (select_item.alias_name_ == alias_name)
        {
            ret = OB_ERR_COLUMN_DUPLICATE;
            jlog(WARNING, "alias name %.*s is ambiguous", (int)alias_name.size(), alias_name.data());
            break;
        }
    }

    return ret;
}

int ObSelectStmt::add_select_item(
        ResultPlan *result_plan,
        uint64_t eid,
        bool is_real_alias,
        const string& alias_name,
        const string& expr_name,
        const ObObjType& type)
{
    int  ret = OB_SUCCESS;
    if (eid != OB_INVALID_ID)
    {
        SelectItem item;
        item.expr_id_ = eid;
        item.is_real_alias_ = is_real_alias;
        ret = ob_write_string(alias_name, item.alias_name_);
        if (ret == OB_SUCCESS)
            ret = ob_write_string(expr_name, item.expr_name_);

        ret = get_column_info_by_expr_id(result_plan, item.expr_id_, item.type_, item.aggr_fun_type, item.select_column_name_);

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

int ObSelectStmt::set_limit_offset(ResultPlan * result_plan, const uint64_t& offset, const uint64_t& limit)
{
    int& ret = result_plan->err_stat_.err_code_ = OB_SUCCESS;
    ObSqlRawExpr* sql_expr = NULL;
    ObConstRawExpr *const_raw_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }

    limit_count_id_ = limit;
    limit_offset_id_ = offset;

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
                    const_raw_expr->get_value().get_int(limit_item_.start);
                }
                else
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "limit_offset set error!!!");
                }
            }
            else
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "limit_offset set error!!!");
            }
        }
    }
    else
    {
        limit_item_.start = 0;
    }

    if (ret != OB_SUCCESS)
    {
        return ret;
    }

    if (limit_count_id_ != OB_INVALID_ID)
    {
        sql_expr = logical_plan->get_expr_by_id(limit_count_id_);
        if (NULL != sql_expr)
        {
            if (sql_expr->get_expr()->is_const())
            {
                const_raw_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
                if (ObIntType == const_raw_expr->get_value().get_type())
                {
                    const_raw_expr->get_value().get_int(limit_item_.end);
                    if (limit_item_.end > MAX_LIMIT_ROWS)
                    {
                        limit_item_.end = MAX_LIMIT_ROWS;
                    }
                }
                else
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "limit_count set error!!!");
                }
            }
            else
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "limit_count set error!!!");
            }
        }
    }
    else
    {
        limit_item_.end = MAX_LIMIT_ROWS;
    }
       
    return ret;
    
}

// return the first expr with name alias_name

uint64_t ObSelectStmt::get_alias_expr_id(string& alias_name)
{
    uint64_t expr_id = OB_INVALID_ID;
    for (uint32_t i = 0; i < select_items_.size(); i++)
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
    uint32_t num = get_joined_table_size();
    for (uint32_t i = 0; i < num; i++)
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
        jlog(WARNING, "logical_plan must exist!!!");
    }


    for (uint32_t i = 0; ret == OB_SUCCESS && i < select_items_.size(); i++)
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
                            if (b_expr == NULL)
                            {
                                ret = OB_ERR_PARSER_MALLOC_FAILED;
                                jlog(WARNING, "Can not malloc space for ObBinaryRefRawExpr!!!");
                                return ret;
                            }
                            else
                            {
                                b_expr = new(b_expr) ObBinaryRefRawExpr();
                                logical_plan->add_raw_expr(b_expr); //added by qinbo for avoiding mem leak
                            }
                            
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
                    jlog(WARNING, "column %.*s of having clause is ambiguous", (int)column_name.size(), column_name.data());
                    //parse_free(ret_expr);
                    ret_expr = NULL;
                    break;
                }
                // for having clause: having cc > 0
                // type 1: select t1.cc   
                // && !select_item.is_real_alias_
                if (expr->get_expr_type() == T_REF_COLUMN)
                {
                    ObBinaryRefRawExpr *col_expr = dynamic_cast<ObBinaryRefRawExpr *> (expr);
                    ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                    if (b_expr == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        jlog(WARNING, "Can not malloc space for ObBinaryRefRawExpr");
                        return ret;
                    }
                    else
                    {
                        b_expr = new(b_expr) ObBinaryRefRawExpr();
                        logical_plan->add_raw_expr(b_expr); //added by qinbo for avoiding mem leak
                    }
                    b_expr->set_expr_type(T_REF_COLUMN);
                    b_expr->set_first_ref_id(col_expr->get_first_ref_id());
                    b_expr->set_second_ref_id(col_expr->get_second_ref_id());

                    //only HAVING can have AGGR functions
                    if (sql_expr->is_contain_aggr())
                    {
                        b_expr->set_related_sql_raw_id(col_expr->get_related_sql_raw_id());
                    }
                    
                    ret_expr = b_expr;
                }
                // type 2: select t1.cc as cc
                // type 3: select t1.c1 as cc
                // type 4: select t1.c1 + t2.c1 as cc
                else
                {
                    ObBinaryRefRawExpr *b_expr = (ObBinaryRefRawExpr*) parse_malloc(sizeof (ObBinaryRefRawExpr), NULL);
                    if (b_expr == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        jlog(WARNING, "Can not malloc space for ObBinaryRefRawExpr");
                        return ret;
                    }
                    else
                    {
                        b_expr = new(b_expr) ObBinaryRefRawExpr();
                        logical_plan->add_raw_expr(b_expr); //added by qinbo for avoiding mem leak
                    }
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
        for (uint32_t i = 0; ret == OB_SUCCESS && i < group_expr_ids_.size(); i++)
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
                    if (b_expr == NULL)
                    {
                        ret = OB_ERR_PARSER_MALLOC_FAILED;
                        jlog(WARNING, "Can not malloc space for ObBinaryRefRawExpr");
                        return ret;
                    }
                    else
                    {
                        b_expr = new(b_expr) ObBinaryRefRawExpr();
                        logical_plan->add_raw_expr(b_expr); //added by qinbo for avoiding mem leak
                    }
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
        jlog(WARNING, "Unknown %.*s in having clause", (int)column_name.size(), column_name.data());
    }
    return ret;
}

int ObSelectStmt::copy_select_items(ObSelectStmt* select_stmt)
{
    int ret = OB_SUCCESS;
    uint32_t num = select_stmt->get_select_item_size();
    SelectItem new_select_item;
    for (uint32_t i = 0; ret == OB_SUCCESS && i < num; i++)
    {
        const SelectItem& select_item = select_stmt->get_select_item(i);
        new_select_item.expr_id_ = select_item.expr_id_;
        new_select_item.type_ = select_item.type_;
        new_select_item.aggr_fun_type = select_item.aggr_fun_type;
        ret = ob_write_string(select_item.alias_name_, new_select_item.alias_name_);
        if (ret == OB_SUCCESS)
            ret = ob_write_string(select_item.expr_name_, new_select_item.expr_name_);
        if (ret == OB_SUCCESS)
            ret = ob_write_string(select_item.select_column_name_, new_select_item.select_column_name_);
        if (ret == OB_SUCCESS)
            select_items_.push_back(new_select_item);
    }
    return ret;
}

void ObSelectStmt::print(FILE* fp, int32_t level, int32_t index)
{
    uint32_t i;

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
                    (int)item.alias_name_.size(), item.alias_name_.data());
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
                for (uint32_t j = 1; j < joined_table->table_ids_.size(); j++)
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
                item.order_type_ == T_SORT_ASC ? "ASC" : "DESC");
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
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
{
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;

    if (set_op_ == NONE)
    {
        make_select_item_string(result_plan, assembled_sql);
        make_from_string(result_plan, assembled_sql);
        make_where_string(result_plan, assembled_sql);
        make_group_by_string(result_plan, assembled_sql);
        make_having_string(result_plan, assembled_sql);
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

    make_order_by_string(result_plan, assembled_sql);
    make_limit_string(result_plan, assembled_sql);

    return ret;
}

/**************************************************
Funtion     :   make_exec_plan_unit_string
Author      :   qinbo
Date        :   2013.12.9
Description :   make select sql
Input       :   ResultPlan& result_plan,
                string where_conditions
                vector<schema_shard*> shard_info
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_exec_plan_unit_string(ResultPlan& result_plan, 
                                                string where_conditions, 
                                                vector<schema_shard*> binding_shard_info,
                                                string &assembled_sql)
{
    make_select_item_string(result_plan, assembled_sql);
    
    //when post process need column while this column is not in select_itmes, append them
    append_select_items_reduce_used(result_plan, assembled_sql);

    if (from_items_.size() != binding_shard_info.size())
    {
        jlog(ERROR, "sql parser error!!!");
        return OB_ERR_PARSE_SQL;
    }
   
    for (uint32_t i = 0; i < from_items_.size(); i++)
    {
        if (0 == i)
        {
            assembled_sql.append("FROM ");
        }

        FromItem& item = from_items_[i];
        string table_name = ObStmt::get_table_item_by_id(item.table_id_)->table_name_;
        if (table_name != binding_shard_info.at(i)->get_table_name())
        {
            assembled_sql.append(binding_shard_info.at(i)->get_shard_name());
            //from multi table
            if (from_items_.size() >1)
            {
                assembled_sql.append(" AS ");
                assembled_sql.append(table_name);
                assembled_sql.append(" ");
            }
        }
        else
        {
            assembled_sql.append(table_name);
        }
        
        if (i == from_items_.size() - 1)
        {
            assembled_sql.append(" ");
        }
        else
        {
            assembled_sql.append(", ");
        }
    }

    if (where_conditions.empty())
    {
        make_where_string(result_plan, assembled_sql);
    }
    else
    {
        assembled_sql.append(where_conditions);
        assembled_sql.append(" ");
    }
    
    make_group_by_string(result_plan, assembled_sql);
    make_having_string(result_plan, assembled_sql);

    if (!is_group_by_order_by_same(result_plan))
    {
        make_order_by_string(result_plan, assembled_sql);
    }
    make_limit_string(result_plan, assembled_sql);    
    return OB_SUCCESS;
}


/**************************************************
Funtion     :   make_select_item_string
Author      :   qinbo
Date        :   2013.9.10
Description :   make select sql
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_select_item_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }

    if (is_distinct_)
        assembled_sql.append("SELECT DISTINCT ");
    else
        assembled_sql.append("SELECT ");


    for (i = 0; i < select_items_.size(); i++)
    {
        string assembled_sql_tmp;
        SelectItem& item = select_items_[i];

        if (item.is_real_alias_)
        {
            sql_expr = logical_plan->get_expr_by_id(item.expr_id_);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "join table expr name error!!!");
                return ret;
            }
            string tmp;
            sql_expr->to_string(result_plan, tmp);
            assembled_sql.append(tmp);
            
            assembled_sql.append(" AS ");
            assembled_sql.append(item.alias_name_);

            if (i < select_items_.size() - 1)
            {
                assembled_sql.append(", ");
            }
            else
            {
                assembled_sql.append(" ");
            }
        }
        else
        {
            sql_expr = logical_plan->get_expr_by_id(item.expr_id_);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "select expr error!!!");
                return ret;
            }

            sql_expr->to_string(result_plan, assembled_sql_tmp);
            assembled_sql.append(assembled_sql_tmp);

            if (i < select_items_.size() - 1)
            {
                assembled_sql.append(", ");
            }
            else
            {
                assembled_sql.append(" ");
            }
        }
    }
    return ret;
}

/**************************************************
Funtion     :   append_select_items_reduce_used
Author      :   qinbo
Date        :   2013.12.6
Description :   this function is used to append extra 
                column names to exec_plan for sql post 
                process(such as order by/group by)
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::append_select_items_reduce_used(
        ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }

    vector<SelectItem> select_items = get_all_select_items();
    vector<GroupItem> group_items = get_all_group_items();
    vector<OrderItem> order_items = get_all_order_items();
    vector<HavingItem> Having_items = get_all_having_items();
    vector<string> exist_column_names;
    uint32_t column_off = 0;

    if (group_items.size() > 0)
    {
        for (i = 0; i < group_items.size(); i++)
        {
            if (!try_fetch_select_item_by_group(select_items,
                    group_items[i].group_column_, column_off))
            {
                if (exist_column_names.size() > 0)
                {
                    vector<string>::iterator pos;
                    pos = find(exist_column_names.begin(),
                            exist_column_names.end(), group_items[i].group_column_);
                    if (pos == exist_column_names.end())
                    {
                        assembled_sql.append(",");
                        assembled_sql.append(group_items[i].group_column_);
                        assembled_sql.append(" ");
                        exist_column_names.push_back(group_items[i].group_column_);
                    }
                }
                else
                {
                    assembled_sql.append(",");
                    assembled_sql.append(group_items[i].group_column_);
                    assembled_sql.append(" ");
                    exist_column_names.push_back(group_items[i].group_column_);
                }
            }
        }
    }

    if (having_expr_ids_.size() > 0)
    {
        for (i = 0; i < Having_items.size(); i++)
        {
            if (!try_fetch_select_item_by_having(select_items,
                    Having_items[i], column_off))
            {
#if 0
                if (exist_column_names.size() > 0)
                {
                    vector<string>::iterator pos;
                    pos = find(exist_column_names.begin(),
                            exist_column_names.end(),
                            Having_items[i].having_column_name);
                    if (pos == exist_column_names.end())
                    {
                        assembled_sql.append(",");
                        assembled_sql.append(Having_items[i].having_column_name);
                        assembled_sql.append(" ");
                        exist_column_names.push_back(
                                Having_items[i].having_column_name);
                    }
                }
                else
#endif
                {
                    assembled_sql.append(",");
                    switch (Having_items[i].aggr_fun_type)
                    {
                        case T_FUN_MAX:
                            assembled_sql.append("MAX(");
                            break;
                        case T_FUN_MIN:
                            assembled_sql.append("MIN(");
                            break;
                        case T_FUN_SUM:
                            assembled_sql.append("SUM(");
                            break;
                        case T_FUN_COUNT:
                            assembled_sql.append("COUNT(");
                            break;
                        case T_FUN_AVG:
                            assembled_sql.append("AVG(");
                            break;
                        default:
                            break;
                    }
                    assembled_sql.append(Having_items[i].having_column_name);
                    assembled_sql.append(")");
                    assembled_sql.append(" ");
                    //exist_column_names.push_back(
                      //      Having_items[i].having_column_name);
                }
            }
        }
    }

    if (!is_group_by_order_by_same(result_plan))
    {
        for (i = 0; i < order_items.size(); i++)
        {
            if (!try_fetch_select_item_by_column_name(select_items,
                    order_items[i].order_column_, column_off))
            {
                if (exist_column_names.size() > 0)
                {
                    vector<string>::iterator pos;
                    pos = find(exist_column_names.begin(),
                            exist_column_names.end(),
                            order_items[i].order_column_);
                    if (pos == exist_column_names.end())
                    {
                        assembled_sql.append(",");
                        assembled_sql.append(order_items[i].order_column_);
                        assembled_sql.append(" ");
                    }
                }
                else
                {
                    assembled_sql.append(",");
                    assembled_sql.append(order_items[i].order_column_);
                    assembled_sql.append(" ");
                }
            }
        }
    }

    return ret;
}


/**************************************************
Funtion     :   make_from_string
Author      :   qinbo
Date        :   2013.10.31
Description :   make_from_string
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_from_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }
    
    assembled_sql.append("FROM ");
    
    for (i = 0; i < from_items_.size(); i++)
    {
        FromItem& item = from_items_[i];
        if (item.is_joined_)
        {
            JoinedTable* joined_table = get_joined_table(item.table_id_);
            for (uint32_t j = 1; j < joined_table->table_ids_.size(); j++)
            {
                if (j == 1)
                {
                    assembled_sql.append(ObStmt::get_table_item_by_id(joined_table->table_ids_.at(j - 1))->table_name_);
                }
    
                switch (joined_table->join_types_.at(j - 1))
                {
                    case JoinedTable::T_FULL:
                        assembled_sql.append(" FULL JOIN ");
                        break;
                    case JoinedTable::T_LEFT:
                        assembled_sql.append(" LEFT JOIN ");
                        break;
                    case JoinedTable::T_RIGHT:
                        assembled_sql.append(" RIGHT JOIN ");
                        break;
                    case JoinedTable::T_INNER:
                        assembled_sql.append(" JOIN ");
                        break;
                    default:
                        break;
                }
    
                assembled_sql.append(ObStmt::get_table_item_by_id(joined_table->table_ids_.at(j))->table_name_);
                assembled_sql.append(" ON ");
    
                sql_expr = logical_plan->get_expr_by_id(joined_table->expr_ids_.at(j - 1));
                if (NULL == sql_expr)
                {
                    ret = OB_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "join table expr name error!!!");
                    return ret;
                }
                string tmp;
                sql_expr->to_string(result_plan, tmp);
                assembled_sql.append(tmp);
                assembled_sql.append(" ");
            }
        }
        else
        {
            assembled_sql.append(item.table_name_);
            if (i == from_items_.size() - 1)
            {
                assembled_sql.append(" ");
            }
            else
            {
                assembled_sql.append(", ");
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
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_group_by_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;

    if (group_items_.size() > 0)
    {
        assembled_sql.append(" GROUP BY ");
        for (i = 0; i < group_items_.size(); i++)
        {
            assembled_sql.append(group_items_.at(i).group_column_);
            assembled_sql.append(" ");
        }
        
        if ((group_items_.size() > 1)&&(i != group_items_.size()- 1))
        {
            assembled_sql.append(", ");        
        }
        else
        {
            assembled_sql.append(" ");        
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
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_order_by_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int&    ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;

    for (i = 0; i < order_items_.size(); i++)
    {
        string  assembled_sql_tmp;
        if (i == 0)
        {
            assembled_sql.append(" ORDER BY ");
        }

        OrderItem& item = order_items_[i];

        assembled_sql.append(item.order_column_);        
        assembled_sql.append(" ");
        assembled_sql.append(item.order_type_ == T_SORT_ASC ? "ASC " : "DESC ");
        if ((order_items_.size() > 1)&&(i != order_items_.size()- 1))
        {
            assembled_sql.append(", ");        
        }
        else
        {
            assembled_sql.append(" ");        
        }
    }

    return ret;
}

/**************************************************
Funtion     :   make_having_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make select sql
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_having_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }


    if (having_expr_ids_.size() > 0)
    {
        assembled_sql.append(" HAVING ");
        for (i = 0; i < having_expr_ids_.size(); i++)
        {
            string  assembled_sql_tmp;
            sql_expr = logical_plan->get_expr_by_id(having_expr_ids_[i]);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "having expr name error!!!");
                return ret;
            }
            assembled_sql.append("(");
            sql_expr->to_string(result_plan, assembled_sql_tmp);
            assembled_sql.append(assembled_sql_tmp);        
            assembled_sql.append(") ");
            if ((having_expr_ids_.size() > 1)&&(i != having_expr_ids_.size()- 1))
            {
                assembled_sql.append(", ");        
            }
            else
            {
                assembled_sql.append(" ");        
            }
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
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_limit_string(ResultPlan& result_plan, string &assembled_sql)
{
    assembled_sql.append("LIMIT ");
    if (is_sql_dispatched_multi_shards())
    {
        assembled_sql.append("0, ");
        stringstream  ss;
        string s;
        ss << limit_item_.start + limit_item_.end;
        ss >> s;
        assembled_sql.append(s);        
    }
    else
    {
        stringstream  ss1;
        string s1;
        ss1 << limit_item_.start;
        ss1 >> s1;
        assembled_sql.append(s1);       

        assembled_sql.append(", ");        

        stringstream  ss2;
        string s2;
        ss2 << limit_item_.end;
        ss2 >> s2;
        assembled_sql.append(s2);        
    }
    return OB_SUCCESS;
}

/**************************************************
Funtion     :   make_where_string
Author      :   qinbo
Date        :   2013.9.24
Description :   make where sql
Input       :   ResultPlan& result_plan,
                string &assembled_sql
Output      :   
 **************************************************/
int64_t ObSelectStmt::make_where_string(ResultPlan& result_plan, string &assembled_sql)
{
    uint32_t i = 0;
    int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
    ObSqlRawExpr* sql_expr = NULL;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        jlog(WARNING, "logical_plan must exist!!!");
    }

    vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

    if (where_exprs.size() > 0)
    {
        assembled_sql.append("WHERE ");        
        for (i = 0; i < where_exprs.size(); i++)
        {
            string  assembled_sql_tmp;
            sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
            if (NULL == sql_expr)
            {
                ret = OB_ERR_LOGICAL_PLAN_FAILD;
                jlog(WARNING, "where expr name error!!!");
                return ret;
            }

            sql_expr->to_string(result_plan, assembled_sql_tmp);
            assembled_sql.append(assembled_sql_tmp);        
            if (i != where_exprs.size() - 1)
            {
                assembled_sql.append(" AND ");        
            }
            else
            {
                assembled_sql.append(" ");        
            }
        }
    }
    
    return ret;
}


/**************************************************
Funtion     :   get_column_info_by_expr_id
Author      :   qinbo
Date        :   2013.12.10
Description :   fetch column info(name, type, aggr fun) by expr_id
Input       :   ResultPlan *result_plan,
                uint64_t expr_id,
                const common::ObObjType column_type,
                const SqlItemType aggr_fun_type,
                const string& column_name
Output      :   
 **************************************************/
int64_t ObSelectStmt::get_column_info_by_expr_id(
                    ResultPlan *result_plan,
                    uint64_t expr_id,
                    ObObjType &column_type,
                    SqlItemType &aggr_fun_type,
                    string& column_name)
{
    int             ret = OB_SUCCESS;
    ObSqlRawExpr*   sql_expr = NULL;
    string          assembled_sql_tmp;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "logical_plan must exist!!!");
        return ret;
    }
    
    sql_expr = logical_plan->get_expr_by_id(expr_id);
    
    if (NULL == sql_expr)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "select item error!!!");
        return ret;
    }
    
    ObBinaryRefRawExpr *select_expr = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
    if (NULL == select_expr)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "We do not support this sql now!!!");
        return ret;
    }
    
    if (select_expr->get_first_ref_id() == OB_INVALID_ID)
    {
        sql_expr = logical_plan->get_expr_by_id(select_expr->get_related_sql_raw_id());
        if (NULL == sql_expr)
        {
            ret = OB_ERR_ILLEGAL_ID;
            jlog(WARNING, "ref column error!!!");
            return ret;
        }
    
        if (sql_expr->get_expr()->is_aggr_fun())
        {
            ObAggFunRawExpr *agg_fun_raw_expr = dynamic_cast<ObAggFunRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
    
            if (NULL != agg_fun_raw_expr->get_param_expr())
            {
                if (!agg_fun_raw_expr->get_param_expr()->is_column())
                {
                    ret = OB_ERR_ILLEGAL_ID;
                    jlog(WARNING, "select item error!!!");
                    return ret;
                }
    
                agg_fun_raw_expr->get_param_expr()->to_string(*result_plan, assembled_sql_tmp);
                column_type = agg_fun_raw_expr->get_param_expr()->get_result_type();
                column_name.assign(assembled_sql_tmp);
            }
        }
    }
    else if (select_expr->is_column())
    {
        ret = select_expr->to_string(*result_plan, assembled_sql_tmp);
        if (OB_SUCCESS != ret)
        {
            return ret;
        }
        column_type = select_expr->get_result_type();
        column_name.assign(assembled_sql_tmp);
    }
    else
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "select item error!!!");
        return ret;
    }
    
    if (sql_expr->is_contain_aggr())
    {
        aggr_fun_type = sql_expr->get_contain_aggr_type();
    }
    else
    {
        aggr_fun_type = T_INVALID;
    }

    return ret;
}


/**************************************************
Funtion     :   get_having_column_by_expr_id
Author      :   qinbo
Date        :   2013.12.10
Description :   fetch having related column info(name, type, aggr fun) by expr_id
Input       :   ResultPlan *result_plan,
                uint64_t expr_id,
                const common::ObObjType column_type,
                const SqlItemType aggr_fun_type,
                const string& column_name
Output      :   
 **************************************************/
int64_t ObSelectStmt::get_having_column_by_expr_id( 
                    ResultPlan *result_plan,
                    uint64_t expr_id,
                    ObObjType &column_type,
                    SqlItemType &aggr_fun_type,
                    uint32_t    &aggr_fun_operate,
                    double      &aggr_fun_value,
                    string      &column_name)
{
    int             ret = OB_SUCCESS;
    ObSqlRawExpr*   sql_expr = NULL;
    string          assembled_sql_tmp;
    int64_t         int_value   = 0;
    float           float_value = 0.0;
    
    ObLogicalPlan*  logical_plan = static_cast<ObLogicalPlan*> (result_plan->plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "logical_plan must exist!!!");
        return ret;
    }

    sql_expr = logical_plan->get_expr_by_id(expr_id);

    if (NULL == sql_expr)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "having item error!!!");
        return ret;
    }
    
    aggr_fun_operate = sql_expr->get_expr()->get_expr_type();
    ObBinaryOpRawExpr   *select_op      = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
    if (NULL == select_op)
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "We do not support this sql now!!!");
        return ret;
    }
    
    ObBinaryRefRawExpr  *first_expr     = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (select_op->get_first_op_expr()));
    ObConstRawExpr      *second_expr    = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (select_op->get_second_op_expr()));
    if ((NULL == first_expr)||(NULL == second_expr))
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "We do not support this sql now!!!");
        return ret;
    }

    if (first_expr->get_first_ref_id() == OB_INVALID_ID)
    {
        sql_expr = logical_plan->get_expr_by_id(first_expr->get_related_sql_raw_id());
        if (NULL == sql_expr)
        {
            ret = OB_ERR_ILLEGAL_ID;
            jlog(WARNING, "ref column error!!!");
            return ret;
        }
        if (sql_expr->get_expr()->is_aggr_fun())
        {
            ObAggFunRawExpr *agg_fun_raw_expr = dynamic_cast<ObAggFunRawExpr *> (const_cast<ObRawExpr *> (sql_expr->get_expr()));
    
            if (NULL != agg_fun_raw_expr->get_param_expr())
            {
                if (!agg_fun_raw_expr->get_param_expr()->is_column())
                {
                    ret = OB_ERR_ILLEGAL_ID;
                    jlog(WARNING, "having item error!!!");
                    return ret;
                }
    
                agg_fun_raw_expr->get_param_expr()->to_string(*result_plan, assembled_sql_tmp);
                column_type = agg_fun_raw_expr->get_param_expr()->get_result_type();
                column_name.assign(assembled_sql_tmp);
            }
        }
    }
    else if (first_expr->is_column())
    {
        ret = first_expr->to_string(*result_plan, assembled_sql_tmp);
        if (OB_SUCCESS != ret)
        {
            jlog(WARNING, "having item convert error!!!");
            return ret;
        }   
        
        column_type = first_expr->get_result_type();
        column_name.assign(assembled_sql_tmp);
    }
    else
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "having item error!!!");
        return ret;
    }
    
    if (sql_expr->is_contain_aggr())
    {
        aggr_fun_type = sql_expr->get_contain_aggr_type();
    }
    else
    {
        aggr_fun_type = T_INVALID;
    }


    if ((T_INT != second_expr->get_expr_type())
        &&(T_FLOAT != second_expr->get_expr_type())
        &&(T_DOUBLE != second_expr->get_expr_type()))
    {
        ret = OB_ERR_ILLEGAL_ID;
        jlog(WARNING, "Aggr func only support INT/FLOAT/DOUBLE/DECIMAL type value!!!");
        return ret;
    }
    else
    {
        if (T_INT == second_expr->get_expr_type())
        {
            second_expr->get_value().get_int(int_value);
            aggr_fun_value = (double)int_value;
        }
        else if (T_FLOAT == second_expr->get_expr_type())
        {
            second_expr->get_value().get_float(float_value);
            aggr_fun_value = (double)float_value;
        } 
        else if (T_DOUBLE == second_expr->get_expr_type())
        {
            second_expr->get_value().get_double(aggr_fun_value);
        }
    }

    return ret;
}



