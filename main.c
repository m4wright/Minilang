#include "code_generation.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

bool has_valid_extension(char *filename){
	int string_length = strlen(filename);
	if (string_length < 5){
		return false;
	}
	char *extension = ".min";
	return (filename[string_length-4] = '.' && filename[string_length-3] == 'm' 
		&& filename[string_length-2] == 'i' && filename[string_length-1] == 'n');
}

FILE *get_pretty_print_file(char *filename){
	// this assumes that the file extension is valid 
	
}

void yyparse();
FILE *output_pretty;
int main(int argc, char **argv){
	if (argc > 1){
		if (!has_valid_extension(argv[1])){
			printf("Invalid file extension: filename should be 'filename'.min not %s\n", argv[1]);
			exit(EXIT_FAILURE);
		}
		yyin = fopen(argv[1], "r");
		output_pretty = fopen("test.output.min", "w");
		if (yyin == NULL){
			printf("File %s does not exist!\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	yyparse();
	pretty_print(program);
	fclose(output_pretty);
	exit(EXIT_SUCCESS);
	return 0;
}