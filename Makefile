

	
#################################################################################	
#################################################################################	
#################################################################################	
#################################################################################	

all: libsql.a parser_test


SYSLIBS_test =

	
CPPFLAGS = \
	#-I/usr/local/mysql-cpp-connector/mysql-connector-c++-1.1.3-linux-glibc2.3-x86-64bit/include \
	#-I/usr/local/include
	
	
USERLIBS_test = $(SYSLIBS_test) \
	#-L/usr/local/mysql/lib \
	#-L/usr/local/mysql-cpp-connector/mysql-connector-c++-1.1.3-linux-glibc2.3-x86-64bit/lib

LDLIBS = $(USERLIBS_test)  \
	../sql/libsql.a ../route/libroute.a -lcrypto ../log/liblog.a \
	/usr/local/lib/libzookeeper_mt.a \
	/usr/local/lib/libjson_linux-gcc-4.1.2_libmt.a \
	-lmysqlclient 
	

##libsql.a
OBJS_SQL =  \
	parse_malloc.o \
	parse_node.o \
	sql_non_reserved_keywords.o \
	sql_parser.lex.o \
	sql_parser.tab.o \
	utility.o \
	ob_number.o \
	ob_object.o \
	ob_obj_type.o \
	sql_raw_expr.o \
	ob_obj_cast.o \
	ob_expr_obj.o \
	ob_stmt.o \
	sql_delete_stmt.o \
	sql_insert_stmt.o  \
	sql_update_stmt.o \
	sql_select_stmt.o \
	sql_show_stmt.o \
	sql_variable_set_stmt.o \
	sql_logical_plan.o\
	dml_build_plan.o \
	crud_build_plan.o \
	query_reduce.o \
	jd_exec_plan.o \
	dispatch_command.o \

#libsql.a

%o: %c
	gcc -Wall -g -c -o  $@ $<

%o: %cpp
	g++ -Wall -g -c -o  $@ $<
	
libsql.a: $(OBJS_SQL)
	ar rv libsql.a ${OBJS_SQL}
	g++  -Wl,-rpath -Wl,LIBDIR $(CCFLAGS_test) $(CPPFLAGS) -o parser_test parser_test.cpp $(LDLIBS)


parser_test: parser_test.cpp
	g++  -Wl,-rpath -Wl,LIBDIR $(CCFLAGS_test) $(CPPFLAGS) -o $@ parser_test.cpp $(LDLIBS)


.PHONY:clean 
clean: 
	rm -f *.o parser_test libsql.a
	

.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux
	
	