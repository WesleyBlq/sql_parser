
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse_node.h"

int main (void)
{
    ParseResult result;
    char *sql = NULL;
    
    if(parse_init(&result))
    {
      printf("parse_init error!!!\n");
    }
    
    fprintf(stderr, "<<Part 1 : SQL STRING>>\n%s\n", sql);

    sql = "select user_id, sum(qty) sum_qty from order_list group by user_id having item_id >9;";
    
    parse_sql(&result, sql, strlen(sql));
    fflush(stderr);
    if(result.result_tree_ == 0)
    {
      fprintf(stderr, "parse_sql error!\n");
      fprintf(stderr, "%s at %d:%d\n", result.error_msg_, result.line_, result.start_col_);
    }
    else
    {
      fprintf(stderr, "\n<<Part 2 : PARSE TREE>>\n");
      print_tree(result.result_tree_, 0);
    }

    return 1;
}

