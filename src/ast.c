#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/ast.h"
#include "../include/function.h"
#include "../include/misc.h"
#include "../include/parser.h"
#include "../include/token.h"

extern stqruct function *functions[MAX_FUNCTION_COUNT];
extern struct token *current_token;

int operation_priority[] = {0, 0, 10, 10, 20, 20, 0};

int op_priority(int tokentype) {
  int priority = operation_priority[tokentype];
  if (priority == 0) {
    fatal("Syntax error on token : %s", token_to_string(current_token));
  }
  return priority;
}

struct ASTNode *make_ast_node(int op, struct ASTNode *left,
                              struct ASTNode *right, int value) {
  struct ASTNode *node = malloc(sizeof(struct ASTNode));
  if (!node) {
    fatal("Unable to allocate memory for ASTNode");
  }
  node->op = op;
  node->left = left;
  node->right = right;
  node->value = value;
  return node;
}

struct ASTNode *make_ast_leaf(int op, int value) {
  return make_ast_node(op, NULL, NULL, value);
}

struct ASTNode *make_ast_unary(int op, struct ASTNode *child, int value) {
  return make_ast_node(op, child, NULL, value);
}

double interpret_AST(struct ASTNode *tree, bool is_func, double func_value) {
  switch (tree->op) {
  case A_ADD:
    return interpret_AST(tree->left, is_func, func_value) +
           interpret_AST(tree->right, is_func, func_value);
  case A_SUB:
    return interpret_AST(tree->left, is_func, func_value) -
           interpret_AST(tree->right, is_func, func_value);
  case A_MUL:
    return interpret_AST(tree->left, is_func, func_value) *
           interpret_AST(tree->right, is_func, func_value);
  case A_DIV:
    return interpret_AST(tree->left, is_func, func_value) /
           interpret_AST(tree->right, is_func, func_value);
  case A_INT:
    return tree->value;
  case A_VAR:
    if (is_func)
      return func_value;
    exit(1);
  case A_FUNC:
    return evaluate_function(get_function(tree->value),
                             interpret_AST(tree->left, false, 0));
  }
  fatal("Unreachable");
  exit(FAILURE);
}

void free_ast(struct ASTNode *tree) {
  if (tree->left)
    free_ast(tree->left);
  if (tree->right)
    free_ast(tree->right);
  free(tree);
}

int levels[1000] = {0};
void print_ast(struct ASTNode *tree, int level) {
  int i;
  if (tree == NULL)
    return;

  for (i = 0; i < level; i++)
    if (i == level - 1)
      printf("%s───", levels[level - 1] ? "├" : "└");
    else
      printf("%s   ", levels[i] ? "│" : "  ");
  printf("%s ", token_type_to_string(tree->op));
  if (tree->op == A_INT)
    printf("%d", tree->value);
  printf("\n");
  levels[level] = 1;
  print_ast(tree->left, level + 1);
  levels[level] = 0;
  print_ast(tree->right, level + 1);
}
