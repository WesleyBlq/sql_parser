
OBJS = parse_malloc.o parse_node.o sql_non_reserved_keywords.o sql_parser.lex.o sql_parser.tab.o parser_test.o \
	utility.o ob_number.o ob_object.o \
	ob_raw_expr.o ob_stmt.o

sql_parser: $(OBJS)  
	g++ -o sql_parser -I. $(OBJS) 
	
.PHONY:clean 
clean: 
	rm -f *.o sql_parser