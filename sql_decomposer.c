/************************************************************
  Copyright (C), 2013-2015
  FileName:     sql_decomposer.c
  Author:       qinbo(gqinbo@gmail.com)      
  Version :          
  Date:         
  Description:  sql语句分拆优化模块   
  History: 
      <author>  <time>   <version >     <desc>
      qinbo    2013/6/5     1.0         build this moudle  
***********************************************************/
#include <errno.h>
#include "util/log.h"
#include "sql_decomposer.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

#define int32_t  int32
#define uint64_t uint64

class SqlParser
{
    private:
        uint32 sql_length;
        
    public:
        ParseNode* parse(char *sql);
        uint32 get_sql_length();
};


/*对分片信息的封装(该类有wangfeng提供)*/
class TABLET_INFO
{
    private:
        /**<  全局唯一的tablet_server_id */
        string tablet_server_id;
        DATABASE_INFO* database_info;
     public:
        
}


/*对执行单元的封装*/
class  ExecPlanUnit
{
    private:
        string sql;
        TABLET_INFO *db_info;
    public:
        void set_exec_plan_sql(string &sql);
        void set_exec_plan_db_info(TABLET_INFO *db_info)
}

/*对执行计划的封装*/
class ExecPlan
{
    private:
        vector<ExecPlanUnit*> exec_plan;
        bool    is_first_plan;
        char    parent_sql_type;        /**if need to be reparsed*/
    public:
        bool get_parent_sql_type();
        void set_parent_sql_type(uint8 parent_sql_type);
        void set_first_plan_true();
        void is_first_plan();
}


/*执行计划本身的class*/
class QueryPlan
{
    private:
        vector<ExecPlan*> exec_plan;

    public:
       friend class Optimizor;
}


/*用于操作执行计划的动作的class*/
class Query
{
    private:
        QueryPlan *query_plans;
        bool is_all_plan_done;
        bool is_next_plan_list_reparsed;
        
    public:
        void generate_exec_plans(string &sql);       /*generate the whole exec_plan*/
        void releas_exec_plans();
        
        ExecPlan* popActuator();
        void pushActuator(ExecPlan* exec_plan);
        
        bool is_all_plan_done();
        void set_all_plan_done();
        void set_next_plan_reparsed();
        bool is_next_plan_reparsed();
        void reparse_next_plan(QueryPlan* exec_query_plan);
}


/*
          ob_sql.cpp
FUNCTION: resolve
*/
#if 1
int sql_generate_plan(QueryPlan *result_plan,ParseNode* parse_tree)
{
    int ret = 0;
    bool is_preparable = false;
    switch (parse_tree->type_)
    {
      case T_STMT_LIST:
      case T_SELECT:
      case T_DELETE:
      case T_INSERT:
      case T_UPDATE:
      case T_BEGIN:
      case T_COMMIT:
      case T_ROLLBACK:
        is_preparable = true;
        break;
      default:
        break;
    }
    

    if (&& parse_tree != NULL)
    {
        switch (parse_tree->type_)
        {
        case T_STMT_LIST:
        {
            //ret = decompose_multi_stmt(result_plan, parse_tree);
            break;
        }
        case T_SELECT:
        {
            //ret = decompose_select_stmt(result_plan, parse_tree);
            break;
        }
        case T_DELETE:
        {
            //ret = decompose_delete_stmt(result_plan, parse_tree);
            break;
        }
        case T_INSERT:
        {
            ret = decompose_insert_stmt(result_plan, parse_tree);
            break;
        }
        case T_UPDATE:
        {
            //ret = decompose_update_stmt(result_plan, parse_tree);
            break;
        }
      #if 0
      case T_EXPLAIN:
      {
        //ret = decompose_explain_stmt(result_plan, parse_tree);
        break;
      }
      case T_CREATE_TABLE:
      {
        //ret = decompose_create_table_stmt(result_plan, parse_tree);
        break;
      }
      case T_DROP_TABLE:
      {
        //ret = decompose_drop_table_stmt(result_plan, parse_tree);
        break;
      }
      case T_ALTER_TABLE:
      {
        //ret = decompose_alter_table_stmt(result_plan, parse_tree);
        break;
      }
      case T_SHOW_TABLES:
      case T_SHOW_VARIABLES:
      case T_SHOW_COLUMNS:
      case T_SHOW_SCHEMA:
      case T_SHOW_CREATE_TABLE:
      case T_SHOW_TABLE_STATUS:
      case T_SHOW_SERVER_STATUS:
      case T_SHOW_WARNINGS:
      case T_SHOW_GRANTS:
      case T_SHOW_PARAMETERS:
      {
        //ret = decompose_show_stmt(result_plan, parse_tree);
        break;
      }
      case T_CREATE_USER:
      {
        //ret = decompose_create_user_stmt(result_plan, parse_tree);
        break;
      }
      case T_DROP_USER:
      {
        //ret = decompose_drop_user_stmt(result_plan, parse_tree);
        break;
      }
      case T_SET_PASSWORD:
      {
        //ret = decompose_set_password_stmt(result_plan, parse_tree);
        break;
      }
      case T_RENAME_USER:
      {
        //ret = decompose_rename_user_stmt(result_plan, parse_tree);
        break;
      }
      case T_LOCK_USER:
      {
        //ret = decompose_lock_user_stmt(result_plan, parse_tree);
        break;
      }
      case T_GRANT:
      {
        //ret = decompose_grant_stmt(result_plan, parse_tree);
        break;
      }
      case T_REVOKE:
      {
        //ret = decompose_revoke_stmt(result_plan, parse_tree);
        break;
      }
      case T_PREPARE:
      {
        //ret = decompose_prepare_stmt(result_plan, parse_tree);
        break;
      }
      case T_VARIABLE_SET:
      {
        //ret = decompose_variable_set_stmt(result_plan, parse_tree);
        break;
      }
      case T_EXECUTE:
      {
        //ret = decompose_execute_stmt(result_plan, parse_tree);
        break;
      }
      case T_DEALLOCATE:
      {
        //ret = decompose_deallocate_stmt(result_plan, parse_tree);
        break;
      }
      case T_BEGIN:
        //ret = decompose_start_trans_stmt(result_plan, parse_tree);
        break;
      case T_COMMIT:
        ret = decompose_commit_stmt(result_plan, parse_tree);
        break;
      case T_ROLLBACK:
        ret = decompose_rollback_stmt(result_plan, parse_tree);
        break;
      case T_ALTER_SYSTEM:
        ret = decompose_alter_sys_cnf_stmt(result_plan, parse_tree);
        break;
      default:
        TBSYS_LOG(ERROR, "unknown top parse_tree type=%d", parse_tree->type_);
        ret = OB_ERR_UNEXPECTED;
        break;
    #endif
    };
  }
  return ret;
}


/* 1. distinct */
/* 2. select clause */
/* 3. from clause */      /*JOIN的处理在此处*/
/* 4. where */
/* 5. group by */
/* 6. having */
/* 7. set operation */
/* 8. all specified? */
/* 9. former select stmt  UNION关键词前一个sql语句*/
/* 10. later select stmt  UNION关键词后一个sql语句 */
/* 11. order by */
/* 12. limit */
/* 13. for update */
/* 14 hints */          /*默认不支持*/
int decompose_select_stmt(QueryPlan *result_plan,ParseNode* parse_tree)
{
    
    
    
}


/* 0.target relation */
/* 1.column list */
/* 2.value list */
/* 3.value from sub-query */
/* 4.is replacement */
int decompose_insert_stmt(QueryPlan *result_plan,ParseNode* parse_tree)
{
    char *table_name = NULL;
    ParseNode* table_node = NULL;
    
    table_node = node->children_[0];
    if (table_node->type_ != T_IDENT)
    {
        ret = SQL_ERR_PARSER_SYNTAX;
        return ret;
    }

    table_name = table_node->str_value_;
}



#endif    

