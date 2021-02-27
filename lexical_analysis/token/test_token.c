#include "Token.h"

int yy_lex(alpha_token_t *head)
{
    long int i;

    for (i = 0; i < 1000000; i++)
    {
        alpha_token_insert(head, i + 1, "Test1", "Test2");
    }

    return 0;
}

int main()
{
    alpha_token_t *head;
    head = alpha_token_init();

    yy_lex(head);

    //alpha_token_print(head);
    return 0;
}

