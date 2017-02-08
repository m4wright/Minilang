#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
	adds_to_hash("x", int_type);
	printf("%d\n", declared("x"));
	var_type t = get_type("x");
	switch (t){
		case int_type:
			printf("int type\n");
			break;
		case float_type:
			printf("float type\n");
			break;
		case string_type:
			printf("string type\n");
			break;
		case error_type:
			printf("error_type\n");
			break;
	}
}
