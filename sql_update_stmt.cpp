
#include <stdio.h>
#include <stdlib.h>
#include "sql_update_stmt.h"
#include "sql_logical_plan.h"
#include "parse_malloc.h"
#include "utility.h"

namespace jdbd
{
    namespace sql
    {
        using namespace jdbd::common;

        ObUpdateStmt::ObUpdateStmt()
        : ObStmt(T_UPDATE)
        {
        }

        ObUpdateStmt::~ObUpdateStmt()
        {
        }

        void ObUpdateStmt::print(FILE* fp, int32_t level, int32_t index)
        {
            print_indentation(fp, level);
            fprintf(fp, "ObUpdateStmt %d Begin\n", index);
            ObStmt::print(fp, level + 1);
            print_indentation(fp, level + 1);
            fprintf(fp, "UPDATE ::= <%ld>\n", table_id_);
            print_indentation(fp, level + 1);
            fprintf(fp, "SET ::= ");
            for (uint32_t i = 0; i < update_columns_.size(); i++)
            {
                if (i > 0)
                    fprintf(fp, ", <%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
                else
                    fprintf(fp, "<%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
            }
            fprintf(fp, "\n");
            print_indentation(fp, level);
            fprintf(fp, "ObUpdateStmt %d End\n", index);
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
        int64_t ObUpdateStmt::make_stmt_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ret = make_update_table_string(result_plan, assembled_sql);
            if (OB_SUCCESS == ret)
            {
                ret = make_update_column_string(result_plan, assembled_sql);
            }
            
            if (OB_SUCCESS == ret)
            {
                ret = make_update_where_string(result_plan, assembled_sql);
            }
            
            return ret;
        }

        /**************************************************
        Funtion     :   make_exec_plan_unit_string
        Author      :   qinbo
        Date        :   2013.12.10
        Description :   make select sql
        Input       :   ResultPlan& result_plan, 
                        string where_conditions, 
                        vector<schema_shard*> shard_info,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_exec_plan_unit_string(ResultPlan& result_plan, string where_conditions, vector<schema_shard*> &shard_info,string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);

            assembled_sql.append("UPDATE ");
            string table_name = ObStmt::get_table_item_by_id(table_id_)->table_name_ ;
            if (table_name != shard_info.at(0)->get_table_name())
            {
                assembled_sql.append(shard_info.at(0)->get_shard_name());
            }
            else
            {
                assembled_sql.append(table_name);
            }

            assembled_sql.append(" SET ");
            make_update_column_string(result_plan, assembled_sql);
            
            if (where_conditions.empty())
            {
                make_update_where_string(result_plan, assembled_sql);
            }
            else
            {
                assembled_sql.append(where_conditions);
                assembled_sql.append(" ");
            }
            return ret;
        }

        
        /**************************************************
        Funtion     :   make_update_table_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update table sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_table_string(ResultPlan& result_plan, string &assembled_sql)
        {
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);

            assembled_sql.append("UPDATE ");
            assembled_sql.append(ObStmt::get_table_item_by_id(table_id_)->table_name_);
            assembled_sql.append(" SET ");
            return ret;
        }

        /**************************************************
        Funtion     :   make_update_column_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update column name sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_column_string(ResultPlan& result_plan, string &assembled_sql)
        {
            uint32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);
            
            for (i = 0; i < update_columns_.size(); i++)
            {
                string assembled_sql_tmp;
                assembled_sql.append(ObStmt::get_column_item(i)->column_name_);
                assembled_sql.append(" = ");

                sql_expr = logical_plan->get_expr_by_id(update_exprs_.at(i));

                if (NULL == sql_expr)
                {
                    ret = JD_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "update expr name error!!!");
                    return ret;
                }

                //BEGIN: Added by qinbo: sql value type is same with column meta info
                const ColumnItem* column_item = ObStmt::get_column_item(i);
                
                schema_db* db_schema = meta_reader::get_instance().get_DB_schema_with_lock(result_plan.db_name);
                if (NULL == db_schema)
                {
                    ret = JD_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "Database %s should not be empty in db schema", result_plan.db_name.data());
                    return ret;
                }
                
                schema_table* table_schema = db_schema->get_table_from_db_by_id(column_item->table_id_);
                if (NULL == table_schema)
                {
                    ret = JD_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "Table with id %d should not be empty in table schema", column_item->table_id_);
                    return ret;
                }
                schema_column* column_schema =  table_schema->get_column_from_table(column_item->column_name_);
                if (NULL == column_schema)
                {
                    ret = JD_ERR_LOGICAL_PLAN_FAILD;
                    jlog(WARNING, "Column %s should not be empty in table schema", column_item->column_name_.data());
                    return ret;
                }
                
                if (column_schema->get_column_type() != sql_expr->get_expr()->get_expr_type())
                {
                    if (((T_INT == column_schema->get_column_type())
                        ||(T_FLOAT == column_schema->get_column_type())
                        ||(T_DOUBLE == column_schema->get_column_type())
                        ||(T_BOOL == column_schema->get_column_type()))
                        &&(T_STRING == sql_expr->get_expr()->get_expr_type()))
                    {
                        ret = JD_ERR_SQL_VALUE_TYPE_ERR;
                        jlog(WARNING, "update column meta type is %d while actual update value type is %d", 
                                    column_schema->get_column_type(),
                                    sql_expr->get_expr()->get_expr_type());
                        return ret;
                    }
                }
                //END: Added by qinbo: sql value type is same with column meta info

                sql_expr->to_string(result_plan, assembled_sql_tmp);
                assembled_sql.append(assembled_sql_tmp);

                if (i != update_columns_.size() - 1)
                {
                    assembled_sql.append(" , ");
                }
                else
                {
                    assembled_sql.append(" ");
                }
            }
            
            return ret;
        }

        
        /**************************************************
        Funtion     :   make_update_where_string
        Author      :   qinbo
        Date        :   2013.10.31
        Description :   make update where item sql
        Input       :   ResultPlan& result_plan,
                        string &assembled_sql
        Output      :   
         **************************************************/
        int64_t ObUpdateStmt::make_update_where_string(ResultPlan& result_plan, string &assembled_sql)
        {
            uint32_t i = 0;
            int& ret = result_plan.err_stat_.err_code_ = OB_SUCCESS;
            ObSqlRawExpr* sql_expr = NULL;

            ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
            OB_ASSERT(NULL != logical_plan);
            
            vector<uint64_t>& where_exprs = ObStmt::get_where_exprs();

            if (where_exprs.size() > 0)
            {
                assembled_sql.append("WHERE ");
                for (i = 0; i < where_exprs.size(); i++)
                {
                    string assembled_sql_tmp;
                    sql_expr = logical_plan->get_expr_by_id(where_exprs[i]);
                    if (NULL == sql_expr)
                    {
                        ret = JD_ERR_LOGICAL_PLAN_FAILD;
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
        Funtion     :   decompose_where_items
        Author      :   qinbo
        Date        :   2013.9.24
        Description :   generate distributed where conditions items
        Input       :   ObRawExpr* sql_expr
        Output      :   vector<vector<ObRawExpr*> > &atomic_exprs_array
        return      :   
         **************************************************/
        int ObUpdateStmt::decompose_where_items(ObRawExpr* sql_expr, vector<vector<ObRawExpr*> > &atomic_exprs_array)
        {
            uint32_t i = 0;
        
            if (sql_expr->is_or_expr())
            {
                vector<vector<ObRawExpr*> > left_atomic_exprs_array;
        
                ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (sql_expr));
                ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();
        
                if (left_sql_item->is_and_expr() || left_sql_item->is_or_expr())
                {
                    (void)decompose_where_items(left_sql_item, left_atomic_exprs_array);
                }
                else
                {
                    vector<ObRawExpr*> atomic_exprs1;
                    atomic_exprs1.push_back(left_sql_item);
                    left_atomic_exprs_array.push_back(atomic_exprs1);
                }
        
                ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
                vector<vector<ObRawExpr*> > right_atomic_exprs_array;
        
                if (right_sql_item->is_and_expr() || right_sql_item->is_or_expr())
                {
                    (void)decompose_where_items(right_sql_item, right_atomic_exprs_array);
                }
                else
                {
                    vector<ObRawExpr*> atomic_exprs2;
                    atomic_exprs2.push_back(right_sql_item);
                    right_atomic_exprs_array.push_back(atomic_exprs2);
                }
        
                //add with each other
                for (i = 0; i < left_atomic_exprs_array.size(); i++)
                {
                    atomic_exprs_array.push_back(left_atomic_exprs_array.at(i));
                }
        
                for (i = 0; i < right_atomic_exprs_array.size(); i++)
                {
                    atomic_exprs_array.push_back(right_atomic_exprs_array.at(i));
                }
        
                return WHERE_IS_OR_AND;
            }
            else if (sql_expr->is_and_expr())
            {
                vector<vector<ObRawExpr*> > left_atomic_exprs_array;
        
                ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (sql_expr));
                ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();
        
                if (left_sql_item->is_and_expr() || left_sql_item->is_or_expr())
                {
                    (void)decompose_where_items(left_sql_item, left_atomic_exprs_array);
                }
                else
                {
                    vector<ObRawExpr*> atomic_exprs1;
                    atomic_exprs1.push_back(left_sql_item);
                    left_atomic_exprs_array.push_back(atomic_exprs1);
                }
        
                ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
                vector<vector<ObRawExpr*> > right_atomic_exprs_array;
        
                if (right_sql_item->is_and_expr() || right_sql_item->is_or_expr())
                {
                    (void)decompose_where_items(right_sql_item, right_atomic_exprs_array);
                }
                else
                {
                    vector<ObRawExpr*> atomic_exprs2;
                    atomic_exprs2.push_back(right_sql_item);
                    right_atomic_exprs_array.push_back(atomic_exprs2);
                }
        
                //X with each other
                for (i = 0; i < left_atomic_exprs_array.size(); i++)
                {
                    uint32_t j;
                    for (j = 0; j < right_atomic_exprs_array.size(); j++)
                    {
                        vector<ObRawExpr*> atomic_exprs;
        
                        uint32_t k;
                        vector<ObRawExpr*> left_atomic_exprs = left_atomic_exprs_array.at(i);
                        for (k = 0; k < left_atomic_exprs.size(); k++)
                        {
                            atomic_exprs.push_back(left_atomic_exprs.at(k));
                        }
                        vector<ObRawExpr*> right_atomic_exprs = right_atomic_exprs_array.at(j);
                        for (k = 0; k < right_atomic_exprs.size(); k++)
                        {
                            atomic_exprs.push_back(right_atomic_exprs.at(k));
                        }
        
                        atomic_exprs_array.push_back(atomic_exprs);
                    }
                }
        
                return WHERE_IS_OR_AND;
            }
    #if 1
            else
            {
                vector<ObRawExpr*> one_expr;
                one_expr.push_back(sql_expr);
                atomic_exprs_array.push_back(one_expr);
                return WHERE_IS_OR_AND;
            }
    #else //do not support sub query now
            else
            {
                return WHERE_IS_SUBQUERY;
            }
    #endif
        }

    }
}
