#include "../include/token.h"
#include "../include/misc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *token_to_string(struct token *token) {
  int size = 0;
  char *string = malloc(sizeof(char) * MAX_TOKEN_STRING_SIZE);
  char *beginning = "[token ";
  strcpy(string, beginning);
  size += strlen(beginning);
  char *type = token_type_to_string(token->type);
  strcat(string, type);
  size += strlen(type);
  int size_available = MAX_TOKEN_STRING_SIZE - size -
                       6; // 1 = \0, 1 = ] 4 = " -> " 1 + 1 + 4 = 6
  char *value = malloc(sizeof(char) * (size_available));
  switch (token->type) {
  case T_INT:
    strcat(string, " -> ");
    snprintf(value, size_available, "%d", token->value);
  case T_IDENT:
    strcat(string, " -> ");
    snprintf(value, size_available, "%s", token->word);
  }
  int value_len = strlen(value);
  if (value_len > size_available - 3) {
    value[value_len - 1] = value[value_len - 2] = value[value_len - 3] = '.';
  }

  size += strlen(value);
  if (token->type == T_INT || token->type == T_IDENT)
    strcat(string, value);
  strcat(string, "]");
  return string;
}

char *token_type_to_string(int token_type) {
  switch (token_type) {
  case T_EOF:
    return "T_EOF";
  case T_UNKNOWN:
    return "Unrecognized";
  case T_INT:
    return "T_INT";
  case T_PLUS:
    return "T_PLUS";
  case T_MINUS:
    return "T_MINUS";
  case T_STAR:
    return "T_STAR";
  case T_SLASH:
    return "T_SLASH";
  case T_POW:
    return "T_POW";
  case T_LPAR:
    return "T_LPAR";
  case T_RPAR:
    return "T_RPAR";
  case T_PRINT:
    return "T_PRINT";
  case T_SEMI:
    return "T_SEMI";
  case T_IDENT:
    return "T_IDENT";
  case T_VAR:
    return "T_VAR";
  case T_EQUAL:
    return "T_EQUAL";
  case T_FUNC:
    return "T_FUNC";
  }

  return "unreachable";
}
