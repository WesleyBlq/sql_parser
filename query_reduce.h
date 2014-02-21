/* 
 * File:   query_reduce.h
 * Author: tangchao
 *
 * Created on 2013年11月25日, 上午10:10
 */

#ifndef _QUERY_REDUCE_H
#define	_QUERY_REDUCE_H

#include <mysql.h>
#include <vector>
#include "sql_item_type.h"
#include "sql_select_stmt.h"
#include <mysql.h>

using namespace jdbd::common;
using namespace jdbd::sql;

#define NO_REDUCE                                       1
#define REDUCE_GROUP                                    2
#define REDUCE_AGGREGATE                                3
#define REDUCE_HAVING                                   4
#define REDUCE_ORDER                                    5

#define EXECUTE_GROUP                                   10
#define EXECUTE_AGGREGATE                               11
#define EXECUTE_HAVING                                  12
#define EXECUTE_ORDER                                   13

using namespace std;
using namespace jdbd::common;
using namespace jdbd::sql;

class OrderPostReduce
{
public:
    OrderPostReduce(bool sort, int32_t pos, enum enum_field_types field_type);
    OrderPostReduce(const OrderPostReduce& orig);
    virtual ~OrderPostReduce();

    bool get_sort();
    int32_t get_pos();
    enum enum_field_types get_field_type();
private:
    /* ASC:false, DESC:true*/
    bool sort;
    /* in select list */
    int32_t pos;
    enum enum_field_types field_type;
};

class AggrFuncPostReduce
{
public:
    AggrFuncPostReduce(int32_t pos, int32_t func,
            enum enum_field_types field_type);
    AggrFuncPostReduce(const AggrFuncPostReduce& orig);
    virtual ~AggrFuncPostReduce();
    
    int32_t get_pos();
    int32_t get_func();
    enum enum_field_types get_field_type();
private:
    int32_t pos;
    int32_t func;
    enum enum_field_types field_type;
};

class HavingPostReduce
{
public:
    HavingPostReduce(int32_t pos, int32_t func, int32_t operate, double value,
            enum enum_field_types field_type);
    HavingPostReduce(const HavingPostReduce& orig);
    virtual ~HavingPostReduce();

    int32_t get_pos();
    int32_t get_func();
    int32_t get_operate();
    double get_value();
    enum enum_field_types get_field_type();
private:
    int32_t pos;
    int32_t func;
    int32_t operate;
    double value;
    enum enum_field_types field_type;
};

class QueryPostReduce
{
public:
    QueryPostReduce();
    QueryPostReduce(const QueryPostReduce& orig);
    virtual ~QueryPostReduce();

    void set_post_reduce_info(ResultPlan& result_plan, ObSelectStmt *select_stmt);
    void set_post_reduce_type(int32_t reduce);                                  //start process sequence type 
    void set_appended_column_num(uint32_t original_field_num, uint32_t real_field_num);   //column nums.
    void set_limit_reduce_info(uint64_t row_offset, uint64_t row_count);                   //limit     
    void add_group_reduce_info(bool sort, int32_t pos, enum enum_field_types field_type);  //pos: column sequ in select columns 
    void add_aggr_func_reduce_info(int32_t pos, int32_t func, enum enum_field_types field_type);//same to 
    void add_having_reduce_info(int32_t pos, int32_t func, int32_t operate, double value, enum enum_field_types field_type);
    void add_order_reduce_info(bool sort, int32_t pos, enum enum_field_types field_type);
    void set_original_field_item(vector<SelectItem> &select_items_);
    vector<SelectItem> &get_original_field_item( );
    void set_all_from_tables(vector<string> from_tables);
    vector<string>     get_all_from_tables(); 

    int32_t get_reduce();
    uint32_t get_group_size();
    uint32_t get_func_size();
    uint32_t get_having_size();
    uint32_t get_order_size();

    vector<OrderPostReduce> get_group();
    vector<OrderPostReduce> get_order();
    vector<AggrFuncPostReduce> get_func();
    vector<HavingPostReduce> get_having();

    uint32_t get_original_field_num();
    uint32_t get_real_field_num();
    uint64_t get_row_offset();
    uint64_t get_row_count();

    vector<OrderPostReduce> get_using_key();
    int32_t get_execute_code();
    
private:
    int32_t     reduce; /* NO_REDUCE, REDUCE_GROUP,REDUCE_AGGREGATE,REDUCE_HAVING,REDUCE_ORDER */
    int32_t     execute_code;
    uint32_t    original_field_num;
    uint32_t    real_field_num;
    uint64_t    row_offset;
    uint64_t    row_count;
    vector<OrderPostReduce>     group;
    vector<OrderPostReduce>     order;
    vector<AggrFuncPostReduce>  func;
    vector<HavingPostReduce>    having;
    vector<SelectItem>          select_items;
    vector<string>              from_tables;
    
    bool  find_column_if_exist(vector<string> &columns, string goal_column, uint32_t column_off);
    bool  is_sort_asc(SqlItemType sort_type)
    {
        if ( sort_type == T_SORT_ASC)
        {
            return false;
        }
        return true;
    }

    enum enum_field_types trans_ob_sql2_mysql(ObObjType ob_sql_type);
};

#endif	/* _QUERY_REDUCE_H */

