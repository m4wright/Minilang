/*
	NOTE: while building up the tree, types are not checked
	Type checking occurs after
*/

#include <stdlib.h>
#include "hash.h"
#ifndef AST_H
#define AST_H

typedef enum exp_type {
	variable_type, int_literal, float_literal, string_literal, uminus_type,
	times_type, plus_type, div_type, minus_type
};


typedef struct EXPR {
	expr_type expression_type;
	var_type type;

	union {
		char *id;
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
	id_type_pair *decl;
	struct DECLARATIONS *next;
	struct DECLARATIONS *prev;
} DECLARATIONS;

struct STATEMENTS;

typedef struct STATEMENT {
	enum {WHILE_STMT,IF_STMT,PRINT_STMT,READ_STMT,ASSIGNMENT_STMT} statement_type;
	union {
		struct {struct EXPR *condition; struct STATEMENTS *statements;} WHILE;
		struct {struct EXPR *condition; struct STATEMENTS *statements;} IF;
		struct {struct EXPR *to_print;} PRINT;
		char *var_to_read;															// variable name for read
		struct {char *var_name; type var_type; struct EXPR *assign;} ASSIGNMENT;
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

var_type get_type_from_op(var_type1, var_type2, exp_type op);

EXPR *makeEXPRvariable(char *var_name);
EXPR *makeEXPRint(int value);
EXPR *makeEXPRfloat(float value);
EXPR *makeEXPRstring(char *string);
EXPR *makeEXPRuminus(EXPR *child);
EXPR *makeEXPRtimes(EXPR *left, EXPR *right);
EXPR *makeEXPRdiv(EXPR *left, EXPR *right);
EXPR *makeEXPRplus(EXPR *left, EXPR *right);
EXPR *makeEXPRminus(EXPR *left, EXPR *right);

id_type_pair *makeDECLARATION(char *identifier, var_type type);
DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, id_type_pair *elem);

extern PROGRAM program;

#endif