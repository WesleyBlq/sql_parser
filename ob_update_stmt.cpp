#include "ob_update_stmt.h"
#include <stdio.h>
#include <stdlib.h>

namespace oceanbase
{
  namespace sql
  {
    using namespace oceanbase::common;

    ObUpdateStmt::ObUpdateStmt()
    : ObStmt(T_UPDATE)
    {
    }

    ObUpdateStmt::~ObUpdateStmt()
    {
    }

    void ObUpdateStmt::print(FILE* fp, int32_t level, int32_t index)
    {
      print_indentation(fp, level);
      fprintf(fp, "ObUpdateStmt %d Begin\n", index);
      ObStmt::print(fp, level + 1);
      print_indentation(fp, level + 1);
      fprintf(fp, "UPDATE ::= <%ld>\n", table_id_);
      print_indentation(fp, level + 1);
      fprintf(fp, "SET ::= ");
      for (int64_t i = 0; i < update_columns_.size(); i++)
      {
        if (i > 0)
          fprintf(fp, ", <%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
        else
          fprintf(fp, "<%ld, %ld>", update_columns_.at(i), update_exprs_.at(i));
      }
      fprintf(fp, "\n");
      print_indentation(fp, level);
      fprintf(fp, "ObUpdateStmt %d End\n", index);
    }

    int64_t ObUpdateStmt::make_stmt_string( ResultPlan& result_plan,
                                            char* buf, 
                                            const int64_t buf_len)
    {
  
    }


  }
}
