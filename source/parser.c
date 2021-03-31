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

    SymbolTableEntry *symTabEntry;

#line 238 "parser.c"

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
#define YYFINAL  67
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   563

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

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
       0,    53,    53,    54,    57,    62,    67,    72,    77,    82,
      87,    92,    97,   102,   109,   110,   113,   122,   127,   132,
     137,   142,   147,   152,   157,   162,   169,   174,   179,   184,
     189,   194,   199,   204,   211,   218,   225,   232,   239,   247,
     255,   260,   265,   272,   280,   287,   295,   303,   308,   313,
     318,   326,   332,   343,   349,   354,   361,   368,   375,   380,
     385,   392,   397,   404,   409,   416,   423,   423,   430,   430,
     441,   441,   441,   446,   446,   446,   446,   456,   461,   466,
     471,   476,   481,   488,   498,   507,   514,   519,   526,   533,
     540,   545
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
  "indexed", "indexedelem", "block", "$@1", "$@2", "funcdef", "$@3", "$@4",
  "$@5", "$@6", "$@7", "const", "idlist", "ifstmt", "whilestmt", "forstmt",
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

#define YYPACT_NINF (-151)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     182,  -151,  -151,  -151,  -151,    -3,    20,    94,  -151,    36,
      19,    38,    50,    23,   217,    41,    67,   233,    80,  -151,
    -151,  -151,   233,     2,     2,   101,  -151,   182,   372,  -151,
     453,  -151,     6,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,   102,   182,   233,   436,    25,    26,  -151,   309,   103,
    -151,   233,   233,   233,  -151,  -151,  -151,   393,  -151,  -151,
    -151,  -151,  -151,    91,    -5,     6,    -5,  -151,  -151,  -151,
     233,   233,   233,   233,   233,   233,   233,   233,   233,   233,
     233,   233,   233,   233,   233,   108,   111,   233,  -151,  -151,
    -151,  -151,  -151,   233,   233,   113,  -151,   141,   462,  -151,
     233,  -151,   112,  -151,   118,   330,   351,     5,   121,   128,
    -151,   123,   490,   477,    45,    45,  -151,  -151,  -151,   503,
     503,   516,   516,   516,   516,   267,    30,  -151,   127,   436,
     288,    43,  -151,  -151,   233,   436,  -151,   233,   182,   182,
     233,  -151,  -151,    46,   118,  -151,  -151,   233,  -151,  -151,
     244,    77,   119,  -151,   414,   128,  -151,   135,    78,  -151,
    -151,   182,   233,    81,   116,  -151,  -151,  -151,    90,  -151,
    -151,   182,   116,  -151,  -151
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    77,    78,    43,    79,    68,    60,     0,    13,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    81,
      82,    80,     0,     0,     0,     0,    15,     2,     0,    37,
      38,    46,    39,    40,    11,    12,    42,     5,     6,     7,
       8,     0,     0,     0,    58,     0,     0,    63,     0,     0,
      45,     0,     0,    60,    73,    70,    90,     0,     9,    10,
      32,    44,    31,     0,    33,     0,    35,     1,    14,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    60,     0,     0,     0,    34,    36,
      52,    54,    55,     0,    60,     0,    67,     0,     0,    62,
       0,    61,     0,    30,    41,     0,     0,     0,     0,    85,
      91,     0,    18,    17,    25,    26,    27,    28,    29,    20,
      19,    24,    23,    22,    21,     0,     0,    47,     0,    16,
       0,     0,    49,    69,     0,    59,    64,    60,     0,     0,
       0,    74,    83,     0,     0,    48,    56,    60,    50,    51,
       0,     0,    86,    88,     0,    85,    71,     0,     0,    65,
      53,     0,    60,     0,     0,    84,    57,    87,     0,    75,
      72,     0,     0,    89,    76
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -151,  -151,   -18,   100,    -6,  -151,    83,  -151,    85,  -151,
    -151,  -151,   -51,  -151,  -151,    49,  -150,  -151,  -151,    -4,
    -151,  -151,  -151,  -151,  -151,  -151,     0,  -151,  -151,  -151,
    -151
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    90,
      91,    92,    45,    33,    46,    47,    34,    41,    42,    35,
     109,   164,   108,   155,   172,    36,   143,    37,    38,    39,
      40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      44,    48,   107,    49,    83,   -66,    84,     3,    57,    68,
      85,    60,    86,    63,   170,    93,    62,    94,   140,   100,
       9,    95,   174,     1,     2,     3,     4,    43,    54,     6,
      51,     7,    18,   126,    55,    99,   101,    98,     9,   100,
     102,    50,   146,   131,   100,   105,   106,    44,    17,    52,
      18,    19,    20,    21,    58,   149,    22,   100,   156,   111,
     157,    53,    23,    24,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,    44,    68,
      59,   129,    74,    75,    76,    61,   151,   130,    44,   160,
     166,   100,   100,   169,   135,   157,   158,     1,     2,     3,
       4,    67,   171,     6,   100,     7,    64,    66,    65,    65,
      96,   168,     9,   127,    13,   104,   128,    13,   132,    43,
     152,   153,    17,     5,    18,    19,    20,    21,   150,   137,
      22,    44,   141,   142,   154,   144,    23,    24,   147,   161,
     165,    44,    97,   167,     1,     2,     3,     4,     5,   133,
       6,   136,     7,   173,     8,   163,    44,     0,     0,     9,
      10,     0,    11,    12,    13,    14,    15,    16,     0,    17,
       0,    18,    19,    20,    21,     0,     0,    22,     0,     0,
       0,     0,     0,    23,    24,     1,     2,     3,     4,     5,
       0,     6,     0,     7,     0,     8,     0,     0,     0,     0,
       9,    10,     0,    11,    12,    13,    14,    15,    16,     0,
      17,     0,    18,    19,    20,    21,     0,     0,    22,     0,
       1,     2,     3,     4,    23,    24,     6,     0,     7,     0,
      56,     0,     0,     0,     0,     9,     1,     2,     3,     4,
       0,     0,     6,     0,     7,    17,     0,    18,    19,    20,
      21,     9,   159,    22,     0,     0,     0,     0,     0,    23,
      24,    17,     0,    18,    19,    20,    21,     0,     0,    22,
       0,    70,     0,    71,     0,    23,    24,   145,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,     0,     0,    70,     0,    71,     0,   148,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    70,     0,    71,     0,     0,
       0,   103,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,    70,     0,    71,     0,
       0,     0,   138,     0,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,    70,     0,    71,
       0,     0,     0,   139,     0,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    70,     0,
      71,     0,     0,     0,     0,    69,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    70,
       0,    71,     0,     0,     0,     0,   110,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
      70,     0,    71,     0,     0,     0,     0,   162,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    70,     0,    71,     0,     0,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    83,    70,    84,    71,     0,     0,    85,     0,
      86,    72,    73,    74,    75,    76,    77,    78,   134,     0,
      79,    80,    81,    82,     0,     0,     0,    87,     0,    70,
       0,    71,     0,     0,     0,    88,    89,    72,    73,    74,
      75,    76,    77,    78,    70,     0,    79,    80,    81,    82,
       0,     0,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    72,    73,
      74,    75,    76,   -67,   -67,     0,     0,    79,    80,    81,
      82,    72,    73,    74,    75,    76,     0,     0,     0,     0,
     -67,   -67,   -67,   -67
};

static const yytype_int16 yycheck[] =
{
       6,     7,    53,     7,     9,     8,    11,     5,    14,    27,
      15,    17,    17,    11,   164,     9,    22,    11,    13,    14,
      18,    15,   172,     3,     4,     5,     6,     7,     5,     9,
      11,    11,    30,    84,    11,    10,    10,    43,    18,    14,
      14,     5,    12,    94,    14,    51,    52,    53,    28,    11,
      30,    31,    32,    33,    13,    12,    36,    14,    12,    63,
      14,    11,    42,    43,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    97,
      13,    87,    37,    38,    39,     5,   137,    93,    94,    12,
      12,    14,    14,    12,   100,    14,   147,     3,     4,     5,
       6,     0,    12,     9,    14,    11,    23,    24,    23,    24,
       8,   162,    18,     5,    23,    12,     5,    23,     5,     7,
     138,   139,    28,     7,    30,    31,    32,    33,   134,    11,
      36,   137,    11,     5,   140,    12,    42,    43,    11,    20,
       5,   147,    42,   161,     3,     4,     5,     6,     7,     8,
       9,   102,    11,   171,    13,   155,   162,    -1,    -1,    18,
      19,    -1,    21,    22,    23,    24,    25,    26,    -1,    28,
      -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    42,    43,     3,     4,     5,     6,     7,
      -1,     9,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,
      18,    19,    -1,    21,    22,    23,    24,    25,    26,    -1,
      28,    -1,    30,    31,    32,    33,    -1,    -1,    36,    -1,
       3,     4,     5,     6,    42,    43,     9,    -1,    11,    -1,
      13,    -1,    -1,    -1,    -1,    18,     3,     4,     5,     6,
      -1,    -1,     9,    -1,    11,    28,    -1,    30,    31,    32,
      33,    18,     8,    36,    -1,    -1,    -1,    -1,    -1,    42,
      43,    28,    -1,    30,    31,    32,    33,    -1,    -1,    36,
      -1,    27,    -1,    29,    -1,    42,    43,    10,    -1,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    44,    45,
      46,    47,    -1,    -1,    27,    -1,    29,    -1,    10,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    27,    -1,    29,    -1,    -1,
      -1,    12,    -1,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    44,    45,    46,    47,    27,    -1,    29,    -1,
      -1,    -1,    12,    -1,    35,    36,    37,    38,    39,    40,
      41,    -1,    -1,    44,    45,    46,    47,    27,    -1,    29,
      -1,    -1,    -1,    12,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    46,    47,    27,    -1,
      29,    -1,    -1,    -1,    -1,    13,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    44,    45,    46,    47,    27,
      -1,    29,    -1,    -1,    -1,    -1,    13,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    44,    45,    46,    47,
      27,    -1,    29,    -1,    -1,    -1,    -1,    13,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    27,    -1,    29,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    39,    40,    41,    -1,    -1,    44,    45,
      46,    47,     9,    27,    11,    29,    -1,    -1,    15,    -1,
      17,    35,    36,    37,    38,    39,    40,    41,    16,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,    34,    -1,    27,
      -1,    29,    -1,    -1,    -1,    42,    43,    35,    36,    37,
      38,    39,    40,    41,    27,    -1,    44,    45,    46,    47,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44,    45,    46,    47,    35,    36,    37,    38,    39,
      40,    41,    -1,    -1,    44,    45,    46,    47,    35,    36,
      37,    38,    39,    40,    41,    -1,    -1,    44,    45,    46,
      47,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      44,    45,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     9,    11,    13,    18,
      19,    21,    22,    23,    24,    25,    26,    28,    30,    31,
      32,    33,    36,    42,    43,    50,    51,    52,    53,    54,
      55,    56,    57,    62,    65,    68,    74,    76,    77,    78,
      79,    66,    67,     7,    53,    61,    63,    64,    53,    68,
       5,    11,    11,    11,     5,    11,    13,    53,    13,    13,
      53,     5,    53,    11,    55,    57,    55,     0,    51,    13,
      27,    29,    35,    36,    37,    38,    39,    40,    41,    44,
      45,    46,    47,     9,    11,    15,    17,    34,    42,    43,
      58,    59,    60,     9,    11,    15,     8,    52,    53,    10,
      14,    10,    14,    12,    12,    53,    53,    61,    71,    69,
      13,    68,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    61,     5,     5,    53,
      53,    61,     5,     8,    16,    53,    64,    11,    12,    12,
      13,    11,     5,    75,    12,    10,    12,    11,    10,    12,
      53,    61,    51,    51,    53,    72,    12,    14,    61,     8,
      12,    20,    13,    75,    70,     5,    12,    51,    61,    12,
      65,    12,    73,    51,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    54,    54,
      54,    54,    54,    55,    55,    55,    55,    56,    56,    56,
      56,    57,    57,    57,    58,    58,    59,    60,    61,    61,
      61,    62,    62,    63,    63,    64,    66,    65,    67,    65,
      69,    70,    68,    71,    72,    73,    68,    74,    74,    74,
      74,    74,    74,    75,    75,    75,    76,    76,    77,    78,
      79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     3,     1,     1,     2,     2,     1,     3,     4,     3,
       4,     4,     2,     6,     1,     1,     3,     5,     1,     3,
       0,     3,     3,     1,     3,     5,     0,     3,     0,     4,
       0,     0,     7,     0,     0,     0,     9,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     5,     7,     5,     9,
       2,     3
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
#line 57 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Expr Statement\n");
                                            }
                                        }
#line 1620 "parser.c"
    break;

  case 5:
#line 62 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> If/Ifelse Statement\n");
                                            }
                                        }
#line 1630 "parser.c"
    break;

  case 6:
#line 67 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> While Statement\n");
                                            }
                                        }
#line 1640 "parser.c"
    break;

  case 7:
#line 72 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> For Statement\n");
                                            }
                                        }
#line 1650 "parser.c"
    break;

  case 8:
#line 77 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Return Statement\n");
                                            }
                                        }
#line 1660 "parser.c"
    break;

  case 9:
#line 82 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Break Statement\n");
                                            }
                                        }
#line 1670 "parser.c"
    break;

  case 10:
#line 87 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Continue Statement\n");
                                            }
                                        }
#line 1680 "parser.c"
    break;

  case 11:
#line 92 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Block Statement\n");
                                            }
                                        }
#line 1690 "parser.c"
    break;

  case 12:
#line 97 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Func Def Statement\n");
                                            }
                                        }
#line 1700 "parser.c"
    break;

  case 13:
#line 102 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Semicolon Statement\n");
                                            }
                                        }
#line 1710 "parser.c"
    break;

  case 16:
#line 113 "syn_an.y"
                                        {
                                            
                                            if(TRACE_PRINT){
                                                printf("-> Assignment Expression\n");
                                            }

                                            ManageAssignValue((yyvsp[-2].symTabEntry));
                                        
                                        }
#line 1724 "parser.c"
    break;

  case 17:
#line 122 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> OR Expression\n");
                                            }
                                        }
#line 1734 "parser.c"
    break;

  case 18:
#line 127 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> AND Expression\n");
                                            }
                                        }
#line 1744 "parser.c"
    break;

  case 19:
#line 132 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> != Expression\n");
                                            }
                                        }
#line 1754 "parser.c"
    break;

  case 20:
#line 137 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> == Expression\n");
                                            }
                                        }
#line 1764 "parser.c"
    break;

  case 21:
#line 142 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> <= Expression\n");
                                            }
                                        }
#line 1774 "parser.c"
    break;

  case 22:
#line 147 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> < Expression\n");
                                            }
                                        }
#line 1784 "parser.c"
    break;

  case 23:
#line 152 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> >= Expression\n");
                                            }
                                        }
#line 1794 "parser.c"
    break;

  case 24:
#line 157 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> > Expression\n");
                                            }
                                        }
#line 1804 "parser.c"
    break;

  case 25:
#line 162 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> + Expression\n");
                                            }
                                            

                                        }
#line 1816 "parser.c"
    break;

  case 26:
#line 169 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> - Expression\n");
                                            }
                                        }
#line 1826 "parser.c"
    break;

  case 27:
#line 174 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> * Expression\n");
                                            }
                                        }
#line 1836 "parser.c"
    break;

  case 28:
#line 179 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> / Expression\n");
                                            }
                                        }
#line 1846 "parser.c"
    break;

  case 29:
#line 184 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> MOD Expression\n");
                                            }
                                        }
#line 1856 "parser.c"
    break;

  case 30:
#line 189 "syn_an.y"
                                                      {
                                            if(TRACE_PRINT){
                                                printf("-> ( Expression )\n");
                                            }
                                        }
#line 1866 "parser.c"
    break;

  case 31:
#line 194 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> -Expression\n");
                                            }
                                        }
#line 1876 "parser.c"
    break;

  case 32:
#line 199 "syn_an.y"
                                        {
                                           if(TRACE_PRINT){
                                                printf("-> NOT Expression\n");
                                            }
                                        }
#line 1886 "parser.c"
    break;

  case 33:
#line 204 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> ++val Expression\n");
                                            }

                                            ManageAssignValue((yyvsp[0].symTabEntry));
                                        }
#line 1898 "parser.c"
    break;

  case 34:
#line 211 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> val++ Expression\n");
                                            }

                                            ManageAssignValue((yyvsp[-1].symTabEntry));
                                        }
#line 1910 "parser.c"
    break;

  case 35:
#line 218 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> --val Expression\n");
                                            }

                                            ManageAssignValue((yyvsp[0].symTabEntry));
                                        }
#line 1922 "parser.c"
    break;

  case 36:
#line 225 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> val-- Expression\n");
                                            }

                                            ManageAssignValue((yyvsp[-1].symTabEntry));
                                        }
#line 1934 "parser.c"
    break;

  case 37:
#line 232 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Primary Expression\n");
                                            }
                                        }
#line 1944 "parser.c"
    break;

  case 38:
#line 239 "syn_an.y"
                                        {                                            
                                            if(TRACE_PRINT){
                                                printf("-> lvalue \n");
                                            }
                                            //printf("AAA: %d\n", $1->type);
                                            ManagePrimaryLValue((yyvsp[0].symTabEntry));    

                                        }
#line 1957 "parser.c"
    break;

  case 39:
#line 247 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Function Call\n");
                                            }

                                            //edw einai to anapodo x();

                                        }
#line 1970 "parser.c"
    break;

  case 40:
#line 255 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Object definition\n");
                                            }
                                        }
#line 1980 "parser.c"
    break;

  case 41:
#line 260 "syn_an.y"
                                                            {
                                                                if(TRACE_PRINT){
                                                                    printf("-> (func definition)\n");
                                                                }
                                                            }
#line 1990 "parser.c"
    break;

  case 42:
#line 265 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Const\n");
                                            }
                                        }
#line 2000 "parser.c"
    break;

  case 43:
#line 272 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Identifier %s\n", (yyvsp[0].string_value));
                                            }
                                            
                                            (yyval.symTabEntry) = EvaluateLValue((yyvsp[0].string_value));
                                        }
#line 2012 "parser.c"
    break;

  case 44:
#line 280 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Local Identifier %s\n", (yyvsp[0].string_value));
                                            }

                                            (yyval.symTabEntry) = EvaluateLocalLValue((yyvsp[0].string_value));
                                        }
#line 2024 "parser.c"
    break;

  case 45:
#line 287 "syn_an.y"
                                        {

                                            if(TRACE_PRINT){
                                                printf("-> Global Identifier %s\n", (yyvsp[0].string_value));
                                            }

                                            (yyval.symTabEntry) = EvaluateGlobalLValue((yyvsp[0].string_value));
                                        }
#line 2037 "parser.c"
    break;

  case 46:
#line 295 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Member\n");
                                            }
                                        }
#line 2047 "parser.c"
    break;

  case 47:
#line 303 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> lvalue . %s\n", (yyvsp[0].string_value));
                                                            }
                                                        }
#line 2057 "parser.c"
    break;

  case 48:
#line 308 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> Lvalue [ expression ]\n");
                                                            }
                                                        }
#line 2067 "parser.c"
    break;

  case 49:
#line 313 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> Call.%s\n", (yyvsp[0].string_value));
                                                            }
                                                        }
#line 2077 "parser.c"
    break;

  case 50:
#line 318 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> call [ expr ]\n");
                                                            }
                                                        }
#line 2087 "parser.c"
    break;

  case 51:
#line 326 "syn_an.y"
                                                                                                    {
                                                                                                        if(TRACE_PRINT){
                                                                                                            printf("-> Call ( elist )\n");
                                                                                                        }

                                                                                                    }
#line 2098 "parser.c"
    break;

  case 52:
#line 332 "syn_an.y"
                                                                                                    {
                                                                                                        if(TRACE_PRINT){
                                                                                                            if((yyvsp[-1].symTabEntry)->type < 3){
                                                                                                                //logika prepei error message
                                                                                                                printf("-> %s callsuffix\n", ((yyvsp[-1].symTabEntry)->value).varVal->name);
                                                                                                            }else{
                                                                                                                printf("-> %s callsuffix\n",  ((yyvsp[-1].symTabEntry)->value).funcVal->name);
                                                                                                            }
                                                                                                        }

                                                                                                    }
#line 2114 "parser.c"
    break;

  case 53:
#line 343 "syn_an.y"
                                                                                                    {
                                                                                                        if(TRACE_PRINT){
                                                                                                            printf("-> Function Definition\n");
                                                                                                        }                                                                                                    }
#line 2123 "parser.c"
    break;

  case 54:
#line 349 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> Normal Call\n");
                                }
                            }
#line 2133 "parser.c"
    break;

  case 55:
#line 354 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> Method Call\n");
                                }
                            }
#line 2143 "parser.c"
    break;

  case 56:
#line 361 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> ( elist )\n");
                                                            }
                                                        }
#line 2153 "parser.c"
    break;

  case 57:
#line 368 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> ..%s ( elist )\n", (yyvsp[-3].string_value));
                                                                                }
                                                                            }
#line 2163 "parser.c"
    break;

  case 58:
#line 375 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> expr\n");
                                            }
                                        }
#line 2173 "parser.c"
    break;

  case 59:
#line 380 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> elist , expr\n");
                                            }
                                        }
#line 2183 "parser.c"
    break;

  case 60:
#line 385 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Empty Elist\n");
                                            }
                                        }
#line 2193 "parser.c"
    break;

  case 61:
#line 392 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        printf("-> [ indexed ]\n");
                                                    }
                                                }
#line 2203 "parser.c"
    break;

  case 62:
#line 397 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        printf("-> [ elist ]\n");
                                                    }
                                                }
#line 2213 "parser.c"
    break;

  case 63:
#line 404 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        printf("-> Indexed Element\n");
                                                    }
                                                }
#line 2223 "parser.c"
    break;

  case 64:
#line 409 "syn_an.y"
                                                {
                                                    if(TRACE_PRINT){
                                                        printf("-> Indexed , Indexed Element\n");
                                                    }
                                                }
#line 2233 "parser.c"
    break;

  case 65:
#line 416 "syn_an.y"
                                                        {
                                                            if(TRACE_PRINT){
                                                                printf("-> { expr : expr }\n");
                                                            }
                                                        }
#line 2243 "parser.c"
    break;

  case 66:
#line 423 "syn_an.y"
                       {scope++;}
#line 2249 "parser.c"
    break;

  case 67:
#line 423 "syn_an.y"
                                                                {
                                                                    ScopeTable_hide_scope(scopeTab, scope);
                                                                    scope--;
                                                                    if(TRACE_PRINT){
                                                                        printf("-> Empty Block\n");
                                                                    }
                                                                }
#line 2261 "parser.c"
    break;

  case 68:
#line 430 "syn_an.y"
                         {scope++;}
#line 2267 "parser.c"
    break;

  case 69:
#line 430 "syn_an.y"
                                                                {
                                                                    ScopeTable_hide_scope(scopeTab, scope);
                                                                    scope--;
                                                                    if(TRACE_PRINT){
                                                                        printf("-> Statement Block\n");
                                                                    }
                                                                }
#line 2279 "parser.c"
    break;

  case 70:
#line 441 "syn_an.y"
                                      { ManageIDFunctionDefinition("__F"); unamed_functions++; scope++;}
#line 2285 "parser.c"
    break;

  case 71:
#line 441 "syn_an.y"
                                                                                                                                  {scope--;}
#line 2291 "parser.c"
    break;

  case 72:
#line 441 "syn_an.y"
                                                                                                                                                        {
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> Function Definition without ID\n");
                                                                                                    }
                                                                                                }
#line 2301 "parser.c"
    break;

  case 73:
#line 446 "syn_an.y"
                            { ManageIDFunctionDefinition((yyvsp[0].string_value)); }
#line 2307 "parser.c"
    break;

  case 74:
#line 446 "syn_an.y"
                                                                                 {scope++;}
#line 2313 "parser.c"
    break;

  case 75:
#line 446 "syn_an.y"
                                                                                                                     {scope--;}
#line 2319 "parser.c"
    break;

  case 76:
#line 447 "syn_an.y"
                                                                                                {
                                                                                                    
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> Function Definition with ID\n");
                                                                                                    }
                                                                                                    
                                                                                                }
#line 2331 "parser.c"
    break;

  case 77:
#line 456 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> Integer %d\n", (yyvsp[0].int_value));
                                }
                            }
#line 2341 "parser.c"
    break;

  case 78:
#line 461 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> Real %f\n", (yyvsp[0].real_value));
                                }
                            }
#line 2351 "parser.c"
    break;

  case 79:
#line 466 "syn_an.y"
                            {
                               if(TRACE_PRINT){
                                    printf("-> String %s\n", (yyvsp[0].string_value));
                                }
                            }
#line 2361 "parser.c"
    break;

  case 80:
#line 471 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> NIL\n");
                                }
                            }
#line 2371 "parser.c"
    break;

  case 81:
#line 476 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> TRUE\n");
                                }
                            }
#line 2381 "parser.c"
    break;

  case 82:
#line 481 "syn_an.y"
                            {
                                if(TRACE_PRINT){
                                    printf("-> FALSE");
                                }
                            }
#line 2391 "parser.c"
    break;

  case 83:
#line 488 "syn_an.y"
                                {
                                    
                                    if(TRACE_PRINT){
                                        printf("-> Single ID List %s\n", (yyvsp[0].string_value));
                                    }

                                    if(CheckAddFormal((yyvsp[0].string_value)) == NULL)
                                        ;
                                    
                                }
#line 2406 "parser.c"
    break;

  case 84:
#line 498 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        printf("-> , ID List %s\n", (yyvsp[0].string_value));
                                    }

                                    if(CheckAddFormal((yyvsp[0].string_value)) == NULL)
                                        ;
                                    
                                }
#line 2420 "parser.c"
    break;

  case 85:
#line 507 "syn_an.y"
                                {
                                    if(TRACE_PRINT){
                                        printf("-> , Empty ID List\n");
                                    }
                                }
#line 2430 "parser.c"
    break;

  case 86:
#line 514 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> If\n");
                                                                                }
                                                                            }
#line 2440 "parser.c"
    break;

  case 87:
#line 519 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> If Else\n");
                                                                                }
                                                                            }
#line 2450 "parser.c"
    break;

  case 88:
#line 526 "syn_an.y"
                                                                            {
                                                                                if(TRACE_PRINT){
                                                                                    printf("-> While\n");
                                                                                }
                                                                            }
#line 2460 "parser.c"
    break;

  case 89:
#line 533 "syn_an.y"
                                                                                                {
                                                                                                    if(TRACE_PRINT){
                                                                                                        printf("-> For\n");
                                                                                                    }
                                                                                                }
#line 2470 "parser.c"
    break;

  case 90:
#line 540 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Simple Return\n");
                                            }
                                        }
#line 2480 "parser.c"
    break;

  case 91:
#line 545 "syn_an.y"
                                        {
                                            if(TRACE_PRINT){
                                                printf("-> Expr Return\n");
                                            }
                                        }
#line 2490 "parser.c"
    break;


#line 2494 "parser.c"

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
#line 552 "syn_an.y"


int yyerror(char *message){
    fprintf_red(stderr, "[Syntax Analysis] -- ERROR: %s: at line %d, on token: %s\n", message, yylineno, yytext);
    return 0;
}

int main(int argc, char **argv){

    FILE *ost;
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

    symTab = SymbolTable_init();
    scopeTab = ScopeTable_init();

    SymbolTable_add_libfun(symTab, scopeTab);

    yyparse();

    //SymbolTable_print(symTab);
    ScopeTable_print(scopeTab);

    fclose(ost);
    fclose(yyin);
    
    return 0;   
}
