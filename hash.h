#include <stdlib.h>

#ifndef bool
#define bool int
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#ifndef HASH_SIZE
#define HASH_SIZE 317
#endif

#ifndef HASH_H
#define HASH_H

typedef enum var_type {
	int_type, float_type, string_type, error_type
} var_type;

typedef struct id_type_pair {
	char *identifier;
	var_type type;
	int line_number;
} id_type_pair;

typedef struct list_elem {
	id_type_pair *value;
	struct list_elem *next;
} list_elem;

typedef struct list {
	list_elem *head;
	list_elem *tail;
} list;

extern list *HASH_TABLE[HASH_SIZE];

int hash_function(char *identifier);

list *add_to_list(id_type_pair *element, list *l);
void add_to_hash(id_type_pair *pair);


var_type get_type(char *identifier);
bool declared(char *identifier);

#endif