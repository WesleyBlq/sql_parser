#include <string.h>
#include "ob_raw_expr.h"
//#include "ob_transformer.h"
#include "parse_node.h"
//#include "ob_prepare.h"
//#include "ob_result_set.h"
#include "ob_select_stmt.h"
#include "ob_logical_plan.h"


using namespace oceanbase::sql;
using namespace oceanbase::common;


bool ObRawExpr::is_const() const
{
    return (type_ >= T_INT && type_ <= T_NULL);
}

bool ObRawExpr::is_column() const
{
    return (type_ == T_REF_COLUMN);
}

/**************************************************
Funtion     :   is_or_expr
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is linked by OR
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_or_expr() const
{
    return (type_ == T_OP_OR);
}

/**************************************************
Funtion     :   is_and_expr
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is linked by AND
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_and_expr() const
{
    return (type_ == T_OP_AND);
}

/**************************************************
Funtion     :   is_column_and_sharding_key
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is sharding column
Input       :   ResultPlan& result_plan
Output      :   
 **************************************************/
bool ObRawExpr::is_column_and_sharding_key(ResultPlan& result_plan) const
{
    if (!is_column())
    {
        return false;
    }

    ObBinaryRefRawExpr *binary_ref_raw_expr = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (this));

    schema_table* table_schema = meta_reader::get_instance().get_table_schema_by_id(result_plan.db_name, binary_ref_raw_expr->get_first_ref_id());
    if (NULL == table_schema)
    {
        return false;
    }

    schema_column* column_schema = table_schema->get_column_from_table_by_id(binary_ref_raw_expr->get_second_ref_id());
    if (column_schema == NULL)
    {
        return false;
    }

    if (column_schema->is_sharding_key())
    {
        return true;
    }

    return false;
}

/**************************************************
Funtion     :   get_table_name_in_sharding_column
Author      :   qinbo
Date        :   2013.10.29
Description :   get expr's related table name
Input       :   ResultPlan& result_plan, string &table_name
Output      :   
 **************************************************/
bool ObRawExpr::get_table_name_in_sharding_column(ResultPlan& result_plan, string &table_name) const
{
    if (!is_column_and_sharding_key(result_plan))
    {
        return false;
    }
    
    ObBinaryRefRawExpr *binary_ref_raw_expr = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (this));

    schema_table* table_schema = meta_reader::get_instance().get_table_schema_by_id(result_plan.db_name, binary_ref_raw_expr->get_first_ref_id());
    if (NULL == table_schema)
    {
        return false;
    }

    table_name.assign(table_schema->get_table_name());
    return true;
}

/**************************************************
Funtion     :   get_column_and_sharding_key
Author      :   qinbo
Date        :   2013.9.25
Description :   get this expr's column name when this is sharding column
Input       :   ResultPlan& result_plan, string &column_name
Output      :   
 **************************************************/
bool ObRawExpr::get_column_and_sharding_key(ResultPlan& result_plan, string &column_name) const
{
    if (!is_column())
    {
        return false;
    }

    ObBinaryRefRawExpr *binary_ref_raw_expr = dynamic_cast<ObBinaryRefRawExpr *> (const_cast<ObRawExpr *> (this));

    schema_table* table_schema = meta_reader::get_instance().get_table_schema_by_id(result_plan.db_name, binary_ref_raw_expr->get_first_ref_id());
    if (NULL == table_schema)
    {
        return false;
    }

    schema_column* column_schema = table_schema->get_column_from_table_by_id(binary_ref_raw_expr->get_second_ref_id());
    if (column_schema == NULL)
    {
        return false;
    }

    column_name = column_schema->get_column_name();

    return true;
}

bool ObRawExpr::is_equal_filter() const
{
    bool ret = false;
    if (type_ == T_OP_EQ || type_ == T_OP_IS)
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->is_const()
                || binary_expr->get_second_op_expr()->is_const())
            ret = true;
    }
    return false;
}

/**************************************************
Funtion     :   is_equal_filter_with_route
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is need to get route or not
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_equal_filter_need_route(ResultPlan& result_plan) const
{
    bool ret = false;
    if (type_ == T_OP_EQ || type_ == T_OP_IS)
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (((binary_expr->get_first_op_expr()->is_const())
                && binary_expr->get_second_op_expr()->is_column_and_sharding_key(result_plan))
                || (binary_expr->get_second_op_expr()->is_const())
                &&(binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan)))
        {
            ret = true;
        }
    }
    return ret;
}

/**************************************************
Funtion		:	is_contain_filter
Author		:	qinbo
Date		:	2013.9.11
Description	:   is T_OP_IN/T_OP_NOT_IN or not
Input		:	
Output		:	
 **************************************************/
bool ObRawExpr::is_contain_filter() const
{
    bool ret = false;
    int32_t expr_size = 0;
    ObRawExpr* raw_expr = NULL;

    if ((type_ == T_OP_IN) || (type_ == T_OP_NOT_IN))
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));

        ObMultiOpRawExpr *multi_expr = dynamic_cast<ObMultiOpRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_second_op_expr()));
        expr_size = multi_expr->get_expr_size();

        for (int32_t i = 0; i < expr_size; i++)
        {
            raw_expr = multi_expr->get_op_expr(i);
            if (raw_expr->is_const())
            {
                ret = true;
            }
            else
            {
                ret = false;
                break;
            }
        }
    }
    return ret;
}

/**************************************************
Funtion     :   is_contain_filter_with_route
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is need to get route or not
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_contain_filter_need_route(ResultPlan& result_plan) const
{
    bool ret = false;
    int32_t expr_size = 0;
    ObRawExpr* raw_expr = NULL;
    if ((type_ == T_OP_IN) || (type_ == T_OP_NOT_IN))
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        ObMultiOpRawExpr *multi_expr = dynamic_cast<ObMultiOpRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_second_op_expr()));
        expr_size = multi_expr->get_expr_size();

        for (int32_t i = 0; i < expr_size; i++)
        {
            raw_expr = multi_expr->get_op_expr(i);
            if (raw_expr->is_const())
            {
                ret = true;
            }
            else
            {
                ret = false;
                return ret;
            }
        }

        if (binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan))
        {
            return true;
        }
    }
    return ret;
}

/**************************************************
Funtion     :   is_range_filter
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is range filter
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_range_filter() const
{
    bool ret = false;
    if (type_ >= T_OP_LE && type_ <= T_OP_GT)
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->is_const()
                || binary_expr->get_second_op_expr()->is_const())
            ret = true;
    }
    else if (type_ == T_OP_BTW)
    {
        ObTripleOpRawExpr *triple_expr = dynamic_cast<ObTripleOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (triple_expr->get_second_op_expr()->is_const()
                && triple_expr->get_third_op_expr()->is_const())
            ret = true;
    }
    return ret;
}

/**************************************************
Funtion     :   is_range_filter_with_route
Author      :   qinbo
Date        :   2013.9.25
Description :   this expr is need to get route or not
Input       :   
Output      :   
 **************************************************/
bool ObRawExpr::is_range_filter_need_route(ResultPlan& result_plan) const
{
    bool ret = false;
    if (type_ >= T_OP_LE && type_ <= T_OP_GT)
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (((binary_expr->get_first_op_expr()->is_const())
                && binary_expr->get_second_op_expr()->is_column_and_sharding_key(result_plan))
                || (binary_expr->get_second_op_expr()->is_const())
                &&(binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan)))
        {
            ret = true;
        }
    }
    else if (type_ == T_OP_BTW)
    {
        ObTripleOpRawExpr *triple_expr = dynamic_cast<ObTripleOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (triple_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan)
                && triple_expr->get_second_op_expr()->is_const()
                && triple_expr->get_third_op_expr()->is_const())
        {
            ret = true;
        }
    }
    return ret;
}

bool ObRawExpr::is_join_cond() const
{
    bool ret = false;
    if (type_ == T_OP_EQ)
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->get_expr_type() == T_REF_COLUMN
                && binary_expr->get_second_op_expr()->get_expr_type() == T_REF_COLUMN)
            ret = true;
    }
    return ret;
}

bool ObRawExpr::is_aggr_fun() const
{
    bool ret = false;
    if (type_ >= T_FUN_MAX && type_ <= T_FUN_AVG)
        ret = true;
    return ret;
}


/**************************************************
Funtion     :   try_get_table_name
Author      :   qinbo
Date        :   2013.10.29
Description :   try get table name
Input       :   ResultPlan& result_plan ,string &table_name
Output      :   
 **************************************************/
bool ObRawExpr::try_get_table_name(ResultPlan& result_plan ,string &table_name) const
{
    if (!is_need_to_get_route(result_plan))
    {
        return false;
    }

    if (is_equal_filter_need_route(result_plan))
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan))
        {
            return(binary_expr->get_first_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
        }
        else
        {   
            return(binary_expr->get_second_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
        }
    }
    else if (is_contain_filter_need_route(result_plan))
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan))
        {
            return(binary_expr->get_first_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
        }
        else
        {   
            return(binary_expr->get_second_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
        }
    }
    else if (is_range_filter_need_route(result_plan))
    {
        if (type_ >= T_OP_LE && type_ <= T_OP_GT)
        {
            ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
            if (binary_expr->get_first_op_expr()->is_column_and_sharding_key(result_plan))
            {
                return(binary_expr->get_first_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
            }
            else
            {   
                return(binary_expr->get_second_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
            }
        }
        else if (type_ == T_OP_BTW)
        {
            ObTripleOpRawExpr *triple_expr = dynamic_cast<ObTripleOpRawExpr *> (const_cast<ObRawExpr *> (this));
            return(triple_expr->get_first_op_expr()->get_table_name_in_sharding_column(result_plan ,table_name));
        }
    }
    return false;
}


/**************************************************
Funtion		:	is_need_to_get_route
Author		:	qinbo
Date		:	2013.9.11
Description	:   this expr is need to get route or not
Input		:	ResultPlan& result_plan
Output		:	
 **************************************************/
bool ObRawExpr::is_need_to_get_route(ResultPlan& result_plan) const
{
    if (is_equal_filter_need_route(result_plan) ||
            is_contain_filter_need_route(result_plan) ||
            is_range_filter_need_route(result_plan))
    {
        return true;
    }
    return false;

}

/**************************************************
Funtion     :   convert_ob_expr_to_route
Author      :   qinbo
Date        :   2013.10.14
Description :   convert ob style expr to route used key relation
Input       :   ResultPlan& result_plan, key_data& key_relation
Output      :   
 **************************************************/
bool ObRawExpr::convert_ob_expr_to_route(ResultPlan& result_plan, key_data& key_relation) const
{
    string column_name;

    if (!this->is_need_to_get_route(result_plan))
    {
        return false;
    }

    if (this->is_equal_filter_need_route(result_plan))
    {
        key_relation.key_value_num = 1;
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->is_const())
        {
            if (binary_expr->get_second_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                    &&(key_relation.sharding_key == column_name))
            {
                key_relation.key_relation = this->get_expr_type();

                ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_first_op_expr()));
                const_expr->get_ob_const_expr_to_key_data(key_relation, 0);
            }
        }
        else if (binary_expr->get_second_op_expr()->is_const())
        {
            if (binary_expr->get_first_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                    &&(key_relation.sharding_key == column_name))
            {
                key_relation.key_relation = this->get_expr_type();
                ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_second_op_expr()));
                const_expr->get_ob_const_expr_to_key_data(key_relation, 0);
            }
        }

    }
    else if (this->is_contain_filter_need_route(result_plan))
    {
        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
        if (binary_expr->get_first_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                &&(key_relation.sharding_key == column_name))
        {
            key_relation.key_relation = this->get_expr_type();
            key_relation.key_value_num = 0;
            ObMultiOpRawExpr *multi_expr = dynamic_cast<ObMultiOpRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_second_op_expr()));
            int32_t expr_size = multi_expr->get_expr_size();
            ObRawExpr *raw_expr = NULL;
            ObConstRawExpr *const_expr = NULL;

            for (int32_t i = 0; i < expr_size; i++)
            {
                raw_expr = multi_expr->get_op_expr(i);
                if (raw_expr->is_const())
                {
                    key_relation.key_value_num++;

                    const_expr = dynamic_cast<ObConstRawExpr*> (const_cast<ObRawExpr *> (raw_expr));
                    const_expr->get_ob_const_expr_to_key_data(key_relation, i);
                }
            }
        }
    }
    else if (this->is_range_filter_need_route(result_plan))
    {
        if (this->get_expr_type() >= T_OP_LE && this->get_expr_type() <= T_OP_GT)
        {
            key_relation.key_value_num = 1;
            ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *> (const_cast<ObRawExpr *> (this));
            if (binary_expr->get_first_op_expr()->is_const())
            {
                if (binary_expr->get_second_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                        &&(key_relation.sharding_key == column_name))
                {
                    key_relation.key_relation = this->get_expr_type();

                    ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_first_op_expr()));
                    const_expr->get_ob_const_expr_to_key_data(key_relation, 0);
                }
            }
            else if (binary_expr->get_second_op_expr()->is_const())
            {
                if (binary_expr->get_first_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                        &&(key_relation.sharding_key == column_name))
                {
                    key_relation.key_relation = this->get_expr_type();
                    ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (binary_expr->get_second_op_expr()));
                    const_expr->get_ob_const_expr_to_key_data(key_relation, 0);
                    return true;
                }
            }
        }
        else if (this->get_expr_type() == T_OP_BTW)
        {
            key_relation.key_value_num = 2;
            ObTripleOpRawExpr *triple_expr = dynamic_cast<ObTripleOpRawExpr *> (const_cast<ObRawExpr *> (this));
            if (triple_expr->get_first_op_expr()->get_column_and_sharding_key(result_plan, column_name)
                    &&(key_relation.sharding_key == column_name))
            {
                key_relation.key_relation = this->get_expr_type();
                ObConstRawExpr *const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (triple_expr->get_second_op_expr()));
                const_expr->get_ob_const_expr_to_key_data(key_relation, 0);

                const_expr = dynamic_cast<ObConstRawExpr *> (const_cast<ObRawExpr *> (triple_expr->get_third_op_expr()));
                const_expr->get_ob_const_expr_to_key_data(key_relation, 1);
            }
        }
    }

    return true;

}

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
void ObConstRawExpr::get_ob_const_expr_to_key_data(key_data& key_relation,
        uint32_t seq) const
{
    ObObj value_ = this->get_value();

    switch (this->get_expr_type())
    {
        case T_INT:
        case T_DATE:
        {
            value_.get_int(key_relation.value.key_integer[seq]);
            break;
        }
        case T_STRING:
        case T_BINARY:
        case T_DECIMAL:
        {
            string str;
            value_.get_varchar(str);
            strncpy(&key_relation.value.key_str[seq][0], str.data(), str.size());
            break;
        }
        case T_FLOAT:
        {
            value_.get_float((float&) key_relation.value.key_float[seq]);
            break;
        }
        case T_DOUBLE:
        {
            value_.get_double(key_relation.value.key_float[seq]);
            break;
        }
        case T_BOOL:
        {
            value_.get_bool(key_relation.value.key_bool);
            break;
        }
        case T_NULL:
        case T_UNKNOWN:
        default:
            break;
    }
}

int ObConstRawExpr::set_value_and_type(const common::ObObj& val)
{
    int ret = OB_SUCCESS;
    switch (val.get_type())
    {
        case ObNullType: // 空类型
            this->set_expr_type(T_NULL);
            this->set_result_type(ObNullType);
            break;
        case ObIntType:
            this->set_expr_type(T_INT);
            this->set_result_type(ObIntType);
            break;
        case ObFloatType: // @deprecated
            this->set_expr_type(T_FLOAT);
            this->set_result_type(ObFloatType);
            break;
        case ObDoubleType: // @deprecated
            this->set_expr_type(T_DOUBLE);
            this->set_result_type(ObDoubleType);
            break;
        case ObPreciseDateTimeType: // =5
        case ObCreateTimeType:
        case ObModifyTimeType:
            this->set_expr_type(T_DATE);
            this->set_result_type(ObPreciseDateTimeType);
            break;
        case ObVarcharType:
            this->set_expr_type(T_STRING);
            this->set_result_type(ObVarcharType);
            break;
        case ObExtendType:
        {
            this->set_expr_type(T_QUESTIONMARK);
            this->set_result_type(ObIntType);
            int64_t v = 0;
            val.get_ext(v);
            value_.set_int(v);
            break;
        }
        case ObBoolType:
            this->set_expr_type(T_BOOL);
            this->set_result_type(ObBoolType);
            break;
        default:
            ret = OB_NOT_SUPPORTED;
            jlog(WARNING, "obj type not support, type=%d", val.get_type());
            break;
    }
    if (OB_LIKELY(OB_SUCCESS == ret))
    {
        if (ObExtendType != val.get_type())
        {
            value_ = val;
        }
    }
    return ret;
}

void ObConstRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObConstRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s : ", get_type_name(get_expr_type()));
    switch (get_expr_type())
    {
        case T_INT:
        {
            int64_t i = 0;
            value_.get_int(i);
            fprintf(fp, "%ld\n", i);
            break;
        }
        case T_STRING:
        case T_BINARY:
        {
            string str;
            value_.get_varchar(str);
            fprintf(fp, "%.*s\n", (int32_t)str.size(), str.data());
            break;
        }
        case T_DATE:
        {
            ObDateTime d = static_cast<ObDateTime> (0L);
            value_.get_datetime(d);
            fprintf(fp, "%ld\n", d);
            break;
        }
        case T_FLOAT:
        {
            float f = 0.0f;
            value_.get_float(f);
            fprintf(fp, "%f\n", f);
            break;
        }
        case T_DOUBLE:
        {
            double d = 0.0f;
            value_.get_double(d);
            fprintf(fp, "%lf\n", d);
            break;
        }
        case T_DECIMAL:
        {
            string str;
            value_.get_varchar(str);
            fprintf(fp, "%.*s\n", (int32_t)str.size(), str.data());
            break;
        }
        case T_BOOL:
        {
            bool b = false;
            value_.get_bool(b);
            fprintf(fp, "%s\n", b ? "TRUE" : "FALSE");
            break;
        }
        case T_NULL:
        {
            fprintf(fp, "NULL\n");
            break;
        }
        case T_UNKNOWN:
        {
            fprintf(fp, "UNKNOWN\n");
            break;
        }
        default:
            fprintf(fp, "error type!\n");
            break;
    }
}

/**************************************************
Funtion		:	ObConstRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string& assembled_sql
 **************************************************/
int64_t ObConstRawExpr::to_string(ResultPlan& result_plan, string& assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    char buf_tmp[RAW_EXPR_BUF_SIZE] = {0};

    switch (get_expr_type())
    {
        case T_STRING:
        case T_BINARY:
        {
            assembled_sql.append("\'");
            value_.to_string(buf_tmp, RAW_EXPR_BUF_SIZE);
            assembled_sql.append(buf_tmp, strlen(buf_tmp));
            assembled_sql.append("\'");
            break;
        }
        default:
            value_.to_string(buf_tmp, RAW_EXPR_BUF_SIZE);
            assembled_sql.append(buf_tmp, strlen(buf_tmp));
            break;
    }
    return ret;
}


#if 0
int ObConstRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    UNUSED(logical_plan);
    UNUSED(physical_plan);
    float f = 0.0f;
    double d = 0.0;
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();
    switch (item.type_)
    {
        case T_STRING:
        case T_BINARY:
            ret = value_.get_varchar(item.string_);
            break;
        case T_FLOAT:
            ret = value_.get_float(f);
            item.value_.float_ = f;
            break;
        case T_DOUBLE:
            ret = value_.get_double(d);
            item.value_.double_ = d;
            break;
        case T_DECIMAL:
            ret = value_.get_varchar(item.string_);
            break;
        case T_INT:
            ret = value_.get_int(item.value_.int_);
            break;
        case T_BOOL:
            ret = value_.get_bool(item.value_.bool_);
            break;
        case T_DATE:
            ret = value_.get_precise_datetime(item.value_.datetime_);
            break;
        case T_QUESTIONMARK:
        {
            ObSqlContext *sql_context = NULL;
            ObResultSet *result_set = NULL;
            if (transformer == NULL
                    || (sql_context = transformer->get_sql_context()) == NULL
                    || sql_context->session_info_ == NULL
                    || (result_set = sql_context->session_info_->get_current_result_set()) == NULL)
            {
                ret = OB_NOT_INIT;
                jlog(ERROR, "Session stored param placeholder is needed\n");
                break;
            }
            else if ((ret = value_.get_int(item.value_.int_)) != OB_SUCCESS)
            {
                jlog(ERROR, "invalid question mark value, type=%d", value_.get_type());
                break;
            }
            else if (item.value_.int_ < 0 || item.value_.int_ >= result_set->get_params().count())
            {
                jlog(ERROR, "Wrong index of question mark position, pos = %ld\n", item.value_.int_);
                break;
            }
            else
            {
                ObObj *place_holder = result_set->get_params().at(item.value_.int_);
                item.value_.int_ = reinterpret_cast<int64_t> (place_holder);
            }
            break;
        }
        case T_SYSTEM_VARIABLE:
        case T_TEMP_VARIABLE:
        {
            ObSqlContext *sql_context = NULL;
            string var_name;
            const ObObj *var_ptr = NULL;
            if (transformer == NULL
                    || (sql_context = transformer->get_sql_context()) == NULL
                    || sql_context->session_info_ == NULL)
            {
                ret = OB_NOT_INIT;
                jlog(ERROR, "Session information is needed\n");
            }
            else if ((ret = value_.get_varchar(var_name)) != OB_SUCCESS)
            {
                jlog(ERROR, "invalid question mark value, type=%d", value_.get_type());
            }
            else if (item.type_ == T_SYSTEM_VARIABLE
                    && (var_ptr = sql_context->session_info_->get_sys_variable_value(var_name)) == NULL)
            {
                ret = OB_ERR_VARIABLE_UNKNOWN;
                jlog(ERROR, "System variable %.*s does not exists", var_name.size(), var_name.data());
            }
            else if (item.type_ == T_TEMP_VARIABLE
                    && (var_ptr = sql_context->session_info_->get_variable_value(var_name)) == NULL)
            {
                ret = OB_ERR_VARIABLE_UNKNOWN;
                jlog(USER_ERROR, "Variable %.*s does not exists", var_name.size(), var_name.data());
            }
            else
            {
                item.value_.int_ = reinterpret_cast<int64_t> (var_ptr);
                jlog(DEBUG, "get system variable type=%d name=%.*s ptr=%p val=%s",
                        item.type_, var_name.size(), var_name.data(), var_ptr, to_cstring(*var_ptr));
            }
            break;
        }
        case T_NULL:
            break;
        default:
            jlog(WARNING, "unexpected expression type %d", item.type_);
            ret = OB_ERR_EXPR_UNKNOWN;
            break;
    }
    if (OB_SUCCESS == ret)
    {
        ret = inter_expr.add_expr_item(item);
    }
    return ret;
}
#endif

void ObUnaryRefRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObUnaryRefRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s : %lu\n", get_type_name(get_expr_type()), id_);
}

/**************************************************
Funtion		:	ObUnaryRefRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string &assembled_sql
 **************************************************/
int64_t ObUnaryRefRawExpr::to_string(ResultPlan& result_plan, string &assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    uint64_t id = 0;
    string assembled_sql_tmp;

    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
    if (logical_plan == NULL)
    {
        ret = OB_ERR_LOGICAL_PLAN_FAILD;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "logical_plan must exist!!! at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    assembled_sql.append("(");
    id = get_ref_id();

    ObSelectStmt *sub_select = dynamic_cast<ObSelectStmt *> (logical_plan->get_query(id));

    if (!sub_select)
    {
        ret = OB_ERR_PARSER_SYNTAX;
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Sub-query of In operator is not select statment at %s:%d", __FILE__,__LINE__);
        return ret;
    }

    sub_select->make_stmt_string(result_plan, assembled_sql_tmp);
    assembled_sql.append(assembled_sql_tmp);
    assembled_sql.append(")");

    return ret;
}

#if 0
int ObUnaryRefRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    item.type_ = get_expr_type();
    if (transformer == NULL || logical_plan == NULL || physical_plan == NULL)
    {
        jlog(ERROR, "transformer error");
        ret = OB_ERROR;
    }
    else
    {
        ErrStat err_stat;
        int32_t index = OB_INVALID_INDEX;
        ret = transformer->gen_physical_select(logical_plan, physical_plan, err_stat, id_, &index);
        item.value_.int_ = index;
    }
    if (ret == OB_SUCCESS && OB_INVALID_INDEX == item.value_.int_)
    {
        jlog(ERROR, "generating physical plan for sub-query error");
        ret = OB_ERROR;
    }
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObBinaryRefRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObBinaryRefRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    if (first_id_ == OB_INVALID_ID)
        fprintf(fp, "%s : [table_id, column_id] = [NULL, %lu]\n",
            get_type_name(get_expr_type()), second_id_);
    else
        fprintf(fp, "%s : [table_id, column_id] = [%lu, %lu]\n",
            get_type_name(get_expr_type()), first_id_, second_id_);
}

/**************************************************
Funtion		:	ObBinaryRefRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string &assembled_sql
 **************************************************/
int64_t ObBinaryRefRawExpr::to_string(ResultPlan& result_plan, string &assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    string assembled_sql_tmp;

    ObSqlRawExpr* sql_expr = NULL;

    if (first_id_ == OB_INVALID_ID)
    {
        ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*> (result_plan.plan_tree_);
        if (logical_plan == NULL)
        {
            ret = OB_ERR_LOGICAL_PLAN_FAILD;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "logical_plan must exist!!! at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        sql_expr = logical_plan->get_expr_by_id(related_sql_raw_id);
        if (NULL == sql_expr)
        {
            ret = OB_ERR_LOGICAL_PLAN_FAILD;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "ref column error!!! at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        sql_expr->to_string(result_plan, assembled_sql_tmp);
        assembled_sql.append(assembled_sql_tmp);
    }
    else
    {
        schema_table* table_schema = meta_reader::get_instance().get_table_schema_by_id(result_plan.db_name, first_id_);
        if (NULL == table_schema)
        {
            ret = OB_ERR_SCHEMA_UNSET;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Schema(s) are not set at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        schema_column* column_schema = table_schema->get_column_from_table_by_id(second_id_);
        if (column_schema == NULL)
        {
            ret = OB_ERR_SCHEMA_UNSET;
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Schema(s) are not set at %s:%d", __FILE__,__LINE__);
            return ret;
        }

        if (is_op_name_field)
        {
            assembled_sql.append(table_schema->get_table_name());
            assembled_sql.append(".");
            assembled_sql.append(column_schema->get_column_name());
        }
        else
        {
            assembled_sql.append(column_schema->get_column_name());
        }
    }

    return ret;
}

#if 0

int ObBinaryRefRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    UNUSED(transformer);
    UNUSED(logical_plan);
    UNUSED(physical_plan);
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();

    if (ret == OB_SUCCESS && get_expr_type() == T_REF_COLUMN)
    {
        item.value_.cell_.tid = first_id_;
        item.value_.cell_.cid = second_id_;
    }
    else
    {
        // No other type
        ret = OB_ERROR;
    }
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObUnaryOpRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObUnaryOpRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    expr_->print(fp, level + 1);
}

/**************************************************
Funtion		:	ObUnaryOpRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:   string &assembled_sql

 **************************************************/
int64_t ObUnaryOpRawExpr::to_string(ResultPlan& result_plan, string &assembled_sql) const
{
    /*T_OP_NOT, no need to get route*/
    int64_t ret = OB_SUCCESS;
    string assembled_sql_tmp;

    assembled_sql.append(get_type_symbol(get_expr_type()));
    assembled_sql.append("(");
    expr_->to_string(result_plan, assembled_sql_tmp);
    assembled_sql.append(assembled_sql_tmp);
    assembled_sql.append(")");
    return ret;
}

#if 0

int ObUnaryOpRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();
    item.value_.int_ = 1; /* One operator */

    ret = expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObBinaryOpRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObBinaryOpRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    first_expr_->print(fp, level + 1);
    second_expr_->print(fp, level + 1);
}

/**************************************************
Funtion		:	ObBinaryOpRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string &assembled_sql
 **************************************************/
int64_t ObBinaryOpRawExpr::to_string(ResultPlan& result_plan, string &assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    string assembled_sql_tmp1;
    string assembled_sql_tmp2;

    if (T_OP_OR == get_expr_type())
    {
        assembled_sql.append("(");
    }
    first_expr_->to_string(result_plan, assembled_sql_tmp1);
    assembled_sql.append(assembled_sql_tmp1);
    assembled_sql.append(get_type_symbol(get_expr_type()));
    second_expr_->to_string(result_plan, assembled_sql_tmp2);
    assembled_sql.append(assembled_sql_tmp2);

    if (T_OP_OR == get_expr_type())
    {
        assembled_sql.append(")");
    }
    return ret;
}

void ObBinaryOpRawExpr::set_op_exprs(ObRawExpr *first_expr, ObRawExpr *second_expr)
{
    SqlItemType exchange_type = T_MIN_OP;
    switch (get_expr_type())
    {
        case T_OP_LE:
            exchange_type = T_OP_GE;
            break;
        case T_OP_LT:
            exchange_type = T_OP_GT;
            break;
        case T_OP_GE:
            exchange_type = T_OP_LE;
            break;
        case T_OP_GT:
            exchange_type = T_OP_LT;
            break;
        case T_OP_EQ:
        case T_OP_NE:
            exchange_type = get_expr_type();
            break;
        default:
            exchange_type = T_MIN_OP;
            break;
    }
    if (exchange_type != T_MIN_OP
            && first_expr && first_expr->is_const()
            && second_expr && second_expr->is_column())
    {
        set_expr_type(exchange_type);
        first_expr_ = second_expr;
        second_expr_ = first_expr;
    }
    else
    {
        first_expr_ = first_expr;
        second_expr_ = second_expr;
    }
}

#if 0
int ObBinaryOpRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    bool dem_1_to_2 = false;
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();
    item.value_.int_ = 2; /* Two operators */

    // all form with 1 dimension and without sub-select will be changed to 2 dimensions
    // c1 in (1, 2, 3) ==> (c1) in ((1), (2), (3))
    if ((ret = first_expr_->fill_sql_expression(
            inter_expr,
            transformer,
            logical_plan,
            physical_plan)) == OB_SUCCESS
            && (get_expr_type() == T_OP_IN || get_expr_type() == T_OP_NOT_IN))
    {
        if (!first_expr_ || !second_expr_)
        {
            ret = OB_ERR_EXPR_UNKNOWN;
        }
        else if (first_expr_->get_expr_type() != T_OP_ROW
                && first_expr_->get_expr_type() != T_REF_QUERY
                && second_expr_->get_expr_type() == T_OP_ROW)
        {
            dem_1_to_2 = true;
            ExprItem dem2;
            dem2.type_ = T_OP_ROW;
            dem2.data_type_ = ObIntType;
            dem2.value_.int_ = 1;
            ret = inter_expr.add_expr_item(dem2);
        }
        if (OB_LIKELY(ret == OB_SUCCESS))
        {
            ExprItem left_item;
            left_item.type_ = T_OP_LEFT_PARAM_END;
            left_item.data_type_ = ObIntType;
            switch (first_expr_->get_expr_type())
            {
                case T_OP_ROW:
                case T_REF_QUERY:
                    left_item.value_.int_ = 2;
                    break;
                default:
                    left_item.value_.int_ = 1;
                    break;
            }
            if (dem_1_to_2)
                left_item.value_.int_ = 2;
            ret = inter_expr.add_expr_item(left_item);
        }
    }
    if (ret == OB_SUCCESS)
    {
        if (!dem_1_to_2)
        {
            ret = second_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
        }
        else
        {
            ExprItem dem2;
            dem2.type_ = T_OP_ROW;
            dem2.data_type_ = ObIntType;
            dem2.value_.int_ = 1;
            ObMultiOpRawExpr *row_expr = dynamic_cast<ObMultiOpRawExpr*> (second_expr_);
            if (row_expr != NULL)
            {
                ExprItem row_item;
                row_item.type_ = row_expr->get_expr_type();
                row_item.data_type_ = row_expr->get_result_type();
                row_item.value_.int_ = row_expr->get_expr_size();
                for (int32_t i = 0; ret == OB_SUCCESS && i < row_expr->get_expr_size(); i++)
                {
                    if ((ret = row_expr->get_op_expr(i)->fill_sql_expression(
                            inter_expr,
                            transformer,
                            logical_plan,
                            physical_plan)) != OB_SUCCESS
                            || (ret = inter_expr.add_expr_item(dem2)) != OB_SUCCESS)
                    {
                        break;
                    }
                }
                if (ret == OB_SUCCESS)
                    ret = inter_expr.add_expr_item(row_item);
            }
            else
            {
                ret = OB_ERR_EXPR_UNKNOWN;
            }
        }
    }
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObTripleOpRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObTripleOpRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    first_expr_->print(fp, level + 1);
    second_expr_->print(fp, level + 1);
    third_expr_->print(fp, level + 1);
}

/**************************************************
Funtion		:	ObTripleOpRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string& assembled_sql
 **************************************************/
int64_t ObTripleOpRawExpr::to_string(ResultPlan& result_plan, string& assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    string  assembled_sql_tmp1;
    string  assembled_sql_tmp2;
    string  assembled_sql_tmp3;

    first_expr_->to_string(result_plan, assembled_sql_tmp1);
    assembled_sql.append(assembled_sql_tmp1);
    assembled_sql.append(get_type_symbol(get_expr_type()));
    
    second_expr_->to_string(result_plan, assembled_sql_tmp2);
    assembled_sql.append(assembled_sql_tmp2);
    assembled_sql.append(" ");
    assembled_sql.append("AND ");
    
    third_expr_->to_string(result_plan, assembled_sql_tmp3);
    assembled_sql.append(assembled_sql_tmp3);
    assembled_sql.append(" ");
    return ret;
}

void ObTripleOpRawExpr::set_op_exprs(
        ObRawExpr *first_expr,
        ObRawExpr *second_expr,
        ObRawExpr *third_expr)
{
    first_expr_ = first_expr;
    second_expr_ = second_expr;
    third_expr_ = third_expr;
}

#if 0

int ObTripleOpRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();
    item.value_.int_ = 3; /* thress operators */

    if (ret == OB_SUCCESS)
        ret = first_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = second_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = third_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObMultiOpRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObMultiOpRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    for (uint32_t i = 0; i < exprs_.size(); i++)
    {
        exprs_[i]->print(fp, level + 1);
    }
}

/**************************************************
Funtion		:	ObMultiOpRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string&  assembled_sql
 **************************************************/
int64_t ObMultiOpRawExpr::to_string(ResultPlan& result_plan, string& assembled_sql) const
{
    string  assembled_sql_tmp;

    assembled_sql.append("(");

    for (uint32_t i = 0; i < exprs_.size(); i++)
    {
        exprs_[i]->to_string(result_plan, assembled_sql_tmp);
        assembled_sql.append(assembled_sql_tmp);

        if (i != exprs_.size() - 1)
        {
            assembled_sql.append(",");
        }
    }
    assembled_sql.append(")");
    return OB_SUCCESS;
}

#if 0

int ObMultiOpRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    item.type_ = get_expr_type();
    item.data_type_ = get_result_type();
    item.value_.int_ = exprs_.size();

    for (int32_t i = 0; ret == OB_SUCCESS && i < exprs_.size(); i++)
    {
        ret = exprs_[i]->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    }
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

#if 0

void ObCaseOpRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    if (arg_expr_)
        arg_expr_->print(fp, level + 1);
    for (int32_t i = 0; i < when_exprs_.size() && i < then_exprs_.size(); i++)
    {
        when_exprs_[i]->print(fp, level + 1);
        then_exprs_[i]->print(fp, level + 1);
    }
    if (default_expr_)
    {
        default_expr_->print(fp, level + 1);
    }
    else
    {
        for (int i = 0; i < level; ++i) fprintf(fp, "    ");
        fprintf(fp, "DEFAULT : NULL\n");
    }
}

int ObCaseOpRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    if (arg_expr_ == NULL)
        item.type_ = T_OP_CASE;
    else
        item.type_ = T_OP_ARG_CASE;
    item.data_type_ = get_result_type();
    item.value_.int_ = (arg_expr_ == NULL ? 0 : 1) + when_exprs_.size() + then_exprs_.size();
    item.value_.int_ += (default_expr_ == NULL ? 0 : 1);

    if (ret == OB_SUCCESS && arg_expr_ != NULL)
        ret = arg_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    for (int32_t i = 0; ret == OB_SUCCESS && i < when_exprs_.size() && i < then_exprs_.size(); i++)
    {
        ret = when_exprs_[i]->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
        if (ret != OB_SUCCESS)
            break;
        ret = then_exprs_[i]->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    }
    if (ret == OB_SUCCESS && default_expr_ != NULL)
        ret = default_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item(item);
    return ret;
}
#endif

void ObAggFunRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "ObAggFunRawExpr\n");
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s\n", get_type_name(get_expr_type()));
    if (distinct_)
    {
        for (int i = 0; i < level; ++i) fprintf(fp, "    ");
        fprintf(fp, "DISTINCT\n");
    }
    if (param_expr_)
        param_expr_->print(fp, level + 1);
}

/**************************************************
Funtion		:	ObAggFunRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string& assembled_sql
 **************************************************/
int64_t ObAggFunRawExpr::to_string(ResultPlan& result_plan, string& assembled_sql) const
{
    int64_t ret = OB_SUCCESS;
    string  assembled_sql_tmp;

    assembled_sql.append(get_type_symbol(get_expr_type()));
    if (distinct_)
    {
        assembled_sql.append("DISTINCT");
    }

    if (param_expr_)
    {
        assembled_sql.append("(");
        param_expr_->to_string(result_plan, assembled_sql_tmp);
        assembled_sql.append(assembled_sql_tmp);
        assembled_sql.append(")");
    }
    return ret;
}

#if 0

int ObAggFunRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    inter_expr.set_aggr_func(get_expr_type(), distinct_);
    if (param_expr_)
        ret = param_expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    return ret;
}
#endif

#if 0

void ObSysFunRawExpr::print(FILE* fp, int32_t level) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "%s : %.*s\n", get_type_name(get_expr_type()), func_name_.size(), func_name_.data());
    for (int32_t i = 0; i < exprs_.size(); i++)
    {
        exprs_[i]->print(fp, level + 1);
    }
}

int ObSysFunRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan) const
{
    int ret = OB_SUCCESS;
    ExprItem item;
    item.type_ = T_FUN_SYS;
    item.string_ = func_name_;
    item.value_.int_ = exprs_.size();
    for (int32_t i = 0; ret == OB_SUCCESS && i < exprs_.size(); i++)
    {
        ret = exprs_[i]->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
        if (ret != OB_SUCCESS)
        {
            jlog(WARNING, "Add parameters of system function failed, param %d", i + 1);
            break;
        }
    }
    if (ret == OB_SUCCESS && (ret = inter_expr.add_expr_item(item)) != OB_SUCCESS)
    {
        jlog(WARNING, "Add system function %.*s failed", func_name_.size(), func_name_.data());
    }
    return ret;
}
#endif

ObSqlRawExpr::ObSqlRawExpr()
{
    expr_id_ = OB_INVALID_ID;
    table_id_ = OB_INVALID_ID;
    column_id_ = OB_INVALID_ID;
    is_apply_ = false;
    contain_aggr_ = false;
    contain_alias_ = false;
    is_columnlized_ = false;
    expr_ = NULL;
}

ObSqlRawExpr::ObSqlRawExpr(
        uint64_t expr_id, uint64_t table_id, uint64_t column_id, ObRawExpr* expr)
{
    table_id_ = table_id;
    expr_id_ = expr_id;
    column_id_ = column_id;
    is_apply_ = false;
    contain_aggr_ = false;
    contain_alias_ = false;
    is_columnlized_ = false;
    expr_ = expr;
}

#if 0

int ObSqlRawExpr::fill_sql_expression(
        ObSqlExpression& inter_expr,
        ObTransformer *transformer,
        ObLogicalPlan *logical_plan,
        ObPhysicalPlan *physical_plan)
{
    int ret = OB_SUCCESS;
    if (!(transformer == NULL && logical_plan == NULL && physical_plan == NULL)
            && !(transformer != NULL && logical_plan != NULL && physical_plan != NULL))
    {
        jlog(WARNING, "(ObTransformer, ObLogicalPlan, ObPhysicalPlan) should be set together");
    }

    inter_expr.set_tid_cid(table_id_, column_id_);
    if (ret == OB_SUCCESS)
        ret = expr_->fill_sql_expression(inter_expr, transformer, logical_plan, physical_plan);
    if (ret == OB_SUCCESS)
        ret = inter_expr.add_expr_item_end();
    return ret;
}
#endif

void ObSqlRawExpr::print(FILE* fp, int32_t level, int32_t index) const
{
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "<ObSqlRawExpr %d Begin>\n", index);
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "expr_id = %lu\n", expr_id_);
    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    if (table_id_ == OB_INVALID_ID)
        fprintf(fp, "(table_id : column_id) = (NULL : %lu)\n", column_id_);
    else
        fprintf(fp, "(table_id : column_id) = (%lu : %lu)\n", table_id_, column_id_);

    if (NULL != expr_)
        expr_->print(fp, level);

    for (int i = 0; i < level; ++i) fprintf(fp, "    ");
    fprintf(fp, "<ObSqlRawExpr %d End>\n", index);
}

/**************************************************
Funtion		:	ObSqlRawExpr::to_string
Author		:	qinbo
Date		:	2013.9.11
Description	:   convert expr to string
Input		:	
Output		:	string& assembled_sql
 **************************************************/
int64_t ObSqlRawExpr::to_string(ResultPlan& result_plan, string& assembled_sql) const
{
    key_data key_relation;
    if (NULL != expr_)
    {
        expr_->to_string(result_plan, assembled_sql);
    }
    return OB_SUCCESS;
}

