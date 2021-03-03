/**
 * @file Token.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-03-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
 
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TOKEN_TYPE {
  UNDEFINED,
  KEYWORD,
  OPERATOR,
  CONST_INT,
  CONST_REAL,
  STRING,
  IDENT,
  LINE_COMMENT,
  BLOCK_COMMENT,
  NESTED_COMMENT,
  PUNCTUATION
};

struct alpha_token_t {
  unsigned int numline;              /* Arithmos Grammis */
  unsigned int endline;              /* Arithmos telous grammis */
  unsigned int numToken;             /* Arithmos Token */
  char *content;                     /* Periexomena Token*/
  char *type;                        /* Eidos Token */
  enum TOKEN_TYPE token_type;        /* Typos Token */
  struct alpha_token_t *alpha_yylex; /* Next Token */
};

typedef struct alpha_token_t alpha_token_t;

alpha_token_t *alpha_token_init();

void alpha_token_insert(alpha_token_t *head, unsigned int numline,
                        unsigned int endline, char *content,
                        enum TOKEN_TYPE token_type, char *type);

void alpha_token_print(alpha_token_t *token, FILE *ost);

void alpha_token_print_list(alpha_token_t *head, FILE *ost);

void alpha_token_free_list(alpha_token_t *head);