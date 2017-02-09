#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef CODE_GEN_H
#define CODE_GEN_H

extern FILE *pretty_file;
void pretty_print(PROGRAM program);
char *type_to_string(var_type type); 

#endif