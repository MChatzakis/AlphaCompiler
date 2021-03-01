#include "Colors.h"
#include <stdio.h>

void fprintf_red(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_RED);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}

void fprintf_green(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_GREEN);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}

void fprintf_yellow(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_YELLOW);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}

void fprintf_blue(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_BLUE);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}

void fprintf_magenta(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_MAGENTA);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}

void fprintf_cyan(FILE *stream, const char *str) {
  fprintf(stream, ANSI_COLOR_CYAN);
  fprintf(stream, "%s",str);
  fprintf(stream, ANSI_COLOR_RESET);
}