#include "ob_insert_stmt.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace oceanbase::common;
using namespace oceanbase::sql;

ObInsertStmt::ObInsertStmt()
: ObStmt(T_INSERT)
{
  sub_query_id_ = OB_INVALID_ID;
  is_replace_ = false;
}

ObInsertStmt::~ObInsertStmt()
{
  for (int64_t i = 0; i < value_vectors_.size(); i++)
  {
    vector<uint64_t>& value_row = value_vectors_.at(i);
    value_row.clear();
  }
}

void ObInsertStmt::print(FILE* fp, int32_t level, int32_t index)
{
  print_indentation(fp, level);
  fprintf(fp, "<ObInsertStmt %d Begin>\n", index);
  ObStmt::print(fp, level + 1);
  print_indentation(fp, level + 1);
  fprintf(fp, "INTO ::= <%ld>\n", table_id_);
  if (sub_query_id_ == OB_INVALID_ID)
  {
    print_indentation(fp, level + 1);
    fprintf(fp, "VALUES ::= ");
    for (int64_t i = 0; i < value_vectors_.size(); i++)
    {
      if (i == 0)
        fprintf(fp, "<");
      else
        fprintf(fp, ", <");
      vector<uint64_t>& value_row = value_vectors_.at(i);
      for (int j = 0; j < value_row.size(); j++)
      {
        if (j == 0)
          fprintf(fp, "%ld", value_row.at(j));
        else
          fprintf(fp, ", %ld", value_row.at(j));
      }
      fprintf(fp, ">");
    }
    fprintf(fp, "\n");
  }
  else
  {
    print_indentation(fp, level + 1);
    fprintf(fp, "SUBQUERY ::= <%ld>\n", sub_query_id_);
  }
  print_indentation(fp, level);
  fprintf(fp, "<ObInsertStmt %d End>\n", index);
}
