#ifndef AST_H
#define AST_H

#include <stdbool.h>

struct ASTNode {
  int op;
  struct ASTNode *left;
  struct ASTNode *right;
  double value; // for int literals
};

enum {
  A_INT = 1,
  A_ADD,
  A_SUB,
  A_MUL,
  A_DIV,
  A_POW,
  A_IDENT,
  A_VAR,
  A_FUNC,
  A_EOF
};

int op_priority(int tokentype);

struct ASTNode *make_ast_leaf(int op, double value);
struct ASTNode *make_ast_unary(int op, struct ASTNode *child, double value);
struct ASTNode *make_ast_node(int op, struct ASTNode *left,
                              struct ASTNode *right, double value);
double interpret_AST(struct ASTNode *tree, bool is_func, double func_value);

void free_ast(struct ASTNode *tree);
void print_ast(struct ASTNode *tree, int level);
#endif
