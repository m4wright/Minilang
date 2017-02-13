%{
	#include "hash.h"
	#include "parser.tab.h"
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
%}

extern int yylex();

%option yylineno
%option noyywrap

%%

\/\/.*						{}
[ \r\n\t]+					{}


var 		{return tVAR;}
while 		{return tWHILE; yylloc.first_line = yylineno;} 
done 		{return tDONE; yylloc.first_line = yylineno;}
do 			{return tDO; yylloc.first_line = yylineno;}
float 		{return tFLOAT; yylloc.first_line = yylineno;}
int 		{return tINT; yylloc.first_line = yylineno;}
string 		{return tSTRING; yylloc.first_line = yylineno;}
print 		{return tPRINT; yylloc.first_line = yylineno;}
read 		{return tREAD; yylloc.first_line = yylineno;}
if 		 	{return tIF; yylloc.first_line = yylineno;}
then 		{return tTHEN; yylloc.first_line = yylineno;}
else		{return tELSE; yylloc.first_line = yylineno;}
endif 		{return tENDIF; yylloc.first_line = yylineno;}



[()=;:]					{return yytext[0]; yylloc.first_line = yylineno;}
"*"						{return MULT; yylloc.first_line = yylineno;}
"+"						{return PLUS; yylloc.first_line = yylineno;}
"/"						{return DIV; yylloc.first_line = yylineno;}
"-"						{return MINUS; yylloc.first_line = yylineno;}



(0|([1-9][0-9]*))\.[0-9]+ {
	yylval.float64 = atof(yytext);
	yylloc.first_line = yylineno;
	return FLOAT;
}

0|([1-9][0-9]*)	{
	yylval.integer = atoi(yytext);
	yylloc.first_line = yylineno;
	return INTEGER;
}


[a-zA-Z_][a-zA-A0-9_]*	{
	yylval.id_name = malloc(strlen(yytext) + 1);
	sprintf(yylval.id_name, "%s", yytext);
	yylloc.first_line = yylineno;
	return tID;
}

\"(\\[abfnrtv"\\]|[^"\\])*\"	{
	yylval.string = malloc(strlen(yytext) - 1); 		// the token will not have the quote symbols
	yytext[strlen(yytext)-1] = '\0';
	yytext++;
	sprintf(yylval.string, "%s", yytext);
	yylloc.first_line = yylineno;
	return STRING;
}

. {
	fprintf(stderr, "ERROR: unexpected character: %c on line %d\n", yytext[0], yylineno);
	exit(EXIT_FAILURE);	
}


%%


