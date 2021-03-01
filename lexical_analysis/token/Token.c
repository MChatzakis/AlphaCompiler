#include "Token.h"
#include <string.h>

char token_types_str[][12] = {"UNDEFINED", "KEYWORD",    "OPERATOR",
                              "CONST_INT", "CONST_REAL", "STRING",
                              "ID",        "COMMENT",    "PUNCTUATION"};

alpha_token_t *alpha_token_init() {
  alpha_token_t *head;
  head = (alpha_token_t *)malloc(sizeof(alpha_token_t));

  head->numline = 0;
  head->endline = 0;
  head->numToken = 0;
  head->content = NULL;
  head->token_type = UNDEFINED;
  head->type = NULL;

  return head;
}

void alpha_token_insert(alpha_token_t *head, unsigned int numline,
                        unsigned int endline, char *content,
                        enum TOKEN_TYPE token_type, char *type) {
  alpha_token_t *curr, *ptr;
  static unsigned int total_tokens = 0;

  assert(head); // if(head == NULL) exit(-1);

  if (!total_tokens) {
    ptr = head;
  } else {
    ptr = (alpha_token_t *)malloc(sizeof(alpha_token_t));
  }

  total_tokens++;

  ptr->numline = numline;
  ptr->endline = endline;
  ptr->numToken = total_tokens;
  ptr->content = NULL;
  ptr->token_type = token_type;
  ptr->type = NULL;
  ptr->alpha_yylex = NULL;

  if (content != NULL) {
    ptr->content = (char *)malloc(strlen(content) * sizeof(char));
    strcpy(ptr->content, content);
  }

  if (type != NULL) {
    ptr->type = (char *)malloc(strlen(type) * sizeof(char));
    strcpy(ptr->type, type);
  }

  if (total_tokens == 1) {
    return;
  }

  curr = head;
  while ((curr->alpha_yylex) != NULL) {
    curr = curr->alpha_yylex;
  }

  curr->alpha_yylex = ptr;
}

void alpha_token_print(alpha_token_t *token) {
  assert(token);

  if (token->token_type == STRING || token->token_type == IDENT) {
    printf("%u: #%u  \"%s\" %s \"%s\" <-char*\n", token->numline,
           token->numToken, token->content, token_types_str[token->token_type],
           token->content);
  } else if (token->token_type == CONSTINT) {
    printf("%u: #%u  \"%s\" %s %s <-integer\n", token->numline, token->numToken,
           token->content, token_types_str[token->token_type], token->content);
  } else if (token->token_type == CONSTREAL) {
    printf("%u: #%u  \"%s\" %s %s <-real\n", token->numline, token->numToken,
           token->content, token_types_str[token->token_type], token->content);
  } else if (token->token_type == COMMENT) {
    if (strcmp(token->type, "LINE_COMMENT") == 0) {
      printf("%u: #%u  \"%s\" %s %s <-enumerated\n", token->numline,
             token->numToken, token->content,
             token_types_str[token->token_type], token->type);
    } else if (strcmp(token->type, "BLOCK_COMMENT") == 0) {
      printf("%u: #%u  \"%d - %d\" %s %s <-enumerated\n", token->numline,
             token->numToken, token->numline, token->endline,
             token_types_str[token->token_type], token->type);
      // printf("Starting line: %u\n", token->numline);
      // printf("End line: %u\n", token->endline);
    } else if (strcmp(token->type, "NESTED_COMMENT") == 0) {
      printf("%u: #%u  \"%s\" %s %s <-enumerated\n", token->numline,
             token->numToken, token->content,
             token_types_str[token->token_type], token->type);
    }
  } else {
    printf("%u: #%u  \"%s\" %s %s <-enumerated\n", token->numline,
           token->numToken, token->content, token_types_str[token->token_type],
           token->type);
  }
}

void alpha_token_print_list(alpha_token_t *head) {
  alpha_token_t *curr;
  curr = head;

  while (curr != NULL) {
    // printf("Token [%u,%u,%s,%s]\n", curr->numline, curr->numToken,
    // curr->content, curr->type);
    alpha_token_print(curr);
    curr = curr->alpha_yylex;
  }
}

void alpha_token_free_list(alpha_token_t *head) {
  alpha_token_t *curr, *prev;

  assert(head);

  curr = head;
  prev = NULL;

  while (curr != NULL) {
    prev = curr;
    curr = curr->alpha_yylex;

    free(prev->content);
    prev->content = NULL;
    free(prev->type);
    prev->type = NULL;

    free(prev);
    prev = NULL;
  }
}