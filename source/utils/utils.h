#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

/* -------------------- Terminal Colors -------------------- */
void fprintf_red(FILE *stream, const char *str, ...);
void fprintf_avm_red(const char *str, ...);
void fprintf_green(FILE *stream, const char *str, ...);
void fprintf_yellow(FILE *stream, const char *str, ...);
void fprintf_avm_yellow(const char *str, ...);
void fprintf_blue(FILE *stream, const char *str, ...);
void fprintf_magenta(FILE *stream, const char *str, ...);
void fprintf_cyan(FILE *stream, const char *str, ...);

/* -------------------- Number Stack -------------------- */
typedef struct NumberStackNode
{
    unsigned int val;
    struct NumberStackNode *next;
} NumberStackNode;

typedef struct NumberStack
{
    unsigned int size;
    struct NumberStackNode *top;
} NumberStack;

NumberStack *NumberStack_init();
int NumberStack_isEmpty(NumberStack *ns);
NumberStackNode *NumberStack_push(NumberStack *ns, unsigned int val);
unsigned int NumberStack_top(NumberStack *ns);
unsigned int NumberStack_pop(NumberStack *ns);
void NumberStack_print(NumberStack *ns);

