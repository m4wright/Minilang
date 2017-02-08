all : minc

minc : parser.tab.o lex.yy.o main.o tree.h tree.o declarations.o hash.h hash.o
	gcc lex.yy.o parser.tab.o tree.o declarations.o hash.o expressions.o -o minc

parser.tab.c parser.tab.h : parser.y
	bison -d parser.y 

lex.yy.c : parser.tab.h scanner.l
	flex scanner.l


clean : 
	rm parser.tab.*; rm lex.yy.c; rm *.o; rm minc;
