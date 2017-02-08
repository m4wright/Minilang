#include <stdlib.h>
#include "hash.h"
#ifndef AST_H
#define AST_H


typedef struct EXPR {
	enum {
		variableT, string_varT, intT=intType, floatT=floatType, stringT=stringType, uminus_intT, uminus_floatT,
		times_intT, times_floatT, times_stringT, plus_intT, plus_floatT,
		plus_stringT, div_intT, div_floatT, minus_intT, minus_floatT
	} type;
	union {
		hash_element variable;
		int int_num;
		float float_num;
		char *string;
		struct {struct EXPR *child;} uminus;
		struct {struct EXPR *left; struct EXPR *right;} times;
		struct {struct EXPR *left; struct EXPR *right;} div;
		struct {struct EXPR *left; struct EXPR *right;} plus;
		struct {struct EXPR *left; struct EXPR *right;} minus;
	} val;
} EXPR;


typedef struct DECLARATIONS {
	hash_element *decl;
	struct DECLARATIONS *next;
	struct DECLARATIONS *prev;
} DECLARATIONS;

struct STATEMENTS;

typedef struct STATEMENT {
	enum {WHILE_STMT,IF_STMT,PRINT_STMT,READ_STMT,ASSIGNMENT_STMT} type;
	union {
		struct {struct EXPR *condition; struct STATEMENTS *statements;} WHILE;
		struct {struct EXPR *condition; struct STATEMENTS *statements;} IF;
		struct {struct EXPR *to_print;} PRINT;
		char *var_name;															// variable name for read
		struct {char *var_name; struct EXPR *assign;} ASSIGNMENT;
	} val;	

} STATEMENT;

typedef struct STATEMENTS {
	STATEMENT *stmt;
	struct STATEMENTS *next;
	struct STATEMENTS *prev;
} STATEMENTS;

typedef struct PROGRAM {
	DECLARATIONS *declarations;
	STATEMENTS *statements;
} PROGRAM;

EXPR *makeEXPRvariable(char *var_name);
EXPR *makeEXPRint(int value);
EXPR *makeEXPRfloat(float value);
EXPR *makeEXPRstring(char *string);
EXPR *makeEXPRuminus(EXPR *child);
EXPR *makeEXPRtimes(EXPR *left, EXPR *right);
EXPR *makeEXPRdiv(EXPR *left, EXPR *right);
EXPR *makeEXPRplus(EXPR *left, EXPR *right);
EXPR *makeEXPRminus(EXPR *left, EXPR *right);

hash_element *makeDECLARATION(char *identifier, var_type type);
DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, hash_element *elem);

extern PROGRAM program;

#endif