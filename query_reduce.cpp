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

HavingPostReduce::HavingPostReduce(int32_t pos, int32_t func, int32_t operate, int32_t value,
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

    vector<SelectItem>  select_items    = select_stmt->fetch_select_from_tree(result_plan, "");
    vector<GroupItem>   group_items     = select_stmt->fetch_group_from_tree(result_plan, "");
    vector<OrderItem>   order_items     = select_stmt->fetch_order_from_tree(result_plan, "");
    vector<HavingItem>  Having_items    = select_stmt->fetch_having_from_tree(result_plan, "");
    uint32_t            raw_select_num  = select_items.size();

    if (group_items.size() > 0)
    {
        for (i = 0; i < group_items.size(); i++)
        {
            GroupItem group_item = group_items.at(i);
            reduce_type = REDUCE_GROUP;
                        
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, group_items[i].group_column_, column_off))
            {
                if(!find_column_if_exist(exist_column_names, group_items[i].group_column_, vector_off))
                {
                    add_group_reduce_info(group_item.group_type_, raw_select_num + exist_column_names.size(), MYSQL_TYPE_LONG);
                    exist_column_names.push_back(group_items[i].group_column_);
                }
                else
                {
                    add_group_reduce_info(group_item.group_type_, raw_select_num + vector_off, MYSQL_TYPE_LONG);
                }
            }
            else
            {
                add_group_reduce_info(group_item.group_type_, column_off, MYSQL_TYPE_LONG);
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
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, order_item.order_column, column_off))
            {
                if(!find_column_if_exist(exist_column_names, order_item.order_column, vector_off))
                {
                    add_order_reduce_info(order_item.order_type_, raw_select_num + exist_column_names.size(), MYSQL_TYPE_LONG);
                    exist_column_names.push_back(order_item.order_column);
                }
                else
                {
                    add_order_reduce_info(order_item.order_type_, raw_select_num + vector_off, MYSQL_TYPE_LONG);
                }
            }
            else
            {
                add_order_reduce_info(order_item.order_type_, column_off, MYSQL_TYPE_LONG);
            }
        }
    }

    if (Having_items.size() > 0)
    {
        for (i = 0; i < Having_items.size(); i++)
        {
            if (!select_stmt->try_fetch_select_item_by_column_name(select_items, Having_items[i].having_column_name, column_off))
            {
                if(!find_column_if_exist(exist_column_names, Having_items[i].having_column_name, vector_off))
                {
                    //add_having_reduce_info(column_off, 0);
                    exist_column_names.push_back(Having_items[i].having_column_name);
                }
                else
                {
                    //add_having_reduce_info(column_off, 0);
                }
            }
            else
            {
                //add_having_reduce_info(column_off, 0);
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

void QueryPostReduce::set_limit_reduce_info(uint64_t *row_offset, uint64_t *row_count)
{
    if (row_offset)
    {
        this->row_offset = *row_offset;
    }
    else
    {
        this->row_offset = 0;

    }
    if (row_count)
    {
        this->row_count = *row_count;
    }
    else
    {
        this->row_count = 0xFFFFFFFF;
    }
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

void QueryPostReduce::add_having_reduce_info(int32_t pos, int32_t func, int32_t operate, int32_t value, enum enum_field_types field_type)
{
    this->having.push_back(HavingPostReduce(pos, func, operate, value, field_type));
}

void QueryPostReduce::add_order_reduce_info(bool sort, int32_t pos, enum enum_field_types field_type)
{
    this->order.push_back(OrderPostReduce(sort, pos, field_type));
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
