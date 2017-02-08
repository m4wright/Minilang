#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *output_pretty;

void pretty_print(PROGRAM *program){
	pretty_print_declarations(program->declarations);
	pretty_print_statements(program->statements);
}

void pretty_print_declarations(DECLARATIONS *declarations){

}

void pretty_print_declaration(id_type_pair *declaration){
	fprintf(output_pretty, "var %d: %s;\n", declaration->identifier, type_to_string(declaration->typ));
}
