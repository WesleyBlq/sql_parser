
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
    
    sql = "INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees')";
    fprintf(stderr, "<<Part 1 : SQL STRING>>\n%s\n", sql);
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

