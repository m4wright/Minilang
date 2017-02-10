#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_mult(char *string, int multiplier){
	int string_length = strlen(string);
	char *result = malloc(string_length*multiplier + 1);
	int i;
	for (i = 0; i < multiplier; i++){
		sprintf((result + i*string_length), "%s", string);
	}
	return result;
}

char *string_add(char *string1, char *string2){
	char *result = malloc(sizeof(string1) + sizeof(string2) + 1);
	sprintf(result, "%s%s", string1, string2);
	return result;
}
