#include "comment_stack.h"
#include <assert.h>

comment_stack_t *comment_stack_init() {
  comment_stack_t *st;
  st = malloc(sizeof(comment_stack_t));
  st->size = 0;
  st->top = NULL;
}

int comment_stack_is_empty(comment_stack_t *st) {
  assert(st);
  return (st->size == 0);
}

int comment_stack_push(comment_stack_t *st, unsigned int n) {

  comment_node_t *new_node;

  assert(st);

  new_node = malloc(sizeof(comment_node_t));
  if (new_node == NULL) {
    return -1;
  }

  new_node->next = st->top;
  new_node->starting_line = n;

  st->top = new_node;
  st->size++;
  return 0;
}

unsigned int comment_stack_top(comment_stack_t *st) {
  if (comment_stack_is_empty(st)) {
    exit(-1);
  }

  return st->top->starting_line;
}

unsigned int comment_stack_pop(comment_stack_t *st) {

  unsigned int tmp;
  comment_node_t *del;

  assert(st);

  if (comment_stack_is_empty(st)) {
    exit(-1);
  }

  tmp = st->top->starting_line;
  del = st->top;
  st->top = st->top->next;
  st->size--;
  del->next = NULL;
  free(del);

  return tmp;
}

void comment_stack_print(comment_stack_t *st) {
  comment_node_t *curr;

  assert(st);

  if (comment_stack_is_empty(st)) {
    return;
  }

  printf("Comment stack \\/:\n");
  curr = st->top;
  while (curr) {
    printf("Starting line: %u.\n", curr->starting_line);
    curr = curr->next;
  }
}