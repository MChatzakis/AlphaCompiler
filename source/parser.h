/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    SymbolTableEntry *symTabEntry;


#line 163 "parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
