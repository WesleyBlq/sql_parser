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
     TABLE = 392,
     TABLES = 393,
     THEN = 394,
     TIME = 395,
     TIMESTAMP = 396,
     TINYINT = 397,
     TRAILING = 398,
     TRANSACTION = 399,
     TO = 400,
     UPDATE = 401,
     USER = 402,
     USING = 403,
     VALUES = 404,
     VARCHAR = 405,
     VARBINARY = 406,
     WHERE = 407,
     WHEN = 408,
     WITH = 409,
     WORK = 410,
     AUTO_INCREMENT = 411,
     CHUNKSERVER = 412,
     COMPRESS_METHOD = 413,
     CONSISTENT_MODE = 414,
     EXPIRE_INFO = 415,
     GRANTS = 416,
     MERGESERVER = 417,
     REPLICA_NUM = 418,
     ROOTSERVER = 419,
     SERVER = 420,
     SERVER_IP = 421,
     SERVER_PORT = 422,
     SERVER_TYPE = 423,
     STATUS = 424,
     TABLET_BLOCK_SIZE = 425,
     TABLET_MAX_SIZE = 426,
     UNLOCKED = 427,
     UPDATESERVER = 428,
     USE_BLOOM_FILTER = 429,
     VARIABLES = 430,
     VERBOSE = 431,
     WARNINGS = 432
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
#define YYFINAL  152
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2507

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  189
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  144
/* YYNRULES -- Number of rules.  */
#define YYNRULES  453
/* YYNRULES -- Number of states.  */
#define YYNSTATES  801

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   432

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      40,    41,    34,    32,   188,    33,    42,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   187,
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
     184,   185,   186
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
     885,   889,   891,   893,   895,   897,   899,   900,   904,   910,
     916,   921,   926,   931,   934,   939,   943,   947,   951,   955,
     959,   963,   968,   971,   972,   974,   977,   982,   984,   986,
     987,   988,   991,   994,   995,   997,  1001,  1003,  1007,  1012,
    1014,  1016,  1020,  1022,  1026,  1032,  1039,  1042,  1043,  1047,
    1051,  1053,  1057,  1062,  1064,  1066,  1068,  1069,  1073,  1074,
    1077,  1081,  1084,  1087,  1094,  1096,  1100,  1103,  1105,  1107,
    1110,  1112,  1114,  1117,  1119,  1121,  1123,  1125,  1127,  1128,
    1130,  1132,  1138,  1141,  1142,  1147,  1149,  1151,  1153,  1155,
    1157,  1160,  1162,  1166,  1170,  1174,  1179,  1184,  1190,  1196,
    1200,  1202,  1204,  1206,  1210,  1213,  1214,  1216,  1220,  1224,
    1226,  1228,  1233,  1240,  1242,  1246,  1250,  1255,  1260,  1266,
    1268,  1269,  1271,  1273,  1274,  1278,  1282,  1286,  1289,  1294,
    1296,  1300,  1310,  1313,  1314,  1318,  1322,  1326,  1327,  1329,
    1331,  1333,  1335,  1339,  1346,  1347,  1349,  1351,  1353,  1355,
    1357,  1359,  1361,  1363,  1365,  1367,  1369,  1371,  1373,  1375,
    1377,  1379,  1381,  1383,  1385,  1387,  1389,  1391,  1393,  1395,
    1397,  1399,  1401,  1403
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     190,     0,    -1,   191,    81,    -1,   191,   187,   192,    -1,
     192,    -1,   236,    -1,   230,    -1,   211,    -1,   208,    -1,
     207,    -1,   227,    -1,   267,    -1,   270,    -1,   302,    -1,
     305,    -1,   310,    -1,   315,    -1,   321,    -1,   313,    -1,
     276,    -1,   281,    -1,   283,    -1,   285,    -1,   288,    -1,
     295,    -1,   300,    -1,   292,    -1,   293,    -1,   294,    -1,
      -1,   198,    -1,   193,   188,   198,    -1,   328,    -1,   329,
      42,   328,    -1,   329,    42,    34,    -1,     4,    -1,     6,
      -1,     5,    -1,     9,    -1,     8,    -1,    10,    -1,    12,
      -1,    14,    -1,    13,    -1,   137,    42,   328,    -1,   194,
      -1,   195,    -1,    40,   198,    41,    -1,    40,   193,   188,
     198,    41,    -1,   200,    -1,   205,    -1,   237,    -1,    84,
     237,    -1,   196,    -1,    32,   197,    -1,    33,   197,    -1,
     197,    32,   197,    -1,   197,    33,   197,    -1,   197,    34,
     197,    -1,   197,    35,   197,    -1,   197,    36,   197,    -1,
     197,    38,   197,    -1,   197,    37,   197,    -1,   196,    -1,
      32,   198,    -1,    33,   198,    -1,   198,    32,   198,    -1,
     198,    33,   198,    -1,   198,    34,   198,    -1,   198,    35,
     198,    -1,   198,    36,   198,    -1,   198,    38,   198,    -1,
     198,    37,   198,    -1,   198,    26,   198,    -1,   198,    25,
     198,    -1,   198,    24,   198,    -1,   198,    22,   198,    -1,
     198,    23,   198,    -1,   198,    21,   198,    -1,   198,    28,
     198,    -1,   198,    20,    28,   198,    -1,   198,    19,   198,
      -1,   198,    18,   198,    -1,    20,   198,    -1,   198,    31,
      10,    -1,   198,    31,    20,    10,    -1,   198,    31,     8,
      -1,   198,    31,    20,     8,    -1,   198,    31,    11,    -1,
     198,    31,    20,    11,    -1,   198,    29,   197,    19,   197,
      -1,   198,    20,    29,   197,    19,   197,    -1,   198,    30,
     199,    -1,   198,    20,    30,   199,    -1,   198,    27,   198,
      -1,   237,    -1,    40,   193,    41,    -1,    56,   201,   202,
     204,    80,    -1,   198,    -1,    -1,   203,    -1,   202,   203,
      -1,   162,   198,   148,   198,    -1,    79,   198,    -1,    -1,
     330,    40,    34,    41,    -1,   330,    40,   206,   198,    41,
      -1,   330,    40,   193,    41,    -1,   330,    40,   198,    47,
     216,    41,    -1,   330,    40,   250,    41,    -1,   330,    40,
      41,    -1,    45,    -1,    75,    -1,    72,    88,   263,   242,
      -1,   155,   263,   138,   209,   242,    -1,   210,    -1,   209,
     188,   210,    -1,   328,    24,   198,    -1,    64,   146,   212,
     263,    40,   213,    41,   224,    -1,    98,    20,    84,    -1,
      -1,   214,    -1,   213,   188,   214,    -1,   215,    -1,   123,
     104,    40,   233,    41,    -1,   328,   216,   222,    -1,   151,
      -1,   140,    -1,   110,    -1,   100,    -1,    50,    -1,    70,
     217,    -1,   113,   217,    -1,    52,    -1,    86,   218,    -1,
     125,    -1,    76,   219,    -1,   150,   220,    -1,    68,    -1,
      57,   221,    -1,    51,   221,    -1,   159,   221,    -1,   160,
     221,    -1,    65,    -1,   112,    -1,    67,    -1,   149,   220,
      -1,    40,     5,   188,     5,    41,    -1,    40,     5,    41,
      -1,    -1,    40,     5,    41,    -1,    -1,   121,    -1,    -1,
      40,     5,    41,    -1,    -1,    40,     5,    41,    -1,    -1,
     222,   223,    -1,    -1,    20,    10,    -1,    10,    -1,    71,
     195,    -1,   165,    -1,   123,   104,    -1,   225,    -1,   224,
     188,   225,    -1,    -1,   169,   226,     4,    -1,   180,   226,
       5,    -1,   179,   226,     5,    -1,   172,   226,     5,    -1,
     167,   226,     4,    -1,   183,   226,     8,    -1,   168,   226,
     144,    -1,    24,    -1,    -1,    77,   146,   228,   229,    -1,
      -1,    98,    84,    -1,   262,    -1,   229,   188,   262,    -1,
     231,   102,   263,   232,   158,   234,    -1,   231,   102,   263,
     236,    -1,   231,   102,   263,    40,   233,    41,   236,    -1,
     127,    -1,   101,    -1,    40,   233,    41,    -1,    -1,   328,
      -1,   233,   188,   328,    -1,    40,   235,    41,    -1,   234,
     188,    40,   235,    41,    -1,   198,    -1,   235,   188,   198,
      -1,   238,    -1,   237,    -1,    40,   238,    41,    -1,    40,
     237,    41,    -1,   239,    -1,   241,   249,    -1,   240,   253,
     249,    -1,   240,   252,   243,   249,    -1,   135,   244,   258,
     260,   248,    -1,   135,   244,   258,   260,    88,    78,   242,
     248,    -1,   241,    -1,   237,    -1,   135,   244,   258,   260,
      88,   261,   242,   251,   257,    -1,   240,    16,   258,   240,
      -1,   240,    17,   258,   240,    -1,   240,    15,   258,   240,
      -1,    -1,   161,   198,    -1,   161,     7,   198,    -1,   107,
     247,   114,   247,    -1,   114,   247,   107,   247,    -1,   107,
     247,    -1,   114,   247,    -1,   107,   247,   188,   247,    -1,
      -1,    95,   245,    96,    -1,   246,    -1,   245,   188,   246,
      -1,    -1,   124,    -1,     5,    -1,    12,    -1,    -1,   243,
      -1,    -1,    87,   155,    -1,   198,    88,   198,    -1,    53,
     198,    88,   198,    -1,   105,   198,    88,   198,    -1,   152,
     198,    88,   198,    -1,    53,    88,   198,    -1,   105,    88,
     198,    -1,   152,    88,   198,    -1,    -1,    93,    54,   193,
      -1,   253,    -1,    -1,   116,    54,   254,    -1,   255,    -1,
     254,   188,   255,    -1,   198,   256,    -1,    -1,    48,    -1,
      73,    -1,    -1,    94,   198,    -1,    -1,    45,    -1,    75,
      -1,   198,    -1,   198,   331,    -1,   198,    47,   331,    -1,
      34,    -1,   259,    -1,   260,   188,   259,    -1,   262,    -1,
     261,   188,   262,    -1,   263,    -1,   329,    42,   263,    -1,
     263,    47,   329,    -1,   263,   329,    -1,   237,    47,   329,
      -1,   237,   329,    -1,   264,    -1,    40,   264,    41,    47,
     329,    -1,   329,    -1,    40,   264,    41,    -1,   262,   265,
     103,   262,   115,   198,    -1,   262,   103,   262,   115,   198,
      -1,    89,   266,    -1,   106,   266,    -1,   131,   266,    -1,
      99,    -1,   118,    -1,    -1,    85,   269,   268,    -1,   236,
      -1,   207,    -1,   230,    -1,   208,    -1,   185,    -1,    -1,
     139,   147,   274,    -1,   139,    63,    88,   263,   274,    -1,
     139,    63,    30,   263,   274,    -1,   139,   146,   178,   274,
      -1,   139,   174,   178,   274,    -1,   139,   273,   184,   274,
      -1,   139,   133,    -1,   139,    64,   146,   263,    -1,    74,
     263,   275,    -1,    73,   263,   275,    -1,   139,   186,   271,
      -1,   139,   205,   186,    -1,   139,   170,   272,    -1,   139,
     119,   274,    -1,   107,     5,   188,     5,    -1,   107,     5,
      -1,    -1,   284,    -1,    87,    66,    -1,    87,    66,    40,
      41,    -1,    90,    -1,   136,    -1,    -1,    -1,    28,     4,
      -1,   161,   198,    -1,    -1,     4,    -1,    64,   156,   277,
      -1,   278,    -1,   277,   188,   278,    -1,   279,    97,    54,
     280,    -1,     4,    -1,     4,    -1,    77,   156,   282,    -1,
     279,    -1,   282,   188,   279,    -1,   138,   120,   284,    24,
     280,    -1,    46,   156,   279,    97,    54,   280,    -1,    87,
     279,    -1,    -1,   126,   156,   287,    -1,   279,   154,   279,
      -1,   286,    -1,   287,   188,   286,    -1,    46,   156,   279,
     289,    -1,   109,    -1,   181,    -1,   164,    -1,    -1,   163,
      61,   141,    -1,    -1,    49,   290,    -1,   143,   153,   291,
      -1,    60,   290,    -1,   132,   290,    -1,    92,   296,   115,
     299,   154,   282,    -1,   297,    -1,   296,   188,   297,    -1,
      45,   298,    -1,    46,    -1,    64,    -1,    64,   156,    -1,
      72,    -1,    77,    -1,    92,   117,    -1,   101,    -1,   155,
      -1,   135,    -1,   127,    -1,   129,    -1,    -1,    34,    -1,
     329,    -1,   130,   296,   301,    88,   282,    -1,   115,   299,
      -1,    -1,   122,   303,    88,   304,    -1,   331,    -1,   236,
      -1,   230,    -1,   208,    -1,   207,    -1,   138,   306,    -1,
     307,    -1,   306,   188,   307,    -1,    14,   308,   198,    -1,
     328,   308,   198,    -1,    90,   328,   308,   198,    -1,   136,
     328,   308,   198,    -1,    91,    42,   328,   308,   198,    -1,
     137,    42,   328,   308,   198,    -1,    13,   308,   198,    -1,
     154,    -1,    24,    -1,    14,    -1,    83,   303,   311,    -1,
     157,   312,    -1,    -1,   309,    -1,   312,   188,   309,    -1,
     314,   122,   303,    -1,    69,    -1,    77,    -1,    46,   146,
     263,   316,    -1,    46,   146,   263,   126,   154,   263,    -1,
     317,    -1,   316,   188,   317,    -1,    43,   318,   215,    -1,
      77,   318,   328,   319,    -1,    46,   318,   328,   320,    -1,
     126,   318,   328,   154,   331,    -1,    62,    -1,    -1,    55,
      -1,   128,    -1,    -1,   138,    20,    10,    -1,    77,    20,
      10,    -1,   138,    71,   195,    -1,    77,    71,    -1,    46,
     145,   138,   322,    -1,   323,    -1,   322,   188,   323,    -1,
     328,    24,   195,   324,   325,   177,    24,   326,   327,    -1,
      59,     4,    -1,    -1,   134,    24,   111,    -1,   134,    24,
     142,    -1,   134,    24,    53,    -1,    -1,   173,    -1,   182,
      -1,   166,    -1,   171,    -1,    58,    24,     5,    -1,   175,
      24,     4,   176,    24,     5,    -1,    -1,     3,    -1,   332,
      -1,     3,    -1,   332,    -1,     3,    -1,     3,    -1,   332,
      -1,   165,    -1,   166,    -1,   167,    -1,   168,    -1,   169,
      -1,   170,    -1,   171,    -1,   172,    -1,   173,    -1,   174,
      -1,   175,    -1,   176,    -1,   177,    -1,   178,    -1,   179,
      -1,   180,    -1,   181,    -1,   182,    -1,   183,    -1,   184,
      -1,   185,    -1,   186,    -1
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
    1720,  1722,  1724,  1729,  1731,  1733,  1735,  1737,  1741,  1754,
    1758,  1765,  1774,  1784,  1788,  1790,  1792,  1797,  1798,  1799,
    1804,  1805,  1807,  1813,  1814,  1824,  1830,  1834,  1840,  1846,
    1852,  1864,  1870,  1874,  1886,  1890,  1896,  1901,  1911,  1917,
    1923,  1927,  1938,  1944,  1949,  1962,  1967,  1971,  1976,  1980,
    1986,  1997,  2009,  2021,  2032,  2036,  2042,  2048,  2053,  2058,
    2063,  2068,  2073,  2078,  2083,  2088,  2093,  2100,  2105,  2110,
    2115,  2126,  2166,  2171,  2182,  2189,  2194,  2196,  2198,  2200,
    2211,  2219,  2223,  2230,  2236,  2243,  2250,  2257,  2264,  2271,
    2280,  2281,  2285,  2296,  2303,  2308,  2313,  2317,  2330,  2338,
    2340,  2351,  2357,  2368,  2372,  2379,  2384,  2390,  2395,  2404,
    2405,  2409,  2410,  2411,  2415,  2420,  2425,  2429,  2443,  2451,
    2455,  2462,  2477,  2480,  2484,  2486,  2488,  2491,  2495,  2500,
    2505,  2510,  2518,  2522,  2527,  2538,  2540,  2557,  2559,  2576,
    2580,  2582,  2595,  2596,  2597,  2598,  2599,  2600,  2601,  2602,
    2603,  2604,  2605,  2606,  2607,  2608,  2609,  2610,  2611,  2612,
    2613,  2614,  2615,  2616
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
  "SMALLINT", "SNAPSHOT", "SPFILE", "START", "STATIC", "SYSTEM", "TABLE",
  "TABLES", "THEN", "TIME", "TIMESTAMP", "TINYINT", "TRAILING",
  "TRANSACTION", "TO", "UPDATE", "USER", "USING", "VALUES", "VARCHAR",
  "VARBINARY", "WHERE", "WHEN", "WITH", "WORK", "AUTO_INCREMENT",
  "CHUNKSERVER", "COMPRESS_METHOD", "CONSISTENT_MODE", "EXPIRE_INFO",
  "GRANTS", "MERGESERVER", "REPLICA_NUM", "ROOTSERVER", "SERVER",
  "SERVER_IP", "SERVER_PORT", "SERVER_TYPE", "STATUS", "TABLET_BLOCK_SIZE",
  "TABLET_MAX_SIZE", "UNLOCKED", "UPDATESERVER", "USE_BLOOM_FILTER",
  "VARIABLES", "VERBOSE", "WARNINGS", "';'", "','", "$accept", "sql_stmt",
  "stmt_list", "stmt", "expr_list", "column_ref", "expr_const",
  "simple_expr", "arith_expr", "expr", "in_expr", "case_expr", "case_arg",
  "when_clause_list", "when_clause", "case_default", "func_expr",
  "distinct_or_all", "delete_stmt", "update_stmt", "update_asgn_list",
  "update_asgn_factor", "create_table_stmt", "opt_if_not_exists",
  "table_element_list", "table_element", "column_definition", "data_type",
  "opt_decimal", "opt_float", "opt_precision", "opt_time_precision",
  "opt_char_length", "opt_column_attribute_list", "column_attribute",
  "opt_table_option_list", "table_option", "opt_equal_mark",
  "drop_table_stmt", "opt_if_exists", "table_list", "insert_stmt",
  "replace_or_insert", "opt_insert_columns", "column_list",
  "insert_vals_list", "insert_vals", "select_stmt", "select_with_parens",
  "select_no_parens", "no_table_select", "select_clause", "simple_select",
  "opt_where", "select_limit", "opt_hint", "opt_hint_list", "hint_option",
  "limit_expr", "opt_select_limit", "opt_for_update", "parameterized_trim",
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
     426,   427,   428,   429,   430,   431,   432,    59,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   189,   190,   191,   191,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     192,   192,   192,   192,   192,   192,   192,   192,   192,   192,
     193,   193,   194,   194,   194,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   196,   196,   196,   196,   196,
     196,   196,   196,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   198,   198,   198,   198,   199,   199,   200,   201,   201,
     202,   202,   203,   204,   204,   205,   205,   205,   205,   205,
     205,   206,   206,   207,   208,   209,   209,   210,   211,   212,
     212,   213,   213,   214,   214,   215,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   216,   216,   216,
     216,   216,   216,   216,   216,   216,   216,   217,   217,   217,
     218,   218,   219,   219,   220,   220,   221,   221,   222,   222,
     223,   223,   223,   223,   223,   224,   224,   224,   225,   225,
     225,   225,   225,   225,   225,   226,   226,   227,   228,   228,
     229,   229,   230,   230,   230,   231,   231,   232,   232,   233,
     233,   234,   234,   235,   235,   236,   236,   237,   237,   238,
     238,   238,   238,   239,   239,   240,   240,   241,   241,   241,
     241,   242,   242,   242,   243,   243,   243,   243,   243,   244,
     244,   245,   245,   245,   246,   247,   247,   248,   248,   249,
     249,   250,   250,   250,   250,   250,   250,   250,   251,   251,
     252,   252,   253,   254,   254,   255,   256,   256,   256,   257,
     257,   258,   258,   258,   259,   259,   259,   259,   260,   260,
     261,   261,   262,   262,   262,   262,   262,   262,   262,   262,
     263,   264,   264,   264,   265,   265,   265,   265,   266,   266,
     267,   268,   268,   268,   268,   269,   269,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   270,   270,   270,
     270,   271,   271,   271,   272,   272,   272,   273,   273,   273,
     274,   274,   274,   275,   275,   276,   277,   277,   278,   279,
     280,   281,   282,   282,   283,   283,   284,   284,   285,   286,
     287,   287,   288,   289,   289,   290,   290,   291,   291,   292,
     292,   293,   294,   295,   296,   296,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   297,   297,   298,   298,   299,
     299,   300,   301,   301,   302,   303,   304,   304,   304,   304,
     305,   306,   306,   307,   307,   307,   307,   307,   307,   307,
     308,   308,   309,   310,   311,   311,   312,   312,   313,   314,
     314,   315,   315,   316,   316,   317,   317,   317,   317,   318,
     318,   319,   319,   319,   320,   320,   320,   320,   321,   322,
     322,   323,   324,   324,   325,   325,   325,   325,   326,   326,
     326,   326,   327,   327,   327,   328,   328,   329,   329,   330,
     331,   331,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332,   332,   332,   332,   332,   332,   332,
     332,   332,   332,   332
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
       3,     1,     1,     1,     1,     1,     0,     3,     5,     5,
       4,     4,     4,     2,     4,     3,     3,     3,     3,     3,
       3,     4,     2,     0,     1,     2,     4,     1,     1,     0,
       0,     2,     2,     0,     1,     3,     1,     3,     4,     1,
       1,     3,     1,     3,     5,     6,     2,     0,     3,     3,
       1,     3,     4,     1,     1,     1,     0,     3,     0,     2,
       3,     2,     2,     6,     1,     3,     2,     1,     1,     2,
       1,     1,     2,     1,     1,     1,     1,     1,     0,     1,
       1,     5,     2,     0,     4,     1,     1,     1,     1,     1,
       2,     1,     3,     3,     3,     4,     4,     5,     5,     3,
       1,     1,     1,     3,     2,     0,     1,     3,     3,     1,
       1,     4,     6,     1,     3,     3,     4,     4,     5,     1,
       0,     1,     1,     0,     3,     3,     3,     2,     4,     1,
       3,     9,     2,     0,     3,     3,     3,     0,     1,     1,
       1,     1,     3,     6,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
      29,     0,     0,   336,   336,     0,   389,     0,     0,     0,
     390,     0,   286,     0,   186,     0,     0,   185,     0,   336,
     219,     0,   309,     0,     0,     0,     0,     4,     9,     8,
       7,    10,     6,     0,     5,   206,   195,   199,   241,   205,
      11,    12,    19,    20,    21,    22,    23,    26,    27,    28,
      24,    25,    13,    14,    15,    18,     0,    16,    17,   206,
       0,     0,     0,     0,   335,   339,   341,   120,     0,     0,
     427,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   313,   270,   428,   313,   178,     0,   430,
     385,   365,   431,   285,     0,   358,   347,   348,   350,   351,
       0,   353,   356,   355,   354,     0,   344,     0,     0,   363,
     342,   223,   251,   425,     0,     0,     0,     0,   327,     0,
       0,   370,   371,     0,   426,   429,     0,     0,   307,   310,
     293,   308,     0,   310,   327,     0,   303,     0,     0,     0,
     338,     0,     1,     2,    29,     0,   251,   251,   251,     0,
       0,   229,     0,   200,     0,   198,   197,     0,     0,   319,
       0,     0,     0,   315,   316,     0,   211,   314,   296,   295,
       0,     0,   322,   321,     0,   383,   282,   284,   283,   281,
     280,   357,   346,   349,   352,     0,     0,     0,     0,   330,
     328,     0,     0,   224,     0,   221,   252,   253,     0,   381,
     380,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,   310,   287,     0,
     299,   304,   310,     0,   297,   298,   310,     0,     0,   340,
       0,     3,   188,     0,     0,     0,     0,     0,     0,   229,
     201,   230,   388,   408,   409,     0,   400,   400,   400,   400,
     391,   393,     0,   333,   334,   332,     0,     0,     0,     0,
       0,   113,   179,     0,   177,     0,   180,   262,   268,   270,
       0,   382,   386,   384,   359,     0,   360,   345,   369,   368,
     367,   366,   364,     0,     0,   362,     0,   220,     0,   425,
      35,    37,    36,    39,    38,    40,    41,    43,    42,     0,
       0,     0,   257,     0,    99,     0,     0,    45,    46,    63,
     254,    49,    50,    51,   258,   227,    32,     0,   426,   379,
     373,     0,     0,   326,     0,     0,     0,   372,   374,   310,
     310,   294,   311,   312,   290,   305,   291,   302,   292,     0,
     110,   111,     0,   112,     0,     0,     0,    30,     0,     0,
       0,   211,   115,     0,     0,     0,   183,   219,   206,   210,
     205,   208,   209,   246,   242,   243,   225,   226,   216,   217,
     202,     0,     0,   399,     0,     0,     0,     0,     0,     0,
       0,   119,     0,   317,     0,     0,   212,   206,     0,   268,
       0,     0,   267,   279,   277,     0,   279,   279,     0,     0,
     265,     0,   323,     0,     0,   329,   331,   361,   222,    83,
      64,    65,     0,    30,    51,    98,     0,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   255,     0,     0,   228,   203,     0,   375,     0,   320,
     324,   376,     0,   289,   288,     0,     0,   105,     0,     0,
       0,     0,     0,     0,   107,     0,     0,     0,     0,   109,
     337,     0,   114,     0,     0,   189,     0,   251,   247,   248,
     245,     0,     0,     0,     0,   410,   413,   395,     0,     0,
     403,   392,     0,   400,   394,   325,     0,     0,   121,   123,
     318,   213,   271,   181,   266,   278,   274,     0,   275,   276,
       0,   264,   263,   387,   343,     0,    47,     0,   104,   100,
      44,    82,    81,     0,     0,     0,    78,    76,    77,    75,
      74,    73,    94,    79,     0,     0,    53,     0,     0,    92,
      95,    86,    84,    88,     0,    66,    67,    68,    69,    70,
      72,    71,   256,   211,   211,   260,   259,    34,    33,   377,
     378,   306,   301,   235,     0,   236,     0,   237,     0,    31,
     130,   157,   133,   157,   143,   145,   138,   149,   153,   151,
     129,   128,   144,   149,   135,   127,   155,   155,   126,   157,
     157,     0,   231,   106,   116,   117,   187,     0,     0,   182,
       0,   244,   214,   218,   215,     0,   417,   159,     0,     0,
     397,   401,   402,   396,     0,     0,   167,     0,     0,     0,
       0,    31,     0,     0,   101,     0,    80,     0,    93,    54,
      55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    87,    85,    89,   227,     0,   238,   232,   233,   234,
       0,   140,   139,     0,   131,   152,   136,     0,   134,   132,
       0,   146,   137,   141,   142,   108,   184,   190,   193,     0,
       0,     0,   412,     0,     0,   125,     0,   407,     0,     0,
     398,     0,   176,   176,   176,   176,   176,   176,   176,   118,
     165,   122,   269,   273,     0,    48,     0,   103,    97,     0,
      90,    56,    57,    58,    59,    60,    62,    61,    96,   204,
     261,     0,   249,     0,     0,     0,     0,   191,     0,     0,
       0,     0,     0,   161,     0,     0,     0,   163,   158,   405,
     404,   406,     0,   175,     0,     0,     0,     0,     0,     0,
       0,     0,   272,   102,    91,     0,     0,   207,   156,   148,
       0,   150,   154,   194,     0,   416,   414,   415,     0,   160,
     162,   164,   124,   172,   174,   168,   171,   170,   169,   173,
     166,   239,   250,     0,   192,   420,   421,   418,   419,   424,
     147,     0,     0,   411,     0,     0,   422,     0,     0,     0,
     423
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,   356,   317,   318,   319,   547,   320,
     549,   321,   426,   528,   529,   635,   322,   358,    28,    29,
     361,   362,    30,   172,   507,   508,   509,   601,   664,   668,
     666,   671,   661,   685,   738,   699,   700,   744,    31,   181,
     274,    32,    33,   365,   484,   609,   679,    34,   323,    36,
      37,    38,    39,   271,   454,   122,   204,   205,   378,   455,
     163,   359,   722,   160,   161,   374,   375,   490,   757,   208,
     324,   325,   564,   565,   277,   278,   408,   516,    40,   190,
     104,    41,   234,   230,   148,   226,   178,    42,   173,   174,
     182,   460,    43,   183,    44,   216,    45,   199,   200,    46,
     265,    65,   239,    47,    48,    49,    50,   115,   116,   192,
     285,    51,   202,    52,   100,   292,    53,   131,   132,   211,
     282,    54,   185,   283,    55,    56,    57,   260,   261,   388,
     623,   620,    58,   253,   254,   616,   684,   789,   793,   326,
     327,   149,   101,   328
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -481
static const yytype_int16 yypact[] =
{
    2069,    -6,   131,   -81,   -81,   -66,  -481,    27,  1868,  1868,
      76,  1898,   -98,   446,  -481,  1898,    67,  -481,   446,   -81,
      52,   462,   360,    32,  1868,   217,   -55,  -481,  -481,  -481,
    -481,  -481,  -481,   134,  -481,   -50,  -481,  -481,    35,     7,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,   124,  -481,  -481,   199,
     208,   115,  1868,   267,  -481,  -481,  -481,   185,   267,  1868,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,   288,  -481,  -481,   288,   195,   267,  -481,
     146,  -481,  -481,  -481,     4,   178,  -481,   160,  -481,  -481,
     204,  -481,  -481,  -481,  -481,   -45,  -481,   235,   267,    20,
    -481,   201,    36,  -481,     3,     3,  1922,   292,   250,  1922,
     300,   159,  -481,     3,  -481,  -481,    54,   210,  -481,   -11,
    -481,  -481,   174,   -11,   270,   176,   252,   213,   203,   356,
     238,   265,  -481,  -481,  2069,  1868,    36,    36,    36,   350,
      10,   -15,   255,  -481,  1898,  -481,  -481,  1922,   232,  -481,
      12,   387,  1868,   223,  -481,   315,   253,  -481,  -481,  -481,
     331,  1240,  -481,   230,   403,  -481,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  1684,   446,     4,   268,  -481,
     233,  1684,   339,  -481,   -42,  -481,  -481,  -481,   970,  -481,
    -481,  1554,  1554,     3,  1922,   267,   395,     3,  1922,  1738,
    1554,  1868,  1868,  1868,   424,  1554,  -481,   -11,  -481,    61,
    -481,  -481,   -11,   426,  -481,  -481,   -11,   728,   371,  -481,
    1922,  -481,     9,    18,    18,    18,  1554,   236,   236,   346,
    -481,  -481,  -481,   247,  -481,   412,   377,   377,   377,    13,
     257,  -481,   394,  -481,  -481,  -481,   370,   415,   267,   409,
    1024,  -481,  -481,  1713,   278,  1528,   202,  1641,  -481,   422,
     267,  -481,  -481,   281,  -481,   313,  -481,  -481,  -481,  -481,
    -481,  -481,  -481,   267,   267,  -481,   267,  -481,   201,   164,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  1554,
    1554,  1554,  -481,  1208,  1554,   430,   431,  -481,  -481,  -481,
     920,  -481,  -481,  -481,  -481,   -43,  -481,   432,   438,  2469,
    2469,  1554,     3,  -481,   468,  1554,     3,  -481,  2469,   -11,
     -11,  -481,  -481,  2469,  -481,   442,  -481,   306,  -481,   454,
    -481,  -481,  1262,  -481,  1316,  1500,    -9,  2223,  1554,   456,
     357,   -82,  -481,   475,  1765,   342,  -481,    52,  -481,   485,
    -481,   485,  -481,  2365,   320,  -481,  -481,  -481,    24,   396,
    -481,  1922,   276,  -481,  1922,  1922,  1922,  1868,  1922,   254,
     468,  -481,  1829,  -481,   468,  1554,  2469,   998,   202,   463,
    1240,  1868,  -481,   391,  -481,  1240,   391,   391,   416,  1868,
    -481,  1868,  -481,   403,   267,  -481,  -481,   230,  -481,   820,
    -481,  -481,   333,  2396,   279,  2469,   367,  -481,  1922,  1554,
    1554,   282,  1554,  1554,  1554,  1554,  1554,  1554,  1554,  1554,
    1608,   482,   316,  1554,  1554,  1554,  1554,  1554,  1554,  1554,
    1898,  -481,  1293,   970,  -481,  -481,  1796,  2469,  1554,  -481,
    -481,  2469,  1554,  -481,  -481,   491,   526,  -481,  1554,  2253,
    1554,  2294,  1554,  2324,  -481,  1554,  2080,  1554,  2421,  -481,
    -481,  1922,  -481,  1554,    -8,  -481,   493,    36,  -481,  -481,
    -481,  1554,   236,   236,   236,  -481,   477,  -481,  2080,    91,
      59,  -481,   383,   377,  -481,  -481,   435,    -2,  -481,  -481,
    -481,  2469,   496,   202,  -481,  -481,  -481,   229,  -481,  -481,
    1240,  -481,  -481,  -481,   230,  1554,  -481,  1554,   -32,  -481,
    -481,   794,   820,  1554,  1608,   482,   582,   582,   582,   582,
     582,   582,   757,   837,  1608,  1608,  -481,   452,  1208,  -481,
    -481,  -481,  -481,  -481,   330,   423,   423,   512,   512,   512,
     512,  -481,  -481,   253,   -72,   202,  -481,  -481,  -481,  2469,
    2469,  -481,  -481,  2469,  1554,  2469,  1554,  2469,  1554,  2469,
    -481,   511,  -481,   511,  -481,  -481,  -481,   518,   443,   519,
    -481,  -481,  -481,   518,  -481,  -481,   523,   523,  -481,   511,
     511,   524,  2469,  -481,  -481,  2469,    -6,  1922,  1554,   381,
     970,  -481,  -481,  -481,  -481,   566,   450,  -481,    57,   163,
    -481,  -481,  -481,  -481,  1898,   532,   388,  1829,  1868,  1554,
     240,  2445,  1091,  1554,  -481,   507,   837,   542,  -481,  -481,
    -481,  1608,  1608,  1608,  1608,  1608,  1608,  1608,  1608,     2,
    2469,  -481,  -481,  -481,    10,  1240,   504,  2469,  2469,  2469,
     595,  -481,  -481,   597,  -481,  -481,  -481,   598,  -481,  -481,
     600,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  2469,    14,
     567,   -63,  -481,   599,   445,    26,   639,  -481,   640,   276,
    -481,  1922,   627,   627,   627,   627,   627,   627,   627,   465,
    -481,  -481,  -481,  2469,  1554,  -481,  1554,  2469,  -481,  1608,
     558,   490,   490,   616,   616,   616,   616,  -481,  -481,  -481,
     202,   602,   564,   618,    15,   621,   630,  -481,  1554,  1554,
    1240,    47,   649,  -481,   671,   276,   578,  -481,  -481,  -481,
    -481,  -481,    19,  -481,   679,   541,   682,   685,   686,   687,
     688,   388,  2469,  2469,   558,  1554,  1554,  -481,  -481,  -481,
     689,  -481,  -481,  2469,    21,  -481,  -481,  -481,   206,  -481,
    -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,  -481,
    -481,   499,  2469,   654,  -481,  -481,  -481,  -481,  -481,   -39,
    -481,   673,   674,  -481,   695,   698,  -481,   528,   681,   702,
    -481
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -481,  -481,  -481,   555,  -309,  -481,  -367,  -379,  -471,   231,
     175,  -481,  -481,  -481,   183,  -481,   690,  -481,   -64,   -37,
    -481,   234,  -481,  -481,  -481,    86,   332,   219,   125,  -481,
    -481,   122,  -480,  -481,  -481,  -481,   -31,  -182,  -481,  -481,
    -481,   -35,  -481,  -481,    30,  -481,    -5,  -101,     0,     6,
    -481,   106,   147,  -350,   563,   358,  -481,   428,  -235,    75,
     -93,  -481,  -481,  -481,  -481,  -481,   237,  -481,  -481,  -134,
     286,   133,  -481,  -172,    33,   471,  -481,  -108,  -481,  -481,
    -481,  -481,  -481,  -481,  -481,  -114,   650,  -481,  -481,   467,
     -33,  -308,  -481,  -280,  -481,   601,  -481,   453,  -481,  -481,
    -481,    74,  -481,  -481,  -481,  -481,  -481,   731,   554,  -481,
     550,  -481,  -481,  -481,    -1,  -481,  -481,  -481,   533,  -105,
     340,  -481,  -481,  -481,  -481,  -481,  -481,  -481,   365,   118,
    -481,  -481,  -481,  -481,   374,  -481,  -481,  -481,  -481,   -19,
      29,  -481,  -310,    -3
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -430
static const yytype_int16 yytable[] =
{
      35,    59,   133,   189,   422,    95,    95,    60,   102,   276,
     451,   482,   102,   379,   117,   496,   417,   224,   134,   791,
     212,    95,   243,   244,   245,   730,   153,   209,   220,   228,
     170,  -196,   474,   606,     1,   175,   733,    94,    94,   626,
     186,    93,    96,   718,     1,   452,   734,   633,  -229,   364,
     156,   157,   158,    94,   297,   727,   759,   151,     1,    95,
     772,   546,   784,   637,   247,   169,    95,   187,   250,   188,
     195,   248,   162,   639,   640,   383,     7,   686,    66,   270,
      67,   206,   505,    64,   221,   198,   510,   103,  -229,   270,
      68,    94,  -240,   120,   162,   168,   291,   735,    94,  -240,
     765,   398,   176,   662,    35,    14,   481,   213,   331,   262,
     217,   207,   335,   344,   621,    69,   655,   247,   346,   673,
     674,   263,   348,   134,   248,   453,   134,   345,   687,    20,
     527,    17,   154,   288,   524,   201,   792,  -196,   492,    20,
     562,   366,   222,   196,    20,   453,   298,   121,   255,   736,
     225,   159,    95,   367,    35,   546,   380,   210,   766,    24,
     289,   102,   290,   252,   134,   546,   546,   387,   618,    95,
     710,   711,   712,   713,   714,   715,   716,   717,    95,   475,
     607,   275,   333,   688,    94,   150,   627,   622,   242,   767,
     475,   737,    95,   264,  -229,   332,   333,    35,    95,   336,
     133,    94,   728,   760,  -429,   267,  -427,   607,   196,   728,
     279,   134,   493,   654,   656,   134,   134,   152,    95,    95,
      95,   363,    97,   118,   286,   463,   464,   458,   513,   619,
     286,   462,    98,   517,   689,   175,   155,   134,   754,   649,
     165,   376,    35,   368,   368,   368,   164,   412,   377,   166,
      94,    94,    94,   167,   339,   340,   341,   612,   613,   614,
     415,   198,   546,   546,   546,   546,   546,   546,   546,   546,
      95,   169,    95,   397,    95,   256,    61,    62,   257,    60,
     300,   301,   302,   171,   303,   304,   305,    63,   306,   307,
     308,   403,   177,   180,  -206,  -206,  -206,   256,   518,   519,
     257,   404,   279,   184,   402,   405,   410,   191,   406,   258,
     533,   534,   535,   424,   690,   427,   193,   102,   403,    60,
     165,   194,   741,   197,   551,   203,   552,   553,   404,   403,
     546,   258,   405,   407,   214,   406,   554,   215,   651,   404,
     652,   653,   218,   405,   629,   485,   406,   219,   630,   369,
     371,   372,   227,   610,   232,   704,   223,   229,   259,   233,
     407,   134,   255,   135,    59,   498,   499,   500,   770,   502,
      60,   407,   785,   498,   384,   385,   386,   786,   134,   787,
     503,   134,   134,   134,    95,   134,  -206,   236,   788,   134,
     370,   370,   370,  -206,    95,  -206,   237,    95,    95,   235,
     275,   238,    95,   240,   246,   275,    95,   266,    95,   530,
     251,   268,   269,   316,   270,   272,    94,   281,   280,   334,
     501,   294,   293,   136,   137,   134,   402,   296,   342,   279,
     514,   347,   360,   162,   279,   381,   382,   568,   521,   383,
      94,   550,   329,   330,   522,   389,   781,   102,   390,    95,
     138,   338,   275,   134,   391,   392,   343,   445,   446,   447,
     448,   449,   363,   394,   411,   123,   400,   414,   357,   413,
       1,   641,   459,   428,   456,   124,   125,   373,   134,   139,
    -428,   279,   465,   720,   642,   643,   644,   645,   646,   647,
     648,   105,   106,   140,   466,   467,   141,   479,   480,   483,
     486,   396,   158,   494,   512,   676,   142,   143,   491,   515,
     107,   745,   746,   747,   748,   749,   750,    95,   108,   520,
     275,   525,   548,   109,   644,   645,   646,   647,   648,   527,
     144,   572,   571,   608,   145,   550,   615,   624,   110,   625,
     419,   420,   421,   628,   423,   425,   146,   111,   424,   279,
     449,   660,   126,   127,    60,   692,   693,   694,   663,   667,
     695,   709,   457,   670,   665,   675,   461,   696,   697,   680,
     682,   698,   691,   112,   642,   643,   644,   645,   646,   647,
     648,   113,   128,   469,   683,   471,   473,   708,   677,   478,
     642,   643,   644,   645,   646,   647,   648,   721,   129,   130,
     723,   114,   724,   725,   134,   726,    35,   729,   498,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,   448,
     449,   102,   732,   731,   134,    95,   511,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,   739,
     740,   743,    95,   751,   648,   275,   755,   702,   756,   758,
     531,   532,   761,   536,   537,   538,   539,   540,   541,   542,
     543,   762,   485,   768,   555,   556,   557,   558,   559,   560,
     561,   769,   771,   773,   279,   774,   775,   475,   134,   569,
     776,   777,   778,   570,   783,   790,   779,   794,   795,   573,
     796,   575,   797,   577,   798,   799,   579,   800,   602,   241,
     638,   634,   147,   701,   605,   604,   497,   617,   669,   672,
     780,   742,   373,   249,   764,   487,   418,    95,   611,   719,
     275,   299,   300,   301,   302,   393,   303,   304,   305,   566,
     306,   307,   308,   681,   399,   231,   179,   416,   309,   119,
     287,   295,   337,   523,   504,   495,   631,     0,   632,   279,
     310,   311,   349,     0,   636,     0,     0,     0,   313,   350,
       0,     0,     0,   351,     0,     0,     0,     0,     0,   650,
       0,   352,     0,     0,   314,   439,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,     0,     0,     0,     0,
       0,     0,     0,   353,     0,   657,     0,   658,     0,   659,
       0,     0,   315,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,   354,     0,     0,     0,     0,     0,   678,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,     0,
     703,     0,     0,     0,   707,   316,   440,   441,   442,   443,
     444,   445,   446,   447,   448,   449,     0,     0,     0,     0,
     355,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,     0,     0,     0,
       0,     0,     0,    99,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   752,     0,   753,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
     441,   442,   443,   444,   445,   446,   447,   448,   449,   763,
     678,     0,     0,     0,     0,     0,     0,   450,     0,     0,
       0,     0,     0,   299,   300,   301,   302,     0,   303,   304,
     305,     0,   306,   307,   308,     0,   650,   782,     0,     0,
     309,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,   310,   311,   312,     0,     0,     0,     0,     0,
     313,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   314,   299,   300,   301,
     302,   395,   303,   304,   305,     0,   306,   307,   308,   165,
       0,     0,     0,     0,   309,   401,     0,     0,     0,     0,
       0,     0,     0,     0,   315,     0,   310,   311,     0,     0,
       0,     0,     0,     0,   313,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     314,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,   316,   315,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
       0,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,     0,     0,     0,
       0,   316,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   299,   300,   301,   302,     0,   303,   304,   305,     0,
     306,   307,   308,     0,     0,     0,     0,     0,   309,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   706,
     310,   311,     0,    70,     0,     0,     0,     0,   313,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   314,   299,   300,   301,   302,     0,
     303,   304,   305,     0,   306,   307,   308,     0,     0,     0,
     273,     0,   309,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   315,     0,   310,   311,    70,     0,     0,     0,
       0,     0,   313,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   314,   299,
     300,   301,   302,     0,   303,   304,   305,     0,   306,   307,
     308,     0,     0,   273,     0,     0,   309,     0,     0,     0,
       0,     0,     0,    20,     0,   316,   315,     0,   310,   311,
     468,     0,     0,     0,     0,     0,   313,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   563,   314,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,     0,     0,   316,
     315,     0,     0,     0,   470,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     0,
       0,     0,     0,   316,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   299,   300,   301,   302,     0,   303,   304,
     305,     0,   306,   307,   308,     0,     0,     0,     0,     0,
     309,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    70,   310,   311,     0,     0,     0,     0,     0,     0,
     313,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   314,   299,   300,   301,
     302,     0,   303,   304,   305,     0,   306,   307,   308,     0,
       0,     0,     0,     0,   309,   401,     0,     0,     0,     0,
       0,     0,     0,     0,   315,     0,   310,   311,   472,     0,
       0,     0,     0,     0,   313,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     314,   299,   300,   301,   302,     0,   303,   304,   305,     0,
     306,   307,   308,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   316,   315,     0,
     544,   545,     0,     0,    70,     0,     0,     0,   313,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   314,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    70,   409,     0,
       0,   316,   315,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,    70,     0,   284,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,   123,     0,     0,     0,   316,     0,     0,     0,     0,
       0,   124,   125,   273,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,     0,     0,   123,
       0,     0,     0,     0,     0,     1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,   126,   127,
     567,     0,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    70,     0,     0,   129,   130,     0,     0,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      20,    99,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   123,     0,     0,     0,     0,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,   506,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,     0,     0,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,     0,     0,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,     1,
       0,     0,     0,     0,     0,     2,     0,     0,     3,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
     580,   581,   582,     5,     0,     0,     0,   583,     6,     0,
       0,     7,     8,     9,     0,   584,    10,   585,   586,     0,
     587,     0,    11,     0,    12,     0,   588,     0,     0,     0,
       0,    13,     0,     0,     0,     0,   589,     0,     0,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     590,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     591,    15,   592,   593,     0,    16,    17,     0,     0,    18,
       0,    19,     0,     0,    20,   594,     0,    21,    22,     0,
       0,     0,    23,     0,     0,     0,     0,     0,     0,     0,
     595,     0,     0,     0,    24,     0,     0,     0,     0,   596,
     597,   598,     0,     0,     0,     0,     0,     0,     0,   599,
     600,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,     0,     0,     0,     0,     0,     0,     0,     0,
     476,   429,   430,   431,   432,   433,   434,   435,   436,   437,
     438,   439,   440,   441,   442,   443,   444,   445,   446,   447,
     448,   449,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   477,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,     0,     0,     0,     0,     0,     0,     0,
       0,   574,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,   441,   442,   443,   444,   445,   446,
     447,   448,   449,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   576,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,     0,     0,     0,     0,     0,     0,
       0,     0,   578,   488,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,     0,     0,   526,   489,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   441,   442,   443,   444,   445,   446,   447,   448,   449,
       0,     0,   603,   429,   430,   431,   432,   433,   434,   435,
     436,   437,   438,   439,   440,   441,   442,   443,   444,   445,
     446,   447,   448,   449,     0,     0,   705,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   441,
     442,   443,   444,   445,   446,   447,   448,   449
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-481)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     1,    21,   104,   313,     8,     9,     1,    11,   181,
     320,   361,    15,   248,    15,   382,   296,    28,    21,    58,
     125,    24,   156,   157,   158,    88,    81,    24,   133,   143,
      63,    81,    41,    41,    40,    68,    10,     8,     9,    41,
     104,     8,     9,    41,    40,    88,    20,    79,    41,    40,
      15,    16,    17,    24,    96,    41,    41,    24,    40,    62,
      41,   440,    41,   534,   107,     4,    69,   104,   161,   104,
     115,   114,    87,   544,   545,    62,    72,    20,     4,   161,
     146,    45,   390,   164,    30,   118,   394,   185,    81,   161,
     156,    62,   107,    19,    87,    62,   197,    71,    69,   114,
      53,   273,    69,   583,   104,   101,   188,   126,   213,    97,
     129,    75,   217,   227,    55,    88,   188,   107,   232,   599,
     600,   109,   236,   126,   114,   188,   129,    66,    71,   135,
     162,   127,   187,   197,   414,   115,   175,   187,   114,   135,
     450,   242,    88,   188,   135,   188,   188,    95,   167,   123,
     161,   116,   155,   135,   154,   534,   249,   154,   111,   155,
     197,   164,   197,   164,   167,   544,   545,   154,    77,   172,
     641,   642,   643,   644,   645,   646,   647,   648,   181,   188,
     188,   181,   215,    20,   155,   153,   188,   128,   155,   142,
     188,   165,   195,   181,   187,   214,   229,   197,   201,   218,
     219,   172,   188,   188,    40,   172,    42,   188,   188,   188,
     181,   214,   188,   563,   564,   218,   219,     0,   221,   222,
     223,   240,   146,   156,   195,   339,   340,   332,   400,   138,
     201,   336,   156,   405,    71,   268,   102,   240,   709,   548,
      41,     5,   242,   243,   244,   245,   122,   280,    12,    41,
     221,   222,   223,   138,   221,   222,   223,   492,   493,   494,
     293,   294,   641,   642,   643,   644,   645,   646,   647,   648,
     273,     4,   275,   273,   277,    43,   145,   146,    46,   273,
       4,     5,     6,    98,     8,     9,    10,   156,    12,    13,
      14,    89,     4,    98,    15,    16,    17,    43,   406,   407,
      46,    99,   273,   157,   275,   103,   277,   129,   106,    77,
      28,    29,    30,   313,   624,   315,   156,   320,    89,   313,
      41,   117,   689,    88,     8,   124,    10,    11,    99,    89,
     709,    77,   103,   131,    42,   106,    20,    87,     8,    99,
      10,    11,    42,   103,   115,   364,   106,   188,   520,   243,
     244,   245,   178,   487,   178,   115,   146,    87,   126,   107,
     131,   364,   381,     3,   364,   384,   385,   386,   735,   388,
     364,   131,   166,   392,   256,   257,   258,   171,   381,   173,
     126,   384,   385,   386,   387,   388,   107,   184,   182,   392,
     243,   244,   245,   114,   397,   116,    40,   400,   401,   186,
     400,   163,   405,   138,    54,   405,   409,    20,   411,   428,
     155,   188,    97,   137,   161,    84,   387,    14,   188,    24,
     387,   188,   154,    63,    64,   428,   397,    88,     4,   400,
     401,     5,    61,    87,   405,   188,    24,   456,   409,    62,
     411,   441,   211,   212,   411,   188,   755,   450,    54,   452,
      90,   220,   452,   456,    84,    40,   225,    34,    35,    36,
      37,    38,   481,    54,    42,     3,   188,   154,   237,   188,
      40,    19,     4,    42,    42,    13,    14,   246,   481,   119,
      42,   452,    40,   655,    32,    33,    34,    35,    36,    37,
      38,    45,    46,   133,   188,    41,   136,    41,   141,    24,
     158,   270,    17,   107,    41,   606,   146,   147,   188,   118,
      64,   693,   694,   695,   696,   697,   698,   520,    72,   103,
     520,   188,    40,    77,    34,    35,    36,    37,    38,   162,
     170,     5,    41,    40,   174,   535,    59,   154,    92,   104,
     309,   310,   311,    47,   313,   314,   186,   101,   548,   520,
      38,    40,    90,    91,   548,   167,   168,   169,    40,    40,
     172,    19,   331,    40,   121,    41,   335,   179,   180,   188,
       4,   183,    40,   127,    32,    33,    34,    35,    36,    37,
      38,   135,   120,   352,   134,   354,   355,    80,   607,   358,
      32,    33,    34,    35,    36,    37,    38,    93,   136,   137,
       5,   155,     5,     5,   607,     5,   606,    40,   627,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,   624,   177,    24,   627,   628,   395,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,    10,
      10,    24,   655,   188,    38,   655,    54,   628,    94,    41,
     429,   430,    41,   432,   433,   434,   435,   436,   437,   438,
     439,    41,   691,    24,   443,   444,   445,   446,   447,   448,
     449,    10,   104,     4,   655,   144,     4,   188,   691,   458,
       5,     5,     5,   462,     5,    41,     8,    24,    24,   468,
       5,   470,     4,   472,   176,    24,   475,     5,   477,   154,
     535,   528,    22,   627,   483,   481,   384,   498,   593,   597,
     751,   691,   491,   160,   729,   367,   298,   730,   491,   654,
     730,     3,     4,     5,     6,   268,     8,     9,    10,   453,
      12,    13,    14,   610,   273,   144,    96,   294,    20,    18,
     196,   201,   219,   413,   389,   381,   525,    -1,   527,   730,
      32,    33,    34,    -1,   533,    -1,    -1,    -1,    40,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,   548,
      -1,    53,    -1,    -1,    56,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    -1,   574,    -1,   576,    -1,   578,
      -1,    -1,    84,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   105,    -1,    -1,    -1,    -1,    -1,   608,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
     629,    -1,    -1,    -1,   633,   137,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
     152,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   704,    -1,   706,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,   728,
     729,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,     8,     9,
      10,    -1,    12,    13,    14,    -1,   755,   756,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,     3,     4,     5,
       6,     7,     8,     9,    10,    -1,    12,    13,    14,    41,
      -1,    -1,    -1,    -1,    20,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    32,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   137,    84,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,    -1,    -1,    -1,
      -1,   137,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,     3,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   148,
      32,    33,    -1,     3,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,     3,     4,     5,     6,    -1,
       8,     9,    10,    -1,    12,    13,    14,    -1,    -1,    -1,
      40,    -1,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    84,    -1,    32,    33,     3,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,     3,
       4,     5,     6,    -1,     8,     9,    10,    -1,    12,    13,
      14,    -1,    -1,    40,    -1,    -1,    20,    -1,    -1,    -1,
      -1,    -1,    -1,   135,    -1,   137,    84,    -1,    32,    33,
      88,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    56,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,   137,
      84,    -1,    -1,    -1,    88,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,    -1,
      -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
      -1,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,     3,     4,     5,     6,    -1,     8,     9,
      10,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,     3,     4,     5,
       6,    -1,     8,     9,    10,    -1,    12,    13,    14,    -1,
      -1,    -1,    -1,    -1,    20,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    32,    33,    88,    -1,
      -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,     3,     4,     5,     6,    -1,     8,     9,    10,    -1,
      12,    13,    14,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   137,    84,    -1,
      32,    33,    -1,    -1,     3,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,     3,    47,    -1,
      -1,   137,    84,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,     3,    -1,    34,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,     3,    -1,    -1,    -1,   137,    -1,    -1,    -1,    -1,
      -1,    13,    14,    40,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    40,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,    90,    91,
      34,    -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   135,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,     3,    -1,    -1,   136,   137,    -1,    -1,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     135,     3,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,     3,    -1,    -1,    -1,    -1,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,    40,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      50,    51,    52,    64,    -1,    -1,    -1,    57,    69,    -1,
      -1,    72,    73,    74,    -1,    65,    77,    67,    68,    -1,
      70,    -1,    83,    -1,    85,    -1,    76,    -1,    -1,    -1,
      -1,    92,    -1,    -1,    -1,    -1,    86,    -1,    -1,    -1,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     110,   122,   112,   113,    -1,   126,   127,    -1,    -1,   130,
      -1,   132,    -1,    -1,   135,   125,    -1,   138,   139,    -1,
      -1,    -1,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     140,    -1,    -1,    -1,   155,    -1,    -1,    -1,    -1,   149,
     150,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   159,
     160,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    48,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    41,    73,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    41,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    41,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,    40,    46,    49,    60,    64,    69,    72,    73,    74,
      77,    83,    85,    92,   101,   122,   126,   127,   130,   132,
     135,   138,   139,   143,   155,   190,   191,   192,   207,   208,
     211,   227,   230,   231,   236,   237,   238,   239,   240,   241,
     267,   270,   276,   281,   283,   285,   288,   292,   293,   294,
     295,   300,   302,   305,   310,   313,   314,   315,   321,   237,
     238,   145,   146,   156,   164,   290,   290,   146,   156,    88,
       3,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   263,   329,   332,   263,   146,   156,     3,
     303,   331,   332,   185,   269,    45,    46,    64,    72,    77,
      92,   101,   127,   135,   155,   296,   297,   303,   156,   296,
     290,    95,   244,     3,    13,    14,    90,    91,   120,   136,
     137,   306,   307,   328,   332,     3,    63,    64,    90,   119,
     133,   136,   146,   147,   170,   174,   186,   205,   273,   330,
     153,   263,     0,    81,   187,   102,    15,    16,    17,   116,
     252,   253,    87,   249,   122,    41,    41,   138,   263,     4,
     279,    98,   212,   277,   278,   279,   263,     4,   275,   275,
      98,   228,   279,   282,   157,   311,   207,   208,   230,   236,
     268,   129,   298,   156,   117,   115,   188,    88,   279,   286,
     287,   115,   301,   124,   245,   246,    45,    75,   258,    24,
     154,   308,   308,   328,    42,    87,   284,   328,    42,   188,
     308,    30,    88,   146,    28,   161,   274,   178,   274,    87,
     272,   284,   178,   107,   271,   186,   184,    40,   163,   291,
     138,   192,   263,   258,   258,   258,    54,   107,   114,   243,
     249,   155,   303,   322,   323,   328,    43,    46,    77,   126,
     316,   317,    97,   109,   181,   289,    20,   263,   188,    97,
     161,   242,    84,    40,   229,   237,   262,   263,   264,   329,
     188,    14,   309,   312,    34,   299,   329,   297,   207,   208,
     230,   236,   304,   154,   188,   299,    88,    96,   188,     3,
       4,     5,     6,     8,     9,    10,    12,    13,    14,    20,
      32,    33,    34,    40,    56,    84,   137,   194,   195,   196,
     198,   200,   205,   237,   259,   260,   328,   329,   332,   198,
     198,   308,   328,   279,    24,   308,   328,   307,   198,   263,
     263,   263,     4,   198,   274,    66,   274,     5,   274,    34,
      41,    45,    53,    75,   105,   152,   193,   198,   206,   250,
      61,   209,   210,   328,    40,   232,   236,   135,   237,   240,
     241,   240,   240,   198,   254,   255,     5,    12,   247,   247,
     249,   188,    24,    62,   318,   318,   318,   154,   318,   188,
      54,    84,    40,   278,    54,     7,   198,   237,   262,   264,
     188,    47,   329,    89,    99,   103,   106,   131,   265,    47,
     329,    42,   279,   188,   154,   279,   286,   282,   246,   198,
     198,   198,   193,   198,   237,   198,   201,   237,    42,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      47,   331,    88,   188,   243,   248,    42,   198,   308,     4,
     280,   198,   308,   274,   274,    40,   188,    41,    88,   198,
      88,   198,    88,   198,    41,   188,    47,    88,   198,    41,
     141,   188,   242,    24,   233,   328,   158,   244,    48,    73,
     256,   188,   114,   188,   107,   323,   195,   215,   328,   328,
     328,   263,   328,   126,   317,   280,   123,   213,   214,   215,
     280,   198,    41,   262,   329,   118,   266,   262,   266,   266,
     103,   329,   263,   309,   282,   188,    41,   162,   202,   203,
     328,   198,   198,    28,    29,    30,   198,   198,   198,   198,
     198,   198,   198,   198,    32,    33,   196,   197,    40,   199,
     237,     8,    10,    11,    20,   198,   198,   198,   198,   198,
     198,   198,   331,    78,   261,   262,   259,    34,   328,   198,
     198,    41,     5,   198,    88,   198,    88,   198,    88,   198,
      50,    51,    52,    57,    65,    67,    68,    70,    76,    86,
     100,   110,   112,   113,   125,   140,   149,   150,   151,   159,
     160,   216,   198,    41,   210,   198,    41,   188,    40,   234,
     258,   255,   247,   247,   247,    59,   324,   216,    77,   138,
     320,    55,   128,   319,   154,   104,    41,   188,    47,   115,
     262,   198,   198,    79,   203,   204,   198,   197,   199,   197,
     197,    19,    32,    33,    34,    35,    36,    37,    38,   193,
     198,     8,    10,    11,   242,   188,   242,   198,   198,   198,
      40,   221,   221,    40,   217,   121,   219,    40,   218,   217,
      40,   220,   220,   221,   221,    41,   236,   328,   198,   235,
     188,   260,     4,   134,   325,   222,    20,    71,    20,    71,
     331,    40,   167,   168,   169,   172,   179,   180,   183,   224,
     225,   214,   329,   198,   115,    41,   148,   198,    80,    19,
     197,   197,   197,   197,   197,   197,   197,   197,    41,   248,
     262,    93,   251,     5,     5,     5,     5,    41,   188,    40,
      88,    24,   177,    10,    20,    71,   123,   165,   223,    10,
      10,   195,   233,    24,   226,   226,   226,   226,   226,   226,
     226,   188,   198,   198,   197,    54,    94,   257,    41,    41,
     188,    41,    41,   198,   235,    53,   111,   142,    24,    10,
     195,   104,    41,     4,   144,     4,     5,     5,     5,     8,
     225,   193,   198,     5,    41,   166,   171,   173,   182,   326,
      41,    58,   175,   327,    24,    24,     5,     4,   176,    24,
       5
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
      case 190: /* sql_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 191: /* stmt_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 192: /* stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 193: /* expr_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 194: /* column_ref */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 195: /* expr_const */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 196: /* simple_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 197: /* arith_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 198: /* expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 199: /* in_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 200: /* case_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 201: /* case_arg */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 202: /* when_clause_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 203: /* when_clause */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 204: /* case_default */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 205: /* func_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 206: /* distinct_or_all */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 207: /* delete_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 208: /* update_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 209: /* update_asgn_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 210: /* update_asgn_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 211: /* create_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 212: /* opt_if_not_exists */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 213: /* table_element_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 214: /* table_element */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 215: /* column_definition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 216: /* data_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 217: /* opt_decimal */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 218: /* opt_float */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 219: /* opt_precision */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 220: /* opt_time_precision */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 221: /* opt_char_length */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 222: /* opt_column_attribute_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 223: /* column_attribute */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 224: /* opt_table_option_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 225: /* table_option */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 226: /* opt_equal_mark */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 227: /* drop_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 228: /* opt_if_exists */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 229: /* table_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 230: /* insert_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 231: /* replace_or_insert */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 232: /* opt_insert_columns */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 233: /* column_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 234: /* insert_vals_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 235: /* insert_vals */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 236: /* select_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 237: /* select_with_parens */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 238: /* select_no_parens */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 239: /* no_table_select */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 240: /* select_clause */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 241: /* simple_select */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 242: /* opt_where */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 243: /* select_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 244: /* opt_hint */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 245: /* opt_hint_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 246: /* hint_option */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 247: /* limit_expr */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 248: /* opt_select_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 249: /* opt_for_update */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 250: /* parameterized_trim */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 251: /* opt_groupby */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 252: /* opt_order_by */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 253: /* order_by */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 254: /* sort_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 255: /* sort_key */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 256: /* opt_asc_desc */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 257: /* opt_having */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 258: /* opt_distinct */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 259: /* projection */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 260: /* select_expr_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 261: /* from_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 262: /* table_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 263: /* relation_factor */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 264: /* joined_table */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 265: /* join_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 266: /* join_outer */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 267: /* explain_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 268: /* explainable_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 269: /* opt_verbose */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 270: /* show_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 271: /* opt_limit */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 272: /* opt_for_grant_user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 274: /* opt_show_condition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 275: /* opt_like_condition */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 276: /* create_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 277: /* user_specification_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 278: /* user_specification */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 279: /* user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 280: /* password */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 281: /* drop_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 282: /* user_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 283: /* set_password_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 284: /* opt_for_user */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 285: /* rename_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 286: /* rename_info */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 287: /* rename_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 288: /* lock_user_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 289: /* lock_spec */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 290: /* opt_work */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 292: /* begin_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 293: /* commit_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 294: /* rollback_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 295: /* grant_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 296: /* priv_type_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 297: /* priv_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 298: /* opt_privilege */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 299: /* priv_level */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 300: /* revoke_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 301: /* opt_on_priv_level */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 302: /* prepare_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 303: /* stmt_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 304: /* preparable_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 305: /* variable_set_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 306: /* var_and_val_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 307: /* var_and_val */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 308: /* to_or_eq */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 309: /* argument */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 310: /* execute_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 311: /* opt_using_args */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 312: /* argument_list */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 313: /* deallocate_prepare_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 314: /* deallocate_or_drop */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 315: /* alter_table_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 316: /* alter_column_actions */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 317: /* alter_column_action */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 318: /* opt_column */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 320: /* alter_column_behavior */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 321: /* alter_system_stmt */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 322: /* alter_system_actions */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 323: /* alter_system_action */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 324: /* opt_comment */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 326: /* server_type */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 327: /* opt_cluster_or_address */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 328: /* column_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 329: /* relation_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 330: /* function_name */

        {destroy_tree(((*yyvaluep).node));};

        break;
      case 331: /* column_label */

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

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_TABLES, 1, (yyvsp[(3) - (3)].node)); }
    break;

  case 288:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node)); }
    break;

  case 289:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node)); }
    break;

  case 290:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_TABLE_STATUS, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 291:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_SERVER_STATUS, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 292:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_VARIABLES, 1, (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = (yyvsp[(2) - (4)].ival);
    }
    break;

  case 293:

    { malloc_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_SCHEMA); }
    break;

  case 294:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_CREATE_TABLE, 1, (yyvsp[(4) - (4)].node)); }
    break;

  case 295:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 296:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_COLUMNS, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node)); }
    break;

  case 297:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_WARNINGS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 298:

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

  case 299:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_GRANTS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 300:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_PARAMETERS, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 301:

    {
      if ((yyvsp[(2) - (4)].node)->value_ < 0 || (yyvsp[(4) - (4)].node)->value_ < 0)
      {
        yyerror(&(yylsp[(1) - (4)]), result, "OFFSET/COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_LIMIT, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 302:

    {
      if ((yyvsp[(2) - (2)].node)->value_ < 0)
      {
        yyerror(&(yylsp[(1) - (2)]), result, "COUNT must not be less than 0!");
        YYABORT;
      }
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SHOW_LIMIT, 2, NULL, (yyvsp[(2) - (2)].node));
    }
    break;

  case 303:

    { (yyval.node) = NULL; }
    break;

  case 304:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 305:

    { (yyval.node) = NULL; }
    break;

  case 306:

    { (yyval.node) = NULL; }
    break;

  case 307:

    { (yyval.ival) = 1; }
    break;

  case 308:

    { (yyval.ival) = 0; }
    break;

  case 309:

    { (yyval.ival) = 0; }
    break;

  case 310:

    { (yyval.node) = NULL; }
    break;

  case 311:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LIKE, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 312:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_WHERE_CLAUSE, 1, (yyvsp[(2) - (2)].node)); }
    break;

  case 313:

    { (yyval.node) = NULL; }
    break;

  case 314:

    { malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_OP_LIKE, 1, (yyvsp[(1) - (1)].node)); }
    break;

  case 315:

    {
        merge_nodes((yyval.node), result->malloc_pool_, T_CREATE_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 316:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 317:

    {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 318:

    {
        malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CREATE_USER_SPEC, 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 319:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 320:

    {
        (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 321:

    {
        merge_nodes((yyval.node), result->malloc_pool_, T_DROP_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 322:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 323:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 324:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SET_PASSWORD, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 325:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SET_PASSWORD, 2, (yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 326:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 327:

    {
      (yyval.node) = NULL;
    }
    break;

  case 328:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_RENAME_USER, (yyvsp[(3) - (3)].node));
    }
    break;

  case 329:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_RENAME_INFO, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 330:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 331:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 332:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LOCK_USER, 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 333:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 1;
    }
    break;

  case 334:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BOOL);
      (yyval.node)->value_ = 0;
    }
    break;

  case 335:

    {
      (void)(yyval.node);
    }
    break;

  case 336:

    {
      (void)(yyval.node);
    }
    break;

  case 337:

    {
      (yyval.ival) = 1;
    }
    break;

  case 338:

    {
      (yyval.ival) = 0;
    }
    break;

  case 339:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BEGIN);
      (yyval.node)->value_ = 0;
    }
    break;

  case 340:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_BEGIN);
      (yyval.node)->value_ = (yyvsp[(3) - (3)].ival);
    }
    break;

  case 341:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_COMMIT);
    }
    break;

  case 342:

    {
      (void)(yyvsp[(2) - (2)].node);
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_ROLLBACK);
    }
    break;

  case 343:

    {
      ParseNode *privileges_node = NULL;
      ParseNode *users_node = NULL;
      merge_nodes(privileges_node, result->malloc_pool_, T_PRIVILEGES, (yyvsp[(2) - (6)].node));
      merge_nodes(users_node, result->malloc_pool_, T_USERS, (yyvsp[(6) - (6)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_GRANT,
                                 3, privileges_node, (yyvsp[(4) - (6)].node), users_node);
    }
    break;

  case 344:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 345:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 346:

    {
      (void)(yyvsp[(2) - (2)].node);                 /* useless */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_ALL;
    }
    break;

  case 347:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_ALTER;
    }
    break;

  case 348:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_CREATE;
    }
    break;

  case 349:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_CREATE_USER;
    }
    break;

  case 350:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_DELETE;
    }
    break;

  case 351:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_DROP;
    }
    break;

  case 352:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_GRANT_OPTION;
    }
    break;

  case 353:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_INSERT;
    }
    break;

  case 354:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_UPDATE;
    }
    break;

  case 355:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_SELECT;
    }
    break;

  case 356:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_TYPE);
      (yyval.node)->value_ = T_PRIV_REPLACE;
    }
    break;

  case 357:

    {
      (void)(yyval.node);
    }
    break;

  case 358:

    {
      (void)(yyval.node);
    }
    break;

  case 359:

    {
      /* means global priv_level */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_LEVEL);
    }
    break;

  case 360:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PRIV_LEVEL, 1, (yyvsp[(1) - (1)].node));
    }
    break;

  case 361:

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

  case 362:

    {
      (yyval.node) = (yyvsp[(2) - (2)].node);
    }
    break;

  case 363:

    {
      (yyval.node) = NULL;
    }
    break;

  case 364:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_PREPARE, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 365:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 366:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
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

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_VARIABLE_SET, (yyvsp[(2) - (2)].node));;
      (yyval.node)->value_ = 2;
    }
    break;

  case 371:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 372:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 373:

    {
      (void)((yyvsp[(2) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 374:

    {
      (void)((yyvsp[(2) - (3)].node));
      (yyvsp[(1) - (3)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 375:

    {
      (void)((yyvsp[(3) - (4)].node));
      (yyvsp[(2) - (4)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = 1;
    }
    break;

  case 376:

    {
      (void)((yyvsp[(3) - (4)].node));
      (yyvsp[(2) - (4)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 377:

    {
      (void)((yyvsp[(4) - (5)].node));
      (yyvsp[(3) - (5)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->value_ = 1;
    }
    break;

  case 378:

    {
      (void)((yyvsp[(4) - (5)].node));
      (yyvsp[(3) - (5)].node)->type_ = T_SYSTEM_VARIABLE;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 379:

    {
      (void)((yyvsp[(2) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_VAR_VAL, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
      (yyval.node)->value_ = 2;
    }
    break;

  case 380:

    { (yyval.node) = NULL; }
    break;

  case 381:

    { (yyval.node) = NULL; }
    break;

  case 382:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 383:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_EXECUTE, 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 384:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_ARGUMENT_LIST, (yyvsp[(2) - (2)].node));
    }
    break;

  case 385:

    {
      (yyval.node) = NULL;
    }
    break;

  case 386:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 387:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 388:

    {
      (void)((yyvsp[(1) - (3)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_DEALLOCATE, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 389:

    { (yyval.node) = NULL; }
    break;

  case 390:

    { (yyval.node) = NULL; }
    break;

  case 391:

    {
      ParseNode *alter_actions = NULL;
      merge_nodes(alter_actions, result->malloc_pool_, T_ALTER_ACTION_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_TABLE, 2, (yyvsp[(3) - (4)].node), alter_actions);
    }
    break;

  case 392:

    {
      yyerror(&(yylsp[(1) - (6)]), result, "Table rename is not supported now");
      YYABORT;
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_TABLE_RENAME, 1, (yyvsp[(6) - (6)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_ACTION_LIST, 1, (yyval.node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_TABLE, 2, (yyvsp[(3) - (6)].node), (yyval.node));
    }
    break;

  case 393:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 394:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 395:

    {
      (void)((yyvsp[(2) - (3)].node)); /* make bison mute */
      (yyval.node) = (yyvsp[(3) - (3)].node); /* T_COLUMN_DEFINITION */
    }
    break;

  case 396:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_DROP, 1, (yyvsp[(3) - (4)].node));
      (yyval.node)->value_ = (yyvsp[(4) - (4)].ival);
    }
    break;

  case 397:

    {
      (void)((yyvsp[(2) - (4)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_ALTER, 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));
    }
    break;

  case 398:

    {
      (void)((yyvsp[(2) - (5)].node)); /* make bison mute */
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_COLUMN_RENAME, 2, (yyvsp[(3) - (5)].node), (yyvsp[(5) - (5)].node));
    }
    break;

  case 399:

    { (yyval.node) = NULL; }
    break;

  case 400:

    { (yyval.node) = NULL; }
    break;

  case 401:

    { (yyval.ival) = 2; }
    break;

  case 402:

    { (yyval.ival) = 1; }
    break;

  case 403:

    { (yyval.ival) = 0; }
    break;

  case 404:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NOT_NULL);
    }
    break;

  case 405:

    {
      (void)((yyvsp[(3) - (3)].node)); /* make bison mute */
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_NULL);
    }
    break;

  case 406:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_DEFAULT, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 407:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_NULL);
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CONSTR_DEFAULT, 1, (yyval.node));
    }
    break;

  case 408:

    {
      merge_nodes((yyval.node), result->malloc_pool_, T_SYTEM_ACTION_LIST, (yyvsp[(4) - (4)].node));
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_ALTER_SYSTEM, 1, (yyval.node));
    }
    break;

  case 409:

    {
      (yyval.node) = (yyvsp[(1) - (1)].node);
    }
    break;

  case 410:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_LINK_NODE, 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));
    }
    break;

  case 411:

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

  case 412:

    { (yyval.node) = (yyvsp[(2) - (2)].node); }
    break;

  case 413:

    { (yyval.node) = NULL; }
    break;

  case 414:

    { (yyval.ival) = 0; }
    break;

  case 415:

    { (yyval.ival) = 1; }
    break;

  case 416:

    { (yyval.ival) = 2; }
    break;

  case 417:

    { (yyval.ival) = 2; }
    break;

  case 418:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 1;
    }
    break;

  case 419:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 4;
    }
    break;

  case 420:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 2;
    }
    break;

  case 421:

    {
      malloc_terminal_node((yyval.node), result->malloc_pool_, T_INT);
      (yyval.node)->value_ = 3;
    }
    break;

  case 422:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_CLUSTER, 1, (yyvsp[(3) - (3)].node));
    }
    break;

  case 423:

    {
      malloc_non_terminal_node((yyval.node), result->malloc_pool_, T_SERVER_ADDRESS, 2, (yyvsp[(3) - (6)].node), (yyvsp[(6) - (6)].node));
    }
    break;

  case 424:

    { (yyval.node) = NULL; }
    break;

  case 425:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 426:

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

  case 430:

    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 431:

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
