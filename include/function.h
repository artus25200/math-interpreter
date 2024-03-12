#ifndef FUNCTION_H_
#define FUNCTION_H_

#define MAX_FUNCTION_COUNT 100
#define FUNC_DOES_NOT_EXIST -1

struct function {
  char *name;
  char *var;
  struct ASTNode *computation;
};

struct function *create_function(char *name, char *var,
                                 struct ASTNode *computation);
int add_function(struct function *function);
// GET FUNCTION INDEX BY NAME
int gfibn(char *name);
struct function *get_function(int index);
double evaluate_function(struct function *function, double input);
void create_default_functions();
#endif // FUNCTION_H_
