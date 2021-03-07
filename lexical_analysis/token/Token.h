/**
 * @file Token.h
 * @author Manos Chatzakis and Nikos Fanourakis
 * @brief Library implementing the token abstraction for the lexical analysis
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

/**
 * @brief Token abstraction
 * 
 */
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

/**
 * @brief Initializes the list with an empty node.
 * 
 * @return alpha_token_t* pointer to the new node
 */
alpha_token_t *alpha_token_init();

/**
 * @brief Inserts a new node at the end of the token list.
 * 
 * @param head Head of token list
 * @param numline The starting line
 * @param endline The ending line
 * @param content The data of the token
 * @param token_type The category of the token
 * @param type  The string representation of the token type
 */
void alpha_token_insert(alpha_token_t *head, unsigned int numline,
                        unsigned int endline, char *content,
                        enum TOKEN_TYPE token_type, char *type);

/**
 * @brief Prints a token
 * 
 * @param token The token
 * @param ost The output stream
 */
void alpha_token_print(alpha_token_t *token, FILE *ost);

/**
 * @brief Prints the token list
 * 
 * @param head The list head
 * @param ost The output stream
 */
void alpha_token_print_list(alpha_token_t *head, FILE *ost);

/**
 * @brief Frees the dynamically allocated memory used for token list
 * 
 * @param head The head of the token list
 */
void alpha_token_free_list(alpha_token_t *head);