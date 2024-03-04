#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ast.h"
#include "../include/function.h"
#include "../include/misc.h"

struct function *functions[MAX_FUNCTION_COUNT];
int function_count;

struct function *create_function(char *name, char *var,
                                 struct ASTNode *computation) {
  struct function *function = malloc(sizeof(struct function));
  function->name = malloc(sizeof(char) * (strlen(name) + 1));
  strcpy(function->name, name);
  function->var = malloc(sizeof(char) * (strlen(var) + 1));
  strcpy(function->var, var);
  function->computation = computation;
  return function;
}

int add_function(struct function *function) {
  if (function_count > MAX_FUNCTION_COUNT - 1) {
    fatal(
        "Unable to add function %s(%s), too many functions have been added.\n",
        function->name, function->var);
    return FAILURE;
  }
  if (get_function(gfibn(function->name)) != NULL) {
    fatal("Unable to add function %s(%s), it already exists.\n", function->name,
          function->var);
    return FAILURE;
  }
  functions[function_count] = function;
  function_count++;
  return SUCCESS;
}

int gfibn(char *name) {
  struct function *function;
  for (int i = 0; i < MAX_FUNCTION_COUNT; i++) {
    function = functions[i];
    if (!function)
      return FUNC_DOES_NOT_EXIST;
    if (strcmp(function->name, name) == 0) {
      return i;
    }
  }
  return FUNC_DOES_NOT_EXIST;
}

struct function *get_function(int index) {
  if (index > function_count - 1) {
    return NULL;
  }
  return functions[index];
}

double evaluate_function(struct function *function, double input) {
  return interpret_AST(function->computation, true, input);
}

void delete_functions() {
  int i = 0;
  while (functions[i]) {
    free(functions[i]->name);
    free(functions[i]->var);
    free_ast(functions[i]->computation);
    free(functions[i]);
  }
}
