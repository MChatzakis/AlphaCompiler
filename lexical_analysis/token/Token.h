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
/* /**/ */
struct alpha_token_t
{
    unsigned int numline;              /* Arithmos Grammis */
    unsigned int numToken;             /* Arithmos Token */
    char *content;                     /* Periexomena Token*/
    char *type;                        /* Eidos Token */
    struct alpha_token_t *alpha_yylex; /* Next Token */
};

typedef struct alpha_token_t alpha_token_t;

alpha_token_t *alpha_token_init()
{
    alpha_token_t *head;
    head = (alpha_token_t *)malloc(sizeof(alpha_token_t));

    head->numline = 0;
    head->numToken = 0;
    head->content = NULL;
    head->type = NULL;

    return head;
}

void alpha_token_insert(alpha_token_t *head, unsigned int numline, char *content, char *type)
{
    alpha_token_t *curr, *ptr;
    static unsigned int total_tokens = 0;

    assert(head); //if(head == NULL) exit(-1);

    if (!total_tokens)
    {
        ptr = head;
    }
    else
    {
        ptr = (alpha_token_t *)malloc(sizeof(alpha_token_t));
    }

    total_tokens++;

    ptr->numline = numline;
    ptr->numToken = total_tokens;
    ptr->content = NULL;
    ptr->type = NULL;
    ptr->alpha_yylex = NULL;

    if (content != NULL)
    {
        ptr->content = (char *)malloc(strlen(content) * sizeof(char));
        strcpy(ptr->content, content);
    }

    if (type != NULL)
    {
        ptr->type = (char *)malloc(strlen(type) * sizeof(char));
        strcpy(ptr->type, type);
    }

    if (total_tokens == 1)
    {
        return;
    }

    curr = head;
    while ((curr->alpha_yylex) != NULL)
    {
        curr = curr->alpha_yylex;
    }

    curr->alpha_yylex = ptr;
}

/*void alpha_token_insert_old(alpha_token_t *head, unsigned int numline, char *content, char *type)
{
    alpha_token_t *new_token, *curr, *ptr;
    static unsigned int total_tokens = 0;

    assert(head); //if(head == NULL) exit(-1);

    if (!total_tokens)
    {
        total_tokens++;

        head->numline = numline;
        head->numToken = total_tokens;
        head->content = NULL;
        head->type = NULL;
        head->alpha_yylex = NULL;

        if (content != NULL)
        {
            head->content = (char *)malloc(strlen(content) * sizeof(char));
            strcpy(head->content, content);
        }

        if (type != NULL)
        {
            head->type = (char *)malloc(strlen(type) * sizeof(char));
            strcpy(head->type, type);
        }

        return;
    }

    total_tokens++;

    new_token = (alpha_token_t *)malloc(sizeof(alpha_token_t));

    new_token->numline = numline;
    new_token->numToken = total_tokens;
    new_token->content = NULL;
    new_token->type = NULL;
    new_token->alpha_yylex = NULL;

    if (content != NULL)
    {
        new_token->content = (char *)malloc(strlen(content) * sizeof(char));
        strcpy(new_token->content, content);
    }

    if (type != NULL)
    {
        new_token->type = (char *)malloc(strlen(type) * sizeof(char));
        strcpy(new_token->type, type);
    }

    curr = head;
    while ((curr->alpha_yylex) != NULL)
    {
        curr = curr->alpha_yylex;
    }

    curr->alpha_yylex = new_token;

    return;
}*/

void alpha_token_print(alpha_token_t *token)
{
    assert(token);
    char *dummy = "CATEGORY blabla <-type";
    printf("%u: #%u %s  %s\n",token->numline, token->numToken, token->content, dummy);

}

void alpha_token_print_list(alpha_token_t *head)
{
    alpha_token_t *curr;
    curr = head;

    while (curr != NULL)
    {
        //printf("Token [%u,%u,%s,%s]\n", curr->numline, curr->numToken, curr->content, curr->type);
        alpha_token_print(curr);
        curr = curr->alpha_yylex;
    }
}
