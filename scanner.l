%{
	#include "hash.h"
	#include "parser.tab.h"
%}

extern int yylex();

%%

\/\/.*						{}
[ \r\n\t]+					{}


var 		{return tVAR;}
while 		{return tWHILE;}
done 		{return tDONE;}
do 			{return tDO;}
float 		{return tFLOAT;}
int 		{return tINT;}
string 		{return tSTRING;}
print 		{return tPRINT;}
read 		{return tREAD;}
if 		 	{return tIF;}
then 		{return tTHEN;}
else		{return tELSE;}
endif 		{return tENDIF;}



[()=;:]					{return yytext[0];}
"*"						{return MULT;}
"+"						{return PLUS;}
"/"						{return DIV;}
"-"						{return MINUS;}



(0|([1-9][0-9]*))\.[0-9]+ {
	yylval.float64 = atof(yytext);
	return FLOAT;
}

0|([1-9][0-9]*)	{
	yylval.integer = atoi(yytext);
	return INTEGER;
}


[a-zA-Z_][a-zA-A0-9_]*	{
	yylval.id_name = malloc(strlen(yytext) + 1);
	sprintf(yylval.id_name, "%s", yytext);
	return tID;
}

\"(\\[abfnrtv"\\]|[^"\\])*\"	{
	yylval.string = malloc(strlen(yytext) + 1);
	sprintf(yylval.string, "%s", yytext);
	return STRING;
}

. {
	printf("INVALID: unexpected character: %c\n", yytext[0]);
	exit(EXIT_FAILURE);	
}


%%


int yywrap(void){
	return 1;
}

