#include "hash.h"
#include <string.h>

list *HASH_TABLE[HASH_SIZE];

int hash_function(char *identifier){
	unsigned int result = 0;
	while (*identifier) result = (result << 1) + *identifier++;
	return (result % HASH_SIZE);
}

list *add_to_list(id_type_pair *element, list *l){
	list_elem *to_add = malloc(sizeof(list_elem));
	to_add->value = element;
	to_add->next = NULL;
	if (l == NULL) {
		l = malloc(sizeof(list));
		l->head = to_add;
		l->tail = l->head;
	}else{
		l->tail->next = to_add;
		l->tail = to_add;
	}
	return l;
}

void add_to_hash(id_type_pair *pair){
	int key = hash_function(pair->identifier);
	HASH_TABLE[key] = add_to_list(pair, HASH_TABLE[key]);
}


var_type get_type(char *identifier){
	int key = hash_function(identifier);
	list *elems_in_bucket = HASH_TABLE[key];
	if (elems_in_bucket == NULL) return error_type; 			// not in the hash table
	list_elem *elem = elems_in_bucket->head;
	while (elem){
		if (strcmp(elem->value->identifier, identifier) == 0){
			return elem->value->type;
		}
		elem = elem->next;
	}
	return error_type; 	
}

bool declared(char *identifier){
	return get_type(identifier) != error_type;
}


