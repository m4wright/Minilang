all : main

main : parser.tab.o lex.yy.o main.o tree.h tree.o declarations.o hash.h hash.o

parser.tab.c parser.tab.h : parser.y
	bison -d parser.y 

lex.yy.c : parser.tab.h scanner.l
	flex scanner.l

minc : parser.tab.c parser.tab.h lex.yy.c 
	gcc parser.tab.c lex.yy.c main.c -o minc


clean : 
	rm parser.tab.*; rm lex.yy.c; rm *.o; rm minc;