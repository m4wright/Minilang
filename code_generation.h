#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#ifndef CODE_GEN_H
#define CODE_GEN_H

extern FILE *pretty_file;
extern FILE *c_file;

void print_num_tabs(FILE *file, int num_tabs);
void pretty_print(PROGRAM program);
void c_print(PROGRAM program);
char *type_to_string(var_type type); 

#endif