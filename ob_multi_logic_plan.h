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
    };
  }
}

#endif //OCEANBASE_SQL_MULTIPLAN_H_

