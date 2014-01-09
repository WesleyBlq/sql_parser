#include "sql_logical_plan.h"
#include "sql_select_stmt.h"
#include "sql_delete_stmt.h"
#include "sql_insert_stmt.h"
#include "sql_update_stmt.h"
#include "parse_malloc.h"

namespace jdbd
{
    namespace sql
    {
        using namespace jdbd::sql;
        using namespace jdbd::common;

        ObLogicalPlan::ObLogicalPlan()
        {
            question_marks_count_ = 0;
            // from valid max id desc
            new_gen_tid_ = UINT16_MAX - 2;
            new_gen_cid_ = OB_MAX_TMP_COLUMN_ID;
            new_gen_qid_ = 1;
            new_gen_eid_ = 1;
        }

        ObLogicalPlan::~ObLogicalPlan()
        {
            for (uint32_t i = 0; i < stmts_.size(); ++i)
            {
                //delete stmts_[i];
                stmts_[i]->~ObBasicStmt();
                parse_free(stmts_[i]);
            }
            stmts_.clear();

            for (uint32_t i = 0; i < exprs_.size(); ++i)
            {
                //delete exprs_[i];
                exprs_[i]->~ObSqlRawExpr();
                parse_free(exprs_[i]);
            }
            exprs_.clear();

            for (uint32_t i = 0; i < raw_exprs_store_.size(); ++i)
            {
                if (raw_exprs_store_[i])
                {
                    raw_exprs_store_[i]->~ObRawExpr();
                    parse_free(raw_exprs_store_[i]);
                }
            }
            raw_exprs_store_.clear();
        }

        ObBasicStmt* ObLogicalPlan::get_query(uint64_t query_id) const
        {
            ObBasicStmt *stmt = NULL;
            uint32_t num = stmts_.size();
            for (uint32_t i = 0; i < num; i++)
            {
                if (stmts_[i]->get_query_id() == query_id)
                {
                    stmt = stmts_[i];
                    break;
                }
            }
            OB_ASSERT(NULL != stmt);
            return stmt;
        }

        ObSelectStmt* ObLogicalPlan::get_select_query(uint64_t query_id) const
        {
            ObSelectStmt *select_stmt = NULL;
            uint32_t num = stmts_.size();
            for (uint32_t i = 0; i < num; i++)
            {
                if (stmts_[i]->get_query_id() == query_id)
                {
                    select_stmt = static_cast<ObSelectStmt*> (stmts_[i]);
                    break;
                }
            }
            OB_ASSERT(NULL != select_stmt);
            return select_stmt;
        }

        ObSqlRawExpr* ObLogicalPlan::get_expr(uint64_t expr_id) const
        {
            ObSqlRawExpr *expr = NULL;
            uint32_t num = exprs_.size();
            for (uint32_t i = 0; i < num; i++)
            {
                if (exprs_[i]->get_expr_id() == expr_id)
                {
                    expr = exprs_[i];
                    break;
                }
            }
            OB_ASSERT(NULL != expr);
            return expr;
        }
#if 0

        int ObLogicalPlan::fill_result_set(ObResultSet& result_set, ObSQLSessionInfo* session_info, common::StackAllocator &alloc)
        {
            int ret = OB_SUCCESS;
            result_set.set_affected_rows(0);
            result_set.set_warning_count(0);
            result_set.set_message("");

            ObSelectStmt *select_stmt = NULL;
            ObResultSet::Field field;
            switch (stmts_[0]->get_stmt_type())
            {
                case ObStmt::T_PREPARE:
                {
                    ObPrepareStmt *prepare_stmt = static_cast<ObPrepareStmt*> (stmts_[0]);
                    ObBasicStmt *stmt = get_query(prepare_stmt->get_prepare_query_id());
                    if (stmt == NULL)
                    {
                        ret = OB_ERR_ILLEGAL_ID;
                        jlog(WARN, "wrong prepared query id, id = %lu, ret = %d", prepare_stmt->get_prepare_query_id(), ret);
                        break;
                    }
                        // only select prepare statement need to fill result set
                    else if (stmt->get_stmt_type() != ObBasicStmt::T_SELECT)
                    {
                        break;
                    }
                    else
                    {
                        select_stmt = static_cast<ObSelectStmt*> (stmt);
                        /* then get through */
                    }
                }
                case ObStmt::T_SELECT:
                {
                    if (stmts_[0]->get_stmt_type() == ObBasicStmt::T_SELECT)
                        select_stmt = static_cast<ObSelectStmt*> (stmts_[0]);
                    if (select_stmt == NULL)
                    {
                        ret = OB_ERR_PARSE_SQL;
                        jlog(WARN, "logical plan of select statement error");
                        break;
                    }
                    uint32_t size = select_stmt->get_select_item_size();
                    for (uint32_t i = 0; ret == OB_SUCCESS && i < size; i++)
                    {
                        const SelectItem& select_item = select_stmt->get_select_item(i);
                        if ((ret = ob_write_string(select_item.expr_name_, field.cname_)) != OB_SUCCESS)
                        {
                            jlog(WARN, "fail to alloc string[%.*s] ret=%d", select_item.expr_name_.size(), select_item.expr_name_.data(), ret);
                            break;
                        }

                        ObSqlRawExpr* sql_expr = get_expr(select_item.expr_id_);
                        if (sql_expr == NULL)
                        {
                            jlog(WARN, "fail to get expr. select_item.expr_id_=%lu", select_item.expr_id_);
                            ret = OB_ERR_ILLEGAL_ID;
                            break;
                        }
                        field.type_.set_type(sql_expr->get_result_type());
                        ObRawExpr* expr = sql_expr->get_expr();
                        if (select_stmt->get_set_op() != ObSelectStmt::NONE)
                        {
                            if ((ret = ob_write_string(select_item.expr_name_, field.org_cname_)) != OB_SUCCESS)
                            {
                                jlog(WARN, "fail to alloc string[%.*s] ret=%d", select_item.expr_name_.size(), select_item.expr_name_.data(), ret);
                                break;
                            }
                        }
                        else if (expr->get_expr_type() == T_REF_COLUMN)
                        {
                            ObBinaryRefRawExpr *column_expr = static_cast<ObBinaryRefRawExpr*> (expr);
                            uint64_t table_id = column_expr->get_first_ref_id();
                            uint64_t column_id = column_expr->get_second_ref_id();
                            if (table_id != OB_INVALID_ID)
                            {
                                ColumnItem *column_item = select_stmt->get_column_item_by_id(table_id, column_id);
                                if (column_item == NULL)
                                {
                                    jlog(WARN, "fail to get column item by id. table_id=%lu column_id=%lu", table_id, column_id);
                                    ret = OB_ERR_ILLEGAL_ID;
                                    break;
                                }
                                if (OB_SUCCESS != (ret = ob_write_string(column_item->column_name_, field.org_cname_)))
                                {
                                    jlog(WARN, "fail to alloc string[%.*s] ret=%d", column_item->column_name_.size(), column_item->column_name_.data(), ret);
                                    break;
                                }
                                TableItem *table_item = select_stmt->get_table_item_by_id(table_id);
                                if (table_item == NULL)
                                {
                                    jlog(WARN, "fail to get table item by id. table_id=%lu", table_id);
                                    ret = OB_ERR_ILLEGAL_ID;
                                    break;
                                }
                                if (table_item->alias_name_.size() > 0)
                                {
                                    if (OB_SUCCESS != (ret = ob_write_string(table_item->alias_name_, field.tname_)))
                                    {
                                        jlog(WARN, "fail to alloc string[%.*s] ret=%d", table_item->alias_name_.size(), table_item->alias_name_.data(), ret);
                                        break;
                                    }
                                }
                                else
                                {
                                    if (OB_SUCCESS != (ret = ob_write_string(table_item->table_name_, field.tname_)))
                                    {
                                        jlog(WARN, "fail to alloc string[%.*s] ret=%d", table_item->table_name_.size(), table_item->table_name_.data(), ret);
                                        break;
                                    }
                                }
                                if (OB_SUCCESS != (ret = ob_write_string(table_item->table_name_, field.org_tname_)))
                                {
                                    jlog(WARN, "fail to alloc string[%.*s] ret=%d", table_item->table_name_.size(), table_item->table_name_.data(), ret);
                                    break;
                                }
                            }
                        }
                        if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                        {
                            jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                            break;
                        }

                        field.cname_.assign("");
                        field.org_cname_.assign("");
                        field.tname_.assign("");
                        field.org_tname_.assign("");
                        field.type_.set_type(ObMinType);
                    }
                    break;
                }
                case ObStmt::T_EXPLAIN:
                {
                    ObString tname = ObString::make_string("explain_table");
                    ObString cname = ObString::make_string("Query Plan");
                    field.tname_ = tname;
                    field.org_tname_ = tname;
                    field.cname_ = cname;
                    field.org_cname_ = cname;
                    field.type_.set_type(ObVarcharType);
                    if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                    {
                        jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                        break;
                    }
                    break;
                }
                case ObStmt::T_SHOW_TABLES:
                case ObStmt::T_SHOW_VARIABLES:
                case ObStmt::T_SHOW_COLUMNS:
                case ObStmt::T_SHOW_SCHEMA:
                case ObStmt::T_SHOW_CREATE_TABLE:
                case ObStmt::T_SHOW_TABLE_STATUS:
                case ObStmt::T_SHOW_SERVER_STATUS:
                case ObStmt::T_SHOW_PARAMETERS:
                {
                    ObShowStmt *show_stmt = static_cast<ObShowStmt*> (stmts_[0]);
                    if (show_stmt == NULL)
                    {
                        jlog(WARN, "fail to get Show statement");
                        ret = OB_ERR_PARSE_SQL;
                        break;
                    }
                    TableItem *table_item = show_stmt->get_table_item_by_id(show_stmt->get_sys_table_id());
                    if (table_item == NULL)
                    {
                        jlog(WARN, "fail to get table item by id. table_id=%lu", show_stmt->get_sys_table_id());
                        ret = OB_ERR_ILLEGAL_ID;
                        break;
                    }
                    ObString tname;
                    if (OB_SUCCESS != (ret = ob_write_string(table_item->table_name_, tname)))
                    {
                        jlog(WARN, "fail to alloc string \"%.*s\" ret=%d", table_item->table_name_.size(), table_item->table_name_.data(), ret);
                        break;
                    }
                    field.tname_ = tname;
                    field.org_tname_ = tname;
                    for (uint32_t i = 0; ret == OB_SUCCESS && i < show_stmt->get_column_size(); i++)
                    {
                        ObString cname;
                        const ColumnItem *col_item = show_stmt->get_column_item(i);
                        if (col_item != NULL)
                        {
                            if (OB_SUCCESS != (ret = ob_write_string(col_item->column_name_, cname)))
                            {
                                jlog(WARN, "fail to alloc string \"%.*s\" ret=%d", col_item->column_name_.size(), col_item->column_name_.data(), ret);
                                break;
                            }
                            field.cname_ = cname;
                            field.org_cname_ = cname;
                            field.type_.set_type(col_item->data_type_);
                            if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                            {
                                jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                                break;
                            }
                            field.cname_.assign("");
                            field.org_cname_.assign("");
                            field.type_.set_type(ObMinType);
                        }
                    }
                    break;
                }
                case ObStmt::T_SHOW_WARNINGS:
                {
                    ObString tname = ObString::make_string("show warnings");
                    ObShowStmt *show_stmt = static_cast<ObShowStmt*> (stmts_[0]);
                    if (show_stmt == NULL)
                    {
                        jlog(WARN, "fail to get Show statement");
                        ret = OB_ERR_PARSE_SQL;
                        break;
                    }
                    else
                    {
                        field.tname_ = tname;
                        field.org_tname_ = tname;
                    }
                    if (show_stmt->is_count_warnings())
                    {
                        ObString cname = ObString::make_string("warning_count");
                        field.cname_ = cname;
                        field.org_cname_ = cname;
                        field.type_.set_type(ObIntType);
                        if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                        {
                            jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                            break;
                        }
                    }
                    else
                    {
                        ObString cname[3];
                        cname[0] = ObString::make_string("level");
                        cname[1] = ObString::make_string("code");
                        cname[2] = ObString::make_string("message");
                        for (uint32_t i = 0; ret == OB_SUCCESS && i < 3; i++)
                        {
                            field.cname_ = cname[i];
                            field.org_cname_ = cname[i];
                            if (i == 1)
                                field.type_.set_type(ObIntType);
                            else
                                field.type_.set_type(ObVarcharType);
                            if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                            {
                                jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                                break;
                            }
                        }
                    }
                    break;
                }
                case ObStmt::T_SHOW_GRANTS:
                {
                    ObString tname = ObString::make_string("show grants");
                    ObString cname = ObString::make_string("grants");
                    field.tname_ = tname;
                    field.org_tname_ = tname;
                    field.cname_ = cname;
                    field.org_cname_ = cname;
                    field.type_.set_type(ObVarcharType);
                    if (OB_SUCCESS != (ret = result_set.add_field_column(field)))
                    {
                        jlog(WARN, "fail to add field column to result_set. ret=%d", ret);
                        break;
                    }
                    break;
                }
                case ObStmt::T_EXECUTE:
                {
                    ObExecuteStmt *execute_stmt = static_cast<ObExecuteStmt*> (stmts_[0]);
                    ObResultSet *stored_plan = NULL;
                    if (session_info == NULL)
                    {
                        ret = OB_ERROR;
                        jlog(ERROR, "Session Info is needed. ret=%d", ret);
                    }
                    else if (execute_stmt == NULL)
                    {
                        ret = OB_ERR_PARSE_SQL;
                        jlog(WARN, "fail to get Execute statement");
                    }
                    else if ((stored_plan = session_info->get_plan(execute_stmt->get_stmt_name())) == NULL)
                    {
                        ret = OB_ERR_PREPARE_STMT_UNKNOWN;
                        jlog(USER_ERROR, "statement %.*s not prepared",
                                execute_stmt->get_stmt_name().size(), execute_stmt->get_stmt_name().data());
                    }
                    else if ((ret = result_set.from_prepared(*stored_plan)) != OB_SUCCESS)
                    {
                        jlog(WARN, "fail to fill result set");
                    }
                    else
                    {
                        jlog(DEBUG, "get physical plan, addr=%p", stored_plan->get_physical_plan());
                        jlog(DEBUG, "StoredPlan: %s", to_cstring(*stored_plan->get_physical_plan()));
                    }
                    break;
                }
                default:
                    break;
            }
            if (ret == OB_SUCCESS && question_marks_count_ > 0)
            {
                ret = result_set.pre_assign_params_room(question_marks_count_, alloc);
            }

            return ret;
        }
#endif

        void ObLogicalPlan::print(FILE* fp, int32_t level) const
        {
            uint32_t i;
            fprintf(fp, "<LogicalPlan>\n");
            fprintf(fp, "    <StmtList>\n");

            for (i = 0; i < stmts_.size(); i++)
            {
                ObBasicStmt* stmt = stmts_[i];
                stmt->print(fp, level + 2, i);
            }
            fprintf(fp, "    </StmtList>\n");
            fprintf(fp, "    <ExprList>\n");

            for (i = 0; i < exprs_.size(); i++)
            {
                ObSqlRawExpr* sql_expr = exprs_[i];
                sql_expr->print(fp, level + 2, i);
            }
            fprintf(fp, "    </ExprList>\n");
            fprintf(fp, "</LogicalPlan>\n");
        }

        /**************************************************
        Funtion     :   get_expr_by_id
        Author      :   qinbo
        Date        :   2013.9.10
        Description :   get expr by expr_id
        Input       :   int64_t expr_id
        Output      :   ObSqlRawExpr* 
         **************************************************/
        ObSqlRawExpr* ObLogicalPlan::get_expr_by_id(uint64_t expr_id)
        {
            uint32_t i;
            for (i = 0; i < exprs_.size(); i++)
            {
                ObSqlRawExpr* sql_expr = exprs_[i];
                if (expr_id == sql_expr->get_expr_id())
                {
                    return sql_expr;
                }
            }
            return NULL;
        }

        /**************************************************
        Funtion     :   make_stmt_string
        Author      :   qinbo
        Date        :   2013.9.10
        Description :   make stmt string
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql_tmp
        Output      :   ObSqlRawExpr* 
         **************************************************/
        void ObLogicalPlan::make_stmt_string(ResultPlan& result_plan)
        {
            uint32_t i;
            for (i = 0; i < stmts_.size(); i++)
            {
                string assembled_sql;
                ObBasicStmt* stmt = stmts_[i];
                stmt->make_stmt_string(result_plan, assembled_sql);
                if (assembled_sql.size() > 0)
                {
                    cout << "STMT string: " << assembled_sql << endl;
                }
            }
        }
    }
}
