#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code_generation.h"
#include "tree.h"
#include "type_checker.h"

extern FILE *yyin;

bool has_valid_extension(char *filename){
	int string_length = strlen(filename);
	if (string_length < 5){
		return false;
	}
	char *extension = ".min";
	return (strcmp(extension, filename+string_length-4) == 0); 	// ie last 4 chars of filename are .min
}

void remove_extension(char *filename){
	/*
		this assumes that the file name is valid
		this modifies the actual filename, but thats what is wanted since only
		the filename part is important, not the extension at this point
	*/
	filename[strlen(filename)-4] = '\0';
}

FILE *get_pretty_print_file(char *filename){
	if (!has_valid_extension(filename)){
		printf("Invalid filename, expecting 'filename'.min, not %s\n", filename);
		exit(EXIT_FAILURE);
	}
	remove_extension(filename);
	int filename_length = strlen(filename);
	char *pretty_filename = malloc(filename_length + 12); 	// +11 for '.pretty.min' +1 for null char
	sprintf(pretty_filename, "%s.pretty.min", filename);
	FILE *pretty_file = fopen(pretty_filename, "w");
	free(pretty_filename);
	if (!pretty_file) {
		printf("Could not open the file. Program is terminating\n");
		exit(EXIT_FAILURE);
	}
	return pretty_file;
}

FILE *get_c_file(char *filename){
	// this assumes that the filename is valid but with no extension
	// (removed before during get_pretty_print_file
	char *c_filename = malloc(strlen(filename)+3); 		// +2 for ".c", +1 for null char
	sprintf(c_filename, "%s.c", filename);
	FILE *c_file = fopen(c_filename, "w");
	free(c_filename);
	if (!c_file){
		printf("Could not open the file. Program is terminating\n");
		exit(EXIT_FAILURE);
	}
	return c_file;
}

void yyparse();
FILE *pretty_file;
FILE *c_file;

int main(int argc, char **argv){
	if (argc <= 1){
		printf("Invalid use: run './minc filename'\n");
		exit(EXIT_FAILURE);
	}
	yyin = fopen(argv[1], "r");
	if (yyin == NULL){
		printf("File %s does not exist!\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	pretty_file = get_pretty_print_file(argv[1]); 		
	c_file = get_c_file(argv[1]);
	
	yyparse();
	type_check(program);
	
	pretty_print(program);
	fclose(pretty_file);

	c_print(program);
	fclose(c_file);

	exit(EXIT_SUCCESS);
	return 0;
}