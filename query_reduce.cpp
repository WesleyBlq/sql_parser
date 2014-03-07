/* 
 * File:   query_reduce.cpp
 * Author: tangchao
 * 
 * Created on 2013年11月25日, 上午10:10
 */

#include "../log/log.h"
#include "query_reduce.h"
#include "sql_select_stmt.h"


using namespace std;
using namespace jdbd::common;
using namespace jdbd::sql;

/**************************************************
Funtion     :   OrderPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
OrderPostReduce::OrderPostReduce(bool sort, int32_t pos,
        enum enum_field_types field_type) :
sort(sort), pos(pos), field_type(field_type)
{

}

/**************************************************
Funtion     :   OrderPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
OrderPostReduce::OrderPostReduce(const OrderPostReduce& orig) :
sort(orig.sort), pos(orig.pos), field_type(orig.field_type)
{

}

/**************************************************
Funtion     :   ~OrderPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
OrderPostReduce::~OrderPostReduce()
{

}

/**************************************************
Funtion     :   get_sort
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
bool OrderPostReduce::get_sort()
{
    return this->sort;
}

/**************************************************
Funtion     :   get_pos
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t OrderPostReduce::get_pos()
{
    return this->pos;
}

/**************************************************
Funtion     :   get_field_type
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
enum enum_field_types OrderPostReduce::get_field_type()
{
    return this->field_type;
}

/**************************************************
Funtion     :   AggrFuncPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
AggrFuncPostReduce::AggrFuncPostReduce(int32_t pos, int32_t func,
        enum enum_field_types field_type, int32_t avg_com_pos) : pos(pos), func(func), field_type(field_type),avg_com_pos(avg_com_pos)
{
}

/**************************************************
Funtion     :   AggrFuncPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
AggrFuncPostReduce::AggrFuncPostReduce(const AggrFuncPostReduce& orig)
: pos(orig.pos), func(orig.func), field_type(orig.field_type), avg_com_pos(orig.avg_com_pos)
{
}

/**************************************************
Funtion     :   ~AggrFuncPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
AggrFuncPostReduce::~AggrFuncPostReduce()
{
}

/**************************************************
Funtion     :   get_pos
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t AggrFuncPostReduce::get_pos()
{
    return pos;
}

/**************************************************
Funtion     :   get_func
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t AggrFuncPostReduce::get_func()
{
    return func;
}

/**************************************************
Funtion     :   get_field_type
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
enum enum_field_types AggrFuncPostReduce::get_field_type()
{
    return field_type;
}

/**************************************************
Funtion     :   get_avg_pos
Author      :   qinbo
Date        :   2014.3.5
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t AggrFuncPostReduce::get_avg_pos()
{
    return avg_com_pos;
}

/**************************************************
Funtion     :   HavingPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
HavingPostReduce::HavingPostReduce(int32_t pos, int32_t func, int32_t operate,
        double value, enum enum_field_types field_type) : pos(pos), func(func),
operate(operate), value(value), field_type(field_type)
{
}

/**************************************************
Funtion     :   HavingPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
HavingPostReduce::HavingPostReduce(const HavingPostReduce& orig) : pos(orig.pos),
func(orig.func), operate(orig.operate), value(orig.value),
field_type(orig.field_type)
{
}

/**************************************************
Funtion     :   ~HavingPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
HavingPostReduce::~HavingPostReduce()
{
}

/**************************************************
Funtion     :   get_pos
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t HavingPostReduce::get_pos()
{
    return pos;
}

/**************************************************
Funtion     :   get_func
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t HavingPostReduce::get_func()
{
    return func;
}

/**************************************************
Funtion     :   get_operate
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t HavingPostReduce::get_operate()
{
    return operate;
}

/**************************************************
Funtion     :   get_value
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
double HavingPostReduce::get_value()
{
    return value;
}

/**************************************************
Funtion     :   get_field_type
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
enum enum_field_types HavingPostReduce::get_field_type()
{
    return field_type;
}

/**************************************************
Funtion     :   QueryPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
QueryPostReduce::QueryPostReduce()
{
    row_offset = 0;
    row_count = MAX_LIMIT_ROWS;
    execute_code = NO_REDUCE;
}

/**************************************************
Funtion     :   QueryPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
QueryPostReduce::QueryPostReduce(const QueryPostReduce& orig)
{

}

/**************************************************
Funtion     :   ~QueryPostReduce
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   
Output      :   
return      :   
 **************************************************/
QueryPostReduce::~QueryPostReduce()
{
    group.clear();
    order.clear();
    func.clear();
    having.clear();
}

/**************************************************
Funtion     :   set_post_reduce_info
Author      :   qinbo
Date        :   2013.11.20
Description :   add sql post process info
Input       :   ResultPlan& result_plan,
                ObSelectStmt *select_stmt
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::set_post_reduce_info(ResultPlan& result_plan,
        ObSelectStmt *select_stmt)
{
    uint32_t i = 0;
    int32_t reduce_type = NO_REDUCE;
    uint32_t column_off = 0;
    uint32_t vector_off = 0;
    vector<string> exist_column_names;

    if (NULL == select_stmt)
    {
        return;
    }

    const vector<SelectItem>  &select_items    = select_stmt->get_all_select_items();
    const vector<GroupItem>   &group_items     = select_stmt->get_all_group_items();
    const vector<OrderItem>   &order_items     = select_stmt->get_all_order_items();
    const vector<HavingItem>  &having_items    = select_stmt->get_all_having_items();
    LimitItem           limit_item      = select_stmt->get_limit_item();
    uint32_t            raw_select_num  = select_items.size();


    //set limit 
    set_limit_reduce_info(limit_item.start, limit_item.end);

    uint32_t select_avg_pos = 0;
    for (i = 0; i < raw_select_num; i++)
    {
        SelectItem select_item = select_items.at(i);
        if ((0 != select_item.aggr_fun_type)&&(T_FUN_AVG != select_item.aggr_fun_type))
        {
            add_aggr_func_reduce_info(i, select_item.aggr_fun_type,
                    trans_ob_sql2_mysql(select_item.type_), -1);
        }
    }

    if (group_items.size() > 0)
    {
        for (i = 0; i < group_items.size(); i++)
        {
            GroupItem group_item = group_items.at(i);
            reduce_type = REDUCE_GROUP;

            if (!select_stmt->try_fetch_select_item_by_group(select_items,
                    group_item.group_column_, column_off))
            {
                if (!find_column_if_exist(exist_column_names,
                        group_item.group_column_, vector_off))
                {
                    add_group_reduce_info(is_sort_asc(group_item.group_type_),
                            raw_select_num + exist_column_names.size(),
                            trans_ob_sql2_mysql(group_item.column_type_));
                    exist_column_names.push_back(group_item.group_column_);
                }
                else
                {
                    add_group_reduce_info(is_sort_asc(group_item.group_type_),
                            raw_select_num + vector_off,
                            trans_ob_sql2_mysql(group_item.column_type_));
                }
            }
            else
            {
                add_group_reduce_info(is_sort_asc(group_item.group_type_),
                        column_off,
                        trans_ob_sql2_mysql(group_item.column_type_));
            }
        }

        set_post_reduce_type(REDUCE_GROUP);
    }


    if ((get_func().size() > 0)&&(NO_REDUCE == get_reduce()))
    {
        jlog(ERROR,"(get_func().size() > 0)&&(NO_REDUCE == get_reduce()");
        set_post_reduce_type(REDUCE_AGGREGATE);
    }

    if (having_items.size() > 0)
    {
        for (i = 0; i < having_items.size(); i++)
        {
            HavingItem having_item = having_items.at(i);
            if (!select_stmt->try_fetch_select_item_by_having(select_items,
                    having_item, column_off))
            {
                add_having_reduce_info(raw_select_num
                        + exist_column_names.size(),
                        having_item.aggr_fun_type,
                        having_item.aggr_fun_operate,
                        having_item.aggr_fun_value,
                        trans_ob_sql2_mysql(having_item.column_type_),
                        -1);
            }
            else
            {
                add_having_reduce_info(column_off,
                        having_item.aggr_fun_type,
                        having_item.aggr_fun_operate,
                        having_item.aggr_fun_value,
                        trans_ob_sql2_mysql(having_item.column_type_),
                        -1);
            }
        }

        if (NO_REDUCE == get_reduce())
        {
            set_post_reduce_type(REDUCE_AGGREGATE);
        }
    }

    if (!select_stmt->is_group_by_order_by_same(result_plan))
    {
        for (i = 0; i < order_items.size(); i++)
        {
            OrderItem order_item = order_items.at(i);
            if (NO_REDUCE == reduce_type)
            {
                reduce_type = REDUCE_ORDER;
            }
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items,
                    order_item.order_column_, column_off))
            {
                if (!find_column_if_exist(exist_column_names,
                        order_item.order_column_, vector_off))
                {
                    add_order_reduce_info(is_sort_asc(order_item.order_type_),
                            raw_select_num + exist_column_names.size(),
                            trans_ob_sql2_mysql(order_item.column_type_));
                    exist_column_names.push_back(order_item.order_column_);
                }
                else
                {
                    add_order_reduce_info(is_sort_asc(order_item.order_type_),
                            raw_select_num + vector_off,
                            trans_ob_sql2_mysql(order_item.column_type_));
                }
            }
            else
            {
                add_order_reduce_info(is_sort_asc(order_item.order_type_),
                        column_off,
                        trans_ob_sql2_mysql(order_item.column_type_));
            }
        }

        if (NO_REDUCE == get_reduce())
        {
            set_post_reduce_type(REDUCE_ORDER);
        }
    }

    for (i = 0; i < raw_select_num; i++)
    {
        SelectItem select_item = select_items.at(i);
        if (T_FUN_AVG == select_item.aggr_fun_type)
        {
            add_aggr_func_reduce_info(i, select_item.aggr_fun_type,
                    trans_ob_sql2_mysql(select_item.type_), select_avg_pos + raw_select_num
                        + exist_column_names.size());
            jlog(WARNING, "AGGR_FUNC: select_avg_pos %d", select_avg_pos + raw_select_num
                        + exist_column_names.size());
            select_avg_pos+=2;
        }
    }

    set_appended_column_num(select_items.size(), exist_column_names.size());
}

/**************************************************
Funtion     :   set_post_reduce_type
Author      :   tangchao
Date        :   2013.11.20
Description :   add sql post process info
Input       :   int32_t reduce
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::set_post_reduce_type(int32_t reduce)
{
    this->reduce = reduce;
}

/**************************************************
Funtion     :   set_appended_column_num
Author      :   qinbo
Date        :   2013.11.20
Description :   add sql post process info
Input       :   int32_t reduce
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::set_appended_column_num(uint32_t original_field_num,
        uint32_t real_field_num)
{
    this->original_field_num = original_field_num;
    this->real_field_num = real_field_num;
}

/**************************************************
Funtion     :   set_limit_reduce_info
Author      :   qinbo
Date        :   2013.11.20
Description :   add sql post process info
Input       :   int32_t reduce
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::set_limit_reduce_info(uint64_t row_offset,
        uint64_t row_count)
{
    this->row_offset = row_offset;
    this->row_count = row_count;
}

/**************************************************
Funtion     :   find_column_if_exist
Author      :   qinbo
Date        :   2013.11.20
Description :   whether the column already exist
Input       :   vector<string> &columns,
                string goal_column, 
                uint32_t column_off
Output      :   
return      :   
 **************************************************/
bool QueryPostReduce::find_column_if_exist(vector<string> &columns,
        string goal_column, uint32_t column_off)
{
    if (columns.size() == 0)
    {
        return false;
    }

    for (uint32_t i = 0; i < columns.size(); i++)
    {
        if (goal_column == columns.at(i))
        {
            column_off = i;
            return true;
        }
    }
    return false;
}

/**************************************************
Funtion     :   add_group_reduce_info
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   bool sort, 
                int32_t pos,
                enum enum_field_types field_type
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::add_group_reduce_info(bool sort, int32_t pos,
        enum enum_field_types field_type)
{
    this->group.push_back(OrderPostReduce(sort, pos, field_type));
}

/**************************************************
Funtion     :   add_aggr_func_reduce_info
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   int32_t pos, 
                int32_t func,
                enum enum_field_types field_type
                int32_t avg_com_pos
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::add_aggr_func_reduce_info(int32_t pos, int32_t func,
        enum enum_field_types field_type, int32_t avg_com_pos)
{
    this->func.push_back(AggrFuncPostReduce(pos, func, field_type, avg_com_pos));
}

/**************************************************
Funtion     :   add_having_reduce_info
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   int32_t pos, 
                int32_t func,
                int32_t operate, 
                double value, 
                enum enum_field_types field_type
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::add_having_reduce_info(int32_t pos, int32_t func,
        int32_t operate, double value, enum enum_field_types field_type, int32_t avg_com_pos)
{
    //whether this aggr func is already in func vector
    uint32_t i = 0;
    bool func_exist = false;
    if (get_func_size() > 0)
    {
        for (i = 0; i < get_func_size(); i++)
        {
            AggrFuncPostReduce aggr_func_item = get_func().at(i);
            if ((aggr_func_item.get_field_type() == field_type)
                    &&(aggr_func_item.get_func() == func)
                    &&(aggr_func_item.get_pos() == pos))
            {
                func_exist = true;
                break;
            }
        }

        if (!func_exist)
        {
            this->func.push_back(AggrFuncPostReduce(pos, func, field_type, avg_com_pos));
        }
    }
    else
    {
        if (T_INVALID == func)
        {

        }
        else
        {
            this->func.push_back(AggrFuncPostReduce(pos, func, field_type, avg_com_pos));
        }
    }

    this->having.push_back(HavingPostReduce(pos, func, operate, value,
            field_type));
}

/**************************************************
Funtion     :   add_order_reduce_info
Author      :   tangchao
Date        :   2013.11.20
Description :   
Input       :   bool sort, 
                int32_t pos,
                enum enum_field_types field_type
Output      :   
return      :   
 **************************************************/
void QueryPostReduce::add_order_reduce_info(bool sort, int32_t pos,
        enum enum_field_types field_type)
{
    this->order.push_back(OrderPostReduce(sort, pos, field_type));
}

/**************************************************
Funtion     :   trans_ob_sql2_mysql
Author      :   qinbo
Date        :   2013.11.20
Description :   transfer OB sql expression to MYSQL  sql expression
Input       :   ObObjType ob_sql_type
Output      :   
return      :   
 **************************************************/
enum enum_field_types QueryPostReduce::trans_ob_sql2_mysql(
        ObObjType ob_sql_type)
{
    switch (ob_sql_type)
    {
        case ObNullType:
            return MYSQL_TYPE_NULL;
        case ObIntType:
        case ObBoolType:
            return MYSQL_TYPE_LONGLONG;
        case ObFloatType:
        case ObDoubleType:
            return MYSQL_TYPE_DOUBLE;
        case ObDateTimeType:
            return MYSQL_TYPE_TIME;
        case ObPreciseDateTimeType:
            return MYSQL_TYPE_DATETIME;
        case ObVarcharType:
            return MYSQL_TYPE_VARCHAR;
        case ObDecimalType:
            return MYSQL_TYPE_DECIMAL;
        case ObMinType:
        case ObCreateTimeType:
        case ObModifyTimeType:
            return MYSQL_TYPE_DATETIME;
        case ObExtendType:
        case ObSeqType:
        default:
            return MYSQL_TYPE_GEOMETRY; //we don't support now
    }
}

/**************************************************
Funtion     :   get_reduce
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t QueryPostReduce::get_reduce()
{
    return this->reduce;
}

/**************************************************
Funtion     :   get_group_size
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_group_size()
{
    return this->group.size();
}

/**************************************************
Funtion     :   get_func_size
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_func_size()
{
    return this->func.size();
}

/**************************************************
Funtion     :   get_having_size
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_having_size()
{
    return this->having.size();
}

/**************************************************
Funtion     :   get_order_size
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_order_size()
{
    return this->order.size();
}

/**************************************************
Funtion     :   get_group
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
vector<OrderPostReduce> QueryPostReduce::get_group()
{
    return this->group;
}

/**************************************************
Funtion     :   get_order
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
vector<OrderPostReduce> QueryPostReduce::get_order()
{
    return this->order;
}

/**************************************************
Funtion     :   get_func
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
vector<AggrFuncPostReduce> QueryPostReduce::get_func()
{
    return this->func;
}

/**************************************************
Funtion     :   get_having
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
vector<HavingPostReduce> QueryPostReduce::get_having()
{
    return this->having;
}

/**************************************************
Funtion     :   get_original_field_num
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_original_field_num()
{
    return this->original_field_num;
}

/**************************************************
Funtion     :   get_real_field_num
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint32_t QueryPostReduce::get_real_field_num()
{
    return this->real_field_num;
}

/**************************************************
Funtion     :   get_row_offset
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint64_t QueryPostReduce::get_row_offset()
{
    return this->row_offset;
}

/**************************************************
Funtion     :   get_row_count
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
uint64_t QueryPostReduce::get_row_count()
{
    return this->row_count;
}

/**************************************************
Funtion     :   get_execute_code
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
int32_t QueryPostReduce::get_execute_code()
{
    return execute_code;
}

/**************************************************
Funtion     :   get_using_key
Author      :   tangchao
Date        :   2013.11.20
Description :   get post process info
Input       :   
Output      :   
return      :   
 **************************************************/
vector<OrderPostReduce> QueryPostReduce::get_using_key()
{
    vector<OrderPostReduce> tmp;

    if (group.size())
    {
        execute_code = EXECUTE_GROUP;

        if (func.size())
        {
            reduce = REDUCE_AGGREGATE;
        }
        else if (having.size())
        {
            reduce = REDUCE_HAVING;
        }
        else if (order.size())
        {
            reduce = REDUCE_ORDER;
        }
        else
        {
            reduce = NO_REDUCE;
        }
        return group;
    }

    if (func.size())
    {
        execute_code = EXECUTE_AGGREGATE;

        if (having.size())
        {
            reduce = REDUCE_HAVING;
        }
        else if (order.size())
        {
            reduce = REDUCE_ORDER;
        }
        else
        {
            reduce = NO_REDUCE;
        }
        return tmp;
    }


    if (having.size())
    {
        execute_code = EXECUTE_HAVING;
        if (order.size())
        {
            reduce = REDUCE_ORDER;
        }
        else
        {
            reduce = NO_REDUCE;
        }
        return tmp;
    }


    if (order.size())
    {
        execute_code = EXECUTE_ORDER;
        return order;
    }
    else
    {
        reduce = NO_REDUCE;
        return tmp;
    }
}
