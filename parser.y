%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tree.h"
#include "type_checker.h"

extern char *yytext;
id_type_pair *duplicate = NULL;
int yylex();
int line_number = 1;


void yyerror(const char *msg){
	fprintf (stderr, "INVALID: syntax error before %s on line%d\n", msg, line_number);
	exit(EXIT_FAILURE);
}


PROGRAM program = {NULL,NULL};

%}

%locations

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
	line_number = @1.first_line;
	program.declarations = $1;
	program.statements = $2;
};

DECLARATIONS : %empty 			{$$ = NULL;}
	| DECLARATION DECLARATIONS  {$$ = addToDECLARATIONS($2,$1); line_number = @1.first_line;}
	;

DECLARATION : tVAR tID ':' TYPE ';'{$$ = makeDECLARATION($2,$4, @1.first_line); line_number = @1.first_line;};

TYPE : tFLOAT {$$ = float_type;} 
	 | tINT  {$$ = int_type;}	
	 | tSTRING {$$ = string_type;}
	 ;

STATEMENTS : %empty  		{$$ = NULL;}
	| STATEMENT STATEMENTS{$$ = addToSTATEMENTS($2, $1); line_number = @1.first_line;}
	;

STATEMENT : WHILE | IF | PRINT | READ | ASSIGNMENT; 	// $$ will be equal to the STATEMENT  from the individual parts

WHILE : tWHILE EXPR tDO STATEMENTS tDONE 	{$$ = makeSTATEMENTwhile($2,$4); line_number = @1.first_line;};

IF  : tIF EXPR tTHEN STATEMENTS tENDIF 	 	{$$ = makeSTATEMENTif($2,$4,NULL); line_number = @1.first_line;}
	| tIF EXPR tTHEN STATEMENTS tELSE STATEMENTS tENDIF {$$ = makeSTATEMENTif($2,$4,$6); line_number = @1.first_line;}
	;

PRINT : tPRINT EXPR ';'		{$$ = makeSTATEMENTprint($2); line_number = @1.first_line;};
READ : tREAD tID ';'		{$$ = makeSTATEMENTread($2, @1.first_line); line_number = @1.first_line;};
ASSIGNMENT : tID '=' EXPR ';' {$$ = makeSTATEMENTassignment($1,$3); line_number = @1.first_line;};

EXPR : INTEGER 	 			{$$ = makeEXPRint($1, @1.first_line); line_number = @1.first_line;}
	 | FLOAT 				{$$ = makeEXPRfloat($1, @1.first_line); line_number = @1.first_line;}
	 | tID 					{$$ = makeEXPRvariable($1, @1.first_line); line_number = @1.first_line;}
	 | STRING 				{$$ = makeEXPRstring($1, @1.first_line); line_number = @1.first_line;}
	 | EXPR PLUS EXPR 		{$$ = makeEXPRplus($1,$3, @1.first_line); line_number = @1.first_line;}
	 | EXPR MINUS EXPR 		{$$ = makeEXPRminus($1,$3, @1.first_line); line_number = @1.first_line;}
	 | EXPR MULT EXPR 		{$$ = makeEXPRtimes($1,$3, @1.first_line); line_number = @1.first_line;}
	 | EXPR DIV EXPR 		{$$ = makeEXPRdiv($1,$3, @1.first_line); line_number = @1.first_line;}
	 | '(' EXPR ')' 		{$$ = $2; line_number = @1.first_line;}
	 | MINUS EXPR 	%prec UMINUS 		{$$ = makeEXPRuminus($2, @1.first_line); line_number = @1.first_line;}
	 ;
%%

