#ifndef PARSER_H_
#define PARSER_H_

#include "ast.h"

struct ASTNode *primary();
struct ASTNode *binary_expression(int pp);

#endif // PARSER_H_
