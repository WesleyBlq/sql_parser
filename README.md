说明
=========
该项目为mysql sql解析器，词法分析和语法分析基于oceanbase 0.4版本，后续的语法树解析和
sql语句优化分拆再次拼装代码正在编写，会陆续上传。

编译：
STEP1：$ sh gen_parser.sh
STEP2: $ make

执行： $ ./sql_parser.exe

当insert语句如下时，解析后的语法树：
$ ./sql_parser.exe
<<Part 1 : SQL STRING>>
INSERT INTO Persons (LastName, Address) VALUES ('Wilson', 'Champs-Elysees')

<<Part 2 : PARSE TREE>>
|-T_STMT_LIST
    |-T_INSERT
        |-T_IDENT : persons
        |-T_COLUMN_LIST
            |-T_IDENT : lastname
            |-T_IDENT : address
        |-T_VALUE_LIST
            |-T_VALUE_VECTOR
                |-T_STRING : Wilson
                |-T_STRING : Champs-Elysees
        |-NULL
        |-T_BOOL : FALSE


		
DATE : 2013.6.17
EMAIL: gqinbo@gmail.com


