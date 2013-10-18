
#include "jd_exec_plan.h"

extern meta_reader *g_metareader;

using namespace oceanbase::common;
using namespace oceanbase::sql;

/**************************************************
Funtion     :   set_exec_unit_sql
Author      :   qinbo
Date        :   2013.10.18
Description :   set exec plan unit sql 
Input       :   string sql_
Output      :   
**************************************************/
void ExecPlanUnit::set_exec_unit_sql(string sql_)
{
    sql.assign(sql_);
}

/**************************************************
Funtion     :   set_exec_unit_sql
Author      :   qinbo
Date        :   2013.10.18
Description :   set exec plan unit shard info 
Input       :   schema_shard* shard_info_
Output      :   
**************************************************/
void ExecPlanUnit::set_exec_uint_shard_info(schema_shard* shard_info_)
{
    shard_info = shard_info_;
}

bool SameLevelExecPlan::get_parent_sql_type()
{

}


void SameLevelExecPlan::set_parent_sql_type(uint8_t parent_sql_type)
{

}

void SameLevelExecPlan::set_first_plan_true()
{

}

void SameLevelExecPlan::is_first_plan()
{

}

void SameLevelExecPlan::add_exec_plan_unit(ExecPlanUnit* exec_plan_unit)
{
    exec_plan_units.push_back(exec_plan_unit);

}


template <class T>
int QueryActuator::get_stmt(
    ObLogicalPlan *logical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    T *& stmt)
{
  int& ret = err_stat.err_code_ = OB_SUCCESS;
  /* get statement */
  if (query_id == OB_INVALID_ID)
    stmt = dynamic_cast<T*>(logical_plan->get_main_stmt());
  else
    stmt = dynamic_cast<T*>(logical_plan->get_query(query_id));
  if (stmt == NULL)
  {
    err_stat.err_code_ = OB_ERR_PARSER_SYNTAX;
  }
  return ret;
}


QueryActuator::QueryActuator()
{

}

QueryActuator::~QueryActuator()
{


}

FinalExecPlan* QueryActuator::popActuator()
{


}

void QueryActuator::pushActuator(FinalExecPlan* exec_plan)
{



}


bool QueryActuator::is_all_plan_done()
{



}


void QueryActuator::set_all_plan_done()
{



}


void QueryActuator::set_next_plan_reparsed()
{



}


bool QueryActuator::get_next_plan_reparsed()
{


}

void QueryActuator::reparse_next_plan()
{


}


/**************************************************
Funtion     :   generate_exec_plan
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::generate_exec_plan(
    ResultPlan& result_plan,
    FinalExecPlan*& final_exec_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int& ret = err_stat.err_code_ = OB_SUCCESS;
    bool new_generated = false;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);

    
    if (logical_plan)
    {
      if (OB_LIKELY(NULL == final_exec_plan))
      {
        if ((final_exec_plan = (FinalExecPlan*)parse_malloc(sizeof(FinalExecPlan), NULL)) == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            TBSYS_LOG(DEBUG, "Can not malloc space for FinalExecPlan");
        }
        else
        {
            final_exec_plan = new(final_exec_plan) FinalExecPlan();
            TBSYS_LOG(DEBUG, "new physical plan, addr=%p", final_exec_plan);
            new_generated = true;
        }
      }
      
      ObBasicStmt *stmt = NULL;
      if (ret == OB_SUCCESS)
      {
        if (query_id == OB_INVALID_ID)
          stmt = logical_plan->get_main_stmt();
        else
          stmt = logical_plan->get_query(query_id);
        if (stmt == NULL)
        {
          ret = OB_ERR_ILLEGAL_ID;
          TBSYS_LOG(DEBUG, "Wrong query id to find query statement");
        }
      }
      TBSYS_LOG(DEBUG, "generate physical plan for query_id=%lu stmt_type=%d",
                query_id, stmt->get_stmt_type());
      if (OB_LIKELY(ret == OB_SUCCESS))
      {
        switch (stmt->get_stmt_type())
        {
          case ObBasicStmt::T_SELECT:
            ret = gen_exec_plan_select(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_DELETE:
            ret = gen_exec_plan_delete(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_INSERT:
            ret = gen_exec_plan_insert(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_REPLACE:
            ret = gen_exec_plan_replace(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          case ObBasicStmt::T_UPDATE:
            ret = gen_exec_plan_update(result_plan, final_exec_plan, err_stat, query_id, index);
            break;
          default:
            ret = OB_NOT_SUPPORTED;
            TBSYS_LOG(DEBUG, "Unknown logical plan, stmt_type=%d", stmt->get_stmt_type());
            break;
        }
      }
      
      if (ret != OB_SUCCESS && new_generated && final_exec_plan != NULL)
      {
        final_exec_plan->~FinalExecPlan();
        parse_free(final_exec_plan);
        final_exec_plan = NULL;
      }
    }
    return ret;
}


/**************************************************
Funtion     :   gen_exec_plan_select
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::gen_exec_plan_select(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }

    if (select_stmt->is_from_item_with_join())
    {
        ret = OB_ERR_GEN_PLAN;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not support stmt with JOIN now");
        return ret;
    }
    else
    {
        /*related to 1 table*/
        if (select_stmt->get_from_item_size() == 1)
        {
            generate_select_plan_single_table(result_plan, physical_plan, err_stat, query_id, index);
        }
        /*related to >1 tables*/
        else
        {
            generate_select_plan_multi_table(result_plan, physical_plan, err_stat, query_id, index);
        }
    }


    
}

/**************************************************
Funtion     :   generate_select_plan_single_table
Author      :   qinbo
Date        :   2013.9.27
Description :   generate select exec plan with single table
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::generate_select_plan_single_table(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObSelectStmt *select_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);
    vector<string>      table_names;
    string              table_name;
    
    vector<SelectItem>  select_items;
    SelectItem          select_item;

    vector<string>      where_items;
    string              where_item;
    string              db_name;
    char                buf[SQL_PLAN_BUF_SIZE] = {0};
    string              sql_exec_plan_unit;
    schema_shard*       shard_info = NULL;
    ObSqlRawExpr*       sql_expr = NULL;
    ObRawExpr*          raw_expr = NULL;
    
    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, select_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }

    table_names = select_stmt->fetch_tables_from_tree(result_plan);
    if (table_names.size() > 1)
    {
        ret = JD_ERR_LOGICAL_TREE_WRONG;
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Select stmt size is not right");
        return ret;
    }
    
    table_name = table_names.at(0);
    select_items = select_stmt->fetch_select_from_tree(result_plan, table_name);
    where_items = select_stmt->fetch_where_from_tree(result_plan, table_name);
        
    db_name.assign(result_plan.db_name);

    cout << "db name get " << db_name << endl;
    
    schema_db* db_schema = g_metareader->get_DB_schema(db_name);
    schema_table* table_schema = db_schema->get_table_from_db(table_name);

    SameLevelExecPlan* exec_plan = (SameLevelExecPlan*)parse_malloc(sizeof(SameLevelExecPlan), NULL);
    if (exec_plan == NULL)
    {
        ret = OB_ERR_PARSER_MALLOC_FAILED;
        TBSYS_LOG(WARN, "out of memory");
        snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
            "Can not malloc space for SameLevelExecPlan");
        return ret;
    }
    else
    {
        exec_plan = new(exec_plan) SameLevelExecPlan();
    }

    /*this table is not distributed table*/
    if (!table_schema->get_is_distributed_table())
    {
        if (1 != table_schema->get_all_shards().size())
        {
            ret = JD_ERR_SHARD_NUM_WRONG;
            TBSYS_LOG(WARN, "shard manage wrong");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Shard manage wrong");
            return ret;
        }

        ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*)parse_malloc(sizeof(ExecPlanUnit), NULL);
        if (exec_plan == NULL)
        {
            ret = OB_ERR_PARSER_MALLOC_FAILED;
            TBSYS_LOG(WARN, "out of memory");
            snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                "Can not malloc space for ExecPlanUnit");
            return ret;
        }
        else
        {
            exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
        }

        select_stmt->make_stmt_string( result_plan, buf, SQL_PLAN_BUF_SIZE);

        /*generate sql exec plan*/
        sql_exec_plan_unit.assign(buf, SQL_PLAN_BUF_SIZE);
        exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);

        cout << "exec_plan_unit SQL name: " << sql_exec_plan_unit << endl;

        shard_info = table_schema->get_all_shards().at(0);
        exec_plan_unit->set_exec_uint_shard_info(shard_info);

        /*add exec_plan_unit*/
        exec_plan->add_exec_plan_unit(exec_plan_unit);
    }
    /*this table is distributed table*/
    else
    {     
        /*if there is no where conditions*/
        if (0 == where_items.size())
        {
            if (0 == table_schema->get_all_shards().size())
            {
                ret = JD_ERR_SHARD_NUM_WRONG;
                TBSYS_LOG(WARN, "shard manage wrong");
                snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                    "Shard manage wrong");
                return ret;
            }

            for (uint32_t i = 0; i < table_schema->get_all_shards().size(); i++ )
            {
                shard_info = table_schema->get_all_shards().at(i);
                
                ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*)parse_malloc(sizeof(ExecPlanUnit), NULL);
                if (exec_plan == NULL)
                {
                    ret = OB_ERR_PARSER_MALLOC_FAILED;
                    TBSYS_LOG(WARN, "out of memory");
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Can not malloc space for ExecPlanUnit");
                    return ret;
                }
                else
                {
                    exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                }
                
                memset(buf , 0, SQL_PLAN_BUF_SIZE);
                select_stmt->make_stmt_string( result_plan, buf, SQL_PLAN_BUF_SIZE);
                
                /*generate sql exec plan*/
                sql_exec_plan_unit.assign(buf, SQL_PLAN_BUF_SIZE);
                exec_plan_unit->set_exec_unit_sql(sql_exec_plan_unit);
                
                cout << "exec_plan_unit SQL name: " << sql_exec_plan_unit << endl;
                exec_plan_unit->set_exec_uint_shard_info(shard_info);
                
                /*add exec_plan_unit*/
                exec_plan->add_exec_plan_unit(exec_plan_unit);
            }
        }
        else
        {
            /*decompose where conditions into seperate sql which is linked by AND*/
            vector<uint64_t> expr_ids = select_stmt->get_where_exprs();
            sql_expr =  logical_plan->get_expr_by_id(expr_ids.at(0));
            vector<vector<ObRawExpr*> > atomic_exprs_array = decompose_where_items(sql_expr->get_expr());
            multimap<schema_shard* , vector<ObRawExpr*> > opted_raw_exprs;
            schema_shard*   shard_key = NULL;
            
            cout << "atomic_exprs_array num: " << atomic_exprs_array.size() << endl;

            multimap<schema_shard* , vector<ObRawExpr*> >::iterator p_map1;
            multimap<schema_shard* , vector<ObRawExpr*> >::iterator p_map_tmp;
            multimap<schema_shard* , vector<ObRawExpr*> >::iterator p_map2;
            pair<multimap<schema_shard* , vector<ObRawExpr*> >::iterator, multimap<schema_shard* , vector<ObRawExpr*> >::iterator> raw_exprs_same_shard;

            reparse_where_items_with_route( result_plan,    
                                            table_schema,
                                            atomic_exprs_array,
                                            opted_raw_exprs);
            int ddddd=0;
            for(p_map1 = opted_raw_exprs.begin() ; p_map1 != opted_raw_exprs.end(); )
            {
                ddddd++;
                vector<vector<ObRawExpr*> > final_exprs_array;
                string sql;
                shard_key = p_map1->first;
                raw_exprs_same_shard = opted_raw_exprs.equal_range(p_map1->first);
                for(p_map2 = raw_exprs_same_shard.first; p_map2 != raw_exprs_same_shard.second; p_map2++)
                {
                    final_exprs_array.push_back((*p_map2).second);
                }

                for (int j = 0; j < opted_raw_exprs.count(p_map1->first); j++)
                {
                    p_map1++ ;
                }
                
                append_distributed_where_items(result_plan, sql, final_exprs_array) ;

                ExecPlanUnit* exec_plan_unit = (ExecPlanUnit*)parse_malloc(sizeof(ExecPlanUnit), NULL);
                if (exec_plan == NULL)
                {
                    ret = OB_ERR_PARSER_MALLOC_FAILED;
                    TBSYS_LOG(WARN, "out of memory");
                    snprintf(result_plan.err_stat_.err_msg_, MAX_ERROR_MSG,
                        "Can not malloc space for ExecPlanUnit");
                    return ret;
                }
                else
                {
                    exec_plan_unit = new(exec_plan_unit) ExecPlanUnit();
                }
                
                exec_plan_unit->set_exec_unit_sql(sql);
                cout << "exec_plan_unit shard name: " << shard_key->get_shard_name()<< endl;
                cout << "exec_plan_unit SQL name: " << sql << endl;
                exec_plan_unit->set_exec_uint_shard_info(shard_key);
                
                /*add exec_plan_unit*/
                exec_plan->add_exec_plan_unit(exec_plan_unit);
            }
        }
    }
    
    return 0;
}



/**************************************************
Funtion     :   generate_select_plan_multi_table
Author      :   qinbo
Date        :   2013.9.27
Description :   generate select exec plan with multi table
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::generate_select_plan_multi_table(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{


}

/**************************************************
Funtion     :   gen_exec_plan_update
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::gen_exec_plan_update(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObUpdateStmt *update_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, update_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }

    
}


/**************************************************
Funtion     :   gen_exec_plan_replace
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::gen_exec_plan_replace(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObInsertStmt *replace_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, replace_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
    
    
}


/**************************************************
Funtion     :   gen_exec_plan_delete
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::gen_exec_plan_delete(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObDeleteStmt *delete_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, delete_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
    
    
    
}


/**************************************************
Funtion     :   gen_exec_plan_insert
Author      :   qinbo
Date        :   2013.9.24
Description :   generate exec plan
Input       :   ObLogicalPlan *logical_plan,
                FinalExecPlan*& physical_plan,
                ErrStat& err_stat
Output      :   
**************************************************/
int QueryActuator::gen_exec_plan_insert(
    ResultPlan& result_plan,
    FinalExecPlan* physical_plan,
    ErrStat& err_stat,
    const uint64_t& query_id,
    int32_t* index)
{
    int ret = err_stat.err_code_ = OB_SUCCESS;
    ObInsertStmt *insert_stmt = NULL;
    ObLogicalPlan* logical_plan = static_cast<ObLogicalPlan*>(result_plan.plan_tree_);
    router *route_info = static_cast<router*>(result_plan.route_info);

    /* get statement */
    if (OB_SUCCESS != (ret = get_stmt(logical_plan, err_stat, query_id, insert_stmt)))
    {
        ret = OB_ERR_GEN_PLAN;
        TBSYS_LOG(WARN, "Can not get stmt");
        snprintf(err_stat.err_msg_, MAX_ERROR_MSG,
            "Can not get stmt");
        return ret;
    }
}



/**************************************************
Funtion     :   decompose_where_items
Author      :   qinbo
Date        :   2013.9.24
Description :   generate distributed where conditions items
Input       :   ResultPlan& result_plan,
                vector<WhereSubElem> &where_items
Output      :   
**************************************************/
vector<vector<ObRawExpr*> > QueryActuator::decompose_where_items(ObRawExpr* sql_expr)
{
    int32_t i = 0;
    vector<vector<ObRawExpr*> > atomic_exprs_array;
    
    if (sql_expr->is_or_expr())
    {
        vector<vector<ObRawExpr*> > left_atomic_exprs_array;

        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *>(const_cast<ObRawExpr *>(sql_expr));
        ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();
        
        if (left_sql_item->is_and_expr()||left_sql_item->is_or_expr()) 
        {
            left_atomic_exprs_array = decompose_where_items(left_sql_item);
        } 
        else 
        {
            vector<ObRawExpr*> atomic_exprs1;
            atomic_exprs1.push_back(left_sql_item);
            left_atomic_exprs_array.push_back(atomic_exprs1);
        }
        
        ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
        vector<vector<ObRawExpr*> > right_atomic_exprs_array;
        
        if (right_sql_item->is_and_expr()||right_sql_item->is_or_expr()) 
        {
            right_atomic_exprs_array = decompose_where_items(right_sql_item);
        } 
        else 
        {
            vector<ObRawExpr*> atomic_exprs2;
            atomic_exprs2.push_back(right_sql_item);
            right_atomic_exprs_array.push_back(atomic_exprs2);
        }

        /*add with each other*/
        for (i = 0; i < left_atomic_exprs_array.size(); i++) 
        {
            atomic_exprs_array.push_back(left_atomic_exprs_array.at(i));
        }
        
        for (i = 0; i < right_atomic_exprs_array.size(); i++) 
        {
            atomic_exprs_array.push_back(right_atomic_exprs_array.at(i));
        }
        
        return atomic_exprs_array;
    }
    else if (sql_expr->is_and_expr())
    {
        vector<vector<ObRawExpr*> > left_atomic_exprs_array;

        ObBinaryOpRawExpr *binary_expr = dynamic_cast<ObBinaryOpRawExpr *>(const_cast<ObRawExpr *>(sql_expr));
        ObRawExpr *left_sql_item = binary_expr->get_first_op_expr();
        
        if (left_sql_item->is_and_expr()||left_sql_item->is_or_expr()) 
        {
            left_atomic_exprs_array = decompose_where_items(left_sql_item);
        } 
        else 
        {
            vector<ObRawExpr*> atomic_exprs1;
            atomic_exprs1.push_back(left_sql_item);
            left_atomic_exprs_array.push_back(atomic_exprs1);
        }
        
        ObRawExpr *right_sql_item = binary_expr->get_second_op_expr();
        vector<vector<ObRawExpr*> > right_atomic_exprs_array;
        
        if (right_sql_item->is_and_expr()||right_sql_item->is_or_expr()) 
        {
            right_atomic_exprs_array = decompose_where_items(right_sql_item);
        } else {
            vector<ObRawExpr*> atomic_exprs2;
            atomic_exprs2.push_back(right_sql_item);
            right_atomic_exprs_array.push_back(atomic_exprs2);
        }

        /*X with each other*/
        for (i = 0; i < left_atomic_exprs_array.size(); i++) {
            uint32_t j;
            for (j = 0; j < right_atomic_exprs_array.size(); j++) {
                vector<ObRawExpr*> atomic_exprs;

                uint32_t k;
                vector<ObRawExpr*> left_atomic_exprs = left_atomic_exprs_array.at(i);
                for (k = 0; k < left_atomic_exprs.size(); k++) {
                    atomic_exprs.push_back(left_atomic_exprs.at(k));
                }
                vector<ObRawExpr*> right_atomic_exprs = right_atomic_exprs_array.at(j);
                for (k = 0; k < right_atomic_exprs.size(); k++) {
                    atomic_exprs.push_back(right_atomic_exprs.at(k));
                }

                atomic_exprs_array.push_back(atomic_exprs);
            }
        }
        
        return atomic_exprs_array;
    }
}


/**************************************************
Funtion     :   reparse_where_items_with_route
Author      :   qinbo
Date        :   2013.10.17
Description :   reparse distributed where conditions items
Input       :   ResultPlan& result_plan,
                schema_table table_info,
                vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                vector<vector<ObRawExpr*> > opted_raw_exprs
Output      :   
**************************************************/
bool QueryActuator::reparse_where_items_with_route( 
                ResultPlan& result_plan,
                schema_table* table_info,
                vector<vector<ObRawExpr*> > un_opt_raw_exprs,
                multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs)
{
    ObRawExpr* raw_expr = NULL;
    int ret = 0;
    vector<schema_shard*> all_table_shards = table_info->get_all_shards();


    if (un_opt_raw_exprs.size() == 0) 
    {
        return false;
    }
    
    for (int i = 0; i < un_opt_raw_exprs.size(); i++) 
    {
        vector<ObRawExpr*> atomic_exprs = un_opt_raw_exprs.at(i);
        vector<ObRawExpr*> partition_sql_exprs;

        search_partition_sql_exprs_for_one_table(atomic_exprs, partition_sql_exprs);

        /*if there is no route sql, this sql should be sent to all shards*/
        if (partition_sql_exprs.size() == 0)
        {
            for (int j = 0; j < all_table_shards.size(); j++)
            {
                opted_raw_exprs.insert(pair<schema_shard* , vector<ObRawExpr*> >(all_table_shards.at(j), atomic_exprs));
            }
        }
        /*if there is route sql, this sql should be sent to related shards*/
        else 
        {
            build_shard_exprs_array_with_route(
                                        result_plan,
                                        table_info,
                                        partition_sql_exprs, 
                                        atomic_exprs,
                                        opted_raw_exprs);
        }
    }
    return true;
    
}

/**************************************************
Funtion     :   search_partition_sql_exprs_for_one_table
Author      :   qinbo
Date        :   2013.10.18
Description :   find all expr that need to be partitioned
Input       :   vector<ObRawExpr*>  atomic_exprs,
                vector<ObRawExpr*>  &partition_sql_exprs
Output      :   
**************************************************/
int QueryActuator::search_partition_sql_exprs_for_one_table(
                        vector<ObRawExpr*>  atomic_exprs,
                        vector<ObRawExpr*>  &partition_sql_exprs)
{
    uint32_t i = 0;
    ObRawExpr* raw_expr = NULL;
    
    for (; i < atomic_exprs.size(); i++) 
    {
        raw_expr = atomic_exprs.at(i);
        
        if (raw_expr->is_need_to_get_route())
        {
            partition_sql_exprs.push_back(raw_expr);
        }
    }

    return 0;
}

/**************************************************
Funtion     :   append_distributed_where_items
Author      :   qinbo
Date        :   2013.10.17
Description :   generate distributed where conditions items
Input       :   ResultPlan& result_plan,
                string &sql
                vector<vector<ObRawExpr*> > &atomic_exprs_array
Output      :   
**************************************************/
void QueryActuator::append_distributed_where_items(ResultPlan& result_plan,
                                                string &sql, 
                                                vector<vector<ObRawExpr*> > &atomic_exprs_array) 
{
    char tmp_str[RAW_EXPR_BUF_SIZE] = {0};
    
    if (atomic_exprs_array.size() == 0) 
    {
        return;
    }
    
    for (int i = 0; i < atomic_exprs_array.size(); i++) 
    {
        if (i > 0) 
        {
            sql.append(" OR ");
        }
        vector<ObRawExpr*> atomic_exprs = atomic_exprs_array.at(i);
        for (int j=0; j < atomic_exprs.size(); j++) 
        {
            if (j > 0) 
            {
                sql.append(" AND ");
            }
            memset(tmp_str, 0 ,RAW_EXPR_BUF_SIZE);
            atomic_exprs.at(j)->to_string(result_plan, tmp_str, RAW_EXPR_BUF_SIZE);
            sql.append(tmp_str, RAW_EXPR_BUF_SIZE);
        }
    }
    
    return;
}


/**************************************************
Funtion     :   build_shard_exprs_array_with_route
Author      :   qinbo
Date        :   2013.10.17
Description :   generate distributed where conditions items
Input       :   ResultPlan& result_plan,
                string &sql
                vector<vector<ObRawExpr*> > partition_sql_exprs
                vector<vector<ObRawExpr*> > atomic_exprs,
                multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs
Output      :   
**************************************************/
int QueryActuator::build_shard_exprs_array_with_route( 
                            ResultPlan& result_plan,
                            schema_table* table_info,
                            vector<ObRawExpr*>  partition_sql_exprs,
                            vector<ObRawExpr*>  atomic_exprs,
                            multimap<schema_shard* , vector<ObRawExpr*> > &opted_raw_exprs)
{
    ObRawExpr* raw_expr = NULL;
    int ret = 0;
    
    for (int j = 0; j < partition_sql_exprs.size(); j++) 
    {
        raw_expr = partition_sql_exprs.at(j);
        if (raw_expr->is_need_to_get_route())
        {
            string db_name      = raw_expr->get_db_name();
            string table_name   = table_info->get_table_name();
            map<string, SqlItemType>    sharding_key_tmp = table_info->get_sharding_key();
            vector<key_data>            key_relations;
            key_data                    key_relation;
            vector<schema_shard*>       shard_info;
            
            map<string, SqlItemType>::iterator it = sharding_key_tmp.begin();
            
            while (it != sharding_key_tmp.end()) 
            {
                memset(&key_relation, 0, sizeof(key_data));
                key_relation.db_name        = db_name;
                key_relation.table_name     = table_name;
                key_relation.sharding_key   = it->first;
                key_relation.key_type       = it->second;
                
                if (raw_expr->convert_ob_expr_to_route(key_relation))
                {
                    key_relations.push_back(key_relation);
                }
        
                it++;
            }
        
            if (key_relations.size() > 0)
            {
                router *route_info = (router *)result_plan.route_info;
                route_info->get_route_result(key_relations, &shard_info, &ret);
            }
        }
    }

}

