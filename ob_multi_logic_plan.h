#ifndef OCEANBASE_SQL_MULTIPLAN_H_
#define OCEANBASE_SQL_MULTIPLAN_H_
#include <vector>
#include "ob_logical_plan.h"

namespace oceanbase
{
  namespace sql
  {
    class ObMultiLogicPlan : public vector<ObLogicalPlan*>
    {
    public:
      ObMultiLogicPlan();
      ~ObMultiLogicPlan();
      void print(FILE* fp = stderr);
      void make_stmt_string( ResultPlan& result_plan,
                            char* buf, 
                            const int64_t buf_len);
    };
  }
}

#endif //OCEANBASE_SQL_MULTIPLAN_H_

