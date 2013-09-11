#ifndef OCEANBASE_SQL_UPDATESTMT_H_
#define OCEANBASE_SQL_UPDATESTMT_H_
#include "ob_stmt.h"
#include <stdio.h>
#include <vector>
#include <string>
//#include "common/ob_string_buf.h"

namespace oceanbase
{
  namespace sql
  {
    class ObUpdateStmt : public ObStmt
    {
    public:
      ObUpdateStmt();
      virtual ~ObUpdateStmt();

      uint64_t set_update_table(uint64_t id)
      {
        if (id == oceanbase::common::OB_INVALID_ID)
          return oceanbase::common::OB_INVALID_ID;
        table_id_ = id;
        return id;
      }
      uint64_t get_update_table_id(void)
      {
        return table_id_;
      }
      
      int add_update_column(uint64_t column_id)
      {
        int ret = common::OB_SUCCESS;
        if (column_id != oceanbase::common::OB_INVALID_ID)
          update_columns_.push_back(column_id);
        return ret;
      }
      
      int get_update_column_id(int64_t idx, uint64_t &column_id)
      {
        int ret = common::OB_SUCCESS;
        if (idx < update_columns_.size())
        {
          column_id = update_columns_.at(idx);
        }
        else
        {
          ret = common::OB_INVALID_ARGUMENT;
        }
        return ret;
      }

      int add_update_expr(uint64_t expr_id)
      {
        int ret = common::OB_SUCCESS;
        if (expr_id == oceanbase::common::OB_INVALID_ID)
          ret = common::OB_ERROR;
        else
          update_exprs_.push_back(expr_id);
        return ret;
      }

      int get_update_expr_id(int64_t idx, uint64_t &expr_id)
      {
        int ret = common::OB_SUCCESS;
        if (idx < update_exprs_.size())
        {
          expr_id = update_exprs_.at(idx);
        }
        else
        {
          ret = common::OB_INVALID_ARGUMENT;
        }
        return ret;
      }
     
      int64_t get_update_column_count(void)
      {
        return update_columns_.size();
      }

      void print(FILE* fp, int32_t level, int32_t index);

    private:
      uint64_t   table_id_;
      vector<uint64_t> update_columns_;
      vector<uint64_t> update_exprs_;        
    };
  }
}

#endif //OCEANBASE_SQL_UPDATESTMT_H_
