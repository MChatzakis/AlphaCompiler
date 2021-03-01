#include "comment_stack.h"

int main() {
  comment_stack_t *cs;
  cs = comment_stack_init();
  comment_stack_push(cs, 0);
  comment_stack_push(cs, 10);
  comment_stack_push(cs, 31);
  comment_stack_push(cs, 5);

  comment_stack_pop(cs);
  comment_stack_print(cs);
}