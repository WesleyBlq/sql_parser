˵��
=========
����ĿΪmysql sql���������ʷ��������﷨��������oceanbase 0.4�汾���������﷨��������
sql����Ż��ֲ��ٴ�ƴװ�������ڱ�д����½���ϴ���

���룺
STEP1��$ sh gen_parser.sh
STEP2: $ make

ִ�У� $ ./sql_parser.exe

��insert�������ʱ����������﷨����
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


