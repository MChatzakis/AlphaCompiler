/**
 * @file comment_stack.h
 * @author Manos Chatzakis (4238) Nikos Fanourakis (4237)
 * @brief A stack library used for nested comment detection
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief A node representing a stack element
 * 
 */
struct comment_node_t
{
  unsigned int starting_line;
  struct comment_node_t *next;
};

/**
 * @brief A node representing the whole stack
 * 
 */
struct comment_stack_t
{
  unsigned int size;
  struct comment_node_t *top;
};

typedef struct comment_node_t comment_node_t;
typedef struct comment_stack_t comment_stack_t;

/**
 * @brief Initializes the stack
 * 
 * @return comment_stack_t* A pointer to the memory allocated for the stack node
 */
comment_stack_t *comment_stack_init();

/**
 * @brief Checks if the stack is empty
 * 
 * @param st The stack node
 * @return int True when there are no nodes inside the stack
 */
int comment_stack_is_empty(comment_stack_t *st);

/**
 * @brief Adds an element to the top of the stack
 * 
 * @param st The stack pointer
 * @param n The value of the new element
 * @return int 0 for success, -1 for failure
 */
int comment_stack_push(comment_stack_t *st, unsigned int n);

/**
 * @brief Returns the value of the top stack element
 * 
 * @param st The stack pointer
 * @return unsigned int The value of the top element
 */
unsigned int comment_stack_top(comment_stack_t *st);

/**
 * @brief Returns the value of the top stack element, removes it and frees the allocated memory
 * 
 * @param st The stack pointer
 * @return unsigned int The value of the top element removed
 */
unsigned int comment_stack_pop(comment_stack_t *st);

/**
 * @brief Prints the elements of stack
 * 
 * @param st The stack pointer
 */
void comment_stack_print(comment_stack_t *st);

/**
 * @brief Frees stack
 * 
 * @param st The stack pointer
 */
void comment_stack_free(comment_stack_t *st);
