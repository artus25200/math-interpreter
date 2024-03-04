#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"

char next();

char skip();

void previous();

double parse_number(char c);

char *parse_identifier(char c);

static int keyword(char *identifier);

int scan_token(struct token *token);

#endif // LEXER_H_
