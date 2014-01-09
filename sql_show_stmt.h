
#ifndef SQL_OB_SHOW_STMT_H_
#define SQL_OB_SHOW_STMT_H_
#include <string>
#include "ob_stmt.h"

namespace jdbd
{
  namespace sql
  {
    class ObShowStmt : public ObStmt
    {
    public:
      ObShowStmt(StmtType stmt_type);
      virtual ~ObShowStmt();

      void set_global_scope(bool global_scope);
      void set_sys_table(uint64_t table_id);
      void set_show_table(uint64_t table_id);
      void set_warnings_limit(int64_t offset = 0, int64_t count = -1);
      void set_count_warnings(bool count_warnings);
      void set_full_process(bool full_process);
      void set_user_name(string name);
      uint64_t get_sys_table_id() const;
      uint64_t get_show_table_id() const;
      int64_t get_warnings_offset() const;
      int64_t get_warnings_count() const;
      bool is_global_scope() const;
      bool is_count_warnings() const;
      bool is_full_process() const;
      const string& get_user_name() const;
      const string& get_like_pattern() const;
      void set_like_pattern(const string like_pattern);
      void print(FILE* fp, int32_t level, int32_t index = 0);
    private:
      // disallow copy
      ObShowStmt(const ObShowStmt &other);
      ObShowStmt& operator=(const ObShowStmt &other);
    private:
      uint64_t          sys_table_id_;
      // table_id_ is for  T_SHOW_COLUMNS, T_SHOW_CREATE_TABLE only
      uint64_t          show_table_id_;
      // like_pattern_  and where_expr_ids_ are for
      // T_SHOW_TABLES, T_SHOW_VARIABLES, T_SHOW_COLUMNS
      // T_SHOW_TABLE_STATUS, T_SHOW_SERVER_STATUS only
      string  like_pattern_;
      // global_scope_ is for T_SHOW_VARIABLES only
      bool              global_scope_;
      // following three items are for T_SHOW_WARNINGS
      int64_t           offset_;
      int64_t           row_count_; // -1 means all
      bool              count_warnings_;
      // for T_SHOW_PROCESSLIST
      bool  full_process_;
      // for T_SHOW_GRANTS
      string  user_name_;

    };

    inline void ObShowStmt::set_global_scope(bool global_scope)
    {
      global_scope_ = global_scope;
    }
    inline void ObShowStmt::set_show_table(uint64_t table_id)
    {
      show_table_id_ = table_id;
    }
    inline void ObShowStmt::set_sys_table(uint64_t table_id)
    {
      sys_table_id_ = table_id;
    }
    inline void ObShowStmt::set_warnings_limit(int64_t offset, int64_t count)
    {
      row_count_ = count;
      offset_ = offset;
    }
    inline void ObShowStmt::set_count_warnings(bool count_warnings)
    {
      count_warnings_ = count_warnings;
    }
    inline void ObShowStmt::set_full_process(bool full_process)
    {
      full_process_ = full_process;
    }
    inline void ObShowStmt::set_user_name(string name)
    {
      user_name_ = name;
    }
    inline uint64_t ObShowStmt::get_sys_table_id() const
    {
      return sys_table_id_;
    }
    inline uint64_t ObShowStmt::get_show_table_id() const
    {
      return show_table_id_;
    }
    inline const string& ObShowStmt::get_like_pattern() const
    {
      return like_pattern_;
    }
    inline int64_t ObShowStmt::get_warnings_offset() const
    {
      return offset_;
    }
    inline int64_t ObShowStmt::get_warnings_count() const
    {
      return row_count_;
    }
    inline bool ObShowStmt::is_global_scope() const
    {
      return global_scope_;
    }
    inline bool ObShowStmt::is_count_warnings() const
    {
      return count_warnings_;
    }
    inline bool ObShowStmt::is_full_process() const
    {
      return full_process_;
    }
    inline const string& ObShowStmt::get_user_name() const
    {
      return user_name_;
    }
  }
}

#endif //SQL_OB_SHOW_STMT_H_
