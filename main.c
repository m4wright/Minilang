#include "code_generation.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;

void yyparse();
FILE *output_pretty;
int main(int argc, char **argv){
	if (argc > 1){
		yyin = fopen(argv[1], "r");
		output_pretty = fopen("test.output.min", "w");
		if (yyin == NULL){
			printf("File %s does not exist!\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	yyparse();
	pretty_print(program);
	printf("VALID");
	fclose(output_pretty);
	exit(EXIT_SUCCESS);
	return 0;
}