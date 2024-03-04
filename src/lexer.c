#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/function.h"
#include "../include/lexer.h"
#include "../include/misc.h"
#include "../include/token.h"

#define MAX_IDENT_SIZE 50

char *input;
int size;
int ch = 0;
int Line = 1;
int Linech = -1;

extern bool print_tokens;

extern struct function *current_function;

char next() {
  if (size == 0) {
    fatal("No input entered");
  }
  if (ch > size)
    exit(FAILURE);
  char c = input[ch];
  ch++;
  Linech++;
  return c;
}

void previous() {
  if (ch == 0)
    exit(FAILURE);
  ch--;
  Linech--;
  if (input[ch] == '\n') {
    Line--;
  }
}

char skip() {
  char c = next();
  while (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r') {
    if (c == '\n') {
      Line++;
      Linech = 1;
    }
    c = next();
  }
  return c;
}

double parse_number(char c) {
  double value = 0;
  bool point_reached = false;
  int decimal_count = 1;
  while (isdigit(c) || '.' == c) {
    if (c == '.') {
      if (point_reached)
        exit(1);
      point_reached = true;
    }
    if (!point_reached) {
      value = value * 10 + (c - '0');
    } else {
      // FIXME
      value = value + ((double)(c - '0')) / (double)(pow(10, decimal_count));
      decimal_count++;
    }
    c = next();
  }
  previous();
  return value;
}

char *parse_identifier(char c) {
  char *ident = malloc(sizeof(char) * MAX_IDENT_SIZE);
  int i = 0;
  while (isalnum(c) || c == '_') {
    if (i >= MAX_IDENT_SIZE - 1) {
      fprintf(stderr, "ERROR: Max identifier size reached\n");
      exit(1);
    }
    ident[i] = c;
    c = next();
    ++i;
  }
  previous();
  ident[i] = '\0';
  return ident;
}

int keyword(char *identifier) {
  switch (*identifier) {
  case 'p':
    if (strcmp(identifier, "print") == 0) {
      return T_PRINT;
    }
    break;
  default:
    if (!current_function || !current_function->var)
      break;
    if (strcmp(current_function->var, identifier) == 0) {
      return T_VAR;
    }
  }

  return T_IDENT;
}

int scan_token(struct token *token) {
  char c = skip();

  switch (c) {
  case '\0':
    token->type = T_EOF;
    break;
  case '+':
    token->type = T_PLUS;
    break;
  case '-':
    token->type = T_MINUS;
    break;
  case '*':
    if (next() == '*') {
      token->type = T_POW;
    } else {
      previous();
      token->type = T_STAR;
    }
    break;
  case '/':
    token->type = T_SLASH;
    break;
  case '(':
    token->type = T_LPAR;
    break;
  case ')':
    token->type = T_RPAR;
    break;
  case ';':
    token->type = T_SEMI;
    break;
  case '=':
    token->type = T_EQUAL;
    break;
  default:
    if (isdigit(c)) {
      double number = parse_number(c);
      token->type = T_INT;
      token->value = number;
      break;
    } else if (isalpha(c) || c == '_') {
      char *identifier = parse_identifier(c);
      token->type = keyword(identifier);
      token->word = identifier;
      if (token->type != 0)
        break;
    }
    token->type = T_UNKNOWN;
    token->value = 0;
    token->c = c;
    break;
  }
  if (print_tokens)
    printf("%s\n", token_to_string(token));
  return 1;
}
