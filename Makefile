
OBJS = parse_malloc.o parse_node.o sql_non_reserved_keywords.o sql_parser.lex.o sql_parser.tab.o parser_test.o \
	log.o utility.o ob_number.o ob_object.o ob_obj_type.o \
	ob_raw_expr.o ob_stmt.o \
	ob_delete_stmt.o ob_insert_stmt.o  ob_update_stmt.o ob_select_stmt.o ob_logical_plan.o\
	dml_build_plan.o ob_multi_logic_plan.o

#	ob_obj_cast.o ob_expr_obj.o
sql_parser: $(OBJS)  
	g++ -fpermissive -o sql_parser -I. $(OBJS) 
	
.PHONY:clean 
clean: 
	rm -f *.o sql_parser