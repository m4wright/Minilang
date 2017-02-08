#include "tree.h"
#include <string.h>
#include <stdio.h>


id_type_pair *makeDECLARATION(char *identifier, var_type type){
	id_type_pair *decl = malloc(sizeof(id_type_pair));
	decl->identifier = identifier;
	//decl->identifier = malloc(strlen(identifier)+1);
	//sprintf(decl->identifier, "%s", identifier);
	decl->type = type;
	if (declared(identifier)){
		printf("ERROR: %s already declared\n", identifier);
	}else{
		add_to_hash(decl);
	}
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
	/*if (declared(pair->identifier)){
		printf("ERROR: %s already declared\n", pair->identifier);
		//exit(EXIT_FAILURE);
	}else{
		add_to_hash(pair);
	}*/
	return decls;
}