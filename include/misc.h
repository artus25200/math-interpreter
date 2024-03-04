#ifndef MISC_H
#define MISC_H

#define SUCCESS 0
#define FAILURE 1

#define STR_(X) #X
#define STR(X) STR_(X)

void match(int tokentype, char *name);

void semi();

void rpar();
void lpar();

void fatal(const char *fmt, ...);

#endif
