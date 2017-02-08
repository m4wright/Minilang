#include "tree.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>

id_type_pair *makeDECLARATION(char *identifier, var_type type){
	id_type_pair *decl = malloc(sizeof(id_type_pair));
	decl->identifier = identifier;
	decl->type = type;
	return decl;
}

DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, id_type_pair *pair){
	if (decls == NULL){
		decls = malloc(sizeof(DECLARATIONS));
		decls->next = NULL;
	}else{
		decls->prev = malloc(sizeof(DECLARATIONS));
		decls->prev->next = decls;
		decls = decls->prev;
	}
	decls->decl = pair;
	decls->prev = NULL;
	if (declared(pair->identifier)){
		printf("ERROR: %s already declared\n", elem->identifier);
		exit(EXIT_FAILURE);
	}else{
		add_to_hash(pair);
	}
	return decls;
}