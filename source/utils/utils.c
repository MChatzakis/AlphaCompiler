#include "utils.h"

void fprintf_red(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_RED, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_avm_red(const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stderr, ANSI_COLOR_RED, args);
  vfprintf(stderr, str, args);
  vfprintf(stderr, ANSI_COLOR_RESET, args);
  va_end(args);

  exit(EXIT_FAILURE);
}

void fprintf_avm_yellow( const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stderr, ANSI_COLOR_YELLOW, args);
  vfprintf(stderr, str, args);
  vfprintf(stderr, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_green(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_GREEN, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_yellow(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_YELLOW, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_blue(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_BLUE, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_magenta(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_MAGENTA, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_cyan(FILE *stream, const char *str, ...)
{
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_CYAN, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

NumberStack *NumberStack_init()
{
  NumberStack *ns;
  ns = (NumberStack *)malloc(sizeof(NumberStack));
  if (!ns)
  {
    perror("Could not allocate memory for number stack");
    exit(-1);
  }

  ns->size = 0;
  ns->top = NULL;

  return ns;
}

int NumberStack_isEmpty(NumberStack *ns)
{
  assert(ns);
  return (ns->size == 0);
}

NumberStackNode *NumberStack_push(NumberStack *ns, unsigned int val)
{
  NumberStackNode *node;

  assert(ns);

  node = (NumberStackNode *)malloc(sizeof(NumberStackNode));
  if (!node)
  {
    perror("Could not allocate memory for number node");
    exit(-1);
  }

  node->val = val;
  node->next = ns->top;

  ns->top = node;
  ns->size++;

  return node;
}

unsigned int NumberStack_top(NumberStack *ns)
{
  assert(ns && ns->top);

  return ns->top->val;
}

unsigned int NumberStack_pop(NumberStack *ns)
{
  unsigned int tmp = 0;
  NumberStackNode *del;

  assert(ns && ns->top);

  tmp = ns->top->val;
  del = ns->top;

  ns->top = ns->top->next;
  ns->size--;

  del->next = NULL;
  free(del);

  return tmp;
}

void NumberStack_print(NumberStack *ns)
{
  NumberStackNode *curr;

  assert(ns);

  curr = ns->top;
  printf("Stack \\/:\n");
  while (curr)
  {
    printf("v: %u\n", curr->val);
    curr = curr->next;
  }
}