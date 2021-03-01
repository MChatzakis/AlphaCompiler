#include <stdio.h>
#include <stdlib.h>

struct comment_node_t {
  unsigned int starting_line;
  struct comment_node_t *next;
};

struct comment_stack_t {
  unsigned int size;
  struct comment_node_t *top;
};

typedef struct comment_node_t comment_node_t;
typedef struct comment_stack_t comment_stack_t;

comment_stack_t *comment_stack_init();
int comment_stack_is_empty(comment_stack_t *st);
int comment_stack_push(comment_stack_t *st, unsigned int n);
unsigned int comment_stack_top(comment_stack_t *st);
unsigned int comment_stack_pop(comment_stack_t *st);
void comment_stack_print(comment_stack_t *st);
