#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ast.h"
#include "../include/function.h"
#include "../include/lexer.h"
#include "../include/misc.h"
#include "../include/parser.h"
#include "../include/token.h"

#define MAX_INPUT_SIZE 1000

// ARGS
bool file_input;
bool print_AST;
bool print_tokens;
bool debug;

// INPUT
FILE *Input_file;
char *file_name;

struct token *current_token;
struct function *current_function;

// LEXER.C
extern char *input;
extern int size;
extern int Line;

int read_input(char *filename) {
  Input_file = fopen(filename, "r");
  if (Input_file == NULL)
    return FAILURE;
  fseek(Input_file, 0L, SEEK_END);
  size = ftell(Input_file);
  rewind(Input_file);
  input = malloc(size * sizeof(char));
  fread(input, sizeof(char), size, Input_file);
  fclose(Input_file);
  return SUCCESS;
}

void parse_arguments(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "-file") == 0) {
      file_input = 1;
      file_name = argv[++i];
    }
    if (strcmp(argv[i], "-ast") == 0) {
      print_AST = 1;
    }
    if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-debug") == 0) {
      print_tokens = 1;
    }
  }
}

void statements() {
  struct ASTNode *tree = NULL;
  while (1) {
    switch (current_token->type) {
    case T_IDENT: {
      // function or var declaration
      char *name = current_token->word;
      scan_token(current_token);
      if (current_token->type == T_LPAR) {
        scan_token(current_token);
        match(T_IDENT, "variable name");
        char *var = current_token->word;
        match(T_RPAR, ")");
        current_function = create_function(name, var, NULL);
        match(T_EQUAL, "=");
        current_function->computation = binary_expression(0);
        add_function(current_function);
        current_function = NULL;
      }
      break;
    }
    case T_PRINT:
      scan_token(current_token);
      tree = binary_expression(0);
      if (print_AST)
        print_ast(tree, 0);
      printf("Result : %f\n", interpret_AST(tree, false, 0));
      break;
    default:
      fatal("Unrecognized token : %s", Line, token_to_string(current_token));
    }

    semi();
    if (current_token->type == T_EOF)
      break;
  }
  if (tree)
    free_ast(tree);
}

int main(int argc, char **argv) {
  create_default_functions();
  if (!(current_token = malloc(sizeof(struct token))))
    return FAILURE;
  current_token->type = -1;
  parse_arguments(argc, argv);
  if (file_input) {
    if (read_input(file_name) != SUCCESS)
      return FAILURE;
  } else {
    printf(">>> ");
    input = malloc(sizeof(char) * (MAX_INPUT_SIZE + 1));
    scanf("%" STR(MAX_INPUT_SIZE) "[^\n]s", input);
    size = strlen(input);
  }

  scan_token(current_token);
  statements();
  free(current_token);
  return EXIT_SUCCESS;
}
