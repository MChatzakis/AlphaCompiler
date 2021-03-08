#include <stdio.h>
#include <stdarg.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

void fprintf_red(FILE *stream, const char *str, ...);
void fprintf_green(FILE *stream, const char *str, ...);
void fprintf_yellow(FILE *stream, const char *str, ...);
void fprintf_blue(FILE *stream, const char *str, ...);
void fprintf_magenta(FILE *stream, const char *str, ...);
void fprintf_cyan(FILE *stream, const char *str, ...);
