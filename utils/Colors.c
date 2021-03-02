#include "Colors.h"

void fprintf_red(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_RED, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_green(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_GREEN, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_yellow(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_YELLOW, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_blue(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_BLUE, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_magenta(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_MAGENTA, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

void fprintf_cyan(FILE *stream, const char *str, ...) {
  va_list args;
  va_start(args, str);
  vfprintf(stream, ANSI_COLOR_CYAN, args);
  vfprintf(stream, str, args);
  vfprintf(stream, ANSI_COLOR_RESET, args);
  va_end(args);
}

/*
int main() {
  printf("normal\n");
  fprintf_red(stdout, "red\n");
  printf("normal");
}*/