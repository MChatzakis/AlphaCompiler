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
#line 2 "syn_an.y"

    #ifdef WIN32
    #define YY_NO_UNISTD_H
    static int isatty(int i) {return 0;}
    #elif _WIN32_WCE
    #define YY_NO_UNISTD_H
    static int isatty(void *i) {return 0;}
    #endif

    #include "yacc_libs/yacc_api.h"

#line 82 "parser.c"

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
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
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
    RETURN = 279,
    BREAK = 280,
    CONTINUE = 281,
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
#define RETURN 279
#define BREAK 280
#define CONTINUE 281
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
#line 17 "syn_an.y"

    int int_value;
    char* string_value;
    double real_value;
    expr* exprVal;
    call* callFunc;
    indexedPair* indPair;
    SymbolTableEntry *symTabEntry;


#line 241 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



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
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   833

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

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
       0,    62,    62,    63,    66,    73,    80,    87,    94,   101,
     109,   117,   124,   131,   140,   141,   144,   150,   155,   160,
     165,   170,   175,   180,   185,   190,   195,   200,   205,   210,
     215,   221,   226,   231,   237,   243,   249,   255,   262,   268,
     275,   282,   291,   300,   307,   313,   319,   328,   335,   345,
     350,   357,   364,   372,   379,   389,   401,   407,   415,   421,
     430,   437,   446,   452,   462,   478,   484,   492,   500,   510,
     519,   519,   526,   526,   535,   538,   544,   556,   561,   568,
     574,   596,   603,   610,   617,   624,   631,   640,   646,   655,
     660,   667,   667,   677,   677,   684,   684,   691,   691,   698,
     698,   707,   713
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
  "WHILE", "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT",
  "OR", "LOCAL", "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS", "MINUS", "MUL",
  "DIV", "MODULO", "EQUAL", "NOT_EQUAL", "PLUS_PLUS", "MINUS_MINUS",
  "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL", "UMINUS", "$accept",
  "program", "stmt", "stmts", "expr", "primary", "lvalue", "member",
  "call", "callsuffix", "normcall", "methodcall", "elist", "objectdef",
  "indexed", "indexedelem", "block", "$@1", "$@2", "funcname",
  "funcprefix", "funcargs", "funcbody", "funcdef", "const", "idlist",
  "ifstmt", "whilestmt", "$@3", "forstmt", "$@4", "$@5", "$@6", "$@7",
  "returnstmt", YY_NULLPTR
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

#define YYPACT_NINF (-54)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     211,   -54,   -54,   -54,   -54,    -1,   252,     9,   -54,    17,
      39,    49,    97,    24,   268,    87,   109,   529,   125,   -54,
     -54,   -54,   529,    81,    81,   110,   -54,   211,   647,   -54,
     749,   -54,    15,   -54,   -54,   121,   -54,   -54,   -54,   -54,
     -54,   -54,   126,   211,   529,   -54,   732,    -5,    21,   -54,
     584,   123,   -54,   529,   529,   303,   -54,   -54,   -54,   668,
     -54,   -54,   -54,   -54,   -54,   113,     8,    15,     8,   -54,
     -54,   -54,   529,   529,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   529,   529,   529,   338,   128,   132,   529,
     -54,   -54,   -54,   -54,   -54,   529,   373,   134,    16,   133,
     -54,   170,   758,   -54,   529,   -54,   135,   -54,   137,   605,
     626,   529,    68,   -54,   131,    18,   773,    58,    58,   -54,
     -54,   -54,   786,   786,   316,   316,   316,   316,   540,   -54,
      -8,   -54,   139,   732,   563,   -54,    22,   -54,   -54,   -54,
      32,   -54,   -54,   -54,   529,   732,   -54,   408,   211,   -54,
     689,   529,   137,   -54,   -54,   443,   -54,   -54,   -54,   141,
      80,   -54,    73,   124,   211,   478,   710,   -54,    79,   -54,
     -54,   -54,   211,   -54,   -54,    89,   513,   -54,   -54,   211,
     -54,   -54,    92,   -54,   211,   211,   -54,   -54,   -54,   211,
     -54
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    81,    82,    43,    83,    72,     0,     0,    13,     0,
       0,     0,     0,    75,     0,     0,     0,     0,     0,    85,
      86,    84,     0,     0,     0,     0,    15,     2,     0,    37,
      38,    46,    39,    40,    11,     0,    12,    42,     5,     6,
       7,     8,     0,     0,     0,    66,    62,     0,     0,    67,
       0,     0,    45,     0,     0,     0,    74,    76,   101,     0,
       9,    10,    32,    44,    31,     0,    33,     0,    35,     1,
      14,     4,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      34,    36,    53,    56,    57,     0,     0,     0,     0,     0,
      71,     0,     0,    65,     0,    64,     0,    30,    41,     0,
       0,     0,     0,   102,     0,    18,    17,    25,    26,    27,
      28,    29,    20,    19,    24,    23,    22,    21,     0,    59,
       0,    47,     0,    16,     0,    52,     0,    49,    87,    78,
       0,    79,    80,    73,     0,    63,    68,     0,     0,    91,
       0,     0,     0,    48,    58,     0,    50,    51,    77,     0,
       0,    55,     0,    90,     0,     0,     0,    61,     0,    88,
      69,    54,     0,    92,    99,     0,     0,    60,    89,     0,
      95,    97,     0,   100,     0,     0,    93,    96,    98,     0,
      94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -17,   108,    -6,   -54,    90,   -54,   105,   -54,
     -54,   -54,   -53,   -54,   -54,    46,    54,   -54,   -54,   -54,
     -54,   -54,   -54,    -4,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -54
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    92,
      93,    94,    47,    33,    48,    49,    34,    42,    43,    57,
      35,    99,   142,    36,    37,   140,    38,    39,   164,    40,
     189,   184,   185,   179,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    50,   112,    51,   154,   103,   104,   -70,    59,   104,
      70,    62,     1,     2,     3,     4,    64,    85,     6,    86,
       7,   138,    52,    87,    95,    88,    96,     9,   139,    56,
      97,   105,    13,   130,   157,   106,   104,    17,   102,    18,
      19,    20,    21,   136,   158,    22,   159,   109,   110,    46,
      53,    23,    24,    74,    75,    76,    77,    78,    79,    80,
      54,   114,    81,    82,    83,    84,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      46,   151,   104,   133,    70,   171,     3,   104,   170,   134,
      46,   177,    65,   104,   162,    76,    77,    78,   145,     9,
      60,   180,   168,   104,   186,   150,   104,    72,    55,    73,
      69,    18,   175,    66,    68,    74,    75,    76,    77,    78,
      79,    80,    61,   182,    81,    82,    83,    84,    67,    67,
      63,   163,    98,   131,   100,   108,    13,   132,   160,   137,
       5,    46,    44,   152,   172,   166,   169,   173,   147,    46,
     155,   101,   146,   141,     0,   178,     0,     0,     0,    46,
       0,     0,   183,     0,     0,     0,     0,   187,   188,     0,
      46,     0,   190,     1,     2,     3,     4,     5,   143,     6,
       0,     7,     0,     8,     0,     0,     0,     0,     9,    10,
       0,    11,    12,    13,    14,    15,    16,     0,    17,     0,
      18,    19,    20,    21,     0,     0,    22,     0,     0,     0,
       0,     0,    23,    24,     1,     2,     3,     4,     5,     0,
       6,     0,     7,     0,     8,     0,     0,     0,     0,     9,
      10,     0,    11,    12,    13,    14,    15,    16,     0,    17,
       0,    18,    19,    20,    21,     0,     0,    22,     0,     0,
       0,     0,     0,    23,    24,     1,     2,     3,     4,    44,
       0,     6,    45,     7,     0,     0,     0,     0,     0,     0,
       9,     1,     2,     3,     4,     0,     0,     6,     0,     7,
      17,    58,    18,    19,    20,    21,     9,     0,    22,     0,
       0,     0,     0,     0,    23,    24,    17,     0,    18,    19,
      20,    21,     0,     0,    22,     0,     1,     2,     3,     4,
      23,    24,     6,     0,     7,     0,   111,     0,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    18,    19,    20,    21,     0,     0,    22,
       0,     1,     2,     3,     4,    23,    24,     6,     0,     7,
     129,    74,    75,    76,    77,    78,     9,     0,     0,     0,
     -71,   -71,   -71,   -71,     0,     0,    17,     0,    18,    19,
      20,    21,     0,     0,    22,     0,     1,     2,     3,     4,
      23,    24,     6,     0,     7,   135,     0,     0,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    18,    19,    20,    21,     0,     0,    22,
       0,     1,     2,     3,     4,    23,    24,     6,     0,     7,
     161,     0,     0,     0,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    18,    19,
      20,    21,     0,     0,    22,     0,     1,     2,     3,     4,
      23,    24,     6,     0,     7,   167,     0,     0,     0,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    18,    19,    20,    21,     0,     0,    22,
       0,     1,     2,     3,     4,    23,    24,     6,     0,     7,
     174,     0,     0,     0,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,     0,    18,    19,
      20,    21,     0,     0,    22,     0,     1,     2,     3,     4,
      23,    24,     6,     0,     7,   181,     0,     0,     0,     0,
       0,     9,     1,     2,     3,     4,     0,     0,     6,     0,
       7,    17,     0,    18,    19,    20,    21,     9,     0,    22,
     153,     0,     0,     0,     0,    23,    24,    17,     0,    18,
      19,    20,    21,     0,     0,    22,     0,    72,     0,    73,
       0,    23,    24,   156,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,     0,     0,
      72,     0,    73,     0,     0,     0,   107,     0,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    72,     0,    73,     0,     0,     0,   148,     0,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,    72,     0,    73,     0,     0,     0,   149,     0,
      74,    75,    76,    77,    78,    79,    80,     0,     0,    81,
      82,    83,    84,    72,     0,    73,     0,     0,     0,     0,
      71,    74,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,    72,     0,    73,     0,     0,     0,
       0,   113,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84,    72,     0,    73,     0,     0,
       0,     0,   165,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,    72,     0,    73,     0,
       0,     0,     0,   176,    74,    75,    76,    77,    78,    79,
      80,     0,     0,    81,    82,    83,    84,    72,     0,    73,
       0,     0,     0,     0,     0,    74,    75,    76,    77,    78,
      79,    80,     0,     0,    81,    82,    83,    84,    85,    72,
      86,    73,     0,     0,    87,     0,    88,    74,    75,    76,
      77,    78,    79,    80,   144,     0,    81,    82,    83,    84,
       0,     0,     0,    89,     0,    72,     0,    73,     0,     0,
       0,    90,    91,    74,    75,    76,    77,    78,    79,    80,
      72,     0,    81,    82,    83,    84,     0,     0,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    74,    75,    76,    77,    78,   -71,   -71,     0,     0,
      81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       6,     7,    55,     7,    12,    10,    14,     8,    14,    14,
      27,    17,     3,     4,     5,     6,    22,     9,     9,    11,
      11,     5,     5,    15,     9,    17,    11,    18,    12,     5,
      15,    10,    23,    86,    12,    14,    14,    28,    44,    30,
      31,    32,    33,    96,    12,    36,    14,    53,    54,    55,
      11,    42,    43,    35,    36,    37,    38,    39,    40,    41,
      11,    65,    44,    45,    46,    47,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    13,    14,    89,   101,    12,     5,    14,     8,    95,
      96,    12,    11,    14,   147,    37,    38,    39,   104,    18,
      13,    12,   155,    14,    12,   111,    14,    27,    11,    29,
       0,    30,   165,    23,    24,    35,    36,    37,    38,    39,
      40,    41,    13,   176,    44,    45,    46,    47,    23,    24,
       5,   148,    11,     5,     8,    12,    23,     5,   144,     5,
       7,   147,     7,    12,    20,   151,     5,   164,    11,   155,
      11,    43,   106,    99,    -1,   172,    -1,    -1,    -1,   165,
      -1,    -1,   179,    -1,    -1,    -1,    -1,   184,   185,    -1,
     176,    -1,   189,     3,     4,     5,     6,     7,     8,     9,
      -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    18,    19,
      -1,    21,    22,    23,    24,    25,    26,    -1,    28,    -1,
      30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    42,    43,     3,     4,     5,     6,     7,    -1,
       9,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    18,
      19,    -1,    21,    22,    23,    24,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,     3,     4,     5,     6,     7,
      -1,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    -1,
      18,     3,     4,     5,     6,    -1,    -1,     9,    -1,    11,
      28,    13,    30,    31,    32,    33,    18,    -1,    36,    -1,
      -1,    -1,    -1,    -1,    42,    43,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    36,    -1,     3,     4,     5,     6,
      42,    43,     9,    -1,    11,    -1,    13,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36,
      -1,     3,     4,     5,     6,    42,    43,     9,    -1,    11,
      12,    35,    36,    37,    38,    39,    18,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    36,    -1,     3,     4,     5,     6,
      42,    43,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36,
      -1,     3,     4,     5,     6,    42,    43,     9,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    36,    -1,     3,     4,     5,     6,
      42,    43,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36,
      -1,     3,     4,     5,     6,    42,    43,     9,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    30,    31,
      32,    33,    -1,    -1,    36,    -1,     3,     4,     5,     6,
      42,    43,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    18,     3,     4,     5,     6,    -1,    -1,     9,    -1,
      11,    28,    -1,    30,    31,    32,    33,    18,    -1,    36,
      10,    -1,    -1,    -1,    -1,    42,    43,    28,    -1,    30,
      31,    32,    33,    -1,    -1,    36,    -1,    27,    -1,    29,
      -1,    42,    43,    10,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      27,    -1,    29,    -1,    -1,    -1,    12,    -1,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    27,    -1,    29,    -1,    -1,    -1,    12,    -1,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    44,    45,
      46,    47,    27,    -1,    29,    -1,    -1,    -1,    12,    -1,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    44,
      45,    46,    47,    27,    -1,    29,    -1,    -1,    -1,    -1,
      13,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      44,    45,    46,    47,    27,    -1,    29,    -1,    -1,    -1,
      -1,    13,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    27,    -1,    29,    -1,    -1,
      -1,    -1,    13,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    44,    45,    46,    47,    27,    -1,    29,    -1,
      -1,    -1,    -1,    13,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    44,    45,    46,    47,    27,    -1,    29,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    46,    47,     9,    27,
      11,    29,    -1,    -1,    15,    -1,    17,    35,    36,    37,
      38,    39,    40,    41,    16,    -1,    44,    45,    46,    47,
      -1,    -1,    -1,    34,    -1,    27,    -1,    29,    -1,    -1,
      -1,    42,    43,    35,    36,    37,    38,    39,    40,    41,
      27,    -1,    44,    45,    46,    47,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    11,    13,    18,
      19,    21,    22,    23,    24,    25,    26,    28,    30,    31,
      32,    33,    36,    42,    43,    50,    51,    52,    53,    54,
      55,    56,    57,    62,    65,    69,    72,    73,    75,    76,
      78,    83,    66,    67,     7,    10,    53,    61,    63,    64,
      53,    72,     5,    11,    11,    11,     5,    68,    13,    53,
      13,    13,    53,     5,    53,    11,    55,    57,    55,     0,
      51,    13,    27,    29,    35,    36,    37,    38,    39,    40,
      41,    44,    45,    46,    47,     9,    11,    15,    17,    34,
      42,    43,    58,    59,    60,     9,    11,    15,    11,    70,
       8,    52,    53,    10,    14,    10,    14,    12,    12,    53,
      53,    13,    61,    13,    72,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    12,
      61,     5,     5,    53,    53,    12,    61,     5,     5,    12,
      74,    65,    71,     8,    16,    53,    64,    11,    12,    12,
      53,    13,    12,    10,    12,    11,    10,    12,    12,    14,
      53,    12,    61,    51,    77,    13,    53,    12,    61,     5,
       8,    12,    20,    51,    12,    61,    13,    12,    51,    82,
      12,    12,    61,    51,    80,    81,    12,    51,    51,    79,
      51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    55,    55,    55,    55,    56,    56,    56,
      56,    57,    57,    57,    57,    57,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    62,    62,    63,    63,    64,
      66,    65,    67,    65,    68,    68,    69,    70,    70,    71,
      72,    73,    73,    73,    73,    73,    73,    74,    74,    75,
      75,    77,    76,    79,    78,    80,    78,    81,    78,    82,
      78,    83,    83
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     3,     2,     6,     5,     1,     1,     3,     2,
       5,     4,     1,     3,     3,     3,     2,     1,     3,     5,
       0,     3,     0,     4,     1,     0,     2,     3,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     7,
       5,     0,     6,     0,    10,     0,     9,     0,     9,     0,
       8,     2,     3
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
#line 66 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Expr Statement (stmt -> expr;)\n");
                                            }

                                            resettemp();
                                        }
#line 1689 "parser.c"
    break;

  case 5:
#line 73 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>If/Ifelse Statement (stmt -> ifstmt)\n");
                                            }

                                            resettemp();
                                        }
#line 1701 "parser.c"
    break;

  case 6:
#line 80 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>While Statement (stmt -> whilestmt)\n");
                                            }

                                            resettemp();
                                        }
#line 1713 "parser.c"
    break;

  case 7:
#line 87 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>For Statement (stmt -> forstmt)\n");
                                            }

                                            resettemp();
                                        }
#line 1725 "parser.c"
    break;

  case 8:
#line 94 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Return Statement (stmt -> return)\n");
                                            }

                                            resettemp();
                                        }
#line 1737 "parser.c"
    break;

  case 9:
#line 101 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Break Statement (stmt -> break)\n");
                                            }
                                            ManageLoopKeywords("break");

                                            resettemp();
                                        }
#line 1750 "parser.c"
    break;

  case 10:
#line 109 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Continue Statement (stmt -> continue;)\n");
                                            }
                                            ManageLoopKeywords("continue");

                                            resettemp();
                                        }
#line 1763 "parser.c"
    break;

  case 11:
#line 117 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Block Statement (stmt -> block)\n");
                                            }

                                            resettemp();
                                        }
#line 1775 "parser.c"
    break;

  case 12:
#line 124 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Func Def Statement (stmt -> funcdef)\n");
                                            }

                                            resettemp();
                                        }
#line 1787 "parser.c"
    break;

  case 13:
#line 131 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Semicolon Statement (stmt -> ;)\n");
                                            }

                                            resettemp();
                                        }
#line 1799 "parser.c"
    break;

  case 16:
#line 144 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>Assignment Expression (expr -> lvalue = expr)\n");
                                            }
                                            (yyval.exprVal) = ManageAssignValue((yyvsp[-2].exprVal), (yyvsp[0].exprVal));
                                        }
#line 1810 "parser.c"
    break;

  case 17:
#line 150 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OR Expression (expr -> expr or expr)\n");
                                            }
                                        }
#line 1820 "parser.c"
    break;

  case 18:
#line 155 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>AND Expression (expr -> expr and expr)\n");
                                            }
                                        }
#line 1830 "parser.c"
    break;

  case 19:
#line 160 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT EQUAL Expression (expr -> expr != expr)\n");
                                            }
                                        }
#line 1840 "parser.c"
    break;

  case 20:
#line 165 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>EQUAL Expression (expr -> expr == expr)\n");
                                            }
                                        }
#line 1850 "parser.c"
    break;

  case 21:
#line 170 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS EQUAL Expression (expr -> expr <= expr)\n");
                                            }
                                        }
#line 1860 "parser.c"
    break;

  case 22:
#line 175 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>LESS Expression (expr -> expr < expr)\n");
                                            }
                                        }
#line 1870 "parser.c"
    break;

  case 23:
#line 180 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER EQUAL Expression (expr -> expr >= expr)\n");
                                            }
                                        }
#line 1880 "parser.c"
    break;

  case 24:
#line 185 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>GREATER Expression (expr -> expr > expr)\n");
                                            }
                                        }
#line 1890 "parser.c"
    break;

  case 25:
#line 190 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS Expression (expr -> expr + expr)\n");
                                            }
                                        }
#line 1900 "parser.c"
    break;

  case 26:
#line 195 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS Expression (expr -> expr - expr)\n");
                                            }
                                        }
#line 1910 "parser.c"
    break;

  case 27:
#line 200 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MUL Expression (expr -> expr * expr) \n");
                                            }
                                        }
#line 1920 "parser.c"
    break;

  case 28:
#line 205 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>DIV Expression (expr -> expr / expr) \n");
                                            }
                                        }
#line 1930 "parser.c"
    break;

  case 29:
#line 210 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MODULO Expression (expr -> expr MOD expr)\n");
                                            }
                                        }
#line 1940 "parser.c"
    break;

  case 30:
#line 216 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PARENTHESIS EXPR Expression (expr -> (expr) )\n");
                                            }
                                        }
#line 1950 "parser.c"
    break;

  case 31:
#line 221 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>-EXPR Expression (expr -> -expr)\n");
                                            }
                                        }
#line 1960 "parser.c"
    break;

  case 32:
#line 226 "syn_an.y"
                                        {
                                           if(TRACE_PRINT){
                                                fprintf(ost, "=>NOT Expression (expr -> not expr)\n");
                                            }
                                        }
#line 1970 "parser.c"
    break;

  case 33:
#line 231 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PLUS PLUS lvalue Expression (expr -> ++lvalue)\n");
                                            }
                                            //ManageAssignValue($2);
                                        }
#line 1981 "parser.c"
    break;

  case 34:
#line 237 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue PLUS PLUS Expression (expr -> lvalue++ )\n");
                                            }
                                            //ManageAssignValue($1);
                                        }
#line 1992 "parser.c"
    break;

  case 35:
#line 243 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MINUS MINUS lvalue Expression (expr -> --lvalue)\n");
                                            }
                                            //ManageAssignValue($2);
                                        }
#line 2003 "parser.c"
    break;

  case 36:
#line 249 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue MINUS MINUS Expression (expr -> lvalue--)\n");
                                            }
                                            //ManageAssignValue($1);
                                        }
#line 2014 "parser.c"
    break;

  case 37:
#line 255 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>PRIMARY Expression (expr -> primary)\n");
                                            }
                                        }
#line 2024 "parser.c"
    break;

  case 38:
#line 262 "syn_an.y"
                                        {                                 
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>lvalue (primary -> lvalue)\n");
                                            }
                                            (yyval.exprVal) = ManagePrimaryLValue((yyvsp[0].exprVal));    
                                        }
#line 2035 "parser.c"
    break;

  case 39:
#line 268 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CALL (primary -> call)\n");
                                            }
                                            (yyval.exprVal) = ManagePrimaryFunction((yyvsp[0].exprVal));

                                        }
#line 2047 "parser.c"
    break;

  case 40:
#line 275 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>OBJECT DEF (primary -> objectdef)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2059 "parser.c"
    break;

  case 41:
#line 283 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>(funcdef) (primary -> (funcdef))\n");
                                            }

                                            (yyval.exprVal) = newexpr(programfunc_e);
                                            (yyval.exprVal)->sym = (yyvsp[-1].symTabEntry);
                                        }
#line 2072 "parser.c"
    break;

  case 42:
#line 291 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>CONST (primary -> const)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2084 "parser.c"
    break;

  case 43:
#line 300 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>ID %s (lvalue -> ID)\n", (yyvsp[0].string_value));
                                            }
                                            (yyval.exprVal) = EvaluateLValue((yyvsp[0].string_value));
                                        }
#line 2095 "parser.c"
    break;

  case 44:
#line 307 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> local ID %s (lvalue -> local ID)\n", (yyvsp[0].string_value));
                                            }
                                            (yyval.exprVal) = EvaluateLocalLValue((yyvsp[0].string_value));
                                        }
#line 2106 "parser.c"
    break;

  case 45:
#line 313 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>global ID %s (lvalue -> global ID)\n", (yyvsp[0].string_value));
                                            }
                                            (yyval.exprVal) = EvaluateGlobalLValue((yyvsp[0].string_value));
                                        }
#line 2117 "parser.c"
    break;

  case 46:
#line 319 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>MEMBER (lvalue -> member)\n");
                                            }

                                            (yyval.exprVal) = (yyvsp[0].exprVal);
                                        }
#line 2129 "parser.c"
    break;

  case 47:
#line 328 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue . ID %s (member -> lvalue.ID)\n", (yyvsp[0].string_value));
                                                            }

                                                            (yyval.exprVal) = member_item((yyvsp[-2].exprVal), (yyvsp[0].string_value)); 
                                                        }
#line 2141 "parser.c"
    break;

  case 48:
#line 335 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>lvalue [ EXPR ] (member -> lvalue[expr])\n");
                                                            }

                                                            (yyvsp[-3].exprVal) = emit_iftableitem((yyvsp[-3].exprVal));
                                                            (yyval.exprVal) = newexpr(tableitem_e);
                                                            (yyval.exprVal)->sym = (yyvsp[-3].exprVal)->sym;
                                                            (yyval.exprVal)->index = (yyvsp[-1].exprVal);
                                                        }
#line 2156 "parser.c"
    break;

  case 49:
#line 345 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>Call.ID %s (member -> call.ID)\n", (yyvsp[0].string_value));
                                                            }
                                                        }
#line 2166 "parser.c"
    break;

  case 50:
#line 350 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>CALL [ EXPR ] (member -> call[expr])\n");
                                                            }
                                                        }
#line 2176 "parser.c"
    break;

  case 51:
#line 357 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( ELIST ) (call -> call(elist))\n");
                                                                }           

                                                                (yyval.exprVal) = make_call((yyvsp[-3].exprVal), (yyvsp[-1].exprVal));
                                                            }
#line 2188 "parser.c"
    break;

  case 52:
#line 364 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>CALL ( empty ) (call -> call())\n");
                                                                }                                       
                                                                
                                                                (yyval.exprVal) = make_call((yyvsp[-2].exprVal), NULL);

                                                            }
#line 2201 "parser.c"
    break;

  case 53:
#line 372 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>lvalue ( CALL SUFFIX ) (call -> lvalue callsuffix)\n");                                       
                                                                }
                                                                //$$ = $1;
                                                                (yyval.exprVal) = ManageLvalueCallsuffix((yyvsp[-1].exprVal), (yyvsp[0].callFunc));
                                                            }
#line 2213 "parser.c"
    break;

  case 54:
#line 380 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(ELIST) (call -> ( funcdef(elist) ))\n");
                                                                }
                                                                
                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = (yyvsp[-4].symTabEntry);
                                                                (yyval.exprVal) = make_call(func, (yyvsp[-1].exprVal));
                                                            }
#line 2227 "parser.c"
    break;

  case 55:
#line 390 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    fprintf(ost, "=>(FUNCDEF)(empty) (call -> ( funcdef() ))\n");
                                                                }

                                                                expr* func = newexpr(programfunc_e);
                                                                func->sym = (yyvsp[-3].symTabEntry);
                                                                (yyval.exprVal) = make_call(func, NULL);
                                                            }
#line 2241 "parser.c"
    break;

  case 56:
#line 401 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>NORMAL CALL (callsuffix -> normcall)\n");
                                }
                                (yyval.callFunc) = (yyvsp[0].callFunc);
                            }
#line 2252 "parser.c"
    break;

  case 57:
#line 407 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    fprintf(ost, "=>METHOD CALL (callsuffix -> methodcall)\n");
                                }
                                (yyval.callFunc) = (yyvsp[0].callFunc);
                            }
#line 2263 "parser.c"
    break;

  case 58:
#line 415 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(ELIST) (normcall -> (elist) )\n");
                                                            }
                                                            (yyval.callFunc) = ManageNormalCall((yyvsp[-1].exprVal));
                                                        }
#line 2274 "parser.c"
    break;

  case 59:
#line 421 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>(empty) (normcall -> ())\n");
                                                            }

                                                            (yyval.callFunc) = ManageNormalCall(NULL);
                                                        }
#line 2286 "parser.c"
    break;

  case 60:
#line 430 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (ELIST) (methodcall -> ..ID(elist))\n", (yyvsp[-3].string_value));
                                                                                }

                                                                                (yyval.callFunc) = ManageMethodCall((yyvsp[-1].exprVal),(yyvsp[-3].string_value));
                                                                            }
#line 2298 "parser.c"
    break;

  case 61:
#line 437 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    fprintf(ost, "=> ..%s (empty) (methodcall -> ..ID())\n", (yyvsp[-2].string_value));
                                                                                }

                                                                                (yyval.callFunc) = ManageMethodCall(NULL,(yyvsp[-2].string_value));
                                                                            }
#line 2310 "parser.c"
    break;

  case 62:
#line 446 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>EXPR (elist -> expr)\n");
                                    }
                                    (yyval.exprVal) = (yyvsp[0].exprVal); //kseroume $1->next = NULL 
                                }
#line 2321 "parser.c"
    break;

  case 63:
#line 452 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ELIST , EXPR (elist -> elist COMMA expr)\n");
                                    }
                                    
                                    (yyvsp[0].exprVal)->next = (yyvsp[-2].exprVal);
                                    (yyval.exprVal) = (yyvsp[0].exprVal);
                                }
#line 2334 "parser.c"
    break;

  case 64:
#line 462 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[INDEXED] (objectdef -> [indexed])\n");
                                                    }
                                                    indexedPair* ptr;
                                                    expr* t = newexpr(newtable_e);
                                                    t->sym = newtemp();
                                                    emit(tablecreate_op, t, NULL, NULL, 0, yylineno);
                                                    ptr = (yyvsp[-1].indPair);
                                                    while(ptr){
                                                        emit(tablesetelem_op, t, ptr->key, ptr->val, 0, yylineno);
                                                        ptr = ptr->next;
                                                    }

                                                    (yyval.exprVal) = t;
                                                }
#line 2355 "parser.c"
    break;

  case 65:
#line 478 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[ELIST] (objectdef -> [ELIST])\n");
                                                    }
                                                    (yyval.exprVal) = ManageObjectDef((yyvsp[-1].exprVal));
                                                }
#line 2366 "parser.c"
    break;

  case 66:
#line 484 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        fprintf(ost, "=>[empty] (objectdef -> [])\n");
                                                    }
                                                    (yyval.exprVal) = ManageObjectDef(NULL);
                                                }
#line 2377 "parser.c"
    break;

  case 67:
#line 492 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=>INDEXED_ELEM (indexed -> indexedelem)\n");
                                            }

                                            (yyval.indPair) = (yyvsp[0].indPair);

                                        }
#line 2390 "parser.c"
    break;

  case 68:
#line 500 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                fprintf(ost, "=> INDEXED , INDEXED_ELEM (indexed -> indexed COMMA indexedelem)\n");
                                            }

                                            (yyvsp[0].indPair)->next = (yyvsp[-2].indPair);
                                            (yyval.indPair) = (yyvsp[0].indPair);
                                        }
#line 2403 "parser.c"
    break;

  case 69:
#line 510 "syn_an.y"
                                                    {
                                                        if(TRACE_PRINT){
                                                            fprintf(ost, "=>{EXPR : EXPR} (indexedelem -> { expr : expr })\n");
                                                        }
                                                        /*We are not sure for this -- Check again*/
                                                        (yyval.indPair) = newIndexPair((yyvsp[-3].exprVal), (yyvsp[-1].exprVal));
                                                    }
#line 2415 "parser.c"
    break;

  case 70:
#line 519 "syn_an.y"
                       {scope++;}
#line 2421 "parser.c"
    break;

  case 71:
#line 519 "syn_an.y"
                                                        {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{Empty} (block -> {})\n");
                                                            }
                                                        }
#line 2433 "parser.c"
    break;

  case 72:
#line 526 "syn_an.y"
                         {scope++;}
#line 2439 "parser.c"
    break;

  case 73:
#line 526 "syn_an.y"
                                                        {
                                                            ScopeTable_hide_scope(scopeTab, scope);
                                                            scope--;
                                                            if(TRACE_PRINT){
                                                                fprintf(ost, "=>{STMTS} (block -> {stmts})\n");
                                                            }
                                                        }
#line 2451 "parser.c"
    break;

  case 74:
#line 535 "syn_an.y"
                    {
                        (yyval.string_value) = (yyvsp[0].string_value);
                    }
#line 2459 "parser.c"
    break;

  case 75:
#line 538 "syn_an.y"
                    {
                        GenerateFuncName();
                        (yyval.string_value) = anonymous_func_prefix;
                    }
#line 2468 "parser.c"
    break;

  case 76:
#line 544 "syn_an.y"
                                    {
                                        (yyval.symTabEntry) = ManageIDFunctionDefinition((yyvsp[0].string_value));
                                        if((yyval.symTabEntry) != NULL){
                                            emit(funcstart_op, lvalue_expr((yyval.symTabEntry)), NULL, NULL, 0, yylineno);
                                        }
                                        NumberStack_push(scopeoffsetstack, currscopeoffset());
                                        scope++;
                                        enterscopespace();
                                        resetformalargsoffset();
                                    }
#line 2483 "parser.c"
    break;

  case 77:
#line 556 "syn_an.y"
                                                            {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
#line 2493 "parser.c"
    break;

  case 78:
#line 561 "syn_an.y"
                                                            {
                                                                enterscopespace();
                                                                resetfunctionlocalsoffset(); 
                                                                scope--;
                                                            }
#line 2503 "parser.c"
    break;

  case 79:
#line 568 "syn_an.y"
                        {
                            (yyval.int_value) = currscopeoffset();
                            exitscopespace();
                        }
#line 2512 "parser.c"
    break;

  case 80:
#line 574 "syn_an.y"
                                            {
                                                if(TRACE_PRINT){
                                                    fprintf(ost, "=>FUNCDEF (funcdef -> function ID () block)\n");
                                                }

                                                exitscopespace();
                                                if((yyvsp[-2].symTabEntry) != NULL){
                                                    ((yyvsp[-2].symTabEntry)->value).funcVal->totalLocals = (yyvsp[0].int_value); //check
                                                    emit(funcend_op, lvalue_expr((yyvsp[-2].symTabEntry)), NULL, NULL, 0, yylineno);
                                                }

                                                int offset = NumberStack_pop(scopeoffsetstack);
                                                restorecurrscopeoffset(offset);
                                                
                                                //FuncStack_print(functionStack);
                                                FuncStack_pop(functionStack);
                                                
                                                (yyval.symTabEntry) = (yyvsp[-2].symTabEntry);
                                            }
#line 2536 "parser.c"
    break;

  case 81:
#line 596 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>INTEGER %d (const -> INTEGER)\n", (yyvsp[0].int_value));
                            }

                            (yyval.exprVal) = newexpr_constnum((yyvsp[0].int_value) * 1.0);
                        }
#line 2548 "parser.c"
    break;

  case 82:
#line 603 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>Real %f (const -> REAL)\n", (yyvsp[0].real_value));
                            }

                            (yyval.exprVal) = newexpr_constnum((yyvsp[0].real_value));
                        }
#line 2560 "parser.c"
    break;

  case 83:
#line 610 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>String %s (const -> STRING)\n", (yyvsp[0].string_value));
                            }

                            (yyval.exprVal) = newexpr_conststring((yyvsp[0].string_value)); //strdup inside!
                        }
#line 2572 "parser.c"
    break;

  case 84:
#line 617 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>NIL (const -> NIL)\n");
                            }

                            (yyval.exprVal) = newexpr_nil();
                        }
#line 2584 "parser.c"
    break;

  case 85:
#line 624 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>TRUE (const -> TRUE)\n");
                            }

                            (yyval.exprVal) = newexpr_constbool(1);
                        }
#line 2596 "parser.c"
    break;

  case 86:
#line 631 "syn_an.y"
                        {
                            if(TRACE_PRINT){
                                fprintf(ost, "=>FALSE (const -> FALSE)\n");
                            }

                            (yyval.exprVal) = newexpr_constbool(0);
                        }
#line 2608 "parser.c"
    break;

  case 87:
#line 640 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>ID %s (idlist -> ID)\n", (yyvsp[0].string_value));
                                    }
                                    CheckAddFormal((yyvsp[0].string_value));
                                }
#line 2619 "parser.c"
    break;

  case 88:
#line 646 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        fprintf(ost, "=>IDLIST , ID %s (idlist -> idlist, ID)\n", (yyvsp[0].string_value));
                                    }
                                    CheckAddFormal((yyvsp[0].string_value));
                                }
#line 2630 "parser.c"
    break;

  case 89:
#line 655 "syn_an.y"
                                                                        {
                                                                            if(TRACE_PRINT){
                                                                                fprintf(ost, "=>IF ELSE (ifstmt -> if(expr)stmt else stmt)\n");
                                                                            }
                                                                        }
#line 2640 "parser.c"
    break;

  case 90:
#line 660 "syn_an.y"
                                                                        {
                                                                            if(TRACE_PRINT){
                                                                                fprintf(ost, "=>IF ELSE (ifstmt -> if(expr) stmt)\n");
                                                                            }
                                                                        }
#line 2650 "parser.c"
    break;

  case 91:
#line 667 "syn_an.y"
                                                          {loop_stack++; NumberStack_push(loopStack, scope);}
#line 2656 "parser.c"
    break;

  case 92:
#line 667 "syn_an.y"
                                                                                                                    {
                                                                    if(TRACE_PRINT){
                                                                        fprintf(ost, "=>while(EXPR) (whilestmt -> while(expr) stmt)\n");
                                                                    }
                                                                    loop_stack--;
                                                                    //NumberStack_print(loopStack);
                                                                    NumberStack_pop(loopStack);
                                                                }
#line 2669 "parser.c"
    break;

  case 93:
#line 677 "syn_an.y"
                                                                                        {loop_stack++; NumberStack_push(loopStack, scope);}
#line 2675 "parser.c"
    break;

  case 94:
#line 677 "syn_an.y"
                                                                                                                                                    {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "=>FOR (forstmt -> for(elist; expr; elist))\n");
                                                                                                    }
                                                                                                    loop_stack--;
                                                                                                    NumberStack_pop(loopStack);
                                                                                                }
#line 2687 "parser.c"
    break;

  case 95:
#line 684 "syn_an.y"
                                                                                   {loop_stack++; NumberStack_push(loopStack, scope);}
#line 2693 "parser.c"
    break;

  case 96:
#line 684 "syn_an.y"
                                                                                                                                                    {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "=>FOR (forstmt -> for(; expr; elist))\n");
                                                                                                    }
                                                                                                    loop_stack--;
                                                                                                    NumberStack_pop(loopStack);
                                                                                                }
#line 2705 "parser.c"
    break;

  case 97:
#line 691 "syn_an.y"
                                                                                   {loop_stack++; NumberStack_push(loopStack, scope); }
#line 2711 "parser.c"
    break;

  case 98:
#line 691 "syn_an.y"
                                                                                                                                                     {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "=>FOR (forstmt -> for(elist; expr; ))\n");
                                                                                                    }
                                                                                                    loop_stack--;
                                                                                                    NumberStack_pop(loopStack);
                                                                                                }
#line 2723 "parser.c"
    break;

  case 99:
#line 698 "syn_an.y"
                                                                             {loop_stack++; NumberStack_push(loopStack, scope);}
#line 2729 "parser.c"
    break;

  case 100:
#line 698 "syn_an.y"
                                                                                                                                                    {
                                                                                                    if(TRACE_PRINT){
                                                                                                        fprintf(ost, "=>FOR (forstmt -> for( ; expr; ))\n");
                                                                                                    }
                                                                                                    loop_stack--;
                                                                                                    NumberStack_pop(loopStack);
                                                                                                }
#line 2741 "parser.c"
    break;

  case 101:
#line 707 "syn_an.y"
                                    {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret; (returnstmt -> return;)\n");
                                        }
                                        ManageReturnStatement();
                                    }
#line 2752 "parser.c"
    break;

  case 102:
#line 713 "syn_an.y"
                                    {
                                        if(TRACE_PRINT){
                                            fprintf(ost, "=>ret EXPR; (returnstmt -> return expr;)\n");
                                        }
                                        ManageReturnStatement();
                                    }
#line 2763 "parser.c"
    break;


#line 2767 "parser.c"

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
#line 721 "syn_an.y"


int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
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

    yyparse();

    ScopeTable_print(scopeTab, ost);
    //SymbolTable_print(symTab, ost);

    if(!compileError){
        printQuads();
    }
    else{
        fprintf_red(stderr, "[Alpha Compiler] -- COMPILATION ERROR: Intermediate code generation failed.\n");
    }

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
