/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */


#include <stdint.h>
#include "sql_non_reserved_keywords.h"
#include "parse_node.h"
#include "parse_malloc.h"
#include "sql_item_type.h"
#define YYDEBUG 1



# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "sql_parser.tab.h".  */
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
     PROCESSLIST = 402,
     UPDATE = 403,
     USER = 404,
     USING = 405,
     VALUES = 406,
     VARCHAR = 407,
     VARBINARY = 408,
     WHERE = 409,
     WHEN = 410,
     WITH = 411,
     WORK = 412,
     AUTO_INCREMENT = 413,
     CHUNKSERVER = 414,
     COMPRESS_METHOD = 415,
     CONSISTENT_MODE = 416,
     EXPIRE_INFO = 417,
     GRANTS = 418,
     MERGESERVER = 419,
     REPLICA_NUM = 420,
     ROOTSERVER = 421,
     SERVER = 422,
     SERVER_IP = 423,
     SERVER_PORT = 424,
     SERVER_TYPE = 425,
     STATUS = 426,
     TABLET_BLOCK_SIZE = 427,
     TABLET_MAX_SIZE = 428,
     UNLOCKED = 429,
     UPDATESERVER = 430,
     USE_BLOOM_FILTER = 431,
     VARIABLES = 432,
     VERBOSE = 433,
     WARNINGS = 434
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

/* Copy the second part of user declarations.  */


#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "sql_parser.lex.h"

#define YYLEX_PARAM result->yyscan_info_

extern void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s,...);

extern ParseNode* merge_tree(void *malloc_pool, SqlItemType node_tag, ParseNode* source_tree);

extern ParseNode* new_terminal_node(void *malloc_pool, SqlItemType type);

extern ParseNode* new_non_terminal_node(void *malloc_pool, SqlItemType node_tag, int num, ...);

extern char* copy_expr_string(ParseResult* p, int expr_start, int expr_end);

#define malloc_terminal_node(node, malloc_pool, type) \
do \
{ \
  if ((node = new_terminal_node(malloc_pool, type)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for malloc"); \
    YYABORT; \
  } \
} while(0)

#define malloc_non_terminal_node(node, malloc_pool, node_tag, ...) \
do \
{ \
  if ((node = new_non_terminal_node(malloc_pool, node_tag, ##__VA_ARGS__)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for malloc"); \
    YYABORT; \
  } \
} while(0)

#define merge_nodes(node, malloc_pool, node_tag, source_tree) \
do \
{ \
  if (source_tree == NULL) \
  { \
    node = NULL; \
  } \
  else if ((node = merge_tree(malloc_pool, node_tag, source_tree)) == NULL) \
  { \
    yyerror(NULL, result, "No more space for merging nodes"); \
    YYABORT; \
  } \
} while (0)

#define dup_expr_string(str_ptr, result, expr_start, expr_end) \
  do \
  { \
    str_ptr = NULL; \
    if (expr_end >= expr_start \
      && (str_ptr = copy_expr_string(result, expr_start, expr_end)) == NULL) \
    { \
      yyerror(NULL, result, "No more space for copying expression string"); \
      YYABORT; \
    } \
  } while (0)




#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  154
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2661

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  191
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  144
/* YYNRULES -- Number of rules.  */
#define YYNRULES  455
/* YYNRULES -- Number of states.  */
#define YYNSTATES  804

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   434

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      40,    41,    34,    32,   190,    33,    42,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   189,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    37,    39,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,    10,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    38,    40,
      42,    44,    46,    48,    50,    52,    54,    56,    58,    60,
      61,    63,    67,    69,    73,    77,    79,    81,    83,    85,
      87,    89,    91,    93,    95,    99,   101,   103,   107,   113,
     115,   117,   119,   122,   124,   127,   130,   134,   138,   142,
     146,   150,   154,   158,   160,   163,   166,   170,   174,   178,
     182,   186,   190,   194,   198,   202,   206,   210,   214,   218,
     222,   227,   231,   235,   238,   242,   247,   251,   256,   260,
     265,   271,   278,   282,   287,   291,   293,   297,   303,   305,
     306,   308,   311,   316,   319,   320,   325,   331,   336,   343,
     348,   352,   354,   356,   361,   367,   369,   373,   377,   386,
     390,   391,   393,   397,   399,   405,   409,   411,   413,   415,
     417,   419,   422,   425,   427,   430,   432,   435,   438,   440,
     443,   446,   449,   452,   454,   456,   458,   461,   467,   471,
     472,   476,   477,   479,   480,   484,   485,   489,   490,   493,
     494,   497,   499,   502,   504,   507,   509,   513,   514,   518,
     522,   526,   530,   534,   538,   542,   544,   545,   550,   551,
     554,   556,   560,   567,   572,   580,   582,   584,   588,   589,
     591,   595,   599,   605,   607,   611,   613,   615,   619,   623,
     625,   628,   632,   637,   643,   652,   654,   656,   666,   671,
     676,   681,   682,   685,   689,   694,   699,   702,   705,   710,
     711,   715,   717,   721,   722,   724,   726,   728,   729,   731,
     732,   735,   739,   744,   749,   754,   758,   762,   766,   767,
     771,   773,   774,   778,   780,   784,   787,   788,   790,   792,
     793,   796,   797,   799,   801,   803,   806,   810,   812,   814,
     818,   820,   824,   826,   830,   834,   837,   841,   844,   846,
     852,   854,   858,   865,   871,   874,   877,   880,   882,   884,
     885,   889,   891,   893,   895,   897,   899,   900,   904,   908,
     914,   920,   925,   930,   935,   938,   943,   947,   951,   955,
     959,   963,   967,   970,   975,   978,   979,   981,   984,   989,
     991,   993,   994,   995,   998,  1001,  1002,  1004,  1008,  1010,
    1014,  1019,  1021,  1023,  1027,  1029,  1033,  1039,  1046,  1049,
    1050,  1054,  1058,  1060,  1064,  1069,  1071,  1073,  1075,  1076,
    1080,  1081,  1084,  1088,  1091,  1094,  1101,  1103,  1107,  1110,
    1112,  1114,  1117,  1119,  1121,  1124,  1126,  1128,  1130,  1132,
    1134,  1135,  1137,  1139,  1145,  1148,  1149,  1154,  1156,  1158,
    1160,  1162,  1164,  1167,  1169,  1173,  1177,  1181,  1186,  1191,
    1197,  1203,  1207,  1209,  1211,  1213,  1217,  1220,  1221,  1223,
    1227,  1231,  1233,  1235,  1240,  1247,  1249,  1253,  1257,  1262,
    1267,  1273,  1275,  1276,  1278,  1280,  1281,  1285,  1289,  1293,
    1296,  1301,  1303,  1307,  1317,  1320,  1321,  1325,  1329,  1333,
    1334,  1336,  1338,  1340,  1342,  1346,  1353,  1354,  1356,  1358,
    1360,  1362,  1364,  1366,  1368,  1370,  1372,  1374,  1376,  1378,
    1380,  1382,  1384,  1386,  1388,  1390,  1392,  1394,  1396,  1398,
    1400,  1402,  1404,  1406,  1408,  1410
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     192,     0,    -1,   193,    81,    -1,   193,   189,   194,    -1,
     194,    -1,   238,    -1,   232,    -1,   213,    -1,   210,    -1,
     209,    -1,   229,    -1,   269,    -1,   272,    -1,   304,    -1,
     307,    -1,   312,    -1,   317,    -1,   323,    -1,   315,    -1,
     278,    -1,   283,    -1,   285,    -1,   287,    -1,   290,    -1,
     297,    -1,   302,    -1,   294,    -1,   295,    -1,   296,    -1,
      -1,   200,    -1,   195,   190,   200,    -1,   330,    -1,   331,
      42,   330,    -1,   331,    42,    34,    -1,     4,    -1,     6,
      -1,     5,    -1,     9,    -1,     8,    -1,    10,    -1,    12,
      -1,    14,    -1,    13,    -1,   137,    42,   330,    -1,   196,
      -1,   197,    -1,    40,   200,    41,    -1,    40,   195,   190,
     200,    41,    -1,   202,    -1,   207,    -1,   239,    -1,    84,
     239,    -1,   198,    -1,    32,   199,    -1,    33,   199,    -1,
     199,    32,   199,    -1,   199,    33,   199,    -1,   199,    34,
     199,    -1,   199,    35,   199,    -1,   199,    36,   199,    -1,
     199,    38,   199,    -1,   199,    37,   199,    -1,   198,    -1,
      32,   200,    -1,    33,   200,    -1,   200,    32,   200,    -1,
     200,    33,   200,    -1,   200,    34,   200,    -1,   200,    35,
     200,    -1,   200,    36,   200,    -1,   200,    38,   200,    -1,
     200,    37,   200,    -1,   200,    26,   200,    -1,   200,    25,
     200,    -1,   200,    24,   200,    -1,   200,    22,   200,    -1,
     200,    23,   200,    -1,   200,    21,   200,    -1,   200,    28,
     200,    -1,   200,    20,    28,   200,    -1,   200,    19,   200,
      -1,   200,    18,   200,    -1,    20,   200,    -1,   200,    31,
      10,    -1,   200,    31,    20,    10,    -1,   200,    31,     8,
      -1,   200,    31,    20,     8,    -1,   200,    31,    11,    -1,
     200,    31,    20,    11,    -1,   200,    29,   199,    19,   199,
      -1,   200,    20,    29,   199,    19,   199,    -1,   200,    30,
     201,    -1,   200,    20,    30,   201,    -1,   200,    27,   200,
      -1,   239,    -1,    40,   195,    41,    -1,    56,   203,   204,
     206,    80,    -1,   200,    -1,    -1,   205,    -1,   204,   205,
      -1,   164,   200,   149,   200,    -1,    79,   200,    -1,    -1,
     332,    40,    34,    41,    -1,   332,    40,   208,   200,    41,
      -1,   332,    40,   195,    41,    -1,   332,    40,   200,    47,
     218,    41,    -1,   332,    40,   252,    41,    -1,   332,    40,
      41,    -1,    45,    -1,    75,    -1,    72,    88,   265,   244,
      -1,   157,   265,   138,   211,   244,    -1,   212,    -1,   211,
     190,   212,    -1,   330,    24,   200,    -1,    64,   147,   214,
     265,    40,   215,    41,   226,    -1,    98,    20,    84,    -1,
      -1,   216,    -1,   215,   190,   216,    -1,   217,    -1,   123,
     104,    40,   235,    41,    -1,   330,   218,   224,    -1,   152,
      -1,   140,    -1,   110,    -1,   100,    -1,    50,    -1,    70,
     219,    -1,   113,   219,    -1,    52,    -1,    86,   220,    -1,
     125,    -1,    76,   221,    -1,   151,   222,    -1,    68,    -1,
      57,   223,    -1,    51,   223,    -1,   161,   223,    -1,   162,
     223,    -1,    65,    -1,   112,    -1,    67,    -1,   150,   222,
      -1,    40,     5,   190,     5,    41,    -1,    40,     5,    41,
      -1,    -1,    40,     5,    41,    -1,    -1,   121,    -1,    -1,
      40,     5,    41,    -1,    -1,    40,     5,    41,    -1,    -1,
     224,   225,    -1,    -1,    20,    10,    -1,    10,    -1,    71,
     197,    -1,   167,    -1,   123,   104,    -1,   227,    -1,   226,
     190,   227,    -1,    -1,   171,   228,     4,    -1,   182,   228,
       5,    -1,   181,   228,     5,    -1,   174,   228,     5,    -1,
     169,   228,     4,    -1,   185,   228,     8,    -1,   170,   228,
     144,    -1,    24,    -1,    -1,    77,   147,   230,   231,    -1,
      -1,    98,    84,    -1,   264,    -1,   231,   190,   264,    -1,
     233,   102,   265,   234,   160,   236,    -1,   233,   102,   265,
     238,    -1,   233,   102,   265,    40,   235,    41,   238,    -1,
     127,    -1,   101,    -1,    40,   235,    41,    -1,    -1,   330,
      -1,   235,   190,   330,    -1,    40,   237,    41,    -1,   236,
     190,    40,   237,    41,    -1,   200,    -1,   237,   190,   200,
      -1,   240,    -1,   239,    -1,    40,   240,    41,    -1,    40,
     239,    41,    -1,   241,    -1,   243,   251,    -1,   242,   255,
     251,    -1,   242,   254,   245,   251,    -1,   135,   246,   260,
     262,   250,    -1,   135,   246,   260,   262,    88,    78,   244,
     250,    -1,   243,    -1,   239,    -1,   135,   246,   260,   262,
      88,   263,   244,   253,   259,    -1,   242,    16,   260,   242,
      -1,   242,    17,   260,   242,    -1,   242,    15,   260,   242,
      -1,    -1,   163,   200,    -1,   163,     7,   200,    -1,   107,
     249,   114,   249,    -1,   114,   249,   107,   249,    -1,   107,
     249,    -1,   114,   249,    -1,   107,   249,   190,   249,    -1,
      -1,    95,   247,    96,    -1,   248,    -1,   247,   190,   248,
      -1,    -1,   124,    -1,     5,    -1,    12,    -1,    -1,   245,
      -1,    -1,    87,   157,    -1,   200,    88,   200,    -1,    53,
     200,    88,   200,    -1,   105,   200,    88,   200,    -1,   153,
     200,    88,   200,    -1,    53,    88,   200,    -1,   105,    88,
     200,    -1,   153,    88,   200,    -1,    -1,    93,    54,   195,
      -1,   255,    -1,    -1,   116,    54,   256,    -1,   257,    -1,
     256,   190,   257,    -1,   200,   258,    -1,    -1,    48,    -1,
      73,    -1,    -1,    94,   200,    -1,    -1,    45,    -1,    75,
      -1,   200,    -1,   200,   333,    -1,   200,    47,   333,    -1,
      34,    -1,   261,    -1,   262,   190,   261,    -1,   264,    -1,
     263,   190,   264,    -1,   265,    -1,   331,    42,   265,    -1,
     265,    47,   331,    -1,   265,   331,    -1,   239,    47,   331,
      -1,   239,   331,    -1,   266,    -1,    40,   266,    41,    47,
     331,    -1,   331,    -1,    40,   266,    41,    -1,   264,   267,
     103,   264,   115,   200,    -1,   264,   103,   264,   115,   200,
      -1,    89,   268,    -1,   106,   268,    -1,   131,   268,    -1,
      99,    -1,   118,    -1,    -1,    85,   271,   270,    -1,   238,
      -1,   209,    -1,   232,    -1,   210,    -1,   187,    -1,    -1,
     139,   146,   276,    -1,   139,   148,   276,    -1,   139,    63,
      88,   265,   276,    -1,   139,    63,    30,   265,   276,    -1,
     139,   147,   180,   276,    -1,   139,   176,   180,   276,    -1,
     139,   275,   186,   276,    -1,   139,   133,    -1,   139,    64,
     147,   265,    -1,    74,   265,   277,    -1,    73,   265,   277,
      -1,   139,   188,   273,    -1,   139,   207,   188,    -1,   139,
     172,   274,    -1,   139,   119,   276,    -1,   139,   156,    -1,
     107,     5,   190,     5,    -1,   107,     5,    -1,    -1,   286,
      -1,    87,    66,    -1,    87,    66,    40,    41,    -1,    90,
      -1,   136,    -1,    -1,    -1,    28,     4,    -1,   163,   200,
      -1,    -1,     4,    -1,    64,   158,   279,    -1,   280,    -1,
     279,   190,   280,    -1,   281,    97,    54,   282,    -1,     4,
      -1,     4,    -1,    77,   158,   284,    -1,   281,    -1,   284,
     190,   281,    -1,   138,   120,   286,    24,   282,    -1,    46,
     158,   281,    97,    54,   282,    -1,    87,   281,    -1,    -1,
     126,   158,   289,    -1,   281,   155,   281,    -1,   288,    -1,
     289,   190,   288,    -1,    46,   158,   281,   291,    -1,   109,
      -1,   183,    -1,   166,    -1,    -1,   165,    61,   141,    -1,
      -1,    49,   292,    -1,   143,   154,   293,    -1,    60,   292,
      -1,   132,   292,    -1,    92,   298,   115,   301,   155,   284,
      -1,   299,    -1,   298,   190,   299,    -1,    45,   300,    -1,
      46,    -1,    64,    -1,    64,   158,    -1,    72,    -1,    77,
      -1,    92,   117,    -1,   101,    -1,   157,    -1,   135,    -1,
     127,    -1,   129,    -1,    -1,    34,    -1,   331,    -1,   130,
     298,   303,    88,   284,    -1,   115,   301,    -1,    -1,   122,
     305,    88,   306,    -1,   333,    -1,   238,    -1,   232,    -1,
     210,    -1,   209,    -1,   138,   308,    -1,   309,    -1,   308,
     190,   309,    -1,    14,   310,   200,    -1,   330,   310,   200,
      -1,    90,   330,   310,   200,    -1,   136,   330,   310,   200,
      -1,    91,    42,   330,   310,   200,    -1,   137,    42,   330,
     310,   200,    -1,    13,   310,   200,    -1,   155,    -1,    24,
      -1,    14,    -1,    83,   305,   313,    -1,   159,   314,    -1,
      -1,   311,    -1,   314,   190,   311,    -1,   316,   122,   305,
      -1,    69,    -1,    77,    -1,    46,   147,   265,   318,    -1,
      46,   147,   265,   126,   155,   265,    -1,   319,    -1,   318,
     190,   319,    -1,    43,   320,   217,    -1,    77,   320,   330,
     321,    -1,    46,   320,   330,   322,    -1,   126,   320,   330,
     155,   333,    -1,    62,    -1,    -1,    55,    -1,   128,    -1,
      -1,   138,    20,    10,    -1,    77,    20,    10,    -1,   138,
      71,   197,    -1,    77,    71,    -1,    46,   145,   138,   324,
      -1,   325,    -1,   324,   190,   325,    -1,   330,    24,   197,
     326,   327,   179,    24,   328,   329,    -1,    59,     4,    -1,
      -1,   134,    24,   111,    -1,   134,    24,   142,    -1,   134,
      24,    53,    -1,    -1,   175,    -1,   184,    -1,   168,    -1,
     173,    -1,    58,    24,     5,    -1,   177,    24,     4,   178,
      24,     5,    -1,    -1,     3,    -1,   334,    -1,     3,    -1,
     334,    -1,     3,    -1,     3,    -1,   334,    -1,   167,    -1,
     168,    -1,   169,    -1,   170,    -1,   171,    -1,   172,    -1,
     173,    -1,   174,    -1,   175,    -1,   176,    -1,   177,    -1,
     178,    -1,   179,    -1,   180,    -1,   181,    -1,   182,    -1,
     183,    -1,   184,    -1,   185,    -1,   186,    -1,   187,    -1,
     188,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   213,   213,   222,   229,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     270,   274,   281,   283,   289,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   311,   313,   315,   317,   323,
     331,   335,   339,   347,   348,   352,   356,   357,   358,   359,
     360,   361,   362,   365,   366,   370,   374,   375,   376,   377,
     378,   379,   380,   381,   382,   383,   384,   385,   386,   387,
     388,   389,   393,   397,   401,   405,   409,   413,   417,   421,
     425,   429,   433,   437,   441,   448,   452,   457,   465,   466,
     470,   472,   477,   484,   485,   489,   503,   531,   606,   622,
     626,   635,   639,   653,   667,   676,   680,   687,   701,   718,
     721,   725,   729,   736,   740,   749,   758,   760,   762,   764,
     766,   768,   777,   786,   788,   790,   792,   797,   804,   806,
     813,   820,   827,   834,   836,   838,   844,   856,   858,   861,
     865,   866,   870,   871,   875,   876,   880,   881,   885,   888,
     892,   897,   902,   904,   906,   911,   915,   920,   926,   931,
     936,   941,   946,   951,   956,   965,   966,   977,   987,   988,
     993,   997,  1010,  1022,  1032,  1047,  1052,  1060,  1065,  1069,
    1070,  1077,  1081,  1087,  1088,  1102,  1104,  1109,  1110,  1114,
    1118,  1123,  1133,  1154,  1175,  1200,  1201,  1205,  1230,  1251,
    1272,  1297,  1298,  1302,  1309,  1317,  1325,  1329,  1333,  1345,
    1348,  1362,  1366,  1371,  1377,  1384,  1386,  1392,  1393,  1399,
    1400,  1408,  1415,  1422,  1429,  1436,  1447,  1458,  1473,  1474,
    1481,  1482,  1486,  1493,  1495,  1500,  1508,  1509,  1511,  1517,
    1518,  1526,  1529,  1533,  1540,  1545,  1553,  1561,  1571,  1575,
    1582,  1584,  1589,  1593,  1598,  1602,  1606,  1610,  1614,  1618,
    1627,  1635,  1639,  1643,  1652,  1658,  1664,  1670,  1677,  1678,
    1688,  1696,  1697,  1698,  1699,  1703,  1704,  1714,  1716,  1718,
    1720,  1722,  1724,  1726,  1731,  1733,  1735,  1737,  1739,  1743,
    1756,  1760,  1764,  1769,  1778,  1788,  1792,  1794,  1796,  1801,
    1802,  1803,  1808,  1809,  1811,  1817,  1818,  1828,  1834,  1838,
    1844,  1850,  1856,  1868,  1874,  1878,  1890,  1894,  1900,  1905,
    1915,  1921,  1927,  1931,  1942,  1948,  1953,  1966,  1971,  1975,
    1980,  1984,  1990,  2001,  2013,  2025,  2036,  2040,  2046,  2052,
    2057,  2062,  2067,  2072,  2077,  2082,  2087,  2092,  2097,  2104,
    2109,  2114,  2119,  2130,  2170,  2175,  2186,  2193,  2198,  2200,
    2202,  2204,  2215,  2223,  2227,  2234,  2240,  2247,  2254,  2261,
    2268,  2275,  2284,  2285,  2289,  2300,  2307,  2312,  2317,  2321,
    2334,  2342,  2344,  2355,  2361,  2372,  2376,  2383,  2388,  2394,
    2399,  2408,  2409,  2413,  2414,  2415,  2419,  2424,  2429,  2433,
    2447,  2455,  2459,  2466,  2481,  2484,  2488,  2490,  2492,  2495,
    2499,  2504,  2509,  2514,  2522,  2526,  2531,  2542,  2544,  2561,
    2563,  2580,  2584,  2586,  2599,  2600,  2601,  2602,  2603,  2604,
    2605,  2606,  2607,  2608,  2609,  2610,  2611,  2612,  2613,  2614,
    2615,  2616,  2617,  2618,  2619,  2620
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "INTNUM", "DATE_VALUE",
  "HINT_VALUE", "BOOL", "APPROXNUM", "NULLX", "UNKNOWN", "QUESTIONMARK",
  "SYSTEM_VARIABLE", "TEMP_VARIABLE", "EXCEPT", "UNION", "INTERSECT", "OR",
  "AND", "NOT", "COMP_NE", "COMP_GE", "COMP_GT", "COMP_EQ", "COMP_LT",
  "COMP_LE", "CNNOP", "LIKE", "BETWEEN", "IN", "IS", "'+'", "'-'", "'*'",
  "'/'", "'%'", "MOD", "'^'", "UMINUS", "'('", "')'", "'.'", "ADD", "ANY",
  "ALL", "ALTER", "AS", "ASC", "BEGI", "BIGINT", "BINARY", "BOOLEAN",
  "BOTH", "BY", "CASCADE", "CASE", "CHARACTER", "CLUSTER", "COMMENT",
  "COMMIT", "CONSISTENT", "COLUMN", "COLUMNS", "CREATE", "CREATETIME",
  "CURRENT_USER", "DATE", "DATETIME", "DEALLOCATE", "DECIMAL", "DEFAULT",
  "DELETE", "DESC", "DESCRIBE", "DISTINCT", "DOUBLE", "DROP", "DUAL",
  "ELSE", "END", "END_P", "ERROR", "EXECUTE", "EXISTS", "EXPLAIN", "FLOAT",
  "FOR", "FROM", "FULL", "GLOBAL", "GLOBAL_ALIAS", "GRANT", "GROUP",
  "HAVING", "HINT_BEGIN", "HINT_END", "IDENTIFIED", "IF", "INNER",
  "INTEGER", "INSERT", "INTO", "JOIN", "KEY", "LEADING", "LEFT", "LIMIT",
  "LOCAL", "LOCKED", "MEDIUMINT", "MEMORY", "MODIFYTIME", "NUMERIC",
  "OFFSET", "ON", "ORDER", "OPTION", "OUTER", "PARAMETERS", "PASSWORD",
  "PRECISION", "PREPARE", "PRIMARY", "READ_STATIC", "REAL", "RENAME",
  "REPLACE", "RESTRICT", "PRIVILEGES", "REVOKE", "RIGHT", "ROLLBACK",
  "SCHEMA", "SCOPE", "SELECT", "SESSION", "SESSION_ALIAS", "SET", "SHOW",
  "SMALLINT", "SNAPSHOT", "SPFILE", "START", "STATIC", "SYSTEM",
  "DATABASES", "TABLE", "TABLES", "THEN", "TIME", "TIMESTAMP", "TINYINT",
  "TRAILING", "TRANSACTION", "TO", "PROCESSLIST", "UPDATE", "USER",
  "USING", "VALUES", "VARCHAR", "VARBINARY", "WHERE", "WHEN", "WITH",
  "WORK", "AUTO_INCREMENT", "CHUNKSERVER", "COMPRESS_METHOD",
  "CONSISTENT_MODE", "EXPIRE_INFO", "GRANTS", "MERGESERVER", "REPLICA_NUM",
  "ROOTSERVER", "SERVER", "SERVER_IP", "SERVER_PORT", "SERVER_TYPE",
  "STATUS", "TABLET_BLOCK_SIZE", "TABLET_MAX_SIZE", "UNLOCKED",
  "UPDATESERVER", "USE_BLOOM_FILTER", "VARIABLES", "VERBOSE", "WARNINGS",
  "';'", "','", "$accept", "sql_stmt", "stmt_list", "stmt", "expr_list",
  "column_ref", "expr_const", "simple_expr", "arith_expr", "expr",
  "in_expr", "case_expr", "case_arg", "when_clause_list", "when_clause",
  "case_default", "func_expr", "distinct_or_all", "delete_stmt",
  "update_stmt", "update_asgn_list", "update_asgn_factor",
  "create_table_stmt", "opt_if_not_exists", "table_element_list",
  "table_element", "column_definition", "data_type", "opt_decimal",
  "opt_float", "opt_precision", "opt_time_precision", "opt_char_length",
  "opt_column_attribute_list", "column_attribute", "opt_table_option_list",
  "table_option", "opt_equal_mark", "drop_table_stmt", "opt_if_exists",
  "table_list", "insert_stmt", "replace_or_insert", "opt_insert_columns",
  "column_list", "insert_vals_list", "insert_vals", "select_stmt",
  "select_with_parens", "select_no_parens", "no_table_select",
  "select_clause", "simple_select", "opt_where", "select_limit",
  "opt_hint", "opt_hint_list", "hint_option", "limit_expr",
  "opt_select_limit", "opt_for_update", "parameterized_trim",
  "opt_groupby", "opt_order_by", "order_by", "sort_list", "sort_key",
  "opt_asc_desc", "opt_having", "opt_distinct", "projection",
  "select_expr_list", "from_list", "table_factor", "relation_factor",
  "joined_table", "join_type", "join_outer", "explain_stmt",
  "explainable_stmt", "opt_verbose", "show_stmt", "opt_limit",
  "opt_for_grant_user", "opt_scope", "opt_show_condition",
  "opt_like_condition", "create_user_stmt", "user_specification_list",
  "user_specification", "user", "password", "drop_user_stmt", "user_list",
  "set_password_stmt", "opt_for_user", "rename_user_stmt", "rename_info",
  "rename_list", "lock_user_stmt", "lock_spec", "opt_work",
  "opt_with_consistent_snapshot", "begin_stmt", "commit_stmt",
  "rollback_stmt", "grant_stmt", "priv_type_list", "priv_type",
  "opt_privilege", "priv_level", "revoke_stmt", "opt_on_priv_level",
  "prepare_stmt", "stmt_name", "preparable_stmt", "variable_set_stmt",
  "var_and_val_list", "var_and_val", "to_or_eq", "argument",
  "execute_stmt", "opt_using_args", "argument_list",
  "deallocate_prepare_stmt", "deallocate_or_drop", "alter_table_stmt",
  "alter_column_actions", "alter_column_action", "opt_column",
  "opt_drop_behavior", "alter_column_behavior", "alter_system_stmt",
  "alter_system_actions", "alter_system_action", "opt_comment",
  "opt_config_scope", "server_type", "opt_cluster_or_address",
  "column_name", "relation_name", "function_name", "column_label",
  "unreserved_keyword", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    43,    45,    42,    47,    37,   287,    94,   288,
      40,    41,    46,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,   304,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   372,   373,   374,   375,
     376,   377,   378,   379,   380,   381,   382,   383,   384,   385,
     386,   387,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,   403,   404,   405,
     406,   407,   408,   409,   410,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,   425,
     426,   427,   428,   429,   430,   431,   432,   433,   434,    59,
      44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   191,   192,   193,   193,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     195,   195,   196,   196,   196,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   198,   198,   198,   198,   198,
     198,   198,   198,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   201,   201,   202,   203,   203,
     204,   204,   205,   206,   206,   207,   207,   207,   207,   207,
     207,   208,   208,   209,   210,   211,   211,   212,   213,   214,
     214,   215,   215,   216,   216,   217,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   219,   219,   219,
     220,   220,   221,   221,   222,   222,   223,   223,   224,   224,
     225,   225,   225,   225,   225,   226,   226,   226,   227,   227,
     227,   227,   227,   227,   227,   228,   228,   229,   230,   230,
     231,   231,   232,   232,   232,   233,   233,   234,   234,   235,
     235,   236,   236,   237,   237,   238,   238,   239,   239,   240,
     240,   240,   240,   241,   241,   242,   242,   243,   243,   243,
     243,   244,   244,   244,   245,   245,   245,   245,   245,   246,
     246,   247,   247,   247,   248,   249,   249,   250,   250,   251,
     251,   252,   252,   252,   252,   252,   252,   252,   253,   253,
     254,   254,   255,   256,   256,   257,   258,   258,   258,   259,
     259,   260,   260,   260,   261,   261,   261,   261,   262,   262,
     263,   263,   264,   264,   264,   264,   264,   264,   264,   264,
     265,   266,   266,   266,   267,   267,   267,   267,   268,   268,
     269,   270,   270,   270,   270,   271,   271,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     272,   272,   272,   273,   273,   273,   274,   274,   274,   275,
     275,   275,   276,   276,   276,   277,   277,   278,   279,   279,
     280,   281,   282,   283,   284,   284,   285,   285,   286,   286,
     287,   288,   289,   289,   290,   291,   291,   292,   292,   293,
     293,   294,   294,   295,   296,   297,   298,   298,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   299,   299,   300,
     300,   301,   301,   302,   303,   303,   304,   305,   306,   306,
     306,   306,   307,   308,   308,   309,   309,   309,   309,   309,
     309,   309,   310,   310,   311,   312,   313,   313,   314,   314,
     315,   316,   316,   317,   317,   318,   318,   319,   319,   319,
     319,   320,   320,   321,   321,   321,   322,   322,   322,   322,
     323,   324,   324,   325,   326,   326,   327,   327,   327,   327,
     328,   328,   328,   328,   329,   329,   329,   330,   330,   331,
     331,   332,   333,   333,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334,   334,   334,   334,   334,
     334,   334,   334,   334,   334,   334
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     3,     5,     1,
       1,     1,     2,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     3,     3,     2,     3,     4,     3,     4,     3,     4,
       5,     6,     3,     4,     3,     1,     3,     5,     1,     0,
       1,     2,     4,     2,     0,     4,     5,     4,     6,     4,
       3,     1,     1,     4,     5,     1,     3,     3,     8,     3,
       0,     1,     3,     1,     5,     3,     1,     1,     1,     1,
       1,     2,     2,     1,     2,     1,     2,     2,     1,     2,
       2,     2,     2,     1,     1,     1,     2,     5,     3,     0,
       3,     0,     1,     0,     3,     0,     3,     0,     2,     0,
       2,     1,     2,     1,     2,     1,     3,     0,     3,     3,
       3,     3,     3,     3,     3,     1,     0,     4,     0,     2,
       1,     3,     6,     4,     7,     1,     1,     3,     0,     1,
       3,     3,     5,     1,     3,     1,     1,     3,     3,     1,
       2,     3,     4,     5,     8,     1,     1,     9,     4,     4,
       4,     0,     2,     3,     4,     4,     2,     2,     4,     0,
       3,     1,     3,     0,     1,     1,     1,     0,     1,     0,
       2,     3,     4,     4,     4,     3,     3,     3,     0,     3,
       1,     0,     3,     1,     3,     2,     0,     1,     1,     0,
       2,     0,     1,     1,     1,     2,     3,     1,     1,     3,
       1,     3,     1,     3,     3,     2,     3,     2,     1,     5,
       1,     3,     6,     5,     2,     2,     2,     1,     1,     0,
       3,     1,     1,     1,     1,     1,     0,     3,     3,     5,
       5,     4,     4,     4,     2,     4,     3,     3,     3,     3,
       3,     3,     2,     4,     2,     0,     1,     2,     4,     1,
       1,     0,     0,     2,     2,     0,     1,     3,     1,     3,
       4,     1,     1,     3,     1,     3,     5,     6,     2,     0,
       3,     3,     1,     3,     4,     1,     1,     1,     0,     3,
       0,     2,     3,     2,     2,     6,     1,     3,     2,     1,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       0,     1,     1,     5,     2,     0,     4,     1,     1,     1,
       1,     1,     2,     1,     3,     3,     3,     4,     4,     5,
       5,     3,     1,     1,     1,     3,     2,     0,     1,     3,
       3,     1,     1,     4,     6,     1,     3,     3,     4,     4,
       5,     1,     0,     1,     1,     0,     3,     3,     3,     2,
       4,     1,     3,     9,     2,     0,     3,     3,     3,     0,
       1,     1,     1,     1,     3,     6,     0,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      29,     0,     0,   338,   338,     0,   391,     0,     0,     0,
     392,     0,   286,     0,   186,     0,     0,   185,     0,   338,
     219,     0,   311,     0,     0,     0,     0,     4,     9,     8,
       7,    10,     6,     0,     5,   206,   195,   199,   241,   205,
      11,    12,    19,    20,    21,    22,    23,    26,    27,    28,
      24,    25,    13,    14,    15,    18,     0,    16,    17,   206,
       0,     0,     0,     0,   337,   341,   343,   120,     0,     0,
     429,   434,   435,   436,   437,   438,   439,   440,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   315,   270,   430,   315,   178,     0,   432,
     387,   367,   433,   285,     0,   360,   349,   350,   352,   353,
       0,   355,   358,   357,   356,     0,   346,     0,     0,   365,
     344,   223,   251,   427,     0,     0,     0,     0,   329,     0,
       0,   372,   373,     0,   428,   431,     0,     0,   309,   312,
     294,   310,   312,     0,   312,   302,   329,     0,   305,     0,
       0,     0,   340,     0,     1,     2,    29,     0,   251,   251,
     251,     0,     0,   229,     0,   200,     0,   198,   197,     0,
       0,   321,     0,     0,     0,   317,   318,     0,   211,   316,
     297,   296,     0,     0,   324,   323,     0,   385,   282,   284,
     283,   281,   280,   359,   348,   351,   354,     0,     0,     0,
       0,   332,   330,     0,     0,   224,     0,   221,   252,   253,
       0,   383,   382,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   301,   287,
     312,   288,     0,   300,   306,   312,     0,   298,   299,   312,
       0,     0,   342,     0,     3,   188,     0,     0,     0,     0,
       0,     0,   229,   201,   230,   390,   410,   411,     0,   402,
     402,   402,   402,   393,   395,     0,   335,   336,   334,     0,
       0,     0,     0,     0,   113,   179,     0,   177,     0,   180,
     262,   268,   270,     0,   384,   388,   386,   361,     0,   362,
     347,   371,   370,   369,   368,   366,     0,     0,   364,     0,
     220,     0,   427,    35,    37,    36,    39,    38,    40,    41,
      43,    42,     0,     0,     0,   257,     0,    99,     0,     0,
      45,    46,    63,   254,    49,    50,    51,   258,   227,    32,
       0,   428,   381,   375,     0,     0,   328,     0,     0,     0,
     374,   376,   312,   312,   295,   313,   314,   291,   307,   292,
     304,   293,     0,   110,   111,     0,   112,     0,     0,     0,
      30,     0,     0,     0,   211,   115,     0,     0,     0,   183,
     219,   206,   210,   205,   208,   209,   246,   242,   243,   225,
     226,   216,   217,   202,     0,     0,   401,     0,     0,     0,
       0,     0,     0,     0,   119,     0,   319,     0,     0,   212,
     206,     0,   268,     0,     0,   267,   279,   277,     0,   279,
     279,     0,     0,   265,     0,   325,     0,     0,   331,   333,
     363,   222,    83,    64,    65,     0,    30,    51,    98,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   255,     0,     0,   228,   203,     0,
     377,     0,   322,   326,   378,     0,   290,   289,     0,     0,
     105,     0,     0,     0,     0,     0,     0,   107,     0,     0,
       0,     0,   109,   339,     0,   114,     0,     0,   189,     0,
     251,   247,   248,   245,     0,     0,     0,     0,   412,   415,
     397,     0,     0,   405,   394,     0,   402,   396,   327,     0,
       0,   121,   123,   320,   213,   271,   181,   266,   278,   274,
       0,   275,   276,     0,   264,   263,   389,   345,     0,    47,
       0,   104,   100,    44,    82,    81,     0,     0,     0,    78,
      76,    77,    75,    74,    73,    94,    79,     0,     0,    53,
       0,     0,    92,    95,    86,    84,    88,     0,    66,    67,
      68,    69,    70,    72,    71,   256,   211,   211,   260,   259,
      34,    33,   379,   380,   308,   303,   235,     0,   236,     0,
     237,     0,    31,   130,   157,   133,   157,   143,   145,   138,
     149,   153,   151,   129,   128,   144,   149,   135,   127,   155,
     155,   126,   157,   157,     0,   231,   106,   116,   117,   187,
       0,     0,   182,     0,   244,   214,   218,   215,     0,   419,
     159,     0,     0,   399,   403,   404,   398,     0,     0,   167,
       0,     0,     0,     0,    31,     0,     0,   101,     0,    80,
       0,    93,    54,    55,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    30,    87,    85,    89,   227,     0,   238,
     232,   233,   234,     0,   140,   139,     0,   131,   152,   136,
       0,   134,   132,     0,   146,   137,   141,   142,   108,   184,
     190,   193,     0,     0,     0,   414,     0,     0,   125,     0,
     409,     0,     0,   400,     0,   176,   176,   176,   176,   176,
     176,   176,   118,   165,   122,   269,   273,     0,    48,     0,
     103,    97,     0,    90,    56,    57,    58,    59,    60,    62,
      61,    96,   204,   261,     0,   249,     0,     0,     0,     0,
     191,     0,     0,     0,     0,     0,   161,     0,     0,     0,
     163,   158,   407,   406,   408,     0,   175,     0,     0,     0,
       0,     0,     0,     0,     0,   272,   102,    91,     0,     0,
     207,   156,   148,     0,   150,   154,   194,     0,   418,   416,
     417,     0,   160,   162,   164,   124,   172,   174,   168,   171,
     170,   169,   173,   166,   239,   250,     0,   192,   422,   423,
     420,   421,   426,   147,     0,     0,   413,     0,     0,   424,
       0,     0,     0,   425
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,   359,   320,   321,   322,   550,   323,
     552,   324,   429,   531,   532,   638,   325,   361,    28,    29,
     364,   365,    30,   174,   510,   511,   512,   604,   667,   671,
     669,   674,   664,   688,   741,   702,   703,   747,    31,   183,
     277,    32,    33,   368,   487,   612,   682,    34,   326,    36,
      37,    38,    39,   274,   457,   122,   206,   207,   381,   458,
     165,   362,   725,   162,   163,   377,   378,   493,   760,   210,
     327,   328,   567,   568,   280,   281,   411,   519,    40,   192,
     104,    41,   237,   233,   150,   228,   180,    42,   175,   176,
     184,   463,    43,   185,    44,   218,    45,   201,   202,    46,
     268,    65,   242,    47,    48,    49,    50,   115,   116,   194,
     288,    51,   204,    52,   100,   295,    53,   131,   132,   213,
     285,    54,   187,   286,    55,    56,    57,   263,   264,   391,
     626,   623,    58,   256,   257,   619,   687,   792,   796,   329,
     330,   151,   101,   331
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -518
static const yytype_int16 yypact[] =
{
     458,     4,    69,   -45,   -45,   -52,  -518,    52,  2009,  2009,
     132,  2043,  -105,   390,  -518,  2043,    34,  -518,   390,   -45,
      63,  1586,   206,    56,  2009,   160,   -34,  -518,  -518,  -518,
    -518,  -518,  -518,   117,  -518,   -30,  -518,  -518,    61,     2,
    -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  -518,  -518,  -518,  -518,   103,  -518,  -518,   201,
     230,   136,  2009,   276,  -518,  -518,  -518,   141,   276,  2009,
    -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  -518,   282,  -518,  -518,   282,   185,   276,  -518,
     130,  -518,  -518,  -518,   171,   179,  -518,   152,  -518,  -518,
     214,  -518,  -518,  -518,  -518,   -54,  -518,   258,   276,   -53,
    -518,   223,    36,  -518,    10,    10,  2072,   308,   270,  2072,
     324,   181,  -518,    10,  -518,  -518,    30,   227,  -518,   -11,
    -518,  -518,   -11,   195,   -11,  -518,   296,   210,   284,   205,
     209,   356,   233,   268,  -518,  -518,   458,  2009,    36,    36,
      36,   345,   101,   216,   245,  -518,  2043,  -518,  -518,  2072,
     235,  -518,     5,   387,  2009,   220,  -518,   323,   267,  -518,
    -518,  -518,   337,  1772,  -518,   241,   420,  -518,  -518,  -518,
    -518,  -518,  -518,  -518,  -518,  -518,  -518,  1801,   390,   171,
     283,  -518,   252,  1801,   357,  -518,   -48,  -518,  -518,  -518,
     870,  -518,  -518,  1564,  1564,    10,  2072,   276,   424,    10,
    2072,  1700,  1564,  2009,  2009,  2009,   445,  1564,  -518,  -518,
     -11,  -518,    50,  -518,  -518,   -11,   448,  -518,  -518,   -11,
     761,   402,  -518,  2072,  -518,    18,    35,    35,    35,  1564,
     279,   279,   392,  -518,  -518,  -518,   286,  -518,   453,   418,
     418,   418,    -7,   309,  -518,   436,  -518,  -518,  -518,   416,
     462,   276,   452,  1058,  -518,  -518,   463,   318,  1886,   198,
    1914,  -518,   469,   276,  -518,  -518,   325,  -518,   361,  -518,
    -518,  -518,  -518,  -518,  -518,  -518,   276,   276,  -518,   276,
    -518,   223,    82,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  1564,  1564,  1564,  -518,  1140,  1564,   473,   477,
    -518,  -518,  -518,   953,  -518,  -518,  -518,  -518,   -14,  -518,
     479,   482,  2623,  2623,  1564,    10,  -518,   522,  1564,    10,
    -518,  2623,   -11,   -11,  -518,  -518,  2623,  -518,   488,  -518,
     339,  -518,   492,  -518,  -518,  1246,  -518,  1352,  1458,   -18,
    2377,  1564,   495,   396,   -75,  -518,   515,  1033,   380,  -518,
      63,  -518,   525,  -518,   525,  -518,  2519,   354,  -518,  -518,
    -518,   -65,   438,  -518,  2072,    59,  -518,  2072,  2072,  2072,
    2009,  2072,   278,   522,  -518,  1987,  -518,   522,  1564,  2623,
    1671,   198,   505,  1772,  2009,  -518,   431,  -518,  1772,   431,
     431,   450,  2009,  -518,  2009,  -518,   420,   276,  -518,  -518,
     241,  -518,  1315,  -518,  -518,   364,  2550,   398,  2623,   391,
    -518,  2072,  1564,  1564,   264,  1564,  1564,  1564,  1564,  1564,
    1564,  1564,  1564,  1646,   516,   369,  1564,  1564,  1564,  1564,
    1564,  1564,  1564,  2043,  -518,  1857,   870,  -518,  -518,  1959,
    2623,  1564,  -518,  -518,  2623,  1564,  -518,  -518,   517,   555,
    -518,  1564,  2407,  1564,  2448,  1564,  2478,  -518,  1564,  2232,
    1564,  2575,  -518,  -518,  2072,  -518,  1564,   -17,  -518,   528,
      36,  -518,  -518,  -518,  1564,   279,   279,   279,  -518,   510,
    -518,  2232,    31,    62,  -518,   415,   418,  -518,  -518,   467,
     -16,  -518,  -518,  -518,  2623,   532,   198,  -518,  -518,  -518,
     196,  -518,  -518,  1772,  -518,  -518,  -518,   241,  1564,  -518,
    1564,    41,  -518,  -518,   827,  1315,  1564,  1646,   516,   791,
     791,   791,   791,   791,   791,   648,   886,  1646,  1646,  -518,
     300,  1140,  -518,  -518,  -518,  -518,  -518,   348,   389,   389,
     534,   534,   534,   534,  -518,  -518,   267,   -71,   198,  -518,
    -518,  -518,  2623,  2623,  -518,  -518,  2623,  1564,  2623,  1564,
    2623,  1564,  2623,  -518,   536,  -518,   536,  -518,  -518,  -518,
     541,   461,   543,  -518,  -518,  -518,   541,  -518,  -518,   546,
     546,  -518,   536,   536,   548,  2623,  -518,  -518,  2623,     4,
    2072,  1564,   397,   870,  -518,  -518,  -518,  -518,   588,   460,
    -518,   165,   167,  -518,  -518,  -518,  -518,  2043,   560,   483,
    1987,  2009,  1564,   358,  2599,  2243,  1564,  -518,   523,   886,
     529,  -518,  -518,  -518,  1646,  1646,  1646,  1646,  1646,  1646,
    1646,  1646,   -15,  2623,  -518,  -518,  -518,   101,  1772,   509,
    2623,  2623,  2623,   599,  -518,  -518,   600,  -518,  -518,  -518,
     601,  -518,  -518,   603,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  2623,   -12,   570,   -46,  -518,   589,   433,    26,   604,
    -518,   607,    59,  -518,  2072,   596,   596,   596,   596,   596,
     596,   596,   435,  -518,  -518,  -518,  2623,  1564,  -518,  1564,
    2623,  -518,  1646,   682,   434,   434,   583,   583,   583,   583,
    -518,  -518,  -518,   198,   569,   535,   585,    -9,   615,   620,
    -518,  1564,  1564,  1772,    93,   638,  -518,   653,    59,   562,
    -518,  -518,  -518,  -518,  -518,    -8,  -518,   663,   526,   665,
     666,   667,   668,   680,   483,  2623,  2623,   682,  1564,  1564,
    -518,  -518,  -518,   669,  -518,  -518,  2623,    -6,  -518,  -518,
    -518,   176,  -518,  -518,  -518,  -518,  -518,  -518,  -518,  -518,
    -518,  -518,  -518,  -518,   499,  2623,   649,  -518,  -518,  -518,
    -518,  -518,   -13,  -518,   671,   681,  -518,   687,   700,  -518,
     545,   697,   701,  -518
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -518,  -518,  -518,   568,  -307,  -518,  -375,  -386,  -517,   261,
     187,  -518,  -518,  -518,   197,  -518,   705,  -518,   -20,    -1,
    -518,   247,  -518,  -518,  -518,    99,   350,   234,   142,  -518,
    -518,   140,  -516,  -518,  -518,  -518,   -10,  -204,  -518,  -518,
    -518,     8,  -518,  -518,    48,  -518,    11,  -100,     0,     6,
    -518,   170,   212,  -336,   584,   375,  -518,   447,  -229,    92,
     -84,  -518,  -518,  -518,  -518,  -518,   256,  -518,  -518,  -145,
     295,   139,  -518,  -180,    32,   478,  -518,   -69,  -518,  -518,
    -518,  -518,  -518,  -518,  -518,   -92,   657,  -518,  -518,   485,
      17,  -156,  -518,  -260,  -518,   611,  -518,   464,  -518,  -518,
    -518,    86,  -518,  -518,  -518,  -518,  -518,   740,   561,  -518,
     557,  -518,  -518,  -518,     1,  -518,  -518,  -518,   542,  -106,
     352,  -518,  -518,  -518,  -518,  -518,  -518,  -518,   384,   226,
    -518,  -518,  -518,  -518,   388,  -518,  -518,  -518,  -518,   -19,
      29,  -518,  -312,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -432
static const yytype_int16 yytable[] =
{
      35,    59,   133,   279,   191,    95,    95,    60,   102,   425,
     499,   454,   102,   246,   247,   248,   117,   226,   134,   214,
     640,    95,   382,   477,   609,   629,   721,   222,   485,   730,
     642,   643,   762,   775,   211,   787,   736,    94,    94,   420,
      93,    96,   733,  -229,     1,   794,   737,   155,   300,   495,
     229,  -196,   231,    94,   171,   386,   153,   549,   367,    95,
     223,   197,   203,   303,   304,   305,    95,   306,   307,   308,
     665,   309,   310,   311,   455,     1,   158,   159,   160,   253,
     172,   208,   103,  -229,   188,   177,   676,   677,   273,   164,
      66,    94,   273,   250,   170,    67,   401,   738,    94,   294,
     251,   178,   265,   189,    35,   120,    68,   215,   621,   334,
     219,   209,   190,   338,   266,   484,   348,   624,   224,   658,
     636,    64,  -431,   134,  -429,   496,   134,   713,   714,   715,
     716,   717,   718,   719,   720,   200,   198,   198,   347,    20,
      69,   565,   301,   349,   456,   369,   768,   351,   390,   739,
     258,   549,   227,    20,    95,   156,    35,   527,   121,  -196,
     154,   549,   549,   102,   795,   212,   134,   255,   383,   622,
     370,    95,   478,   610,   630,   478,   456,   161,   731,   291,
      95,   763,   610,   278,   731,   689,    94,   691,   267,   245,
     625,  -229,   118,   740,    95,   757,   319,   335,   292,    35,
      95,   339,   133,    94,   769,   530,   270,   293,   250,   135,
     152,     1,   282,   134,    61,   251,    62,   134,   134,   157,
      95,    95,    95,   516,   366,   166,   289,    63,   520,   461,
     657,   659,   289,   465,   336,   770,   690,   508,   692,   173,
     134,   513,   167,     7,   652,    35,   371,   371,   371,   336,
     466,   467,    94,    94,    94,   342,   343,   344,   549,   549,
     549,   549,   549,   549,   549,   549,   615,   616,   617,   136,
     137,   168,    14,    95,   169,    95,   400,    95,   259,    97,
     171,   260,    60,   182,   379,   406,   179,   406,   177,   186,
      98,   380,   536,   537,   538,   407,   138,   407,    17,   408,
     415,   408,   409,   164,   409,   282,    20,   405,   193,   413,
     195,   632,   261,   418,   200,   693,   427,   744,   430,   644,
     102,   259,    60,  -240,   260,   139,   549,   410,    24,   410,
    -240,   196,   645,   646,   647,   648,   649,   650,   651,   140,
     521,   522,   141,   633,   788,   613,   199,   205,   488,   789,
     216,   790,   142,   143,   144,   261,   654,   217,   655,   656,
     791,   262,   145,   773,   134,   258,   220,    59,   501,   502,
     503,   221,   505,    60,   225,   230,   501,   554,   146,   555,
     556,   134,   147,   232,   134,   134,   134,    95,   134,   557,
     235,   236,   134,   238,   148,   239,   240,    95,   241,   249,
      95,    95,   254,   278,   506,    95,   243,   269,   278,    95,
     271,    95,   533,  -206,  -206,  -206,   372,   374,   375,    94,
     272,   275,   504,   448,   449,   450,   451,   452,   134,   405,
     273,   283,   282,   517,   284,   105,   106,   282,   296,   167,
     571,   524,   297,    94,   553,   299,   525,   406,   337,   345,
     102,   784,    95,   350,   107,   278,   134,   407,   373,   373,
     373,   408,   108,   363,   409,   366,    70,   109,   647,   648,
     649,   650,   651,   707,   332,   333,   384,   385,   723,   164,
     386,   134,   110,   341,   282,   387,   388,   389,   346,   410,
     393,   111,   748,   749,   750,   751,   752,   753,     1,   392,
     394,   360,   395,   276,     2,  -206,   397,     3,   403,   679,
     376,   414,  -206,     1,  -206,   416,   417,   112,     4,   431,
      95,   459,     5,   278,  -430,   113,   462,     6,   468,   469,
       7,     8,     9,   470,   399,    10,   482,   483,   553,   486,
     489,    11,   160,    12,   494,   497,   515,   114,   712,   518,
      13,   427,   282,   523,   528,   530,   551,    60,   574,    14,
     575,   645,   646,   647,   648,   649,   650,   651,   611,   618,
     627,   628,   452,   422,   423,   424,   663,   426,   428,   631,
      15,   666,   668,   670,    16,    17,   673,   683,    18,   678,
      19,   680,   685,    20,   686,   460,    21,    22,    20,   464,
     694,    23,   724,   711,   726,   727,   728,   134,   729,    35,
     732,   501,   735,   734,   742,    24,   472,   743,   474,   476,
     746,   651,   481,   758,   102,   754,   761,   134,    95,   759,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   695,   696,   697,    95,   764,   698,   278,   514,
     705,   765,   771,   772,   699,   700,   774,   776,   701,   778,
     777,   779,   780,   781,   786,   488,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,   282,   782,   478,
     793,   134,   799,   534,   535,   797,   539,   540,   541,   542,
     543,   544,   545,   546,   800,   798,   803,   558,   559,   560,
     561,   562,   563,   564,   645,   646,   647,   648,   649,   650,
     651,   802,   572,   801,   244,   641,   573,   149,   637,   704,
      95,   607,   576,   278,   578,   620,   580,   500,   672,   582,
     675,   605,   745,   767,   783,   490,   252,   608,   421,   722,
     614,   569,   684,   181,   402,   376,   396,   234,   119,   290,
     298,   419,   282,   340,   302,   303,   304,   305,   526,   306,
     307,   308,   498,   309,   310,   311,   507,     0,     0,     0,
       0,   312,     0,     0,     0,     0,     0,     0,     0,   634,
       0,   635,     0,   313,   314,   352,     0,   639,     0,     0,
       0,   316,   353,     0,     0,     0,   354,     0,     0,     0,
       0,     0,   653,     0,   355,     0,     0,   317,   441,   442,
     443,   444,   445,   446,   447,   448,   449,   450,   451,   452,
       0,     0,     0,     0,     0,     0,   356,     0,   660,     0,
     661,     0,   662,     0,     0,   318,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,   357,     0,     0,     0,
       0,     0,   681,   302,   303,   304,   305,     0,   306,   307,
     308,     0,   309,   310,   311,     0,     0,     0,     0,     0,
     312,     0,     0,   706,     0,     0,     0,   710,   319,     0,
       0,     0,   313,   314,   315,     0,     0,     0,     0,     0,
     316,     0,     0,     0,   358,   443,   444,   445,   446,   447,
     448,   449,   450,   451,   452,     0,   317,     0,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,     0,     0,     0,   318,     0,    99,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   755,     0,
     756,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   766,   681,     0,     0,     0,     0,     0,     0,
     453,     0,     0,     0,     0,     0,     0,   319,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   653,
     785,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,   302,   303,   304,   305,   398,   306,   307,   308,     0,
     309,   310,   311,     1,     0,     0,     0,     0,   312,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     313,   314,     0,     0,     0,     0,     0,     0,   316,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   317,     0,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   318,   302,   303,   304,   305,     0,   306,   307,
     308,     0,   309,   310,   311,     0,     0,     0,     0,     0,
     312,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,   313,   314,     0,     0,     0,     0,     0,     0,
     316,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   319,   317,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,     0,   318,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,     0,     0,   302,
     303,   304,   305,     0,   306,   307,   308,     0,   309,   310,
     311,     0,     0,     0,     0,     0,   312,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,   319,   313,   314,
       0,     0,     0,     0,     0,     0,   316,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   317,     0,     0,     0,     0,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
     318,     0,     0,     0,   471,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,     0,   302,   303,   304,   305,     0,
     306,   307,   308,     0,   309,   310,   311,     0,     0,     0,
       0,     0,   312,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   319,   313,   314,     0,     0,     0,     0,
       0,     0,   316,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   317,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,   318,     0,     0,     0,
     473,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   302,   303,   304,   305,     0,   306,   307,   308,     0,
     309,   310,   311,     0,     0,     0,     0,     0,   312,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   319,
     313,   314,     0,     0,     0,     0,     0,     0,   316,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   317,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,     0,   318,     0,     0,     0,   475,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   302,   303,   304,
     305,     0,   306,   307,   308,     0,   309,   310,   311,     0,
       0,     0,     0,     0,   312,     0,     0,     0,     0,   123,
       0,     0,     0,     0,     0,   319,   313,   314,     0,   124,
     125,     0,     0,     0,   316,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     317,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,     0,   318,   302,
     303,   304,   305,     0,   306,   307,   308,     0,   309,   310,
     311,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,     0,   126,   127,   547,   548,
       0,     0,     0,     0,     0,     0,   316,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   319,   317,   123,     0,     0,   128,     0,     0,     0,
       0,     0,   167,   124,   125,     0,     0,     0,   404,     0,
       0,     0,   129,   130,     0,     0,     0,     0,     0,     0,
     318,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    70,     0,     0,     0,     0,
       0,     0,     0,   319,     0,     0,     0,     0,     0,     0,
     126,   127,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,   276,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   287,   129,   130,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      70,     0,     0,     0,     0,     0,     0,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    70,
       0,     0,     0,     0,     0,     0,     0,   276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   404,     0,   566,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   412,   123,     0,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
     123,     0,     0,   570,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    99,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   123,     0,     0,     0,     0,
       0,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,     0,     0,     0,     0,     0,     0,     0,
     509,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     0,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,     0,     0,     0,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   583,   584,   585,     0,     0,     0,     0,   586,
       0,     0,     0,     0,     0,     0,     0,   587,     0,   588,
     589,     0,   590,     0,     0,     0,     0,     0,   591,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   592,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   593,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   594,     0,   595,   596,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   597,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   598,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   599,   600,   601,     0,     0,     0,     0,     0,
       0,     0,   709,   602,   603,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,     0,     0,     0,     0,
       0,     0,     0,     0,   479,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   450,   451,   452,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   480,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,     0,     0,     0,
       0,     0,     0,     0,     0,   577,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,   450,   451,   452,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   579,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,     0,     0,
       0,     0,     0,     0,     0,     0,   581,   491,   432,   433,
     434,   435,   436,   437,   438,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,   450,   451,   452,     0,
       0,   529,   492,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   450,   451,   452,     0,     0,   606,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,     0,     0,
     708,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-518)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     1,    21,   183,   104,     8,     9,     1,    11,   316,
     385,   323,    15,   158,   159,   160,    15,    28,    21,   125,
     537,    24,   251,    41,    41,    41,    41,   133,   364,    41,
     547,   548,    41,    41,    24,    41,    10,     8,     9,   299,
       8,     9,    88,    41,    40,    58,    20,    81,    96,   114,
     142,    81,   144,    24,     4,    62,    24,   443,    40,    62,
      30,   115,   115,     4,     5,     6,    69,     8,     9,    10,
     586,    12,    13,    14,    88,    40,    15,    16,    17,   163,
      63,    45,   187,    81,   104,    68,   602,   603,   163,    87,
       4,    62,   163,   107,    62,   147,   276,    71,    69,   199,
     114,    69,    97,   104,   104,    19,   158,   126,    77,   215,
     129,    75,   104,   219,   109,   190,    66,    55,    88,   190,
      79,   166,    40,   126,    42,   190,   129,   644,   645,   646,
     647,   648,   649,   650,   651,   118,   190,   190,   230,   135,
      88,   453,   190,   235,   190,   245,    53,   239,   155,   123,
     169,   537,   163,   135,   157,   189,   156,   417,    95,   189,
       0,   547,   548,   166,   177,   155,   169,   166,   252,   138,
     135,   174,   190,   190,   190,   190,   190,   116,   190,   199,
     183,   190,   190,   183,   190,    20,   157,    20,   183,   157,
     128,   189,   158,   167,   197,   712,   137,   216,   199,   199,
     203,   220,   221,   174,   111,   164,   174,   199,   107,     3,
     154,    40,   183,   216,   145,   114,   147,   220,   221,   102,
     223,   224,   225,   403,   243,   122,   197,   158,   408,   335,
     566,   567,   203,   339,   217,   142,    71,   393,    71,    98,
     243,   397,    41,    72,   551,   245,   246,   247,   248,   232,
     342,   343,   223,   224,   225,   223,   224,   225,   644,   645,
     646,   647,   648,   649,   650,   651,   495,   496,   497,    63,
      64,    41,   101,   276,   138,   278,   276,   280,    43,   147,
       4,    46,   276,    98,     5,    89,     4,    89,   271,   159,
     158,    12,    28,    29,    30,    99,    90,    99,   127,   103,
     283,   103,   106,    87,   106,   276,   135,   278,   129,   280,
     158,   115,    77,   296,   297,   627,   316,   692,   318,    19,
     323,    43,   316,   107,    46,   119,   712,   131,   157,   131,
     114,   117,    32,    33,    34,    35,    36,    37,    38,   133,
     409,   410,   136,   523,   168,   490,    88,   124,   367,   173,
      42,   175,   146,   147,   148,    77,     8,    87,    10,    11,
     184,   126,   156,   738,   367,   384,    42,   367,   387,   388,
     389,   190,   391,   367,   147,   180,   395,     8,   172,    10,
      11,   384,   176,    87,   387,   388,   389,   390,   391,    20,
     180,   107,   395,   188,   188,   186,    40,   400,   165,    54,
     403,   404,   157,   403,   126,   408,   138,    20,   408,   412,
     190,   414,   431,    15,    16,    17,   246,   247,   248,   390,
      97,    84,   390,    34,    35,    36,    37,    38,   431,   400,
     163,   190,   403,   404,    14,    45,    46,   408,   155,    41,
     459,   412,   190,   414,   444,    88,   414,    89,    24,     4,
     453,   758,   455,     5,    64,   455,   459,    99,   246,   247,
     248,   103,    72,    61,   106,   484,     3,    77,    34,    35,
      36,    37,    38,   115,   213,   214,   190,    24,   658,    87,
      62,   484,    92,   222,   455,   259,   260,   261,   227,   131,
      54,   101,   696,   697,   698,   699,   700,   701,    40,   190,
      84,   240,    40,    40,    46,   107,    54,    49,   190,   609,
     249,    42,   114,    40,   116,   190,   155,   127,    60,    42,
     523,    42,    64,   523,    42,   135,     4,    69,    40,   190,
      72,    73,    74,    41,   273,    77,    41,   141,   538,    24,
     160,    83,    17,    85,   190,   107,    41,   157,    19,   118,
      92,   551,   523,   103,   190,   164,    40,   551,    41,   101,
       5,    32,    33,    34,    35,    36,    37,    38,    40,    59,
     155,   104,    38,   312,   313,   314,    40,   316,   317,    47,
     122,    40,   121,    40,   126,   127,    40,   190,   130,    41,
     132,   610,     4,   135,   134,   334,   138,   139,   135,   338,
      40,   143,    93,    80,     5,     5,     5,   610,     5,   609,
      40,   630,   179,    24,    10,   157,   355,    10,   357,   358,
      24,    38,   361,    54,   627,   190,    41,   630,   631,    94,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   169,   170,   171,   658,    41,   174,   658,   398,
     631,    41,    24,    10,   181,   182,   104,     4,   185,     4,
     144,     5,     5,     5,     5,   694,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,   658,     8,   190,
      41,   694,     5,   432,   433,    24,   435,   436,   437,   438,
     439,   440,   441,   442,     4,    24,     5,   446,   447,   448,
     449,   450,   451,   452,    32,    33,    34,    35,    36,    37,
      38,    24,   461,   178,   156,   538,   465,    22,   531,   630,
     733,   484,   471,   733,   473,   501,   475,   387,   596,   478,
     600,   480,   694,   732,   754,   370,   162,   486,   301,   657,
     494,   456,   613,    96,   276,   494,   271,   146,    18,   198,
     203,   297,   733,   221,     3,     4,     5,     6,   416,     8,
       9,    10,   384,    12,    13,    14,   392,    -1,    -1,    -1,
      -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,
      -1,   530,    -1,    32,    33,    34,    -1,   536,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,   551,    -1,    53,    -1,    -1,    56,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    -1,   577,    -1,
     579,    -1,   581,    -1,    -1,    84,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,   105,    -1,    -1,    -1,
      -1,    -1,   611,     3,     4,     5,     6,    -1,     8,     9,
      10,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,   632,    -1,    -1,    -1,   636,   137,    -1,
      -1,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,   153,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    56,    -1,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
      -1,    -1,    -1,    -1,    84,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   707,    -1,
     709,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,   731,   732,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,   137,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   758,
     759,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    -1,
      12,    13,    14,    40,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    84,     3,     4,     5,     6,    -1,     8,     9,
      10,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,    -1,
      -1,    -1,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   137,    56,    -1,    -1,    -1,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    84,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135,    -1,   137,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    -1,    -1,    -1,    -1,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    -1,
      84,    -1,    -1,    -1,    88,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,     3,     4,     5,     6,    -1,
       8,     9,    10,    -1,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,    32,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    -1,    84,    -1,    -1,    -1,
      88,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,
      32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,    -1,    84,    -1,    -1,    -1,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,     8,     9,    10,    -1,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,   137,    32,    33,    -1,    13,
      14,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,    -1,    84,     3,
       4,     5,     6,    -1,     8,     9,    10,    -1,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    90,    91,    32,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   137,    56,     3,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    41,    13,    14,    -1,    -1,    -1,    47,    -1,
      -1,    -1,   136,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      84,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    34,   136,   137,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
       3,    -1,    -1,    -1,    -1,    -1,    -1,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    78,    -1,    -1,    -1,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,    47,     3,    -1,    -1,    -1,    -1,    -1,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
       3,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,     3,    -1,    -1,    -1,
      -1,    -1,    -1,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,     3,    -1,    -1,    -1,    -1,
      -1,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,    -1,    -1,
      -1,    -1,    -1,    -1,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    50,    51,    52,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    67,
      68,    -1,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   110,    -1,   112,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   150,   151,   152,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   161,   162,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    48,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    41,    73,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    41,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      41,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    40,    46,    49,    60,    64,    69,    72,    73,    74,
      77,    83,    85,    92,   101,   122,   126,   127,   130,   132,
     135,   138,   139,   143,   157,   192,   193,   194,   209,   210,
     213,   229,   232,   233,   238,   239,   240,   241,   242,   243,
     269,   272,   278,   283,   285,   287,   290,   294,   295,   296,
     297,   302,   304,   307,   312,   315,   316,   317,   323,   239,
     240,   145,   147,   158,   166,   292,   292,   147,   158,    88,
       3,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   265,   331,   334,   265,   147,   158,     3,
     305,   333,   334,   187,   271,    45,    46,    64,    72,    77,
      92,   101,   127,   135,   157,   298,   299,   305,   158,   298,
     292,    95,   246,     3,    13,    14,    90,    91,   120,   136,
     137,   308,   309,   330,   334,     3,    63,    64,    90,   119,
     133,   136,   146,   147,   148,   156,   172,   176,   188,   207,
     275,   332,   154,   265,     0,    81,   189,   102,    15,    16,
      17,   116,   254,   255,    87,   251,   122,    41,    41,   138,
     265,     4,   281,    98,   214,   279,   280,   281,   265,     4,
     277,   277,    98,   230,   281,   284,   159,   313,   209,   210,
     232,   238,   270,   129,   300,   158,   117,   115,   190,    88,
     281,   288,   289,   115,   303,   124,   247,   248,    45,    75,
     260,    24,   155,   310,   310,   330,    42,    87,   286,   330,
      42,   190,   310,    30,    88,   147,    28,   163,   276,   276,
     180,   276,    87,   274,   286,   180,   107,   273,   188,   186,
      40,   165,   293,   138,   194,   265,   260,   260,   260,    54,
     107,   114,   245,   251,   157,   305,   324,   325,   330,    43,
      46,    77,   126,   318,   319,    97,   109,   183,   291,    20,
     265,   190,    97,   163,   244,    84,    40,   231,   239,   264,
     265,   266,   331,   190,    14,   311,   314,    34,   301,   331,
     299,   209,   210,   232,   238,   306,   155,   190,   301,    88,
      96,   190,     3,     4,     5,     6,     8,     9,    10,    12,
      13,    14,    20,    32,    33,    34,    40,    56,    84,   137,
     196,   197,   198,   200,   202,   207,   239,   261,   262,   330,
     331,   334,   200,   200,   310,   330,   281,    24,   310,   330,
     309,   200,   265,   265,   265,     4,   200,   276,    66,   276,
       5,   276,    34,    41,    45,    53,    75,   105,   153,   195,
     200,   208,   252,    61,   211,   212,   330,    40,   234,   238,
     135,   239,   242,   243,   242,   242,   200,   256,   257,     5,
      12,   249,   249,   251,   190,    24,    62,   320,   320,   320,
     155,   320,   190,    54,    84,    40,   280,    54,     7,   200,
     239,   264,   266,   190,    47,   331,    89,    99,   103,   106,
     131,   267,    47,   331,    42,   281,   190,   155,   281,   288,
     284,   248,   200,   200,   200,   195,   200,   239,   200,   203,
     239,    42,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    47,   333,    88,   190,   245,   250,    42,
     200,   310,     4,   282,   200,   310,   276,   276,    40,   190,
      41,    88,   200,    88,   200,    88,   200,    41,   190,    47,
      88,   200,    41,   141,   190,   244,    24,   235,   330,   160,
     246,    48,    73,   258,   190,   114,   190,   107,   325,   197,
     217,   330,   330,   330,   265,   330,   126,   319,   282,   123,
     215,   216,   217,   282,   200,    41,   264,   331,   118,   268,
     264,   268,   268,   103,   331,   265,   311,   284,   190,    41,
     164,   204,   205,   330,   200,   200,    28,    29,    30,   200,
     200,   200,   200,   200,   200,   200,   200,    32,    33,   198,
     199,    40,   201,   239,     8,    10,    11,    20,   200,   200,
     200,   200,   200,   200,   200,   333,    78,   263,   264,   261,
      34,   330,   200,   200,    41,     5,   200,    88,   200,    88,
     200,    88,   200,    50,    51,    52,    57,    65,    67,    68,
      70,    76,    86,   100,   110,   112,   113,   125,   140,   150,
     151,   152,   161,   162,   218,   200,    41,   212,   200,    41,
     190,    40,   236,   260,   257,   249,   249,   249,    59,   326,
     218,    77,   138,   322,    55,   128,   321,   155,   104,    41,
     190,    47,   115,   264,   200,   200,    79,   205,   206,   200,
     199,   201,   199,   199,    19,    32,    33,    34,    35,    36,
      37,    38,   195,   200,     8,    10,    11,   244,   190,   244,
     200,   200,   200,    40,   223,   223,    40,   219,   121,   221,
      40,   220,   219,    40,   222,   222,   223,   223,    41,   238,
     330,   200,   237,   190,   262,     4,   134,   327,   224,    20,
      71,    20,    71,   333,    40,   169,   170,   171,   174,   181,
     182,   185,   226,   227,   216,   331,   200,   115,    41,   149,
     200,    80,    19,   199,   199,   199,   199,   199,   199,   199,
     199,    41,   250,   264,    93,   253,     5,     5,     5,     5,
      41,   190,    40,    88,    24,   179,    10,    20,    71,   123,
     167,   225,    10,    10,   197,   235,    24,   228,   228,   228,
     228,   228,   228,   228,   190,   200,   200,   199,    54,    94,
     259,    41,    41,   190,    41,    41,   200,   237,    53,   111,
     142,    24,    10,   197,   104,    41,     4,   144,     4,     5,
       5,     5,     8,   227,   195,   200,     5,    41,   168,   173,
     175,   184,   328,    41,    58,   177,   329,    24,    24,     5,
       4,   178,    24,     5
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (&yylloc, result, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location, result); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseResult* result;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (result);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ParseResult* result)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, result)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    ParseResult* result;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ParseResult* result)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, result)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    ParseResult* result;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , result);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, result); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ParseResult* result)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, result)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    ParseResult* result;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {
      case 3: /* NAME */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 4: /* STRING */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 5: /* INTNUM */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 6: /* DATE_VALUE */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 7: /* HINT_VALUE */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 8: /* BOOL */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 9: /* APPROXNUM */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 10: /* NULLX */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 11: /* UNKNOWN */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 12: /* QUESTIONMARK */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 13: /* SYSTEM_VARIABLE */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 14: /* TEMP_VARIABLE */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 192: /* sql_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 193: /* stmt_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 194: /* stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 195: /* expr_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 196: /* column_ref */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 197: /* expr_const */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 198: /* simple_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 199: /* arith_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 200: /* expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 201: /* in_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 202: /* case_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 203: /* case_arg */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 204: /* when_clause_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 205: /* when_clause */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 206: /* case_default */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 207: /* func_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 208: /* distinct_or_all */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 209: /* delete_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 210: /* update_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 211: /* update_asgn_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 212: /* update_asgn_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 213: /* create_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 214: /* opt_if_not_exists */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 215: /* table_element_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 216: /* table_element */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 217: /* column_definition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 218: /* data_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 219: /* opt_decimal */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 220: /* opt_float */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 221: /* opt_precision */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 222: /* opt_time_precision */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 223: /* opt_char_length */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 224: /* opt_column_attribute_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 225: /* column_attribute */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 226: /* opt_table_option_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 227: /* table_option */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 228: /* opt_equal_mark */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 229: /* drop_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 230: /* opt_if_exists */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 231: /* table_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 232: /* insert_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 233: /* replace_or_insert */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 234: /* opt_insert_columns */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 235: /* column_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 236: /* insert_vals_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 237: /* insert_vals */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 238: /* select_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 239: /* select_with_parens */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 240: /* select_no_parens */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 241: /* no_table_select */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 242: /* select_clause */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 243: /* simple_select */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 244: /* opt_where */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 245: /* select_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 246: /* opt_hint */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 247: /* opt_hint_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 248: /* hint_option */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 249: /* limit_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 250: /* opt_select_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 251: /* opt_for_update */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 252: /* parameterized_trim */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 253: /* opt_groupby */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 254: /* opt_order_by */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 255: /* order_by */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 256: /* sort_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 257: /* sort_key */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 258: /* opt_asc_desc */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 259: /* opt_having */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 260: /* opt_distinct */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 261: /* projection */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 262: /* select_expr_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 263: /* from_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 264: /* table_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 265: /* relation_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 266: /* joined_table */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 267: /* join_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 268: /* join_outer */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 269: /* explain_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 270: /* explainable_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 271: /* opt_verbose */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 272: /* show_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 273: /* opt_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 274: /* opt_for_grant_user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 276: /* opt_show_condition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 277: /* opt_like_condition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 278: /* create_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 279: /* user_specification_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 280: /* user_specification */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 281: /* user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 282: /* password */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 283: /* drop_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 284: /* user_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 285: /* set_password_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 286: /* opt_for_user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 287: /* rename_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 288: /* rename_info */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 289: /* rename_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 290: /* lock_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 291: /* lock_spec */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 292: /* opt_work */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 294: /* begin_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 295: /* commit_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 296: /* rollback_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 297: /* grant_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 298: /* priv_type_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 299: /* priv_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 300: /* opt_privilege */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 301: /* priv_level */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 302: /* revoke_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 303: /* opt_on_priv_level */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 304: /* prepare_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 305: /* stmt_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 306: /* preparable_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 307: /* variable_set_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 308: /* var_and_val_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 309: /* var_and_val */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 310: /* to_or_eq */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 311: /* argument */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 312: /* execute_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 313: /* opt_using_args */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 314: /* argument_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 315: /* deallocate_prepare_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 316: /* deallocate_or_drop */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 317: /* alter_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 318: /* alter_column_actions */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 319: /* alter_column_action */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 320: /* opt_column */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 322: /* alter_column_behavior */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 323: /* alter_system_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 324: /* alter_system_actions */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 325: /* alter_system_action */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 326: /* opt_comment */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 328: /* server_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 329: /* opt_cluster_or_address */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 330: /* column_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 331: /* relation_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 332: /* function_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 333: /* column_label */

        {destroy_tree(((*yyvaluep).node));};

        break;

      default:
        break;
    }
}




/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (ParseResult* result)
#else
int
yyparse (result)
    ParseResult* result;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;


#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
static YYSTYPE yyval_default;
# define YY_INITIAL_VALUE(Value) = Value
#endif
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc = yyloc_default;


    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_STMT_LIST, (yyvsp[(1) - (2)].node));
      result->result_tree_ = (yyval.node);
      YYACCEPT;
    }
    break;

  case 3:

    {
      if ((yyvsp[(3) - (3)].node) != NULL)
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      else
        (yyval.node) = (yyvsp[(1) - (3)].node);
    }
    break;

  case 4:

    {
      (yyval.node) = ((yyvsp[(1) - (1)].node) != NULL) ? (yyvsp[(1) - (1)].node) : NULL;
    }
    break;

  case 5:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 6:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 7:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 8:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 9:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 10:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 11:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 12:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 13:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 14:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 15:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 16:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 17:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 18:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 19:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 20:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 21:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 22:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 23:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 24:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 25:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 26:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 27:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 28:

    {(yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 29:

    { (yyval.node) = NULL; }
    break;

  case 30:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 31:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 32:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 33:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NAME_FIELD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_column);
    }
    break;

  case 34:

    {
      ParseNode *node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_STAR);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NAME_FIELD, 2, (yyvsp[(1) - (3)].node), node);
    }
    break;

  case 35:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 36:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 37:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 38:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 39:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 40:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 41:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 42:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 43:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 44:

    { (yyvsp[(3) - (3)].node)->type_ = T_SYSTEM_VARIABLE; (yyval.node) = (yyvsp[(3) - (3)].node); }
    break;

  case 45:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 46:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 47:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 48:

    {
      ParseNode *node = NULL;
      malloc_non_terminal_node(node, result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node));
      merge_nodes((yyval.node), result->malloc_pool_, T_EXPR_LIST, node);
    }
    break;

  case 49:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
      /*
      yyerror(&@1, result, "CASE expression is not supported yet!");
      YYABORT;
      */
    }
    break;

  case 50:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 51:

    {
    	(yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 52:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_EXISTS, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 53:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 54:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_POS, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 55:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NEG, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 56:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_ADD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 57:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MINUS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 58:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MUL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 59:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_DIV, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 60:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_REM, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 61:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_POW, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 62:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MOD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 63:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 64:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_POS, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 65:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NEG, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 66:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_ADD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 67:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MINUS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 68:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MUL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 69:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_DIV, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 70:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_REM, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 71:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_POW, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 72:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_MOD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 73:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 74:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LT, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 75:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_EQ, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 76:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_GE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 77:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_GT, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 78:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 79:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LIKE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 80:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NOT_LIKE, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node)); }
    break;

  case 81:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_AND, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 82:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_OR, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 83:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NOT, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 84:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 85:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS_NOT, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 86:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 87:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS_NOT, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 88:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 89:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IS_NOT, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 90:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_BTW, 3, (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 91:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NOT_BTW, 3, (yyvsp[(1) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 92:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_IN, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 93:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NOT_IN, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 94:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_CNN, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 95:

    {
    	(yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 96:

    { merge_nodes((yyval.node), result->malloc_pool_, T_EXPR_LIST, (yyvsp[(2) - (3)].node)); }
    break;

  case 97:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_WHEN_LIST, (yyvsp[(3) - (5)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CASE, 3, (yyvsp[(2) - (5)].node), (yyval.node), (yyvsp[(4) - (5)].node));
    }
    break;

  case 98:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 99:

    { (yyval.node) = NULL; }
    break;

  case 100:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 101:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); }
    break;

  case 102:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_WHEN, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 103:

    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 104:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_NULL); }
    break;

  case 105:

    {
      if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "count") != 0)
      {
        yyerror(&(yylsp[(1) - (4)]), result, "Only COUNT function can be with '*' parameter!");
        YYABORT;
      }
      else
      {
        ParseNode* node = NULL;
        malloc_terminal_node(node, result->malloc_pool_, T_STAR);
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_COUNT, 1, node);
      }
    }
    break;

  case 106:

    {
      if (strcasecmp((yyvsp[(1) - (5)].node)->str_value_, "count") == 0)
      {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_COUNT, 2, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (5)].node)->str_value_, "sum") == 0)
      {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SUM, 2, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (5)].node)->str_value_, "max") == 0)
      {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_MAX, 2, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (5)].node)->str_value_, "min") == 0)
      {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_MIN, 2, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (5)].node)->str_value_, "avg") == 0)
      {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_AVG, 2, (yyvsp[(3) - (5)].node), (yyvsp[(4) - (5)].node));
      }
      else
      {
        yyerror(&(yylsp[(1) - (5)]), result, "Wrong system function with 'DISTINCT/ALL'!");
        YYABORT;
      }
    }
    break;

  case 107:

    {
      if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "count") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "COUNT function only support 1 parameter!");
          YYABORT;
        }
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_COUNT, 2, NULL, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "sum") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "SUM function only support 1 parameter!");
          YYABORT;
        }
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SUM, 2, NULL, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "max") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "MAX function only support 1 parameter!");
          YYABORT;
        }
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_MAX, 2, NULL, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "min") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "MIN function only support 1 parameter!");
          YYABORT;
        }
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_MIN, 2, NULL, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "avg") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "AVG function only support 1 parameter!");
          YYABORT;
        }
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_AVG, 2, NULL, (yyvsp[(3) - (4)].node));
      }
      else if (strcasecmp((yyvsp[(1) - (4)].node)->str_value_, "trim") == 0)
      {
        if ((yyvsp[(3) - (4)].node)->type_ == T_LINK_NODE)
        {
          yyerror(&(yylsp[(1) - (4)]), result, "TRIM function syntax error! TRIM don't take %d params", (yyvsp[(3) - (4)].node)->num_child_);
          YYABORT;
        }
        else
        {
          ParseNode* default_type = NULL;
          malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
          default_type->value_ = 0;
          ParseNode* default_operand = NULL;
          malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
          default_operand->str_value_ = " "; /* blank for default */
          default_operand->value_ = strlen(default_operand->str_value_);
          ParseNode *params = NULL;
          malloc_non_terminal_node(params, result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, (yyvsp[(3) - (4)].node));
          malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SYS, 2, (yyvsp[(1) - (4)].node), params);
        }
      }
      else  /* system function */
      {
        ParseNode *params = NULL;
        merge_nodes(params, result->malloc_pool_, T_EXPR_LIST, (yyvsp[(3) - (4)].node));
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SYS, 2, (yyvsp[(1) - (4)].node), params);
      }
    }
    break;

  case 108:

    {
      if (strcasecmp((yyvsp[(1) - (6)].node)->str_value_, "cast") == 0)
      {
        (yyvsp[(5) - (6)].node)->value_ = (yyvsp[(5) - (6)].node)->type_;
        (yyvsp[(5) - (6)].node)->type_ = T_INT;
        ParseNode *params = NULL;
        malloc_non_terminal_node(params, result->malloc_pool_, T_EXPR_LIST, 2, (yyvsp[(3) - (6)].node), (yyvsp[(5) - (6)].node));
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SYS, 2, (yyvsp[(1) - (6)].node), params);
      }
      else
      {
        yyerror(&(yylsp[(1) - (6)]), result, "AS support cast function only!");
        YYABORT;
      }
    }
    break;

  case 109:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SYS, 2, (yyvsp[(1) - (4)].node), (yyvsp[(3) - (4)].node));
    }
    break;

  case 110:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_FUN_SYS, 1, (yyvsp[(1) - (3)].node));
      //yyerror(&@1, result, "system/user-define function is not supported yet!");
      //YYABORT;
    }
    break;

  case 111:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_ALL);
    }
    break;

  case 112:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_DISTINCT);
    }
    break;

  case 113:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_DELETE, 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 114:

    {
      ParseNode* assign_list = NULL;
      merge_nodes(assign_list, result->malloc_pool_, T_ASSIGN_LIST, (yyvsp[(4) - (5)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_UPDATE, 3, (yyvsp[(2) - (5)].node), assign_list, (yyvsp[(5) - (5)].node));
    }
    break;

  case 115:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 116:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 117:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ASSIGN_ITEM, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 118:

    {
      ParseNode *table_elements = NULL;
      ParseNode *table_options = NULL;
      merge_nodes(table_elements, result->malloc_pool_, T_TABLE_ELEMENT_LIST, (yyvsp[(6) - (8)].node));
      merge_nodes(table_options, result->malloc_pool_, T_TABLE_OPTION_LIST, (yyvsp[(8) - (8)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CREATE_TABLE, 4,
              (yyvsp[(3) - (8)].node),                   /* if not exists */
              (yyvsp[(4) - (8)].node),                   /* table name */
              table_elements,       /* columns or primary key */
              table_options         /* table option(s) */
              );
    }
    break;

  case 119:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_IF_NOT_EXISTS); }
    break;

  case 120:

    { (yyval.node) = NULL; }
    break;

  case 121:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 122:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 123:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 124:

    {
      ParseNode* col_list= NULL;
      merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, (yyvsp[(4) - (5)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PRIMARY_KEY, 1, col_list);
    }
    break;

  case 125:

    {
      ParseNode *attributes = NULL;
      merge_nodes(attributes, result->malloc_pool_, T_COLUMN_ATTRIBUTES, (yyvsp[(3) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_DEFINITION, 3, (yyvsp[(1) - (3)].node), (yyvsp[(2) - (3)].node), attributes);
    }
    break;

  case 126:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_INTEGER ); }
    break;

  case 127:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_INTEGER); }
    break;

  case 128:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_INTEGER); }
    break;

  case 129:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_INTEGER); }
    break;

  case 130:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_INTEGER); }
    break;

  case 131:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_DECIMAL);
      else
        merge_nodes((yyval.node), result->malloc_pool_, T_TYPE_DECIMAL, (yyvsp[(2) - (2)].node));
      yyerror(&(yylsp[(1) - (2)]), result, "DECIMAL type is not supported");
      YYABORT;
    }
    break;

  case 132:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_DECIMAL);
      else
        merge_nodes((yyval.node), result->malloc_pool_, T_TYPE_DECIMAL, (yyvsp[(2) - (2)].node));
      yyerror(&(yylsp[(1) - (2)]), result, "NUMERIC type is not supported");
      YYABORT;
    }
    break;

  case 133:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_BOOLEAN ); }
    break;

  case 134:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_FLOAT, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 135:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_DOUBLE); }
    break;

  case 136:

    {
      (void)((yyvsp[(2) - (2)].node)) ; /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_DOUBLE);
    }
    break;

  case 137:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_TIMESTAMP);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_TIMESTAMP, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 138:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_TIMESTAMP); }
    break;

  case 139:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_CHARACTER);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_CHARACTER, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 140:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_CHARACTER);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_CHARACTER, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 141:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_VARCHAR);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_VARCHAR, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 142:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_VARCHAR);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_VARCHAR, 1, (yyvsp[(2) - (2)].node));
    }
    break;

  case 143:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_CREATETIME); }
    break;

  case 144:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_MODIFYTIME); }
    break;

  case 145:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_DATE);
      yyerror(&(yylsp[(1) - (1)]), result, "DATE type is not supported");
      YYABORT;
    }
    break;

  case 146:

    {
      if ((yyvsp[(2) - (2)].node) == NULL)
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_TIME);
      else
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TYPE_TIME, 1, (yyvsp[(2) - (2)].node));
      yyerror(&(yylsp[(1) - (2)]), result, "TIME type is not supported");
      YYABORT;
    }
    break;

  case 147:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node)); }
    break;

  case 148:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 149:

    { (yyval.node) = NULL; }
    break;

  case 150:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 151:

    { (yyval.node) = NULL; }
    break;

  case 152:

    { (yyval.node) = NULL; }
    break;

  case 153:

    { (yyval.node) = NULL; }
    break;

  case 154:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 155:

    { (yyval.node) = NULL; }
    break;

  case 156:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 157:

    { (yyval.node) = NULL; }
    break;

  case 158:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node)); }
    break;

  case 159:

    { (yyval.node) = NULL; }
    break;

  case 160:

    {
      (void)((yyvsp[(2) - (2)].node)) ; /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NOT_NULL);
    }
    break;

  case 161:

    {
      (void)((yyvsp[(1) - (1)].node)) ; /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NULL);
    }
    break;

  case 162:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_DEFAULT, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 163:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_AUTO_INCREMENT); }
    break;

  case 164:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_PRIMARY_KEY); }
    break;

  case 165:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 166:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 167:

    {
      (yyval.node) = NULL;
    }
    break;

  case 168:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPIRE_INFO, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 169:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TABLET_MAX_SIZE, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 170:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TABLET_BLOCK_SIZE, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 171:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_REPLICA_NUM, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 172:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COMPRESS_METHOD, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 173:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_USE_BLOOM_FILTER, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 174:

    {
      (void)((yyvsp[(2) - (3)].node)) ; /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSISTENT_MODE);
      (yyval.node)->value_ = 1;
    }
    break;

  case 175:

    { (yyval.node) = NULL; }
    break;

  case 176:

    { (yyval.node) = NULL; }
    break;

  case 177:

    {
      ParseNode *tables = NULL;
      merge_nodes(tables, result->malloc_pool_, T_TABLE_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_DROP_TABLE, 2, (yyvsp[(3) - (4)].node), tables);
    }
    break;

  case 178:

    { (yyval.node) = NULL; }
    break;

  case 179:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_IF_EXISTS); }
    break;

  case 180:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 181:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 182:

    {
    	ParseNode* val_list = NULL;
      	merge_nodes(val_list, result->malloc_pool_, T_VALUE_LIST, (yyvsp[(6) - (6)].node));
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_INSERT, 5,
                              (yyvsp[(3) - (6)].node),           /* target relation */
                              (yyvsp[(4) - (6)].node),           /* column list */
                              val_list,     /* value list */
                              NULL,         /* value from sub-query */
                              (yyvsp[(1) - (6)].node)            /* is replacement */
                              );
    }
    break;

  case 183:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_INSERT, 5,
                              (yyvsp[(3) - (4)].node),           /* target relation */
                              NULL,         /* column list */
                              NULL,         /* value list */
                              (yyvsp[(4) - (4)].node),           /* value from sub-query */
                              (yyvsp[(1) - (4)].node)            /* is replacement */
                              );
    }
    break;

  case 184:

    {
      ParseNode* col_list = NULL;
      merge_nodes(col_list, result->malloc_pool_, T_COLUMN_LIST, (yyvsp[(5) - (7)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_INSERT, 5,
                              (yyvsp[(3) - (7)].node),           /* target relation */
                              col_list,     /* column list */
                              NULL,         /* value list */
                              (yyvsp[(7) - (7)].node),           /* value from sub-query */
                              (yyvsp[(1) - (7)].node)            /* is replacement */
                              );
    }
    break;

  case 185:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 1;
    }
    break;

  case 186:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 0;
    }
    break;

  case 187:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_COLUMN_LIST, (yyvsp[(2) - (3)].node));
    }
    break;

  case 188:

    { (yyval.node) = NULL; }
    break;

  case 189:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 190:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 191:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_VALUE_VECTOR, (yyvsp[(2) - (3)].node));
    }
    break;

  case 192:

    {
    merge_nodes((yyvsp[(4) - (5)].node), result->malloc_pool_, T_VALUE_VECTOR, (yyvsp[(4) - (5)].node));
    malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (5)].node), (yyvsp[(4) - (5)].node));
  }
    break;

  case 193:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 194:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 195:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 196:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 197:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 198:

    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 199:

    {
      (yyval.node)= (yyvsp[(1) - (1)].node);
    }
    break;

  case 200:

    {
      (yyval.node) = (yyvsp[(1) - (2)].node);
      (yyval.node)->children_[12] = (yyvsp[(2) - (2)].node);
    }
    break;

  case 201:

    {
      /* use the new order by to replace old one */
      ParseNode* select = (ParseNode*)(yyvsp[(1) - (3)].node);
      if (select->children_[10])
        destroy_tree(select->children_[10]);
      select->children_[10] = (yyvsp[(2) - (3)].node);
      select->children_[12] = (yyvsp[(3) - (3)].node);
      (yyval.node) = select;
    }
    break;

  case 202:

    {
      /* use the new order by to replace old one */
      ParseNode* select = (ParseNode*)(yyvsp[(1) - (4)].node);
      if ((yyvsp[(2) - (4)].node))
      {
        if (select->children_[10])
          destroy_tree(select->children_[10]);
        select->children_[10] = (yyvsp[(2) - (4)].node);
      }

      /* set limit value */
      if (select->children_[11])
        destroy_tree(select->children_[11]);
      select->children_[11] = (yyvsp[(3) - (4)].node);
      select->children_[12] = (yyvsp[(4) - (4)].node);
      (yyval.node) = select;
    }
    break;

  case 203:

    {
      ParseNode* project_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, (yyvsp[(4) - (5)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              (yyvsp[(3) - (5)].node),             /* 1. distinct */
                              project_list,   /* 2. select clause */
                              NULL,           /* 3. from clause */
                              NULL,           /* 4. where */
                              NULL,           /* 5. group by */
                              NULL,           /* 6. having */
                              NULL,           /* 7. set operation */
                              NULL,           /* 8. all specified? */
                              NULL,           /* 9. former select stmt */
                              NULL,           /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              (yyvsp[(5) - (5)].node),             /* 12. limit */
                              NULL,           /* 13. for update */
                              (yyvsp[(2) - (5)].node)              /* 14 hints */
                              );
    }
    break;

  case 204:

    {
      ParseNode* project_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, (yyvsp[(4) - (8)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              (yyvsp[(3) - (8)].node),             /* 1. distinct */
                              project_list,   /* 2. select clause */
                              NULL,           /* 3. from clause */
                              (yyvsp[(7) - (8)].node),             /* 4. where */
                              NULL,           /* 5. group by */
                              NULL,           /* 6. having */
                              NULL,           /* 7. set operation */
                              NULL,           /* 8. all specified? */
                              NULL,           /* 9. former select stmt */
                              NULL,           /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              (yyvsp[(8) - (8)].node),             /* 12. limit */
                              NULL,           /* 13. for update */
                              (yyvsp[(2) - (8)].node)              /* 14 hints */
                              );
    }
    break;

  case 205:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 206:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 207:

    {
      ParseNode* project_list = NULL;
      ParseNode* from_list = NULL;
      merge_nodes(project_list, result->malloc_pool_, T_PROJECT_LIST, (yyvsp[(4) - (9)].node));
      merge_nodes(from_list, result->malloc_pool_, T_FROM_LIST, (yyvsp[(6) - (9)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              (yyvsp[(3) - (9)].node),             /* 1. distinct */
                              project_list,   /* 2. select clause */
                              from_list,      /* 3. from clause */
                              (yyvsp[(7) - (9)].node),             /* 4. where */
                              (yyvsp[(8) - (9)].node),             /* 5. group by */
                              (yyvsp[(9) - (9)].node),             /* 6. having */
                              NULL,           /* 7. set operation */
                              NULL,           /* 8. all specified? */
                              NULL,           /* 9. former select stmt */
                              NULL,           /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              NULL,           /* 12. limit */
                              NULL,           /* 13. for update */
                              (yyvsp[(2) - (9)].node)              /* 14 hints */
                              );
    }
    break;

  case 208:

    {
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_UNION);
	    malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              NULL,           /* 1. distinct */
                              NULL,           /* 2. select clause */
                              NULL,           /* 3. from clause */
                              NULL,           /* 4. where */
                              NULL,           /* 5. group by */
                              NULL,           /* 6. having */
                              set_op,   	/* 7. set operation */
                              (yyvsp[(3) - (4)].node),             /* 8. all specified? */
                              (yyvsp[(1) - (4)].node),             /* 9. former select stmt */
                              (yyvsp[(4) - (4)].node),             /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              NULL,           /* 12. limit */
                              NULL,           /* 13. for update */
                              NULL            /* 14 hints */
                              );
    }
    break;

  case 209:

    {
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_INTERSECT);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              NULL,           /* 1. distinct */
                              NULL,           /* 2. select clause */
                              NULL,           /* 3. from clause */
                              NULL,           /* 4. where */
                              NULL,           /* 5. group by */
                              NULL,           /* 6. having */
                              set_op,   /* 7. set operation */
                              (yyvsp[(3) - (4)].node),             /* 8. all specified? */
                              (yyvsp[(1) - (4)].node),             /* 9. former select stmt */
                              (yyvsp[(4) - (4)].node),             /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              NULL,           /* 12. limit */
                              NULL,           /* 13. for update */
                              NULL            /* 14 hints */
                              );
    }
    break;

  case 210:

    {
      ParseNode* set_op = NULL;
      malloc_terminal_node(set_op, result->malloc_pool_, T_SET_EXCEPT);
	    malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SELECT, 14,
                              NULL,           /* 1. distinct */
                              NULL,           /* 2. select clause */
                              NULL,           /* 3. from clause */
                              NULL,           /* 4. where */
                              NULL,           /* 5. group by */
                              NULL,           /* 6. having */
                              set_op,   	  /* 7. set operation */
                              (yyvsp[(3) - (4)].node),             /* 8. all specified? */
                              (yyvsp[(1) - (4)].node),             /* 9. former select stmt */
                              (yyvsp[(4) - (4)].node),             /* 10. later select stmt */
                              NULL,           /* 11. order by */
                              NULL,           /* 12. limit */
                              NULL,           /* 13. for update */
                              NULL            /* 14 hints */
                              );
    }
    break;

  case 211:

    {(yyval.node) = NULL;}
    break;

  case 212:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 213:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_WHERE_CLAUSE, 2, (yyvsp[(3) - (3)].node), (yyvsp[(2) - (3)].node));
    }
    break;

  case 214:

    {
      if ((yyvsp[(2) - (4)].node)->type_ == T_QUESTIONMARK && (yyvsp[(4) - (4)].node)->type_ == T_QUESTIONMARK)
      {
        (yyvsp[(4) - (4)].node)->value_++;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LIMIT_CLAUSE, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 215:

    {
      if ((yyvsp[(2) - (4)].node)->type_ == T_QUESTIONMARK && (yyvsp[(4) - (4)].node)->type_ == T_QUESTIONMARK)
      {
        (yyvsp[(4) - (4)].node)->value_++;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LIMIT_CLAUSE, 2, (yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].node));
    }
    break;

  case 216:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LIMIT_CLAUSE, 2, (yyvsp[(2) - (2)].node), NULL);
    }
    break;

  case 217:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LIMIT_CLAUSE, 2, NULL, (yyvsp[(2) - (2)].node));
    }
    break;

  case 218:

    {
      if ((yyvsp[(2) - (4)].node)->type_ == T_QUESTIONMARK && (yyvsp[(4) - (4)].node)->type_ == T_QUESTIONMARK)
      {
        (yyvsp[(4) - (4)].node)->value_++;
      }
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LIMIT_CLAUSE, 2, (yyvsp[(4) - (4)].node), (yyvsp[(2) - (4)].node));
    }
    break;

  case 219:

    {
      (yyval.node) = NULL;
    }
    break;

  case 220:

    {
      if ((yyvsp[(2) - (3)].node))
      {
        merge_nodes((yyval.node), result->malloc_pool_, T_HINT_OPTION_LIST, (yyvsp[(2) - (3)].node));
      }
      else
      {
        (yyval.node) = NULL;
      }
    }
    break;

  case 221:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 222:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 223:

    {
      (yyval.node) = NULL;
    }
    break;

  case 224:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_READ_STATIC);
    }
    break;

  case 225:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 226:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 227:

    { (yyval.node) = NULL; }
    break;

  case 228:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 229:

    { (yyval.node) = NULL; }
    break;

  case 230:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 1;
    }
    break;

  case 231:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 232:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 233:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 1;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 234:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 2;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 235:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 0;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default */
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, (yyvsp[(3) - (3)].node));
    }
    break;

  case 236:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 1;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default */
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, (yyvsp[(3) - (3)].node));
    }
    break;

  case 237:

    {
      ParseNode *default_type = NULL;
      malloc_terminal_node(default_type, result->malloc_pool_, T_INT);
      default_type->value_ = 2;
      ParseNode *default_operand = NULL;
      malloc_terminal_node(default_operand, result->malloc_pool_, T_STRING);
      default_operand->str_value_ = " "; /* blank for default */
      default_operand->value_ = strlen(default_operand->str_value_);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPR_LIST, 3, default_type, default_operand, (yyvsp[(3) - (3)].node));
    }
    break;

  case 238:

    { (yyval.node) = NULL; }
    break;

  case 239:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_EXPR_LIST, (yyvsp[(3) - (3)].node));
    }
    break;

  case 240:

    { (yyval.node) = (yyvsp[(1) - (1)].node);}
    break;

  case 241:

    { (yyval.node) = NULL; }
    break;

  case 242:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_SORT_LIST, (yyvsp[(3) - (3)].node));
    }
    break;

  case 243:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 244:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 245:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SORT_KEY, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
    }
    break;

  case 246:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SORT_ASC); }
    break;

  case 247:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SORT_ASC); }
    break;

  case 248:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SORT_DESC); }
    break;

  case 249:

    { (yyval.node) = 0; }
    break;

  case 250:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 251:

    {
      (yyval.node) = NULL;
    }
    break;

  case 252:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_ALL);
    }
    break;

  case 253:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_DISTINCT);
    }
    break;

  case 254:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PROJECT_STRING, 1, (yyvsp[(1) - (1)].node));
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_column);
    }
    break;

  case 255:

    {
      ParseNode* alias_node = NULL;
      malloc_non_terminal_node(alias_node, result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PROJECT_STRING, 1, alias_node);
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(1) - (2)]).first_column, (yylsp[(1) - (2)]).last_column);
      dup_expr_string(alias_node->str_value_, result, (yylsp[(2) - (2)]).first_column, (yylsp[(2) - (2)]).last_column);
    }
    break;

  case 256:

    {
      ParseNode* alias_node = NULL;
      malloc_non_terminal_node(alias_node, result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PROJECT_STRING, 1, alias_node);
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(1) - (3)]).first_column, (yylsp[(1) - (3)]).last_column);
      dup_expr_string(alias_node->str_value_, result, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_column);
    }
    break;

  case 257:

    {
      ParseNode* star_node = NULL;
      malloc_terminal_node(star_node, result->malloc_pool_, T_STAR);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PROJECT_STRING, 1, star_node);
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(1) - (1)]).first_column, (yylsp[(1) - (1)]).last_column);
    }
    break;

  case 258:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 259:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 260:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 261:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 262:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 263:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_NAME_FIELD, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      dup_expr_string((yyval.node)->str_value_, result, (yylsp[(3) - (3)]).first_column, (yylsp[(3) - (3)]).last_column);
    }
    break;

  case 264:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 265:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
    }
    break;

  case 266:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 267:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALIAS, 2, (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node));
    }
    break;

  case 268:

    {
    	(yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 269:

    {
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALIAS, 2, (yyvsp[(2) - (5)].node), (yyvsp[(5) - (5)].node));
    	yyerror(&(yylsp[(1) - (5)]), result, "qualied joined table can not be aliased!");
      YYABORT;
    }
    break;

  case 270:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 271:

    {
    	(yyval.node) = (yyvsp[(2) - (3)].node);
    }
    break;

  case 272:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_JOINED_TABLE, 4, (yyvsp[(2) - (6)].node), (yyvsp[(1) - (6)].node), (yyvsp[(4) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 273:

    {
      ParseNode* node = NULL;
      malloc_terminal_node(node, result->malloc_pool_, T_JOIN_INNER);
    	malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_JOINED_TABLE, 4, node, (yyvsp[(1) - (5)].node), (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 274:

    {
      /* make bison mute */
      (void)((yyvsp[(2) - (2)].node));
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_JOIN_FULL);
    }
    break;

  case 275:

    {
      /* make bison mute */
      (void)((yyvsp[(2) - (2)].node));
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_JOIN_LEFT);
    }
    break;

  case 276:

    {
      /* make bison mute */
      (void)((yyvsp[(2) - (2)].node));
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_JOIN_RIGHT);
    }
    break;

  case 277:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_JOIN_INNER);
    }
    break;

  case 278:

    { (yyval.node) = NULL; }
    break;

  case 279:

    { (yyval.node) = NULL; }
    break;

  case 280:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXPLAIN, 1, (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = ((yyvsp[(2) - (3)].node) ? 1 : 0); /* positive: verbose */
    }
    break;

  case 281:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 282:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 283:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 284:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 285:

    { (yyval.node) = (ParseNode*)1; }
    break;

  case 286:

    { (yyval.node) = NULL; }
    break;

  case 287:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_DATABASES, 1, (yyvsp[(3) - (3)].node)); }
    break;

  case 288:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_TABLES, 1, (yyvsp[(3) - (3)].node)); }
    break;

  case 289:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node)); }
    break;

  case 290:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node)); }
    break;

  case 291:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_TABLE_STATUS, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 292:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_SERVER_STATUS, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 293:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_VARIABLES, 1, (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = (yyvsp[(2) - (4)].ival);
    }
    break;

  case 294:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_SCHEMA); }
    break;

  case 295:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_CREATE_TABLE, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 296:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 297:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 298:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_WARNINGS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 299:

    {
      if ((yyvsp[(2) - (3)].node)->type_ != T_FUN_COUNT)
      {
        yyerror(&(yylsp[(1) - (3)]), result, "Only COUNT(*) function is supported in SHOW WARNINGS statement!");
        YYABORT;
      }
      else
      {
        malloc_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_WARNINGS);
        (yyval.node)->value_ = 1;
      }
    }
    break;

  case 300:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_GRANTS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 301:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_PARAMETERS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 302:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_PROCESSLIST); }
    break;

  case 303:

    {
      if ((yyvsp[(2) - (4)].node)->value_ < 0 || (yyvsp[(4) - (4)].node)->value_ < 0)
      {
        yyerror(&(yylsp[(1) - (4)]), result, "OFFSET/COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_LIMIT, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 304:

    {
      if ((yyvsp[(2) - (2)].node)->value_ < 0)
      {
        yyerror(&(yylsp[(1) - (2)]), result, "COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_LIMIT, 2, NULL, (yyvsp[(2) - (2)].node));
    }
    break;

  case 305:

    { (yyval.node) = NULL; }
    break;

  case 306:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 307:

    { (yyval.node) = NULL; }
    break;

  case 308:

    { (yyval.node) = NULL; }
    break;

  case 309:

    { (yyval.ival) = 1; }
    break;

  case 310:

    { (yyval.ival) = 0; }
    break;

  case 311:

    { (yyval.ival) = 0; }
    break;

  case 312:

    { (yyval.node) = NULL; }
    break;

  case 313:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LIKE, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 314:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_WHERE_CLAUSE, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 315:

    { (yyval.node) = NULL; }
    break;

  case 316:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LIKE, 1, (yyvsp[(1) - (1)].node)); }
    break;

  case 317:

    {
        merge_nodes((yyval.node), result->malloc_pool_, T_CREATE_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 318:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 319:

    {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 320:

    {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CREATE_USER_SPEC, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 321:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 322:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 323:

    {
        merge_nodes((yyval.node), result->malloc_pool_, T_DROP_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 324:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 325:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 326:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SET_PASSWORD, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 327:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SET_PASSWORD, 2, (yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 328:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 329:

    {
      (yyval.node) = NULL;
    }
    break;

  case 330:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_RENAME_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 331:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_RENAME_INFO, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 332:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 333:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 334:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LOCK_USER, 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 335:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 1;
    }
    break;

  case 336:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 0;
    }
    break;

  case 337:

    {
      (void)(yyval.node);
    }
    break;

  case 338:

    {
      (void)(yyval.node);
    }
    break;

  case 339:

    {
      (yyval.ival) = 1;
    }
    break;

  case 340:

    {
      (yyval.ival) = 0;
    }
    break;

  case 341:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BEGIN);
      (yyval.node)->value_ = 0;
    }
    break;

  case 342:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BEGIN);
      (yyval.node)->value_ = (yyvsp[(3) - (3)].ival);
    }
    break;

  case 343:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_COMMIT);
    }
    break;

  case 344:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_ROLLBACK);
    }
    break;

  case 345:

    {
      ParseNode *privileges_node = NULL;
      ParseNode *users_node = NULL;
      merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, (yyvsp[(2) - (6)].node));
      merge_nodes(users_node, result->malloc_pool_, T_USERS, (yyvsp[(6) - (6)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_GRANT,
                                 3, privileges_node, (yyvsp[(4) - (6)].node), users_node);
    }
    break;

  case 346:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 347:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 348:

    {
      (void)(yyvsp[(2) - (2)].node);                 /* useless */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_ALL;
    }
    break;

  case 349:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_ALTER;
    }
    break;

  case 350:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_CREATE;
    }
    break;

  case 351:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_CREATE_USER;
    }
    break;

  case 352:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_DELETE;
    }
    break;

  case 353:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_DROP;
    }
    break;

  case 354:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_GRANT_OPTION;
    }
    break;

  case 355:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_INSERT;
    }
    break;

  case 356:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_UPDATE;
    }
    break;

  case 357:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_SELECT;
    }
    break;

  case 358:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_REPLACE;
    }
    break;

  case 359:

    {
      (void)(yyval.node);
    }
    break;

  case 360:

    {
      (void)(yyval.node);
    }
    break;

  case 361:

    {
      /* means global priv_level */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_LEVEL);
    }
    break;

  case 362:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_LEVEL, 1, (yyvsp[(1) - (1)].node));
    }
    break;

  case 363:

    {
      ParseNode *privileges_node = NULL;
      ParseNode *priv_level = NULL;
      merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, (yyvsp[(2) - (5)].node));
      if ((yyvsp[(3) - (5)].node) == NULL)
      {
        /* check privileges: should have and only have ALL PRIVILEGES, GRANT OPTION */
        int check_ok = 0;
        if (2 == privileges_node->num_child_)
        {
          assert(privileges_node->children_[0]->num_child_ == 0);
          assert(privileges_node->children_[0]->type_ == T_PRIV_TYPE);
          assert(privileges_node->children_[1]->num_child_ == 0);
          assert(privileges_node->children_[1]->type_ == T_PRIV_TYPE);
          if ((privileges_node->children_[0]->value_ == T_PRIV_ALL
               && privileges_node->children_[1]->value_ == T_PRIV_GRANT_OPTION)
              || (privileges_node->children_[1]->value_ == T_PRIV_ALL
                  && privileges_node->children_[0]->value_ == T_PRIV_GRANT_OPTION))
          {
            check_ok = 1;
          }
        }
        if (!check_ok)
        {
          yyerror(&(yylsp[(1) - (5)]), result, "support only ALL PRIVILEGES, GRANT OPTION");
          YYABORT;
        }
      }
      else
      {
        priv_level = (yyvsp[(3) - (5)].node);
      }
      ParseNode *users_node = NULL;
      merge_nodes(users_node, result->malloc_pool_, T_USERS, (yyvsp[(5) - (5)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_REVOKE,
                                 3, privileges_node, priv_level, users_node);
    }
    break;

  case 364:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 365:

    {
      (yyval.node) = NULL;
    }
    break;

  case 366:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PREPARE, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 367:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 368:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 369:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 370:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 371:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 372:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_VARIABLE_SET, (yyvsp[(2) - (2)].node));;
      (yyval.node)->value_ = 2;
    }
    break;

  case 373:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 374:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 375:

    {
      (void)((yyvsp[(2) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 376:

    {
      (void)((yyvsp[(2) - (3)].node));
      (yyvsp[(1) - (3)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 377:

    {
      (void)((yyvsp[(3) - (4)].node));
      (yyvsp[(2) - (4)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = 1;
    }
    break;

  case 378:

    {
      (void)((yyvsp[(3) - (4)].node));
      (yyvsp[(2) - (4)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 379:

    {
      (void)((yyvsp[(4) - (5)].node));
      (yyvsp[(3) - (5)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->value_ = 1;
    }
    break;

  case 380:

    {
      (void)((yyvsp[(4) - (5)].node));
      (yyvsp[(3) - (5)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 381:

    {
      (void)((yyvsp[(2) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 382:

    { (yyval.node) = NULL; }
    break;

  case 383:

    { (yyval.node) = NULL; }
    break;

  case 384:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 385:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXECUTE, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 386:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_ARGUMENT_LIST, (yyvsp[(2) - (2)].node));
    }
    break;

  case 387:

    {
      (yyval.node) = NULL;
    }
    break;

  case 388:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 389:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 390:

    {
      (void)((yyvsp[(1) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_DEALLOCATE, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 391:

    { (yyval.node) = NULL; }
    break;

  case 392:

    { (yyval.node) = NULL; }
    break;

  case 393:

    {
      ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_TABLE, 2, (yyvsp[(3) - (4)].node), alter_actions);
    }
    break;

  case 394:

    {
      yyerror(&(yylsp[(1) - (6)]), result, "Table rename is not supported now");
      YYABORT;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TABLE_RENAME, 1, (yyvsp[(6) - (6)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_ACTION_LIST, 1, (yyval.node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_TABLE, 2, (yyvsp[(3) - (6)].node), (yyval.node));
    }
    break;

  case 395:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 396:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 397:

    {
      (void)((yyvsp[(2) - (3)].node)); /* make bison mute */
      (yyval.node) = (yyvsp[(3) - (3)].node); /* T_COLUMN_DEFINITION */
    }
    break;

  case 398:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_DROP, 1, (yyvsp[(3) - (4)].node));
      (yyval.node)->value_ = (yyvsp[(4) - (4)].ival);
    }
    break;

  case 399:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_ALTER, 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 400:

    {
      (void)((yyvsp[(2) - (5)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_RENAME, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 401:

    { (yyval.node) = NULL; }
    break;

  case 402:

    { (yyval.node) = NULL; }
    break;

  case 403:

    { (yyval.ival) = 2; }
    break;

  case 404:

    { (yyval.ival) = 1; }
    break;

  case 405:

    { (yyval.ival) = 0; }
    break;

  case 406:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NOT_NULL);
    }
    break;

  case 407:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NULL);
    }
    break;

  case 408:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_DEFAULT, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 409:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_NULL);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_DEFAULT, 1, (yyval.node));
    }
    break;

  case 410:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_SYTEM_ACTION_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_SYSTEM, 1, (yyval.node));
    }
    break;

  case 411:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 412:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 413:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SYSTEM_ACTION, 5,
                               (yyvsp[(1) - (9)].node),    /* param_name */
                               (yyvsp[(3) - (9)].node),    /* param_value */
                               (yyvsp[(4) - (9)].node),    /* comment */
                               (yyvsp[(8) - (9)].node),    /* server type */
                               (yyvsp[(9) - (9)].node)     /* cluster or IP/port */
                               );
      (yyval.node)->value_ = (yyvsp[(5) - (9)].ival);                /* scope */
    }
    break;

  case 414:

    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 415:

    { (yyval.node) = NULL; }
    break;

  case 416:

    { (yyval.ival) = 0; }
    break;

  case 417:

    { (yyval.ival) = 1; }
    break;

  case 418:

    { (yyval.ival) = 2; }
    break;

  case 419:

    { (yyval.ival) = 2; }
    break;

  case 420:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 1;
    }
    break;

  case 421:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 4;
    }
    break;

  case 422:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 2;
    }
    break;

  case 423:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 3;
    }
    break;

  case 424:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CLUSTER, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 425:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SERVER_ADDRESS, 2, (yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 426:

    { (yyval.node) = NULL; }
    break;

  case 427:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 428:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_IDENT);
      (yyval.node)->str_value_ = parse_strdup((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name, result->malloc_pool_);
      if ((yyval.node)->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }
      else
      {
        (yyval.node)->value_ = strlen((yyval.node)->str_value_);
      }
    }
    break;

  case 429:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 430:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_IDENT);
      (yyval.node)->str_value_ = parse_strdup((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name, result->malloc_pool_);
      if ((yyval.node)->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }
      else
      {
        (yyval.node)->value_ = strlen((yyval.node)->str_value_);
      }
    }
    break;

  case 432:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 433:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_IDENT);
      (yyval.node)->str_value_ = parse_strdup((yyvsp[(1) - (1)].non_reserved_keyword)->keyword_name, result->malloc_pool_);
      if ((yyval.node)->str_value_ == NULL)
      {
        yyerror(NULL, result, "No more space for string duplicate");
        YYABORT;
      }
    }
    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (&yylloc, result, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (&yylloc, result, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc, result);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp, result);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, result, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, result);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, result);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}





void yyerror(YYLTYPE* yylloc, ParseResult* p, char* s, ...)
{
  if (p != NULL)
  {
    p->result_tree_ = 0;
    va_list ap;
    va_start(ap, s);
    vsnprintf(p->error_msg_, MAX_ERROR_MSG, s, ap);
    if (yylloc != NULL)
    {
      p->start_col_ = yylloc->first_column;
      p->end_col_ = yylloc->last_column;
      p->line_ = yylloc->first_line;
    }
  }
}

int parse_init(ParseResult* p)
{
  int ret = 0;  // can not include C++ file "ob_define.h"
  if (!p)
  {
    ret = -1;
    if (p)
    {
      snprintf(p->error_msg_, MAX_ERROR_MSG, "malloc_pool_ must be set");
    }
  }
  if (ret == 0)
  {
    ret = yylex_init_extra(p, &(p->yyscan_info_));
  }
  return ret;
}

int parse_terminate(ParseResult* p)
{
  return yylex_destroy(p->yyscan_info_);
}

int parse_sql(ParseResult* p, const char* buf, size_t len)
{
  int ret = -1;
  p->result_tree_ = 0;
  p->error_msg_[0] = 0;
  p->input_sql_ = buf;
  p->start_col_ = 1;
  p->end_col_ = 1;
  p->line_ = 1;
  p->yycolumn_ = 1;
  p->yylineno_ = 1;

  if (buf == NULL || len <= 0)
  {
    snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be empty");
    return ret;
  }

  while(len > 0 && isspace(buf[len - 1]))
    --len;

  if (len <= 0)
  {
    snprintf(p->error_msg_, MAX_ERROR_MSG, "Input SQL can not be while space only");
    return ret;
  }

  YY_BUFFER_STATE bp;

  //bp = yy_scan_string(buf, p->yyscan_info_);
  bp = yy_scan_bytes(buf, len, p->yyscan_info_);
  yy_switch_to_buffer(bp, p->yyscan_info_);
  ret = yyparse(p);
  yy_delete_buffer(bp, p->yyscan_info_);
  return ret;
}
