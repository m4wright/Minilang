all : minc

minc : parser.tab.o lex.yy.o tree.h declarations.o hash.h hash.o code_generation.h pretty_printer.o expressions.o statements.o main.o
	gcc parser.tab.o lex.yy.o declarations.o hash.o code_generation.h pretty_printer.o expressions.o statements.o main.o -o minc

parser.tab.c parser.tab.h : parser.y
	bison -d parser.y 

lex.yy.c : parser.tab.h scanner.l
	flex scanner.l


clean : 
	rm parser.tab.*; rm lex.yy.c; rm *.o; rm minc;
