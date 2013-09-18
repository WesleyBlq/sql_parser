#include "ob_multi_logic_plan.h"
#include "parse_malloc.h"
#include <string>

namespace oceanbase
{
  namespace sql
  {
    using namespace oceanbase::common;
    ObMultiLogicPlan::ObMultiLogicPlan()
    {
    }
    ObMultiLogicPlan::~ObMultiLogicPlan()
    {
      for(int32_t i = 0; i < size(); ++i)
      {
        //delete at(i);
        at(i)->~ObLogicalPlan();
        parse_free(at(i));
      }
    }

    void ObMultiLogicPlan::print(FILE* fp)
    {
      for(int32_t i = 0; i < size(); ++i)
      {
        at(i)->print(fp);
        fprintf(fp, "\n");
      }
    }
    
    void ObMultiLogicPlan::make_stmt_string( ResultPlan& result_plan,
                          char* buf, 
                          const int64_t buf_len)
    {
        for(int32_t i = 0; i < size(); ++i)
        {
            at(i)->make_stmt_string(result_plan, buf, buf_len );
            fprintf(stderr, "\n");
        }
    }
  }
}

