#ifndef OCEANBASE_SQL_LOGICALPLAN_H_
#define OCEANBASE_SQL_LOGICALPLAN_H_
#include "parse_node.h"
#include "ob_raw_expr.h"
#include "ob_stmt.h"
#include "ob_select_stmt.h"
//#include "ob_result_set.h"
#include <string>
//#include "common/ob_string_buf.h"
#include <vector>
//#include "common/ob_stack_allocator.h"
namespace oceanbase
{
  namespace sql
  {
    //class ObSQLSessionInfo;
    class ObLogicalPlan
    {
    public:
      explicit ObLogicalPlan();
      virtual ~ObLogicalPlan();

#if 0
      oceanbase::common::ObStringBuf* get_name_pool() const
      {
        return name_pool_;
      }
#endif
      ObBasicStmt* get_query(uint64_t query_id) const;

      ObBasicStmt* get_main_stmt()
      {
       ObBasicStmt *stmt = NULL;
        if (stmts_.size() > 0)
          stmt = stmts_[0];
        return stmt;
      }

      ObSelectStmt* get_select_query(uint64_t query_id) const;

      ObSqlRawExpr* get_expr(uint64_t expr_id) const;

      int add_query(ObBasicStmt* stmt)
      {
        int ret = common::OB_SUCCESS;
        if (!stmt)
        {
          TBSYS_LOG(WARN, "fail to allocate space for stmt. %p", stmt);
          ret = common::OB_ERROR;
        }
        stmts_.push_back(stmt);
        return ret;
      }

      int add_expr(ObSqlRawExpr* expr)
      {
        int ret = common::OB_SUCCESS;
        if (!expr) 
        {
          TBSYS_LOG(WARN, "fail to allocate space for expr. %p", expr);
          ret = common::OB_ERROR;
        }
        exprs_.push_back(expr);
        return ret;
      }

      // Just a storage, only need to add raw expression
      int add_raw_expr(ObRawExpr* expr)
      {
        int ret = common::OB_SUCCESS;
        if (!expr)
        {
          TBSYS_LOG(WARN, "fail to allocate space for raw expr. %p", expr);
          ret = common::OB_ERROR;
        }
        raw_exprs_store_.push_back(expr);
        return ret;
      }

#if 0
        int fill_result_set(ObResultSet& result_set, ObSQLSessionInfo *session_info, common::StackAllocator &alloc);
#endif
      uint64_t generate_table_id()
      {
        return new_gen_tid_--;
      }

      uint64_t generate_column_id()
      {
        return new_gen_cid_--;
      }

      // It will reserve 10 id for the caller
      // In fact is for aggregate functions only, 
      // because we need to push part aggregate to tablet and keep top aggregate on all
      uint64_t generate_range_column_id()
      {
        uint64_t ret_cid = new_gen_cid_;
        new_gen_cid_ -= 10;
        return ret_cid;
      }

      uint64_t generate_expr_id()
      {
        return new_gen_eid_++;
      }

      uint64_t generate_query_id()
      {
        return new_gen_qid_++;
      }

      int64_t inc_question_mark()
      {
        return question_marks_count_++;
      }

      int64_t get_question_mark_size() const
      {
        return question_marks_count_;
      }
      int32_t get_stmts_count() const
      {
        return stmts_.size();
      }
      ObBasicStmt* get_stmt(int32_t index) const
      {
        OB_ASSERT(index >= 0 && index < get_stmts_count());
        return stmts_.at(index);
      }
      void print(FILE* fp = stderr, int32_t level = 0) const;
      /**************************************************
      Funtion     :   get_expr_by_id
      Author      :   qinbo
      Date        :   2013.9.10
      Description :   get expr by expr_id
      Input       :   int64_t expr_id
      Output      :   ObSqlRawExpr* 
      **************************************************/
      ObSqlRawExpr* get_expr_by_id(uint64_t expr_id);
      
      /**************************************************
      Funtion     :   get_expr_by_ref_sql_expr_raw_id
      Author      :   qinbo
      Date        :   2013.9.10
      Description :   get expr by sql_expr_raw_id
      Input       :   int64_t expr_id
      Output      :   ObSqlRawExpr* 
      **************************************************/
      ObSqlRawExpr* get_expr_by_ref_sql_expr_raw_id(uint64_t sql_expr_raw_id);
      /**************************************************
      Funtion     :   make_stmt_string
      Author      :   qinbo
      Date        :   2013.9.10
      Description :   make stmt string
      Input       :   ResultPlan& result_plan,
                      char* buf, 
                      const int64_t buf_len
      Output      :   ObSqlRawExpr* 
      **************************************************/
      void make_stmt_string( ResultPlan& result_plan,
                                      char* buf, 
                                      const int64_t buf_len);
#if 0
    protected:
      oceanbase::common::ObStringBuf* name_pool_;
#endif

    private:
      vector<ObBasicStmt*> stmts_;
      vector<ObSqlRawExpr*> exprs_;
      vector<ObRawExpr*> raw_exprs_store_;
      int64_t   question_marks_count_;
      uint64_t  new_gen_tid_;
      uint64_t  new_gen_cid_;
      uint64_t  new_gen_qid_;
      uint64_t  new_gen_eid_;
    };
  }
}

#endif //OCEANBASE_SQL_LOGICALPLAN_H_
