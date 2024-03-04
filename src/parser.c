#include <stdlib.h>

#include "../include/ast.h"
#include "../include/function.h"
#include "../include/lexer.h"
#include "../include/misc.h"
#include "../include/token.h"

#include "../include/parser.h"

extern struct token *current_token;

struct ASTNode *primary() {
  struct ASTNode *node;
  int f_index;
  switch (current_token->type) {
  case T_INT:
    node = make_ast_leaf(A_INT, current_token->value);
    scan_token(current_token);
    return node;
  case T_LPAR:
    scan_token(current_token);
    node = binary_expression(0);
    rpar();
    return node;
  case T_VAR:
    node = make_ast_leaf(A_VAR, 0);
    scan_token(current_token);
    return node;
  case T_IDENT:
    f_index = gfibn(current_token->word);
    if (f_index == FUNC_DOES_NOT_EXIST) {
      fatal("Function %s does not exists. Declare it using %s(x) = ...;",
            current_token->word, current_token->word);
    }
    scan_token(current_token);
    lpar();
    node = make_ast_unary(A_FUNC, binary_expression(0), f_index);
    rpar();
    return node;
  default:
    fatal("Syntax error on token %s", token_to_string(current_token));
  }
  exit(1); // UNREACHABLE
}

struct ASTNode *binary_expression(int pp) { // previous priority
  struct ASTNode *left, *right;
  left = primary();
  if (current_token->type == T_EOF || current_token->type == T_RPAR ||
      current_token->type == T_SEMI)
    return left;

  int token_type = current_token->type;
  while (op_priority(token_type) > pp) {
    scan_token(current_token);
    right = binary_expression(op_priority(token_type));
    left = make_ast_node(token_type, left, right, 0);

    token_type = current_token->type;
    if (token_type == T_EOF || current_token->type == T_RPAR ||
        token_type == T_SEMI) {
      return left;
    }
  }
  return left;
}
