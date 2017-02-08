#include "hash.h"

list *HASH_TABLE[HASH_SIZE];

int hash_function(char *identifier){
	unsigned int result = 0;
	while (*identifier) result = (result << 1) + *identifier++;
	return (result % HASH_SIZE);
}

list *add_to_list(hash_element *element, list *l){
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

void add_to_hash(hash_element *element){
	int key = hash_function(element->identifier);
	HASH_TABLE[key] = add_to_list(element, HASH_TABLE[key]);
}

hash_element *get_hash_element(char *identifier){
	int key = hash_function(identifier);
	list *elems_in_bucket = HASH_TABLE[key];
	if (elems_in_bucket == NULL) return NULL; 			// not in the hash table
	list_elem *elem = elems_in_bucket->head;
	while (elem){
		if (elem->value->identifier == identifier){
			return elem->value;
		}
		elem = elem->next;
	}
	return NULL; 						// not in the hash table
}

bool in_hash_table(char *identifier){
	return get_hash_element(identifier) == NULL;
}


var_type get_variable_type(char *identifier){
	hash_element *value = get_hash_element(identifier);
	if (value != NULL){
		return value->type;
	}
	printf("ERROR: %s has not been declared\n", identifier);
	EXIT(EXIT_FAILURE);
	return NULL;
}
