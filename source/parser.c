/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "../source/syn_an.y"

    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif

    #include "yacc_libs/yacc_api.h"

#line 82 "../source/parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SOURCE_PARSER_H_INCLUDED
# define YY_YY_SOURCE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    REAL = 259,
    ID = 260,
    STRING = 261,
    LEFT_BRACE = 262,
    RIGHT_BRACE = 263,
    LEFT_BRACKET = 264,
    RIGHT_BRACKET = 265,
    LEFT_PARENTHESIS = 266,
    RIGHT_PARENTHESIS = 267,
    SEMICOLON = 268,
    COMMA = 269,
    FULLSTOP = 270,
    COLON = 271,
    DOUBLE_FULLSTOP = 272,
    DOUBLE_COLON = 273,
    IF = 274,
    ELSE = 275,
    WHILE = 276,
    FOR = 277,
    FUNCTION = 278,
    BREAK = 279,
    CONTINUE = 280,
    RETURN = 281,
    AND = 282,
    NOT = 283,
    OR = 284,
    LOCAL = 285,
    TRUE = 286,
    FALSE = 287,
    NIL = 288,
    ASSIGN = 289,
    PLUS = 290,
    MINUS = 291,
    MUL = 292,
    DIV = 293,
    MODULO = 294,
    EQUAL = 295,
    NOT_EQUAL = 296,
    PLUS_PLUS = 297,
    MINUS_MINUS = 298,
    GREATER = 299,
    GREATER_EQUAL = 300,
    LESS = 301,
    LESS_EQUAL = 302,
    UMINUS = 303
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define ID 260
#define STRING 261
#define LEFT_BRACE 262
#define RIGHT_BRACE 263
#define LEFT_BRACKET 264
#define RIGHT_BRACKET 265
#define LEFT_PARENTHESIS 266
#define RIGHT_PARENTHESIS 267
#define SEMICOLON 268
#define COMMA 269
#define FULLSTOP 270
#define COLON 271
#define DOUBLE_FULLSTOP 272
#define DOUBLE_COLON 273
#define IF 274
#define ELSE 275
#define WHILE 276
#define FOR 277
#define FUNCTION 278
#define BREAK 279
#define CONTINUE 280
#define RETURN 281
#define AND 282
#define NOT 283
#define OR 284
#define LOCAL 285
#define TRUE 286
#define FALSE 287
#define NIL 288
#define ASSIGN 289
#define PLUS 290
#define MINUS 291
#define MUL 292
#define DIV 293
#define MODULO 294
#define EQUAL 295
#define NOT_EQUAL 296
#define PLUS_PLUS 297
#define MINUS_MINUS 298
#define GREATER 299
#define GREATER_EQUAL 300
#define LESS 301
#define LESS_EQUAL 302
#define UMINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "../source/syn_an.y"

    int int_value;
    unsigned un_value;
    char* string_value;
    double real_value;
    expr* exprVal;
    call* callFunc;
    indexedPair* indPair;
    SymbolTableEntry *symTabEntry;
    forPrefixJumps* forPrefJumps;
    stmt_t *st;

#line 243 "../source/parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SOURCE_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   746

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  206

#define YYUNDEFTOK  2
#define YYMAXUTOK   303


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    63,    66,    76,    84,    92,   100,   108,
     116,   124,   132,   140,   150,   168,   173,   179,   179,   190,
     190,   200,   200,   209,   209,   218,   225,   232,   239,   246,
     253,   260,   267,   274,   281,   289,   296,   303,   310,   317,
     324,   331,   340,   347,   354,   361,   370,   379,   386,   393,
     400,   409,   416,   428,   435,   449,   456,   463,   470,   480,
     492,   499,   508,   514,   523,   530,   539,   546,   557,   567,
     575,   583,   590,   600,   613,   613,   623,   623,   635,   638,
     644,   662,   667,   674,   680,   686,   691,   718,   725,   732,
     739,   746,   753,   762,   769,   778,   783,   789,   814,   824,
     829,   834,   839,   844,   853,   875,   881,   887,   886,   893,
     893,   900,   906,   916,   923
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "ID", "STRING",
  "LEFT_BRACE", "RIGHT_BRACE", "LEFT_BRACKET", "RIGHT_BRACKET",
  "LEFT_PARENTHESIS", "RIGHT_PARENTHESIS", "SEMICOLON", "COMMA",
  "FULLSTOP", "COLON", "DOUBLE_FULLSTOP", "DOUBLE_COLON", "IF", "ELSE",
  "WHILE", "FOR", "FUNCTION", "BREAK", "CONTINUE", "RETURN", "AND", "NOT",
  "OR", "LOCAL", "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS", "MINUS", "MUL",
  "DIV", "MODULO", "EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS",
  "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL", "UMINUS", "$accept",
  "program", "stmt", "stmts", "expr", "$@1", "$@2", "$@3", "$@4",
  "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "objectdef", "indexed", "indexedelem", "block",
  "$@5", "$@6", "funcname", "funcprefix", "funcargs", "funcbody",
  "funcblockstart", "funcblockend", "funcdef", "const", "idlist",
  "ifprefix", "elseprefix", "ifstmt", "loopstart", "loopend", "loopstmt",
  "whilestart", "whilecond", "whilestmt", "N", "M", "forprefix", "$@7",
  "$@8", "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF (-172)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-75)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     203,  -172,  -172,  -172,  -172,     1,   244,    25,  -172,    22,
      21,  -172,    38,    34,    53,    56,    97,   451,    93,  -172,
    -172,  -172,   451,     7,     7,   112,  -172,   203,   590,  -172,
     102,  -172,    11,  -172,  -172,   103,  -172,  -172,   203,  -172,
     107,  -172,  -172,  -172,  -172,   115,   203,   451,  -172,   658,
      28,    30,  -172,   527,   122,  -172,   451,   260,  -172,  -172,
    -172,  -172,  -172,   611,  -172,  -172,  -172,   114,     4,    11,
       4,  -172,  -172,  -172,  -172,  -172,   451,   451,   451,   451,
     451,  -172,  -172,   451,   451,   451,   451,   451,   295,   130,
     133,   451,  -172,  -172,  -172,  -172,  -172,   451,   330,   136,
      12,  -172,   100,   451,  -172,   365,  -172,   162,   637,  -172,
     451,  -172,   135,  -172,   132,   548,  -172,    46,  -172,   134,
    -172,  -172,    26,    26,  -172,  -172,  -172,   451,   451,   273,
     273,   273,   273,   485,  -172,    72,  -172,   137,   658,   506,
    -172,    75,  -172,  -172,  -172,    76,   140,  -172,   203,   569,
     203,  -172,  -172,    81,  -172,   451,   658,  -172,   400,  -172,
     451,  -172,   132,   451,   451,   686,   686,  -172,  -172,   435,
    -172,  -172,  -172,   145,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,   462,  -172,    82,   658,   451,   699,   673,  -172,    95,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,   138,   658,  -172,
    -172,  -172,  -172,   142,  -172,  -172
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    87,    88,    47,    89,    76,     0,     0,    13,     0,
       0,   102,     0,    79,     0,     0,     0,     0,     0,    91,
      92,    90,     0,     0,     0,     0,    15,     2,     0,    41,
      42,    50,    43,    44,    11,     0,    12,    46,     0,     5,
       0,     6,   105,     7,     8,     0,     0,     0,    70,    66,
       0,     0,    71,     0,     0,    49,     0,     0,    78,    80,
       9,    10,   113,     0,    36,    48,    35,     0,    37,     0,
      39,     1,    14,     4,    19,    17,     0,     0,     0,     0,
       0,    23,    21,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    40,    57,    60,    61,     0,     0,     0,
       0,    84,    98,     0,    99,     0,    75,     0,     0,    69,
       0,    68,     0,    34,    45,     0,   106,     0,   114,     0,
     106,   106,    29,    30,    31,    32,    33,     0,     0,    28,
      27,    26,    25,     0,    63,     0,    51,     0,    16,     0,
      56,     0,    53,    93,    82,     0,     0,    96,     0,     0,
       0,   104,   105,     0,    77,     0,    67,    72,     0,    95,
       0,   106,     0,     0,     0,    24,    22,    52,    62,     0,
      54,    55,    81,     0,    83,    85,    97,   103,   100,    99,
     105,     0,    59,     0,   109,     0,    20,    18,    65,     0,
      94,    86,   101,   105,    99,    73,    58,     0,   107,    64,
     112,   105,   110,     0,   111,   108
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -172,  -172,   -24,   110,    -6,  -172,  -172,  -172,  -172,  -172,
      52,  -172,   108,  -172,  -172,  -172,   -53,  -172,  -172,    41,
      13,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,    -5,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -171,  -172,  -172,
    -172,  -147,  -114,  -172,  -172,  -172,  -172,  -172
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,   121,   120,   128,   127,    29,
      30,    31,    32,    94,    95,    96,    50,    33,    51,    52,
      34,    45,    46,    59,    35,   101,   175,   146,   191,    36,
      37,   145,    38,   148,    39,   150,   192,   151,    40,   104,
      41,   105,   160,    42,   203,   197,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    53,    54,    72,   117,   179,   163,   164,   193,   -74,
      63,    64,     3,    87,   102,    88,    66,   143,    67,    89,
      97,    90,    98,   201,   144,     9,    99,    55,     1,     2,
       3,     4,    56,   194,     6,   135,     7,    18,   109,    58,
     111,   108,   110,     9,   112,   141,   200,   185,    13,    57,
     115,    49,   153,    17,   204,    18,    19,    20,    21,   161,
     110,    22,   119,    78,    79,    80,    60,    23,    24,    61,
     122,   123,   124,   125,   126,    68,    70,   129,   130,   131,
     132,   133,    49,    72,   168,   138,   110,   171,   172,   110,
     173,   139,    49,   180,   196,   110,   110,   149,    65,    49,
       1,     2,     3,     4,   156,   183,     6,   199,     7,   110,
      62,    87,    71,    88,   100,     9,   189,    89,   103,    90,
     147,   165,   166,   106,   176,    17,   178,    18,    19,    20,
      21,    69,    69,    22,   114,   136,    91,    13,   137,    23,
      24,   142,    47,   158,    92,    93,   162,     5,   169,   181,
     190,   202,    49,   157,   184,   205,   107,   186,   187,   174,
       0,     0,     0,    49,     0,     1,     2,     3,     4,     5,
     154,     6,     0,     7,     0,     8,     0,     0,     0,   198,
       9,    10,     0,    11,    12,    13,    14,    15,    16,     0,
      17,     0,    18,    19,    20,    21,     0,     0,    22,     0,
       0,     0,     0,     0,    23,    24,     1,     2,     3,     4,
       5,     0,     6,     0,     7,     0,     8,     0,     0,     0,
       0,     9,    10,     0,    11,    12,    13,    14,    15,    16,
       0,    17,     0,    18,    19,    20,    21,     0,     0,    22,
       0,     0,     0,     0,     0,    23,    24,     1,     2,     3,
       4,    47,     0,     6,    48,     7,     0,     0,     0,     0,
       0,     0,     9,     1,     2,     3,     4,     0,     0,     6,
       0,     7,    17,   116,    18,    19,    20,    21,     9,     0,
      22,     0,     0,     0,     0,     0,    23,    24,    17,     0,
      18,    19,    20,    21,     0,     0,    22,     0,     1,     2,
       3,     4,    23,    24,     6,     0,     7,   134,    76,    77,
      78,    79,    80,     9,     0,     0,     0,   -75,   -75,   -75,
     -75,     0,     0,    17,     0,    18,    19,    20,    21,     0,
       0,    22,     0,     1,     2,     3,     4,    23,    24,     6,
       0,     7,   140,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
      18,    19,    20,    21,     0,     0,    22,     0,     1,     2,
       3,     4,    23,    24,     6,     0,     7,   152,     0,     0,
       0,     0,     0,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,    18,    19,    20,    21,     0,
       0,    22,     0,     1,     2,     3,     4,    23,    24,     6,
       0,     7,   182,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
      18,    19,    20,    21,     0,     0,    22,     0,     1,     2,
       3,     4,    23,    24,     6,     0,     7,   188,     0,     0,
       0,     0,     0,     9,     1,     2,     3,     4,     0,     0,
       6,     0,     7,    17,     0,    18,    19,    20,    21,     9,
     195,    22,     0,     0,     0,     0,     0,    23,    24,    17,
       0,    18,    19,    20,    21,     0,     0,    22,     0,    74,
       0,    75,     0,    23,    24,   167,     0,    76,    77,    78,
      79,    80,    81,    82,     0,     0,    83,    84,    85,    86,
       0,     0,    74,     0,    75,     0,   170,     0,     0,     0,
      76,    77,    78,    79,    80,    81,    82,     0,     0,    83,
      84,    85,    86,    74,     0,    75,     0,     0,     0,   113,
       0,    76,    77,    78,    79,    80,    81,    82,     0,     0,
      83,    84,    85,    86,    74,     0,    75,     0,     0,     0,
     159,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    74,     0,    75,     0,     0,
       0,   177,     0,    76,    77,    78,    79,    80,    81,    82,
       0,     0,    83,    84,    85,    86,    74,     0,    75,     0,
       0,     0,     0,    73,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86,    74,     0,    75,
       0,     0,     0,     0,   118,    76,    77,    78,    79,    80,
      81,    82,     0,     0,    83,    84,    85,    86,    74,     0,
      75,     0,     0,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,   155,     0,    83,    84,    85,    86,     0,
       0,     0,     0,     0,    74,     0,    75,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,     0,
       0,    83,    84,    85,    86,    74,     0,    75,     0,     0,
       0,     0,     0,    76,    77,    78,    79,    80,    81,    82,
      74,     0,    83,    84,    85,    86,     0,     0,    76,    77,
      78,    79,    80,    81,    82,     0,     0,    83,    84,    85,
      86,    76,    77,    78,    79,    80,   -75,   -75,     0,     0,
      83,    84,    85,    86,    76,    77,    78,    79,    80,    81,
      82,     0,     0,    83,    84,    85,    86
};

static const yytype_int16 yycheck[] =
{
       6,     7,     7,    27,    57,   152,   120,   121,   179,     8,
      16,    17,     5,     9,    38,    11,    22,     5,    11,    15,
       9,    17,    11,   194,    12,    18,    15,     5,     3,     4,
       5,     6,    11,   180,     9,    88,    11,    30,    10,     5,
      10,    47,    14,    18,    14,    98,   193,   161,    23,    11,
      56,    57,   105,    28,   201,    30,    31,    32,    33,    13,
      14,    36,    67,    37,    38,    39,    13,    42,    43,    13,
      76,    77,    78,    79,    80,    23,    24,    83,    84,    85,
      86,    87,    88,   107,    12,    91,    14,    12,    12,    14,
      14,    97,    98,    12,    12,    14,    14,   103,     5,   105,
       3,     4,     5,     6,   110,   158,     9,    12,    11,    14,
      13,     9,     0,    11,    11,    18,   169,    15,    11,    17,
      20,   127,   128,     8,   148,    28,   150,    30,    31,    32,
      33,    23,    24,    36,    12,     5,    34,    23,     5,    42,
      43,     5,     7,    11,    42,    43,    12,     7,    11,   155,
       5,    13,   158,   112,   160,    13,    46,   163,   164,   146,
      -1,    -1,    -1,   169,    -1,     3,     4,     5,     6,     7,
       8,     9,    -1,    11,    -1,    13,    -1,    -1,    -1,   185,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      28,    -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,     3,     4,     5,     6,
       7,    -1,     9,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    18,    19,    -1,    21,    22,    23,    24,    25,    26,
      -1,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    42,    43,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    18,     3,     4,     5,     6,    -1,    -1,     9,
      -1,    11,    28,    13,    30,    31,    32,    33,    18,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    42,    43,    28,    -1,
      30,    31,    32,    33,    -1,    -1,    36,    -1,     3,     4,
       5,     6,    42,    43,     9,    -1,    11,    12,    35,    36,
      37,    38,    39,    18,    -1,    -1,    -1,    44,    45,    46,
      47,    -1,    -1,    28,    -1,    30,    31,    32,    33,    -1,
      -1,    36,    -1,     3,     4,     5,     6,    42,    43,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    -1,    36,    -1,     3,     4,
       5,     6,    42,    43,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    30,    31,    32,    33,    -1,
      -1,    36,    -1,     3,     4,     5,     6,    42,    43,     9,
      -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    -1,    36,    -1,     3,     4,
       5,     6,    42,    43,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    18,     3,     4,     5,     6,    -1,    -1,
       9,    -1,    11,    28,    -1,    30,    31,    32,    33,    18,
       8,    36,    -1,    -1,    -1,    -1,    -1,    42,    43,    28,
      -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,    27,
      -1,    29,    -1,    42,    43,    10,    -1,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    44,    45,    46,    47,
      -1,    -1,    27,    -1,    29,    -1,    10,    -1,    -1,    -1,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    44,
      45,    46,    47,    27,    -1,    29,    -1,    -1,    -1,    12,
      -1,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      44,    45,    46,    47,    27,    -1,    29,    -1,    -1,    -1,
      12,    -1,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    27,    -1,    29,    -1,    -1,
      -1,    12,    -1,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    44,    45,    46,    47,    27,    -1,    29,    -1,
      -1,    -1,    -1,    13,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    44,    45,    46,    47,    27,    -1,    29,
      -1,    -1,    -1,    -1,    13,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    46,    47,    27,    -1,
      29,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      39,    40,    41,    16,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    27,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    27,    -1,    29,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    39,    40,    41,
      27,    -1,    44,    45,    46,    47,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      44,    45,    46,    47,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    11,    13,    18,
      19,    21,    22,    23,    24,    25,    26,    28,    30,    31,
      32,    33,    36,    42,    43,    50,    51,    52,    53,    58,
      59,    60,    61,    66,    69,    73,    78,    79,    81,    83,
      87,    89,    92,    95,    96,    70,    71,     7,    10,    53,
      65,    67,    68,    53,    78,     5,    11,    11,     5,    72,
      13,    13,    13,    53,    53,     5,    53,    11,    59,    61,
      59,     0,    51,    13,    27,    29,    35,    36,    37,    38,
      39,    40,    41,    44,    45,    46,    47,     9,    11,    15,
      17,    34,    42,    43,    62,    63,    64,     9,    11,    15,
      11,    74,    51,    11,    88,    90,     8,    52,    53,    10,
      14,    10,    14,    12,    12,    53,    13,    65,    13,    78,
      55,    54,    53,    53,    53,    53,    53,    57,    56,    53,
      53,    53,    53,    53,    12,    65,     5,     5,    53,    53,
      12,    65,     5,     5,    12,    80,    76,    20,    82,    53,
      84,    86,    12,    65,     8,    16,    53,    68,    11,    12,
      91,    13,    12,    91,    91,    53,    53,    10,    12,    11,
      10,    12,    12,    14,    69,    75,    51,    12,    51,    90,
      12,    53,    12,    65,    53,    91,    53,    53,    12,    65,
       5,    77,    85,    86,    90,     8,    12,    94,    53,    12,
      90,    86,    13,    93,    90,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    54,    53,    55,
      53,    56,    53,    57,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    58,    58,    58,    58,    58,    59,    59,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      62,    62,    63,    63,    64,    64,    65,    65,    66,    66,
      66,    67,    67,    68,    70,    69,    71,    69,    72,    72,
      73,    74,    74,    75,    76,    77,    78,    79,    79,    79,
      79,    79,    79,    80,    80,    81,    82,    83,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    93,    92,    94,
      92,    95,    95,    96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     3,     0,     5,     0,
       5,     0,     4,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     3,     2,     6,     5,
       1,     1,     3,     2,     5,     4,     1,     3,     3,     3,
       2,     1,     3,     5,     0,     3,     0,     4,     1,     0,
       2,     3,     2,     1,     0,     0,     5,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     1,     4,     2,     0,
       0,     3,     1,     3,     3,     0,     0,     0,     8,     0,
       7,     7,     6,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4:
#line 66 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Expr Statement (stmt -> expr;)\n");
                                            }
                                            
                                            partEvaluation((yyvsp[-1].exprVal));
                                            resettemp();
                                           
                                            (yyval.st) = NULL;
                                        }
#line 1686 "../source/parser.c"
    break;

  case 5:
#line 76 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>If/Ifelse Statement (stmt -> ifstmt)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = (yyvsp[0].st);
                                        }
#line 1699 "../source/parser.c"
    break;

  case 6:
#line 84 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>While Statement (stmt -> whilestmt)\n");
                                            }
                                            
                                            resettemp();
                                            (yyval.st) = NULL;
                                        }
#line 1712 "../source/parser.c"
    break;

  case 7:
#line 92 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>For Statement (stmt -> forstmt)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = NULL;
                                        }
#line 1725 "../source/parser.c"
    break;

  case 8:
#line 100 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Return Statement (stmt -> return)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = NULL;
                                        }
#line 1738 "../source/parser.c"
    break;

  case 9:
#line 108 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Break Statement (stmt -> break)\n");
                                            }

                                            resettemp();                                          
                                            (yyval.st) = ManageBreak();
                                        }
#line 1751 "../source/parser.c"
    break;

  case 10:
#line 116 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Continue Statement (stmt -> continue;)\n");
                                            }
                                            
                                            resettemp();                                            
                                            (yyval.st) = ManageContinue();
                                        }
#line 1764 "../source/parser.c"
    break;

  case 11:
#line 124 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Block Statement (stmt -> block)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = (yyvsp[0].st);
                                        }
#line 1777 "../source/parser.c"
    break;

  case 12:
#line 132 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Func Def Statement (stmt -> funcdef)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = NULL;
                                        }
#line 1790 "../source/parser.c"
    break;

  case 13:
#line 140 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Semicolon Statement (stmt -> ;)\n");
                                            }

                                            resettemp();
                                            (yyval.st) = NULL;
                                        }
#line 1803 "../source/parser.c"
    break;

  case 14:
#line 150 "../source/syn_an.y"
                                        {
                                            int breaklist1 = 0,breaklist2 = 0, contlist1 = 0, contlist2 = 0; 
                                            
                                            if((yyvsp[-1].st) != NULL){
                                                breaklist1 = (yyvsp[-1].st)->breakList;
                                                contlist1 = (yyvsp[-1].st)->contList;
                                                //free stmt
                                            }

                                            if((yyvsp[0].st) != NULL){
                                                breaklist2 = (yyvsp[0].st)->breakList;
                                                contlist2 = (yyvsp[0].st)->contList;
                                            }

                                            (yyval.st) = newstmt();
                                            (yyval.st)->breakList = mergelist(breaklist1, breaklist2);
                                            (yyval.st)->contList = mergelist(contlist1, contlist2); 
                                        }
#line 1826 "../source/parser.c"
    break;

  case 15:
#line 168 "../source/syn_an.y"
                                        {
                                            (yyval.st) = (yyvsp[0].st);
                                        }
#line 1834 "../source/parser.c"
    break;

  case 16:
#line 173 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Assignment Expression (expr -> lvalue = expr)\n");
                                            }
                                            (yyval.exprVal) = ManageAssignValue((yyvsp[-2].exprVal), (yyvsp[0].exprVal));
                                        }
#line 1845 "../source/parser.c"
    break;

  case 17:
#line 179 "../source/syn_an.y"
                      { (yyvsp[-1].exprVal) = valToBool((yyvsp[-1].exprVal), nextquadlabel(),  nextquadlabel() + 1); }
#line 1851 "../source/parser.c"
    break;

  case 18:
#line 181 "../source/syn_an.y"
                                        { 
                                            
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OR Expression (expr -> expr or expr)\n");
                                            }

                                            (yyvsp[0].exprVal) = valToBool((yyvsp[0].exprVal), nextquadlabel(), nextquadlabel()+1);
                                            (yyval.exprVal) = ManageORexpression((yyvsp[-4].exprVal),(yyvsp[0].exprVal),(yyvsp[-1].un_value));
                                        }
#line 1865 "../source/parser.c"
    break;

  case 19:
#line 190 "../source/syn_an.y"
                       { (yyvsp[-1].exprVal) = valToBool((yyvsp[-1].exprVal), nextquadlabel(),  nextquadlabel() + 1); }
#line 1871 "../source/parser.c"
    break;

  case 20:
#line 192 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>AND Expression (expr -> expr and expr)\n");
                                            }
                                            
                                            (yyvsp[0].exprVal) = valToBool((yyvsp[0].exprVal), nextquadlabel(), nextquadlabel()+1);
                                            (yyval.exprVal) = ManageANDexpression((yyvsp[-4].exprVal),(yyvsp[0].exprVal),(yyvsp[-1].un_value));
                                        }
#line 1884 "../source/parser.c"
    break;

  case 21:
#line 200 "../source/syn_an.y"
                             { partEvaluation((yyvsp[-1].exprVal)); }
#line 1890 "../source/parser.c"
    break;

  case 22:
#line 201 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT EQUAL Expression (expr -> expr != expr)\n");
                                            }

                                            partEvaluation((yyvsp[0].exprVal));
                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-3].exprVal), if_noteq_op, (yyvsp[0].exprVal));
                                        }
#line 1903 "../source/parser.c"
    break;

  case 23:
#line 209 "../source/syn_an.y"
                         { partEvaluation((yyvsp[-1].exprVal)); }
#line 1909 "../source/parser.c"
    break;

  case 24:
#line 210 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>EQUAL Expression (expr -> expr == expr)\n");
                                            }

                                            partEvaluation((yyvsp[0].exprVal));
                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-3].exprVal), if_eq_op, (yyvsp[0].exprVal));
                                        }
#line 1922 "../source/parser.c"
    break;

  case 25:
#line 218 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS EQUAL Expression (expr -> expr <= expr)\n");
                                            }

                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-2].exprVal), if_lesseq_op, (yyvsp[0].exprVal));
                                        }
#line 1934 "../source/parser.c"
    break;

  case 26:
#line 225 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS Expression (expr -> expr < expr)\n");
                                            }

                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-2].exprVal), if_less_op, (yyvsp[0].exprVal));
                                        }
#line 1946 "../source/parser.c"
    break;

  case 27:
#line 232 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER EQUAL Expression (expr -> expr >= expr)\n");
                                            }

                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-2].exprVal), if_greatereq_op, (yyvsp[0].exprVal));
                                        }
#line 1958 "../source/parser.c"
    break;

  case 28:
#line 239 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER Expression (expr -> expr > expr)\n");
                                            }

                                            (yyval.exprVal) = ManageRelationExpression((yyvsp[-2].exprVal), if_greater_op, (yyvsp[0].exprVal));
                                        }
#line 1970 "../source/parser.c"
    break;

  case 29:
#line 246 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS Expression (expr -> expr + expr)\n");
                                            }

                                            (yyval.exprVal) = ManageArithmeticExpression((yyvsp[-2].exprVal),add_op,(yyvsp[0].exprVal));
                                        }
#line 1982 "../source/parser.c"
    break;

  case 30:
#line 253 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS Expression (expr -> expr - expr)\n");
                                            }

                                            (yyval.exprVal) = ManageArithmeticExpression((yyvsp[-2].exprVal),sub_op,(yyvsp[0].exprVal));
                                        }
#line 1994 "../source/parser.c"
    break;

  case 31:
#line 260 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MUL Expression (expr -> expr * expr) \n");
                                            }

                                            (yyval.exprVal) = ManageArithmeticExpression((yyvsp[-2].exprVal),mul_op,(yyvsp[0].exprVal));
                                        }
#line 2006 "../source/parser.c"
    break;

  case 32:
#line 267 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>DIV Expression (expr -> expr / expr) \n");
                                            }

                                            (yyval.exprVal) = ManageArithmeticExpression((yyvsp[-2].exprVal),div_op,(yyvsp[0].exprVal));
                                        }
#line 2018 "../source/parser.c"
    break;

  case 33:
#line 274 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MODULO Expression (expr -> expr MOD expr)\n");
                                            }

                                            (yyval.exprVal) = ManageArithmeticExpression((yyvsp[-2].exprVal),mod_op,(yyvsp[0].exprVal));
                                        }
#line 2030 "../source/parser.c"
    break;

  case 34:
#line 282 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PARENTHESIS EXPR Expression (expr -> (expr) )\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[-1].exprVal);
                                        }
#line 2042 "../source/parser.c"
    break;

  case 35:
#line 289 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>-EXPR Expression (expr -> -expr)\n");
                                            }

                                            (yyval.exprVal) = ManageUminus((yyvsp[0].exprVal));
                                        }
#line 2054 "../source/parser.c"
    break;

  case 36:
#line 296 "../source/syn_an.y"
                                        {
                                           if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT Expression (expr -> not expr)\n");
                                            }

                                            (yyval.exprVal) = ManageNot((yyvsp[0].exprVal));
                                        }
#line 2066 "../source/parser.c"
    break;

  case 37:
#line 303 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS PLUS lvalue Expression (expr -> ++lvalue)\n");
                                            }

                                            (yyval.exprVal) = ManagePlusPlusLvalue((yyvsp[0].exprVal));
                                        }
#line 2078 "../source/parser.c"
    break;

  case 38:
#line 310 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue PLUS PLUS Expression (expr -> lvalue++ )\n");
                                            }

                                            (yyval.exprVal) = ManageLvaluePlusPlus((yyvsp[-1].exprVal));
                                        }
#line 2090 "../source/parser.c"
    break;

  case 39:
#line 317 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS MINUS lvalue Expression (expr -> --lvalue)\n");
                                            }

                                            (yyval.exprVal) = ManageMinusMinusLvalue((yyvsp[0].exprVal));
                                        }
#line 2102 "../source/parser.c"
    break;

  case 40:
#line 324 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue MINUS MINUS Expression (expr -> lvalue--)\n");
                                            }

                                            (yyval.exprVal) = ManageLvalueMinusMinus((yyvsp[-1].exprVal));
                                        }
#line 2114 "../source/parser.c"
    break;

  case 41:
#line 331 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PRIMARY Expression (expr -> primary)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2126 "../source/parser.c"
    break;

  case 42:
#line 340 "../source/syn_an.y"
                                        {                                 
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue (primary -> lvalue)\n");
                                            }

                                            (yyval.exprVal) = ManagePrimaryLValue((yyvsp[0].exprVal));    
                                        }
#line 2138 "../source/parser.c"
    break;

  case 43:
#line 347 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CALL (primary -> call)\n");
                                            }

                                            (yyval.exprVal) = ManagePrimaryFunction((yyvsp[0].exprVal));
                                        }
#line 2150 "../source/parser.c"
    break;

  case 44:
#line 354 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OBJECT DEF (primary -> objectdef)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2162 "../source/parser.c"
    break;

  case 45:
#line 362 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>(funcdef) (primary -> (funcdef))\n");
                                            }

                                            (yyval.exprVal) = newexpr(programfunc_e);
                                            (yyval.exprVal)->sym = (yyvsp[-1].symTabEntry);
                                        }
#line 2175 "../source/parser.c"
    break;

  case 46:
#line 370 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CONST (primary -> const)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2187 "../source/parser.c"
    break;

  case 47:
#line 379 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>ID %s (lvalue -> ID)\n", (yyvsp[0].string_value));
                                            }

                                            (yyval.exprVal) = EvaluateLValue((yyvsp[0].string_value));
                                        }
#line 2199 "../source/parser.c"
    break;

  case 48:
#line 386 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> local ID %s (lvalue -> local ID)\n", (yyvsp[0].string_value));
                                            }

                                            (yyval.exprVal) = EvaluateLocalLValue((yyvsp[0].string_value));
                                        }
#line 2211 "../source/parser.c"
    break;

  case 49:
#line 393 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>global ID %s (lvalue -> global ID)\n", (yyvsp[0].string_value));
                                            }

                                            (yyval.exprVal) = EvaluateGlobalLValue((yyvsp[0].string_value));
                                        }
#line 2223 "../source/parser.c"
    break;

  case 50:
#line 400 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MEMBER (lvalue -> member)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2235 "../source/parser.c"
    break;

  case 51:
#line 409 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue . ID %s (member -> lvalue.ID)\n", (yyvsp[0].string_value));
                                                            }

                                                            (yyval.exprVal) = member_item((yyvsp[-2].exprVal), (yyvsp[0].string_value)); 
                                                        }
#line 2247 "../source/parser.c"
    break;

  case 52:
#line 416 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue [ EXPR ] (member -> lvalue[expr])\n");
                                                            }

                                                            (yyvsp[-3].exprVal) = emit_iftableitem((yyvsp[-3].exprVal));
                                                            partEvaluation((yyvsp[-1].exprVal));

                                                            (yyval.exprVal) = newexpr(tableitem_e);
                                                            (yyval.exprVal)->sym = (yyvsp[-3].exprVal)->sym;
                                                            (yyval.exprVal)->index = (yyvsp[-1].exprVal);
                                                        }
#line 2264 "../source/parser.c"
    break;

  case 53:
#line 428 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>Call.ID %s (member -> call.ID)\n", (yyvsp[0].string_value));
                                                            }

                                                            (yyval.exprVal) = member_item((yyvsp[-2].exprVal), (yyvsp[0].string_value)); 
                                                        }
#line 2276 "../source/parser.c"
    break;

  case 54:
#line 435 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>CALL [ EXPR ] (member -> call[expr])\n");
                                                            }

                                                            (yyvsp[-3].exprVal) = emit_iftableitem((yyvsp[-3].exprVal));
                                                            partEvaluation((yyvsp[-1].exprVal));

                                                            (yyval.exprVal) = newexpr(tableitem_e);
                                                            (yyval.exprVal)->sym = (yyvsp[-3].exprVal)->sym;
                                                            (yyval.exprVal)->index = (yyvsp[-1].exprVal);
                                                        }
#line 2293 "../source/parser.c"
    break;

  case 55:
#line 449 "../source/syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( ELIST ) (call -> call(elist))\n");
                                                                }           

                                                                (yyval.exprVal) = make_call((yyvsp[-3].exprVal), (yyvsp[-1].exprVal));
                                                            }
#line 2305 "../source/parser.c"
    break;

  case 56:
#line 456 "../source/syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( empty ) (call -> call())\n");
                                                                }                                       
                                                                
                                                                (yyval.exprVal) = make_call((yyvsp[-2].exprVal), NULL);
                                                            }
#line 2317 "../source/parser.c"
    break;

  case 57:
#line 463 "../source/syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>lvalue ( CALL SUFFIX ) (call -> lvalue callsuffix)\n");                                       
                                                                }

                                                                (yyval.exprVal) = ManageLvalueCallsuffix((yyvsp[-1].exprVal), (yyvsp[0].callFunc));
                                                            }
#line 2329 "../source/parser.c"
    break;

  case 58:
#line 471 "../source/syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(ELIST) (call -> ( funcdef(elist) ))\n");
                                                                }
                                                                
                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = (yyvsp[-4].symTabEntry);
                                                                (yyval.exprVal) = make_call(func, (yyvsp[-1].exprVal));
                                                            }
#line 2343 "../source/parser.c"
    break;

  case 59:
#line 481 "../source/syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(empty) (call -> ( funcdef() ))\n");
                                                                }

                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = (yyvsp[-3].symTabEntry);
                                                                (yyval.exprVal) = make_call(func, NULL);
                                                            }
#line 2357 "../source/parser.c"
    break;

  case 60:
#line 492 "../source/syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>NORMAL CALL (callsuffix -> normcall)\n");
                                }

                                (yyval.callFunc) = (yyvsp[0].callFunc);
                            }
#line 2369 "../source/parser.c"
    break;

  case 61:
#line 499 "../source/syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>METHOD CALL (callsuffix -> methodcall)\n");
                                }

                                (yyval.callFunc) = (yyvsp[0].callFunc);
                            }
#line 2381 "../source/parser.c"
    break;

  case 62:
#line 508 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(ELIST) (normcall -> (elist) )\n");
                                                            }
                                                            (yyval.callFunc) = ManageNormalCall((yyvsp[-1].exprVal));
                                                        }
#line 2392 "../source/parser.c"
    break;

  case 63:
#line 514 "../source/syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(empty) (normcall -> ())\n");
                                                            }

                                                            (yyval.callFunc) = ManageNormalCall(NULL);
                                                        }
#line 2404 "../source/parser.c"
    break;

  case 64:
#line 523 "../source/syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (ELIST) (methodcall -> ..ID(elist))\n", (yyvsp[-3].string_value));
                                                                                }

                                                                                (yyval.callFunc) = ManageMethodCall((yyvsp[-1].exprVal),(yyvsp[-3].string_value));
                                                                            }
#line 2416 "../source/parser.c"
    break;

  case 65:
#line 530 "../source/syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (empty) (methodcall -> ..ID())\n", (yyvsp[-2].string_value));
                                                                                }

                                                                                (yyval.callFunc) = ManageMethodCall(NULL,(yyvsp[-2].string_value));
                                                                            }
#line 2428 "../source/parser.c"
    break;

  case 66:
#line 539 "../source/syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>EXPR (elist -> expr)\n");
                                    }
                                    partEvaluation((yyvsp[0].exprVal));
                                    (yyval.exprVal) = (yyvsp[0].exprVal);
                                }
#line 2440 "../source/parser.c"
    break;

  case 67:
#line 546 "../source/syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ELIST , EXPR (elist -> elist COMMA expr)\n");
                                    }

                                    partEvaluation((yyvsp[0].exprVal));
                                    (yyvsp[0].exprVal)->next = (yyvsp[-2].exprVal);
                                    (yyval.exprVal) = (yyvsp[0].exprVal);
                                }
#line 2454 "../source/parser.c"
    break;

  case 68:
#line 557 "../source/syn_an.y"
                                                {
                                                    indexedPair *p;

                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[INDEXED] (objectdef -> [indexed])\n");
                                                    }

                                                    p = reverseIndexedPairList((yyvsp[-1].indPair));
                                                    (yyval.exprVal) = ManageIndexedObjectDef(p);
                                                }
#line 2469 "../source/parser.c"
    break;

  case 69:
#line 567 "../source/syn_an.y"
                                                {
                                                    expr *rev;
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[ELIST] (objectdef -> [ELIST])\n");
                                                    }
                                                    rev = reverseExprList((yyvsp[-1].exprVal));
                                                    (yyval.exprVal) = ManageObjectDef(rev);
                                                }
#line 2482 "../source/parser.c"
    break;

  case 70:
#line 575 "../source/syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[empty] (objectdef -> [])\n");
                                                    }
                                                    (yyval.exprVal) = ManageObjectDef(NULL);
                                                }
#line 2493 "../source/parser.c"
    break;

  case 71:
#line 583 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>INDEXED_ELEM (indexed -> indexedelem)\n");
                                            }

                                            (yyval.indPair) = (yyvsp[0].indPair);
                                        }
#line 2505 "../source/parser.c"
    break;

  case 72:
#line 590 "../source/syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> INDEXED , INDEXED_ELEM (indexed -> indexed COMMA indexedelem)\n");
                                            }

                                            (yyvsp[0].indPair)->next = (yyvsp[-2].indPair);
                                            (yyval.indPair) = (yyvsp[0].indPair);
                                        }
#line 2518 "../source/parser.c"
    break;

  case 73:
#line 600 "../source/syn_an.y"
                                                    {
                                                        if(TRACE_PRINT){
                                                            fprintf(ost, "=>{EXPR : EXPR} (indexedelem -> { expr : expr })\n");
                                                        }

                                                        /*We are not sure for this -- Check again*/
                                                        partEvaluation((yyvsp[-3].exprVal));
                                                        partEvaluation((yyvsp[-1].exprVal));

                                                        (yyval.indPair) = newIndexPair((yyvsp[-3].exprVal), (yyvsp[-1].exprVal));
                                                    }
#line 2534 "../source/parser.c"
    break;

  case 74:
#line 613 "../source/syn_an.y"
                       {scope++;}
#line 2540 "../source/parser.c"
    break;

  case 75:
#line 613 "../source/syn_an.y"
                                                        {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;

                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{Empty} (block -> {})\n");
                                                            }

                                                            (yyval.st) = newstmt();
                                                        }
#line 2555 "../source/parser.c"
    break;

  case 76:
#line 623 "../source/syn_an.y"
                         {scope++;}
#line 2561 "../source/parser.c"
    break;

  case 77:
#line 623 "../source/syn_an.y"
                                                        {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;

                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{STMTS} (block -> {stmts})\n");
                                                            }
                                                        
                                                            (yyval.st) = (yyvsp[-1].st);
                                                        }
#line 2576 "../source/parser.c"
    break;

  case 78:
#line 635 "../source/syn_an.y"
                    {
                        (yyval.string_value) = (yyvsp[0].string_value);
                    }
#line 2584 "../source/parser.c"
    break;

  case 79:
#line 638 "../source/syn_an.y"
                    {
                        GenerateFuncName();
                        (yyval.string_value) = anonymous_func_prefix;
                    }
#line 2593 "../source/parser.c"
    break;

  case 80:
#line 644 "../source/syn_an.y"
                                    {
                                        (yyval.symTabEntry) = ManageIDFunctionDefinition((yyvsp[0].string_value));
                                        
                                        if((yyval.symTabEntry) != NULL){
                                            emit(funcstart_op, lvalue_expr((yyval.symTabEntry)), NULL, NULL, 0, yylineno);
                                        }else{
                                            /*...We are not sure about that...*/
                                            emit(funcstart_op, NULL, NULL, NULL, 0, yylineno);
                                        }

                                        NumberStack_push(scopeoffsetstack, currscopeoffset());
                                        scope++;

                                        enterscopespace();
                                        resetformalargsoffset();
                                    }
#line 2614 "../source/parser.c"
    break;

  case 81:
#line 662 "../source/syn_an.y"
                                                            {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
#line 2624 "../source/parser.c"
    break;

  case 82:
#line 667 "../source/syn_an.y"
                                                            {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
#line 2634 "../source/parser.c"
    break;

  case 83:
#line 674 "../source/syn_an.y"
                        {
                            (yyval.un_value) = currscopeoffset();
                            exitscopespace();
                        }
#line 2643 "../source/parser.c"
    break;

  case 84:
#line 680 "../source/syn_an.y"
                        {
                            NumberStack_push(loopStack, loopcounter);
                            loopcounter = 0;
                        }
#line 2652 "../source/parser.c"
    break;

  case 85:
#line 686 "../source/syn_an.y"
                        {
                            loopcounter = NumberStack_pop(loopStack);
                        }
#line 2660 "../source/parser.c"
    break;

  case 86:
#line 691 "../source/syn_an.y"
                                                                        {

                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>FUNCDEF (funcdef -> function ID () block)\n");
                                                }

                                                exitscopespace();
                                                
                                                if((yyvsp[-4].symTabEntry) != NULL){
                                                    ((yyvsp[-4].symTabEntry)->value).funcVal->totalLocals = (yyvsp[-1].un_value); //check
                                                    emit(funcend_op, lvalue_expr((yyvsp[-4].symTabEntry)), NULL, NULL, 0, yylineno);
                                                }else{
                                                    /*We are not sure about that either*/
                                                    emit(funcend_op, NULL, NULL, NULL, 0, yylineno);
                                                }

                                                int offset = NumberStack_pop(scopeoffsetstack);
                                                restorecurrscopeoffset(offset);
                                                
                                                //FuncStack_print(functionStack);
                                                FuncStack_pop(functionStack);
                                                
                                                (yyval.symTabEntry) = (yyvsp[-4].symTabEntry);
                                            }
#line 2689 "../source/parser.c"
    break;

  case 87:
#line 718 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>INTEGER %d (const -> INTEGER)\n", (yyvsp[0].int_value));
                            }

                            (yyval.exprVal) = newexpr_constnum((yyvsp[0].int_value) * 1.0);
                        }
#line 2701 "../source/parser.c"
    break;

  case 88:
#line 725 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>Real %f (const -> REAL)\n", (yyvsp[0].real_value));
                            }

                            (yyval.exprVal) = newexpr_constnum((yyvsp[0].real_value));
                        }
#line 2713 "../source/parser.c"
    break;

  case 89:
#line 732 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>String %s (const -> STRING)\n", (yyvsp[0].string_value));
                            }

                            (yyval.exprVal) = newexpr_conststring((yyvsp[0].string_value)); //strdup inside!
                        }
#line 2725 "../source/parser.c"
    break;

  case 90:
#line 739 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>NIL (const -> NIL)\n");
                            }

                            (yyval.exprVal) = newexpr_nil();
                        }
#line 2737 "../source/parser.c"
    break;

  case 91:
#line 746 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>TRUE (const -> TRUE)\n");
                            }

                            (yyval.exprVal) = newexpr_constbool(1);
                        }
#line 2749 "../source/parser.c"
    break;

  case 92:
#line 753 "../source/syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>FALSE (const -> FALSE)\n");
                            }

                            (yyval.exprVal) = newexpr_constbool(0);
                        }
#line 2761 "../source/parser.c"
    break;

  case 93:
#line 762 "../source/syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ID %s (idlist -> ID)\n", (yyvsp[0].string_value));
                                    }

                                    CheckAddFormal((yyvsp[0].string_value));
                                }
#line 2773 "../source/parser.c"
    break;

  case 94:
#line 769 "../source/syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>IDLIST , ID %s (idlist -> idlist, ID)\n", (yyvsp[0].string_value));
                                    }

                                    CheckAddFormal((yyvsp[0].string_value));
                                }
#line 2785 "../source/parser.c"
    break;

  case 95:
#line 778 "../source/syn_an.y"
                                                            {
                                                                (yyval.un_value) = ManageIfPrefix((yyvsp[-1].exprVal));                                             
                                                            }
#line 2793 "../source/parser.c"
    break;

  case 96:
#line 783 "../source/syn_an.y"
                                    {
                                        (yyval.un_value) = nextquadlabel();
                                        emit(jump_op, NULL, NULL, NULL, 0, yylineno);
                                    }
#line 2802 "../source/parser.c"
    break;

  case 97:
#line 789 "../source/syn_an.y"
                                            {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>IF ELSE (ifstmt -> if(expr)stmt else stmt)\n");
                                                }

                                                int breaklist1 = 0, breaklist2 = 0, contlist1 = 0, contlist2 = 0;

                                                patchlabel((yyvsp[-3].un_value), (yyvsp[-1].un_value) + 1);
                                                patchlabel((yyvsp[-1].un_value), nextquadlabel());

                                                (yyval.st) = newstmt();

                                                if((yyvsp[-2].st) != NULL){
                                                    breaklist1 = (yyvsp[-2].st)->breakList;
                                                    contlist1 = (yyvsp[-2].st)->contList;
                                                }
                                                
                                                if((yyvsp[0].st) != NULL){
                                                    breaklist2 = (yyvsp[0].st)->breakList;
                                                    contlist2 = (yyvsp[0].st)->contList;
                                                }

                                                (yyval.st)->breakList = mergelist(breaklist1, breaklist2);
                                                (yyval.st)->contList = mergelist(contlist1, contlist2);
                                            }
#line 2832 "../source/parser.c"
    break;

  case 98:
#line 814 "../source/syn_an.y"
                                            {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>IF ELSE (ifstmt -> if(expr) stmt)\n");
                                                }

                                                patchlabel((yyvsp[-1].un_value), nextquadlabel());
                                                (yyval.st) = (yyvsp[0].st); //Alert!
                                            }
#line 2845 "../source/parser.c"
    break;

  case 99:
#line 824 "../source/syn_an.y"
                        {
                            ++loopcounter;
                        }
#line 2853 "../source/parser.c"
    break;

  case 100:
#line 829 "../source/syn_an.y"
                        {
                            --loopcounter;
                        }
#line 2861 "../source/parser.c"
    break;

  case 101:
#line 834 "../source/syn_an.y"
                                    {
                                        (yyval.st) = (yyvsp[-1].st);
                                    }
#line 2869 "../source/parser.c"
    break;

  case 102:
#line 839 "../source/syn_an.y"
                        {
                            (yyval.un_value) = nextquadlabel();
                        }
#line 2877 "../source/parser.c"
    break;

  case 103:
#line 844 "../source/syn_an.y"
                                                    {
                                                        partEvaluation((yyvsp[-1].exprVal));
                                                        emit(if_eq_op, (yyvsp[-1].exprVal), newexpr_constbool(1), NULL, nextquadlabel() + 2, yylineno);
                                                        
                                                        (yyval.un_value) = nextquadlabel();
                                                        emit(jump_op, NULL, NULL, NULL, 0, yylineno);
                                                    }
#line 2889 "../source/parser.c"
    break;

  case 104:
#line 854 "../source/syn_an.y"
                                        {
                                            int bl = 0, cl = 0;

                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>while(EXPR) (whilestmt -> while(expr) stmt)\n");
                                            }

                                            emit(jump_op, NULL, NULL, NULL, (yyvsp[-2].un_value), yylineno);
                                            
                                            patchlabel((yyvsp[-1].un_value), nextquadlabel());
                                            
                                            if((yyvsp[0].st) != NULL){
                                                bl = (yyvsp[0].st)->breakList;
                                                cl = (yyvsp[0].st)->contList;
                                            }

                                            patchlist(bl, nextquadlabel());
                                            patchlist(cl, (yyvsp[-2].un_value));
                                        }
#line 2913 "../source/parser.c"
    break;

  case 105:
#line 875 "../source/syn_an.y"
            {
                (yyval.un_value) = nextquadlabel();
                emit(jump_op, NULL, NULL, NULL, 0, yylineno);
            }
#line 2922 "../source/parser.c"
    break;

  case 106:
#line 881 "../source/syn_an.y"
            {
                (yyval.un_value) = nextquadlabel();
            }
#line 2930 "../source/parser.c"
    break;

  case 107:
#line 887 "../source/syn_an.y"
            { 
                //$6 = valToBool($6, nextquadlabel(), nextquadlabel()+1);
            }
#line 2938 "../source/parser.c"
    break;

  case 108:
#line 890 "../source/syn_an.y"
                        {
                            (yyval.forPrefJumps) = ManageForPrefix((yyvsp[-2].exprVal), (yyvsp[-3].un_value));
                        }
#line 2946 "../source/parser.c"
    break;

  case 109:
#line 893 "../source/syn_an.y"
                                                     {
                    //$5 = valToBool($5, nextquadlabel(), nextquadlabel()+1);
                                                        }
#line 2954 "../source/parser.c"
    break;

  case 110:
#line 895 "../source/syn_an.y"
                                                                          {
                                                                        (yyval.forPrefJumps) = ManageForPrefix((yyvsp[-2].exprVal), (yyvsp[-3].un_value));
                                                                    }
#line 2962 "../source/parser.c"
    break;

  case 111:
#line 900 "../source/syn_an.y"
                                                                {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>FOR (forstmt -> for(elist; expr; elist))\n");
                                                                }
                                                                ManageForStatement((yyvsp[-6].forPrefJumps), (yyvsp[-5].un_value), (yyvsp[-2].un_value), (yyvsp[0].un_value), (yyvsp[-1].st));
                                                            }
#line 2973 "../source/parser.c"
    break;

  case 112:
#line 906 "../source/syn_an.y"
                                                                {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>FOR (forstmt -> for(elist; expr; elist))\n");
                                                                }

                                                                ManageForStatement((yyvsp[-5].forPrefJumps), (yyvsp[-4].un_value), (yyvsp[-2].un_value), (yyvsp[0].un_value), (yyvsp[-1].st));
                                                                
                                                            }
#line 2986 "../source/parser.c"
    break;

  case 113:
#line 916 "../source/syn_an.y"
                                    {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret; (returnstmt -> return;)\n");
                                        }

                                        ManageReturnStatement(NULL);
                                    }
#line 2998 "../source/parser.c"
    break;

  case 114:
#line 923 "../source/syn_an.y"
                                    {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret EXPR; (returnstmt -> return expr;)\n");
                                        }
                                        
                                        ManageReturnStatement((yyvsp[-1].exprVal));
                                    }
#line 3010 "../source/parser.c"
    break;


#line 3014 "../source/parser.c"

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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



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
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 932 "../source/syn_an.y"


int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
    //fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d.\n", message, yylineno);
    compileError = 1;
    return 0;
}

int main(int argc, char **argv){

    int opt;
    char* file_name;

    ost = stdout;
    yyin = stdin;

    while ((opt = getopt(argc, argv, "i:o:h")) != -1)
    {
        switch (opt)
        { 
        case 'i':
            file_name = strdup (optarg);
            if(!(yyin = fopen(file_name, "r"))){
                fprintf(stderr, "Cannot read file: %s\n", file_name);
                free(file_name);
                return -1;
            }
            free(file_name);
            break;
        case 'o':
            file_name = strdup (optarg);
            if(!(ost = fopen(file_name, "w+"))){
                fprintf(stderr, "Cannot open file: %s\n", file_name);
                free(file_name);
                return -1;
            }
            free(file_name);
            break;
        case 'h':
            printf("Usage:\n[-i]: The input file. By default input file stream is stdin.\n[-o]: The output file. By default output file stream is stdout.\n[-h]: Prints the help prompt.\n");
            return 0;
        default:
            printf("Wrong command line arguments. Run with \"-h\" for help.\n");
            return -1;    
        }
    }    

    InitFuncNames();
    resettemp();

    symTab = SymbolTable_init();
    scopeTab = ScopeTable_init();
    functionStack = FuncStack_init();
    loopStack = NumberStack_init();
    scopeoffsetstack = NumberStack_init();

    SymbolTable_add_libfun(symTab, scopeTab);

    emit(jump_op, NULL, NULL, NULL, 0, yylineno);

    yyparse();

    //SymbolTable_print(symTab, ost);
    ScopeTable_print(scopeTab, ost);

    if(!compileError){
        printQuads(1, ost);
        //printQuads(0, ost);
        printToFile();
        //quads->target code
    }
    else{
        fprintf_red(stderr, "[Alpha Compiler] -- COMPILATION ERROR: Intermediate code generation failed.\n");
    }



    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
