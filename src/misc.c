#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/lexer.h"
#include "../include/misc.h"
#include "../include/token.h"

extern struct token *current_token;
extern char *file_name;
extern int Line;
extern int Linech;

void match(int tokentype, char *name) {
  if (current_token->type == tokentype) {
    scan_token(current_token);
  } else {
    fatal("Expected %s, got %s", name, token_to_string(current_token));
  }
}

void semi() { match(T_SEMI, ";"); }

void lpar() { match(T_LPAR, "("); }
void rpar() { match(T_RPAR, ")"); }

void fatal(const char *fmt, ...) {
  va_list args;
  va_start(args, fmt);
  fprintf(stderr, "[FATAL][%s:l%d:c%d] ", file_name, Line, Linech);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");
  va_end(args);
  exit(FAILURE);
}
