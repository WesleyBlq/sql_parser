

	
#################################################################################	
#################################################################################	
#################################################################################	
#################################################################################	

all: libsql.a parser_test


SYSLIBS_test = -Wl,-rpath -Wl,LIBDIR -lglog

	
CPPFLAGS = \
	#-I/usr/local/mysql-cpp-connector/mysql-connector-c++-1.1.3-linux-glibc2.3-x86-64bit/include \
	#-I/usr/local/include
	
	
USERLIBS_test = $(SYSLIBS_test) \
	#-L/usr/local/mysql/lib \
	#-L/usr/local/mysql-cpp-connector/mysql-connector-c++-1.1.3-linux-glibc2.3-x86-64bit/lib

LDLIBS = $(USERLIBS_test)  \
	../sql/libsql.a ../route/libroute.a -lcrypto \
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
	ob_raw_expr.o \
	ob_obj_cast.o \
	ob_expr_obj.o \
	ob_stmt.o \
	ob_delete_stmt.o \
	ob_insert_stmt.o  \
	ob_update_stmt.o \
	ob_select_stmt.o \
	ob_show_stmt.o \
	ob_variable_set_stmt.o \
	ob_logical_plan.o\
	dml_build_plan.o \
	crud_build_plan.o \
	jd_exec_plan.o

#libsql.a

%o: %c
	gcc -g -c -o  $@ $<

%o: %cpp
	g++ -g -c -o  $@ $<
	
libsql.a: $(OBJS_SQL)
	ar rv libsql.a ${OBJS_SQL}
	g++  -Wl,-rpath -Wl,LIBDIR $(CCFLAGS_test) $(CPPFLAGS) -o parser_test parser_test.cpp $(LDLIBS)


parser_test: parser_test.cpp
	g++  -Wl,-rpath -Wl,LIBDIR $(CCFLAGS_test) $(CPPFLAGS) -o $@ parser_test.cpp $(LDLIBS)


.PHONY:clean 
clean: 
	rm -f *.o parser_test libsql.a
	