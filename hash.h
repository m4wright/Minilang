#include <stdlib.h>

#ifndef bool
#define bool int
#endif

#ifndef HASH_SIZE
#define HASH_SIZE 317
#endif

#ifndef HASH_H
#define HASH_H

typedef enum var_type {
	intType, floatType, stringType
} var_type;

typedef struct hash_element {
	char *identifier;
	var_type type;
} hash_element;

typedef struct list_elem {
	hash_element *value;
	struct list_elem *next;
} list_elem;

typedef struct list {
	list_elem *head;
	list_elem *tail;
} list;

extern list *HASH_TABLE[HASH_SIZE];

int hash_function(char *identifier);

list *add_to_list(hash_element *element, list *l);
void add_to_hash(hash_element *element);

hash_element *get_hash_element(char *identifier);
bool in_hash_table(char *identifier);
var_type get_variable_type(char *identifier);

#endif