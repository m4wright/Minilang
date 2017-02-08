#include <stdio.h>
#include <stdlib.h>
extern FILE *yyin;

void yyparse();


int main(int argc, char **argv){
	if (argc > 1){
		yyin = fopen(argv[1], "r");
		if (yyin == NULL){
			printf("File %s does not exist!\n", argv[1]);
			exit(EXIT_FAILURE);
		}
	}
	yyparse();

	printf("VALID");
	exit(EXIT_SUCCESS);
	return 0;
}