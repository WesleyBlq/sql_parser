/* 
 * File:   query_reduce.cpp
 * Author: tangchao
 * 
 * Created on 2013年11月25日, 上午10:10
 */
 
#include "../log/jlog.h"
#include "query_reduce.h"
#include "ob_select_stmt.h"


using namespace std;
using namespace oceanbase::common;
using namespace oceanbase::sql;

OrderPostReduce::OrderPostReduce(bool sort, int32_t pos,
        enum enum_field_types field_type) :
sort(sort), pos(pos), field_type(field_type)
{

}

OrderPostReduce::OrderPostReduce(const OrderPostReduce& orig) :
sort(orig.sort), pos(orig.pos), field_type(orig.field_type)
{

}

OrderPostReduce::~OrderPostReduce()
{

}

bool OrderPostReduce::get_sort()
{
    return this->sort;
}

int32_t OrderPostReduce::get_pos()
{
    return this->pos;
}

enum enum_field_types OrderPostReduce::get_field_type()
{
    return this->field_type;
}

AggrFuncPostReduce::AggrFuncPostReduce(int32_t pos, int32_t func,
        enum enum_field_types field_type) : pos(pos), func(func), field_type(field_type)
{
}

AggrFuncPostReduce::AggrFuncPostReduce(const AggrFuncPostReduce& orig) : pos(orig.pos), func(orig.func),
field_type(orig.field_type)
{
}

AggrFuncPostReduce::~AggrFuncPostReduce()
{
}

int32_t AggrFuncPostReduce::get_pos()
{
    return pos;
}

int32_t AggrFuncPostReduce::get_func()
{
    return func;
}

enum enum_field_types AggrFuncPostReduce::get_field_type()
{
    return field_type;
}

HavingPostReduce::HavingPostReduce(int32_t pos, int32_t func, int32_t operate, double value,
        enum enum_field_types field_type) : pos(pos), func(func), operate(operate),
value(value), field_type(field_type)
{
}

HavingPostReduce::HavingPostReduce(const HavingPostReduce& orig) : pos(orig.pos),
func(orig.func), operate(orig.operate), value(orig.value), field_type(orig.field_type)
{
}

HavingPostReduce::~HavingPostReduce()
{
}

int32_t HavingPostReduce::get_pos()
{
    return pos;
}

int32_t HavingPostReduce::get_func()
{
    return func;
}

int32_t HavingPostReduce::get_operate()
{
    return operate;
}

double HavingPostReduce::get_value()
{
    return value;
}

enum enum_field_types HavingPostReduce::get_field_type()
{
    return field_type;
}

QueryPostReduce::QueryPostReduce( )
{
    row_offset = 0;
    row_count = 0xFFFFFFFF;
}

QueryPostReduce::QueryPostReduce(const QueryPostReduce& orig)
{

}

QueryPostReduce::~QueryPostReduce()
{

}

void QueryPostReduce::set_post_reduce_info(ResultPlan& result_plan, ObSelectStmt *select_stmt)
{
    uint32_t    i               = 0;
    int32_t     reduce_type     = NO_REDUCE;
    uint32_t    column_off      = 0;
    uint32_t    vector_off      = 0;
    vector<string> exist_column_names;
    
    if (NULL == select_stmt)
    {
        return;
    }

    vector<SelectItem>  select_items    = select_stmt->get_all_select_items();
    vector<GroupItem>   group_items     = select_stmt->get_all_group_items();
    vector<OrderItem>   order_items     = select_stmt->get_all_order_items();
    vector<HavingItem>  having_items    = select_stmt->get_all_having_items();
    LimitItem           limit_item      = select_stmt->get_limit_item();
    uint32_t            raw_select_num  = select_items.size();

    //set limit 
    set_limit_reduce_info(limit_item.start, limit_item.end);

    if (group_items.size() > 0)
    {
        for (i = 0; i < group_items.size(); i++)
        {
            GroupItem group_item = group_items.at(i);
            reduce_type = REDUCE_GROUP;
                        
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, group_item.group_column_, column_off))
            {
                if(!find_column_if_exist(exist_column_names, group_item.group_column_, vector_off))
                {
                    add_group_reduce_info( is_sort_asc(group_item.group_type_), 
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
    }


    if (having_items.size() > 0)
    {
        for (i = 0; i < having_items.size(); i++)
        {
            HavingItem having_item = having_items.at(i);
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, having_item.having_column_name, column_off))
            {
                if(!find_column_if_exist(exist_column_names, having_item.having_column_name, vector_off))
                {
                    add_having_reduce_info( raw_select_num + exist_column_names.size(), 
                                            having_item.aggr_fun_type, 
                                            having_item.aggr_fun_operate, 
                                            having_item.aggr_fun_value, 
                                            trans_ob_sql2_mysql(having_item.column_type_));
                    exist_column_names.push_back(having_item.having_column_name);
                }
                else
                {
                    add_having_reduce_info( raw_select_num + vector_off,
                                            having_item.aggr_fun_type, 
                                            having_item.aggr_fun_operate, 
                                            having_item.aggr_fun_value, 
                                            trans_ob_sql2_mysql(having_item.column_type_));
                }
            }
            else
            {
                add_having_reduce_info( column_off, 
                                        having_item.aggr_fun_type, 
                                        having_item.aggr_fun_operate, 
                                        having_item.aggr_fun_value, 
                                        trans_ob_sql2_mysql(having_item.column_type_));
            }
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
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, order_item.order_column_, column_off))
            {
                if(!find_column_if_exist(exist_column_names, order_item.order_column_, vector_off))
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
    }

    set_appended_column_num(select_items.size(), exist_column_names.size());
}


void QueryPostReduce::set_post_reduce_type(int32_t reduce)
{
    this->reduce = reduce;
}

void QueryPostReduce::set_appended_column_num(uint32_t original_field_num, uint32_t real_field_num)
{
    this->original_field_num = original_field_num;
    this->real_field_num = real_field_num;
}

void QueryPostReduce::set_limit_reduce_info(uint64_t row_offset, uint64_t row_count)
{
    this->row_offset = row_offset;
    this->row_count = row_count;
}

bool QueryPostReduce::find_column_if_exist(vector<string> &columns, string goal_column, uint32_t column_off)
{
    for (uint32_t i = 0;i< columns.size(); i++)
    {
        if (goal_column == columns.at(i))
        {
            column_off = i;
            return true;
        }
    }
    return false;
}


void QueryPostReduce::add_group_reduce_info(bool sort, int32_t pos, enum enum_field_types field_type)
{
    this->group.push_back(OrderPostReduce(sort, pos, field_type));
}

void QueryPostReduce::add_aggr_func_reduce_info(int32_t pos, int32_t func, enum enum_field_types field_type)
{
    this->func.push_back(AggrFuncPostReduce(pos, func, field_type));
}

void QueryPostReduce::add_having_reduce_info(int32_t pos, int32_t func, int32_t operate, double value, enum enum_field_types field_type)
{
    this->having.push_back(HavingPostReduce(pos, func, operate, value, field_type));
}

void QueryPostReduce::add_order_reduce_info(bool sort, int32_t pos, enum enum_field_types field_type)
{
    this->order.push_back(OrderPostReduce(sort, pos, field_type));
}


enum enum_field_types QueryPostReduce::trans_ob_sql2_mysql(ObObjType ob_sql_type)
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
        case ObExtendType:
        case ObSeqType:
        default:
            return MYSQL_TYPE_GEOMETRY; //we don't support now
    }
}


int32_t QueryPostReduce::get_reduce()
{
    return this->reduce;
}

uint32_t QueryPostReduce::get_group_size()
{
    return this->group.size();
}

uint32_t QueryPostReduce::get_func_size()
{
    return this->func.size();
}

uint32_t QueryPostReduce::get_having_size()
{
    return this->having.size();
}

uint32_t QueryPostReduce::get_order_size()
{
    return this->order.size();
}

vector<OrderPostReduce> QueryPostReduce::get_group()
{
    return this->group;
}

vector<OrderPostReduce> QueryPostReduce::get_order()
{
    return this->order;
}

vector<AggrFuncPostReduce> QueryPostReduce::get_func()
{
    return this->func;
}

vector<HavingPostReduce> QueryPostReduce::get_having()
{
    return this->having;
}

uint32_t QueryPostReduce::get_original_field_num()
{
    return this->original_field_num;
}

uint32_t QueryPostReduce::get_real_field_num()
{
    return this->real_field_num;
}

uint64_t QueryPostReduce::get_row_offset()
{
    return this->row_offset;
}

uint64_t QueryPostReduce::get_row_count()
{
    return this->row_count;
}

int32_t QueryPostReduce::get_execute_code()
{
    return execute_code;
}

vector<OrderPostReduce> QueryPostReduce::get_using_key()
{
    vector<OrderPostReduce> tmp;
    int32_t pos;
    enum enum_field_types field_type;
    bool sort;

    if (REDUCE_GROUP == reduce)
    {
        jlog(INFO, "sql execute step GROUP");
        if (tmp.size())
        {
            jlog(ERROR, "first explain is error.");
            tmp.clear();
        }
        reduce++;
        tmp = group;
        execute_code = EXECUTE_GROUP;
        goto explain_reduce_aggregate;
    }

explain_reduce_aggregate:
    if (REDUCE_AGGREGATE == reduce)
    {
        jlog(INFO, "sql execute step aggregate");
        if (tmp.size())
        {
            reduce++;
            goto explain_reduce_having;
        }
        reduce++;
        execute_code = EXECUTE_AGGREGATE;
        pos = func[0].get_pos();
        field_type = func[0].get_field_type();
        sort = false;
        tmp.push_back(OrderPostReduce(sort, pos, field_type));  
        goto explain_reduce_having;
    }

explain_reduce_having:
    if (REDUCE_HAVING == reduce)
    {
        jlog(INFO, "sql execute step HAVING");
        if (tmp.size())
        {
            if (having.size())
            {
                goto explain_current_reduce;
            }
            else
            {
                reduce++;
                goto explain_reduce_order;
            }
        }

        reduce++;
        if (group.size())
        {
            execute_code = EXECUTE_HAVING;
            tmp = group;
            goto explain_reduce_order;
        }
        else
        {
            jlog(ERROR, "SQL syntax error.");
            goto explain_no_reduce;
        }
    }

explain_reduce_order:
    if (REDUCE_ORDER == reduce)
    {
        jlog(INFO, "sql execute step ORDER");
        if (tmp.size())
        {
            if (order.size())
            {
            }
            else
            {
                reduce = NO_REDUCE;
            }
            goto explain_current_reduce;
        }

        reduce = NO_REDUCE;
        if (order.size())
        {
            tmp = order;
        }
        goto explain_current_reduce;
    }

explain_no_reduce:
    if (reduce == NO_REDUCE)
    {
        jlog(INFO, "sql execute step END");
        tmp.clear();
        execute_code = NO_REDUCE;
        return tmp;
    }

explain_current_reduce:
    jlog(INFO, "sql next execute step %d", execute_code);
    return tmp;
}
