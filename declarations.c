#include "tree.h"
#include "hash.h"
#include <stdio.h>
#include <string.h>

hash_element *makeDECLARATION(char *identifier, var_type type){
	hash_element *element = malloc(sizeof(hash_element));
	element->identifier = identifier;
	element->type = type;
	return element;
}

DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, hash_element *elem){
	if (decls == NULL){
		decls = malloc(sizeof(DECLARATIONS));
		decls->next = NULL;
	}else{
		decls->prev = malloc(sizeof(DECLARATIONS));
		decls->prev->next = decls;
		decls = decls->prev;
	}
	decls->decl = elem;
	decls->prev = NULL;
	if (in_hash_table(elem->identifier)){
		printf("ERROR: %s already declared\n", elem->identifier);
		exit(EXIT_FAILURE);
	}else{
		add_to_hash(elem);
	}
	return decls;
}