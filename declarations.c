#include <stdio.h>
#include "type_checker.h"
#include "tree.h"


id_type_pair *makeDECLARATION(char *identifier, var_type type, int line_number){
	id_type_pair *decl = malloc(sizeof(id_type_pair));
	decl->identifier = identifier;
	decl->type = type;
	decl->line_number = line_number;
	if (duplicate == NULL && declared(identifier)){ 		// ignore if there is already a duplicate, 
		duplicate = decl; 							// we only want to store the first
	}
	add_to_hash(decl); 	
	fprintf(symbol_file, "%s: %s\n", identifier, type_to_string(type));		
	return decl;
}

DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, id_type_pair *pair){
	DECLARATIONS *to_add = malloc(sizeof(DECLARATIONS));
	to_add->decl = pair;
	to_add->next = decls;
	return to_add;
}