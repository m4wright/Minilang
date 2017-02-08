#include "tree.h"
#include <string.h>
#include <stdio.h>


id_type_pair *makeDECLARATION(char *identifier, var_type type){
	id_type_pair *decl = malloc(sizeof(id_type_pair));
	decl->identifier = identifier;
	decl->type = type;
	if (declared(identifier)){
		printf("ERROR: %s already declared\n", identifier);
	}else{
		add_to_hash(decl);
	}
	return decl;
}

DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, id_type_pair *pair){
	DECLARATIONS *to_add = malloc(sizeof(DECLARATIONS));
	to_add->decl = pair;
	to_add->next = decls;
	return to_add;
}