/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SQL_PARSER_TAB_H_INCLUDED
# define YY_YY_SQL_PARSER_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NAME = 258,
     STRING = 259,
     INTNUM = 260,
     DATE_VALUE = 261,
     HINT_VALUE = 262,
     BOOL = 263,
     APPROXNUM = 264,
     NULLX = 265,
     UNKNOWN = 266,
     QUESTIONMARK = 267,
     SYSTEM_VARIABLE = 268,
     TEMP_VARIABLE = 269,
     EXCEPT = 270,
     UNION = 271,
     INTERSECT = 272,
     OR = 273,
     AND = 274,
     NOT = 275,
     COMP_NE = 276,
     COMP_GE = 277,
     COMP_GT = 278,
     COMP_EQ = 279,
     COMP_LT = 280,
     COMP_LE = 281,
     CNNOP = 282,
     LIKE = 283,
     BETWEEN = 284,
     IN = 285,
     IS = 286,
     MOD = 287,
     UMINUS = 288,
     ADD = 289,
     ANY = 290,
     ALL = 291,
     ALTER = 292,
     AS = 293,
     ASC = 294,
     BEGI = 295,
     BIGINT = 296,
     BINARY = 297,
     BOOLEAN = 298,
     BOTH = 299,
     BY = 300,
     CASCADE = 301,
     CASE = 302,
     CHARACTER = 303,
     CLUSTER = 304,
     COMMENT = 305,
     COMMIT = 306,
     CONSISTENT = 307,
     COLUMN = 308,
     COLUMNS = 309,
     CREATE = 310,
     CREATETIME = 311,
     CURRENT_USER = 312,
     DATE = 313,
     DATETIME = 314,
     DEALLOCATE = 315,
     DECIMAL = 316,
     DEFAULT = 317,
     DELETE = 318,
     DESC = 319,
     DESCRIBE = 320,
     DISTINCT = 321,
     DOUBLE = 322,
     DROP = 323,
     DUAL = 324,
     ELSE = 325,
     END = 326,
     END_P = 327,
     ERROR = 328,
     EXECUTE = 329,
     EXISTS = 330,
     EXPLAIN = 331,
     FLOAT = 332,
     FOR = 333,
     FROM = 334,
     FULL = 335,
     GLOBAL = 336,
     GLOBAL_ALIAS = 337,
     GRANT = 338,
     GROUP = 339,
     HAVING = 340,
     HINT_BEGIN = 341,
     HINT_END = 342,
     IDENTIFIED = 343,
     IF = 344,
     INNER = 345,
     INTEGER = 346,
     INSERT = 347,
     INTO = 348,
     JOIN = 349,
     KEY = 350,
     LEADING = 351,
     LEFT = 352,
     LIMIT = 353,
     LOCAL = 354,
     LOCKED = 355,
     MEDIUMINT = 356,
     MEMORY = 357,
     MODIFYTIME = 358,
     NUMERIC = 359,
     OFFSET = 360,
     ON = 361,
     ORDER = 362,
     OPTION = 363,
     OUTER = 364,
     PARAMETERS = 365,
     PASSWORD = 366,
     PRECISION = 367,
     PREPARE = 368,
     PRIMARY = 369,
     READ_STATIC = 370,
     REAL = 371,
     RENAME = 372,
     REPLACE = 373,
     RESTRICT = 374,
     PRIVILEGES = 375,
     REVOKE = 376,
     RIGHT = 377,
     ROLLBACK = 378,
     SCHEMA = 379,
     SCOPE = 380,
     SELECT = 381,
     SESSION = 382,
     SESSION_ALIAS = 383,
     SET = 384,
     SHOW = 385,
     SMALLINT = 386,
     SNAPSHOT = 387,
     SPFILE = 388,
     START = 389,
     STATIC = 390,
     SYSTEM = 391,
     DATABASES = 392,
     TABLE = 393,
     TABLES = 394,
     THEN = 395,
     TIME = 396,
     TIMESTAMP = 397,
     TINYINT = 398,
     TRAILING = 399,
     TRANSACTION = 400,
     TO = 401,
     UPDATE = 402,
     USER = 403,
     USING = 404,
     VALUES = 405,
     VARCHAR = 406,
     VARBINARY = 407,
     WHERE = 408,
     WHEN = 409,
     WITH = 410,
     WORK = 411,
     AUTO_INCREMENT = 412,
     CHUNKSERVER = 413,
     COMPRESS_METHOD = 414,
     CONSISTENT_MODE = 415,
     EXPIRE_INFO = 416,
     GRANTS = 417,
     MERGESERVER = 418,
     REPLICA_NUM = 419,
     ROOTSERVER = 420,
     SERVER = 421,
     SERVER_IP = 422,
     SERVER_PORT = 423,
     SERVER_TYPE = 424,
     STATUS = 425,
     TABLET_BLOCK_SIZE = 426,
     TABLET_MAX_SIZE = 427,
     UNLOCKED = 428,
     UPDATESERVER = 429,
     USE_BLOOM_FILTER = 430,
     VARIABLES = 431,
     VERBOSE = 432,
     WARNINGS = 433
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


  struct _ParseNode *node;
  const struct _NonReservedKeyword *non_reserved_keyword;
  int    ival;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (ParseResult* result);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SQL_PARSER_TAB_H_INCLUDED  */
