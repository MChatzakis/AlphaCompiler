/**
 * @file number_stack.c
 * @author Manos Chatzakis (4238) Nikos Fanourakis (4237)
 * @brief Implementation of number_stack.h
 * @date 2021-03-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "number_stack.h"
#include <assert.h>

number_stack_t *number_stack_init()
{
  number_stack_t *st;
  st = malloc(sizeof(number_stack_t));
  st->size = 0;
  st->top = NULL;
  return st;
}

int number_stack_is_empty(number_stack_t *st)
{
  assert(st);
  return (st->size == 0);
}

int number_stack_push(number_stack_t *st, unsigned int n)
{

  number_node_t *new_node;

  assert(st);

  new_node = malloc(sizeof(number_node_t));
  if (new_node == NULL)
  {
    return -1;
  }

  new_node->next = st->top;
  new_node->scope = n;

  st->top = new_node;
  st->size++;
  return 0;
}

unsigned int number_stack_top(number_stack_t *st)
{
  if (number_stack_is_empty(st))
  {
    exit(-1);
  }

  return st->top->scope;
}

unsigned int number_stack_pop(number_stack_t *st)
{

  unsigned int tmp;
  number_node_t *del;

  assert(st);

  if (number_stack_is_empty(st))
  {
    exit(-1);
  }

  tmp = st->top->scope;
  del = st->top;

  st->top = st->top->next;
  st->size--;

  del->next = NULL;
  free(del);

  return tmp;
}

void number_stack_print(number_stack_t *st)
{
  number_node_t *curr;

  assert(st);

  if (number_stack_is_empty(st))
  {
    return;
  }

  printf("Number stack \\/:\n");
  curr = st->top;
  while (curr)
  {
    printf("Starting line: %u.\n", curr->scope);
    curr = curr->next;
  }
}

void number_stack_free(number_stack_t *st)
{
  assert(st);
  assert(st->size == 0);
  st->top = NULL;
  free(st);
}