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
	struct id_type_pair *declaration;
	struct DECLARATIONS *declarations;
	struct STATEMENT *statement;
	struct STATEMENTS *statements;
	struct EXPR *expression;
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
%type <statement> WHILE
%type <statement> IF
%type <statement> PRINT
%type <statement> READ
%type <statement> ASSIGNMENT
%type <statement> STATEMENT
%type <expression> EXPR
%type <statements> STATEMENTS
%type <declarations> DECLARATIONS


%left PLUS MINUS
%left MULT DIV
%left UMINUS

%start START 

%%

START : DECLARATIONS STATEMENTS {
	program.declarations = $1;
	program.statements = $2;
};

DECLARATIONS : %empty 			{$$ = NULL;}
	| DECLARATIONS DECLARATION  {$$ = addToDECLARATIONS($1,$2);}
	;

DECLARATION : tVAR tID ':' TYPE ';'{$$ = makeDECLARATION($2,$4);};

TYPE : tFLOAT {$$ = float_type;} 
	 | tINT  {$$ = int_type;}	
	 | tSTRING {$$ = string_type;}
	 ;

STATEMENTS : %empty  		{$$ = NULL;}
	| STATEMENTS STATEMENT{$$ = addToSTATEMENTS($1, $2);}
	;

STATEMENT : WHILE | IF | PRINT | READ | ASSIGNMENT; 	// $$ will be equal to the STATEMENT  from the individual parts

WHILE : tWHILE EXPR tDO STATEMENTS tDONE 	{$$ = makeSTATEMENTwhile($2,$4);};

IF  : tIF EXPR tTHEN STATEMENTS tENDIF 	 	{$$ = makeSTATEMENTif($2,$4,NULL);}
	| tIF EXPR tTHEN STATEMENTS tELSE STATEMENTS tENDIF {$$ = makeSTATEMENTif($2,$4,$6);}
	;

PRINT : tPRINT EXPR ';'		{$$ = makeSTATEMENTprint($2);};
READ : tREAD tID ';'		{$$ = makeSTATEMENTread($2);};
ASSIGNMENT : tID '=' EXPR ';' {$$ = makeSTATEMENTassignment($1,$3);};

EXPR : INTEGER 	 			{$$ = makeEXPRint($1);}
	 | FLOAT 				{$$ = makeEXPRfloat($1);}
	 | tID 					{$$ = makeEXPRvariable($1);}
	 | STRING 				{$$ = makeEXPRstring($1);}
	 | EXPR PLUS EXPR 		{$$ = makeEXPRplus($1,$3);}
	 | EXPR MINUS EXPR 		{$$ = makeEXPRminus($1,$3);}
	 | EXPR MULT EXPR 		{$$ = makeEXPRtimes($1,$3);}
	 | EXPR DIV EXPR 		{$$ = makeEXPRdiv($1,$3);}
	 | '(' EXPR ')' 		{$$ = $2;}
	 | MINUS EXPR 	%prec UMINUS 		{$$ = makeEXPRuminus($2);}
	 ;
%%

