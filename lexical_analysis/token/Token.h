#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

enum OPERATOR
{
    PLUS,
    PLUS_PLUS,
    MINUS,
    MINUS_MINUS
};

struct alpha_token_t
{
    unsigned int numline;              /* Arithmos Grammis */
    unsigned int numToken;             /* Arithmos Token */
    char *content;                     /* Periexomena Token*/
    char *type;                        /* Eidos Token */
    struct alpha_token_t *alpha_yylex; /* Next Token */
};

typedef struct alpha_token_t alpha_token_t;

alpha_token_t *alpha_token_init();

void alpha_token_insert(alpha_token_t *head, unsigned int numline, char *content, char *type);

void alpha_token_print(alpha_token_t *token);

void alpha_token_print_list(alpha_token_t *head);