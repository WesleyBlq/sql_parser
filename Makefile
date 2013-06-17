
OBJS = parse_malloc.o parse_node.o sql_non_reserved_keywords.o sql_parser.lex.o sql_parser.tab.o type_name.o main.o 

sql_parser: $(OBJS)  
	gcc -o sql_parser $(OBJS) 
	
.PHONY:clean 
clean: 
	rm -f *.o sql_parser