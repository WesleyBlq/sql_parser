说明
=========
该项目为mysql sql解析器，词法分析和语法分析基于oceanbase 0.4版本，新写sql优化以及根据本地化处理原则和数据路由生成执行计划。
整体过程如下：

编译：
STEP1：$ sh gen_parser.sh
STEP2: $ make

执行： $ ./sql_parser

select join语句如下时，解析后的语法树：
$ ./sql_parser.exe

<<Part 1 : SQL STRING>> SELECT tt.id, tt.name, pp.age FROM tt JOIN pp ON tt.id = pp.id where tt.id = 100 ORDER BY tt.name
<<Part 2 : PARSE TREE>>
|-T_STMT_LIST
    |-T_SELECT
        |-NULL
        |-T_PROJECT_LIST
            |-T_PROJECT_STRING
                |-T_OP_NAME_FIELD
                    |-T_IDENT : tt
                    |-T_IDENT : id
            |-T_PROJECT_STRING
                |-T_OP_NAME_FIELD
                    |-T_IDENT : tt
                    |-T_IDENT : name
            |-T_PROJECT_STRING
                |-T_OP_NAME_FIELD
                    |-T_IDENT : pp
                    |-T_IDENT : age
        |-T_FROM_LIST
            |-T_JOINED_TABLE
                |-T_JOIN_INNER
                |-T_IDENT : tt
                |-T_IDENT : pp
                |-T_OP_EQ
                    |-T_OP_NAME_FIELD
                        |-T_IDENT : tt
                        |-T_IDENT : id
                    |-T_OP_NAME_FIELD
                        |-T_IDENT : pp
                        |-T_IDENT : id
        |-T_OP_EQ
            |-T_OP_NAME_FIELD
                |-T_IDENT : tt
                |-T_IDENT : id
            |-T_INT : 100
        |-NULL
        |-NULL
        |-NULL
        |-NULL
        |-NULL
        |-NULL
        |-T_SORT_LIST
            |-T_SORT_KEY
                |-T_OP_NAME_FIELD
                    |-T_IDENT : tt
                    |-T_IDENT : name
                |-T_SORT_ASC
        |-NULL
        |-NULL
        |-NULL

<<Part 3 : LOGICAL PLAN>>

<LogicalPlan>
    <StmtList>
        ObSelectStmt 0 Begin
        <TableItemList Begin>
            {Num 0, TableId:1, TableName:tt, AliasName:NULL, Type:BASE_TABLE, RefId: 1}
            {Num 1, TableId:2, TableName:pp, AliasName:NULL, Type:BASE_TABLE, RefId: 2}
        <TableItemList End>
        <ColumnItemList Begin>
            {Num 0, ColumnId:1, ColumnName:id, TableRef:1}
            {Num 1, ColumnId:6, ColumnName:id, TableRef:2}
            {Num 2, ColumnId:2, ColumnName:name, TableRef:1}
            {Num 3, ColumnId:8, ColumnName:age, TableRef:2}
        <ColumnItemList End>
        WHERE ::= <5>
        SELECT ::= <2, id>, <3, name>, <4, age>
        FROM ::= <1> INNER JOIN <2> ON <1>
        ORDER BY ::= <6, ASC>
        ObSelectStmt 0 End
    </StmtList>
    <ExprList>
        <ObSqlRawExpr 0 Begin>
        expr_id = 1
        (table_id : column_id) = (NULL : 65519)
        ObBinaryOpRawExpr
        T_OP_EQ
            ObBinaryRefRawExpr
            T_REF_COLUMN : [table_id, column_id] = [1, 1]
            ObBinaryRefRawExpr
            T_REF_COLUMN : [table_id, column_id] = [2, 6]
        <ObSqlRawExpr 0 End>
        <ObSqlRawExpr 1 Begin>
        expr_id = 2
        (table_id : column_id) = (NULL : 65518)
        ObBinaryRefRawExpr
        T_REF_COLUMN : [table_id, column_id] = [1, 1]
        <ObSqlRawExpr 1 End>
        <ObSqlRawExpr 2 Begin>
        expr_id = 3
        (table_id : column_id) = (NULL : 65517)
        ObBinaryRefRawExpr
        T_REF_COLUMN : [table_id, column_id] = [1, 2]
        <ObSqlRawExpr 2 End>
        <ObSqlRawExpr 3 Begin>
        expr_id = 4
        (table_id : column_id) = (NULL : 65516)
        ObBinaryRefRawExpr
        T_REF_COLUMN : [table_id, column_id] = [2, 8]
        <ObSqlRawExpr 3 End>
        <ObSqlRawExpr 4 Begin>
        expr_id = 5
        (table_id : column_id) = (NULL : 65515)
        ObBinaryOpRawExpr
        T_OP_EQ
            ObBinaryRefRawExpr
            T_REF_COLUMN : [table_id, column_id] = [1, 1]
            ObConstRawExpr
            T_INT : 100
        <ObSqlRawExpr 4 End>
        <ObSqlRawExpr 5 Begin>
        expr_id = 6
        (table_id : column_id) = (1 : 2)
        ObBinaryRefRawExpr
        T_REF_COLUMN : [table_id, column_id] = [1, 2]
        <ObSqlRawExpr 5 End>
    </ExprList>
</LogicalPlan>


最终经过tablet定位以及sql重新拼装，最终生成的执行计划为：
I0227 14:07:37 10661 jd_exec_plan.cpp:1712]: exec_plan_unit shard name: tt1
I0227 14:07:37 10661 jd_exec_plan.cpp:1713]: exec_plan_unit SQL name  : SELECT tt.id, tt.name, pp.age FROM tt1 AS tt  JOIN pp1 AS pp  ON tt.id = pp.id   WHERE tt.id = 100  ORDER BY tt.name ASC LIMIT 0, 100000000

然后就可以把sql语句发送到相应的分片中去执行。


DATE : 2014.2.26
EMAIL: gqinbo@gmail.com


