#ifndef TOKEN_H_
#define TOKEN_H_

#define MAX_TOKEN_STRING_SIZE 100

enum {
  T_UNKNOWN = 0,
  T_INT,
  T_PLUS,
  T_MINUS,
  T_STAR,
  T_SLASH,
  T_POW,
  T_IDENT,
  T_VAR,
  T_FUNC,
  T_EOF,
  T_LPAR,
  T_RPAR,
  T_SEMI,
  T_PRINT,
  T_EQUAL
};

struct token {
  int type;
  int value;
  char c;
  char *word;
};

char *token_type_to_string(int token_type);
char *token_to_string(struct token *token);

#endif // TOKEN_H_
