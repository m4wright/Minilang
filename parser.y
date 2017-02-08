%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tree.h"

	
extern char *yytext;
int yylex();


void yyerror(){
	printf("INVALID: ");
	if (strlen(yytext) == 0){
		printf("syntax errror before EOF\n");
	}else{
		printf ("syntax error before %s\n", yytext);
	}
	exit(EXIT_FAILURE);
}

PROGRAM program = {NULL,NULL};

%}

%union {
	int integer;
	float float64;
	char *string;
	char *id_name;
	var_type type;
	struct hash_element *declaration;
}

%token <integer> INTEGER
%token <float64> FLOAT
%token <string> STRING
%token <id_name> tID
%token tVAR 
%token tWHILE
%token tDONE
%token tDO
%token tFLOAT
%token tINT
%token tSTRING
%token tPRINT
%token tREAD
%token tIF
%token tTHEN
%token tELSE
%token tENDIF
%token PLUS
%token MINUS
%token MULT
%token DIV

%type <declaration> DECLARATION
%type <type> TYPE

%left PLUS MINUS
%left MULT DIV
%left UMINUS

%start START 

%%

START : DECLARATIONS STATEMENTS;

DECLARATIONS : %empty 
	| DECLARATION DECLARATIONS{
		program.declarations = addToDECLARATIONS(program.declarations, $1);
	};

DECLARATION : tVAR tID ':' TYPE ';'{$$ = makeDECLARATION($2,$4);};

TYPE : tFLOAT {$$ = floatType;} 
	 | tINT  {$$ = intType;}	
	 | tSTRING {$$ = stringType;}
	 ;

STATEMENTS : %empty | STATEMENT STATEMENTS;

STATEMENT : WHILE | IF | PRINT | READ | ASSIGNMENT;
WHILE : tWHILE EXPR tDO STATEMENTS tDONE;
IF : tIF EXPR tTHEN STATEMENTS tENDIF | tIF EXPR tTHEN STATEMENTS tELSE STATEMENTS tENDIF;
PRINT : tPRINT EXPR ';';
READ : tREAD tID ';';
ASSIGNMENT : tID '=' EXPR ';';

EXPR : INTEGER 
	 | FLOAT
	 | tID
	 | STRING
	 | EXPR PLUS EXPR
	 | EXPR MINUS EXPR
	 | EXPR MULT EXPR
	 | EXPR DIV EXPR
	 | '(' EXPR ')'
	 | MINUS EXPR 	%prec UMINUS
	 ;
%%

