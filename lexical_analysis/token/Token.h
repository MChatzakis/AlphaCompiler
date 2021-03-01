#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TOKEN_TYPE {
  UNDEFINED,
  KEYWORD,
  OPERATOR,
  CONSTINT,
  CONSTREAL,
  STRING,
  IDENT,
  COMMENT,
  PUNCTUATION
};

// enum COMMENT_TYPE { LINE_COMMENT, BLOCK_COMMENT, NESTED_COMMENT };

// enum OPERATOR_TYPE { PLUS, PLUS_PLUS, MINUS, MINUS_MINUS };

struct alpha_token_t {
  unsigned int numline;  /* Arithmos Grammis */
  unsigned int endline;  /* Arithmos telous grammis */
  unsigned int numToken; /* Arithmos Token */

  char *content;              /* Periexomena Token*/
  enum TOKEN_TYPE token_type; /* Typos Token */
  char *type;                 /* Eidos Token */
  void *type_val;
  struct alpha_token_t *alpha_yylex; /* Next Token */
};

typedef struct alpha_token_t alpha_token_t;

alpha_token_t *alpha_token_init();

void alpha_token_insert(alpha_token_t *head, unsigned int numline, unsigned int endline,
                        char *content, enum TOKEN_TYPE token_type, char *type);

void alpha_token_print(alpha_token_t *token);

void alpha_token_print_list(alpha_token_t *head);