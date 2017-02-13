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

FILE *get_symbol_table_filename(char *filename){
	if (!has_valid_extension(filename)){
		fprintf(stderr, "Invalid filename, expecting 'filename'.min, not %s\n", filename);
		exit(EXIT_FAILURE);
	}
	remove_extension(filename);
	char *symbol_filename = malloc(strlen(filename) + 12); 			// +11 for ".symbol.txt", +1 for null char
	sprintf(symbol_filename, "%s.symbol.txt", filename);
	FILE *symbol_file = fopen(symbol_filename, "w");
	free(symbol_filename);
	if (!symbol_file){
		fprintf(stderr, "Could not open the symbol table text file. Program is terminating\n");
	}
	return symbol_file;
}

FILE *get_pretty_print_file(char *filename){
	char *pretty_filename = malloc(strlen(filename) + 12); 	// +11 for '.pretty.min', +1 for null char
	sprintf(pretty_filename, "%s.pretty.min", filename);
	FILE *pretty_file = fopen(pretty_filename, "w");
	free(pretty_filename);
	if (!pretty_file) {
		fprintf(stderr, "Could not open the pretty print file. Program is terminating\n");
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
		fprintf(stderr, "Could not open the c file. Program is terminating\n");
		exit(EXIT_FAILURE);
	}
	return c_file;
}



void yyparse();
FILE *pretty_file;
FILE *symbol_file;
FILE *c_file;

int main(int argc, char **argv){
	if (argc <= 1){
		fprintf(stderr, "Invalid use: run './minc filename'\n");
		exit(EXIT_FAILURE);
	}
	yyin = fopen(argv[1], "r");
	if (yyin == NULL){
		fprintf(stderr, "ERROR: file %s does not exist!\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	symbol_file = get_symbol_table_filename(argv[1]);
	fprintf(symbol_file, "IDENTIFIER: TYPE\n");
	yyparse();

	pretty_file = get_pretty_print_file(argv[1]); 		
	pretty_print(program);
	fclose(pretty_file);

	type_check(program);
	fclose(symbol_file);

	c_file = get_c_file(argv[1]);
	c_print(program);
	fclose(c_file);

	exit(EXIT_SUCCESS);
	return 0;
}