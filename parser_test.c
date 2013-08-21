
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "parse_node.h"

int sql_parser(char * sql)
{
    ParseResult result;
    
    if(parse_init(&result))
    {
      printf("parse_init error!!!\n");
    }
    
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

    if (result.result_tree_)
    {
      destroy_tree(result.result_tree_);
      result.result_tree_ = NULL;
    }

    printf("\n");
}
int main (void)
{
    char *sql1 = "INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees')";
    char *sql2 = "INSERT INTO table2(id, name, address) SELECT id, name, address FROM table1"; 
    char *sql4 = "SELECT Customer,SUM(OrderPrice) FROM Orders \
WHERE Customer='Bush' OR Customer='Adams' \
GROUP BY Customer \
HAVING SUM(OrderPrice)>1500";
                
    char *sql5 = "SELECT Persons.LastName, Persons.FirstName, Orders.OrderNo \
FROM Persons \
INNER JOIN Orders \
ON Persons.Id_P = Orders.Id_P \
ORDER BY Persons.LastName";

    sql_parser(sql1);
    sql_parser(sql2);
    sql_parser(sql4);
	sql_parser(sql5);
    return 1;
}

