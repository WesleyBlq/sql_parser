#ifndef CRUD_BUILD_PLAN_H
#define CRUD_BUILD_PLAN_H

#include "parse_node.h"
#include "ob_stmt.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int resolve_show_stmt(
    ResultPlan* result_plan,
    ParseNode* node,
    uint64_t& query_id);

extern int resolve_variable_set_stmt(
    ResultPlan* result_plan,
    ParseNode* node,
    uint64_t& query_id);


#ifdef __cplusplus
}
#endif

#endif //CRUD_BUILD_PLAN_H

