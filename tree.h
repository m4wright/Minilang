#include <stdlib.h>
#include "hash.h"

#ifndef AST_H
#define AST_H

typedef enum exp_type {
	variable_type, int_literal, float_literal, string_literal, uminus_type,
	times_type, plus_type, div_type, minus_type
} exp_type;


typedef struct EXPR {
	exp_type expression_type;
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
} DECLARATIONS;

struct STATEMENTS;

typedef struct STATEMENT {
	enum {WHILE_STMT,IF_STMT,PRINT_STMT,READ_STMT,ASSIGNMENT_STMT} statement_type;
	union {
		struct {struct EXPR *condition; struct STATEMENTS *statements;} WHILE;
		struct {struct EXPR *condition; struct STATEMENTS *statements; struct STATEMENTS *else_stmts;} IF; 
		// else_part is NULL if there is no else part
		struct {struct EXPR *to_print;} PRINT;
		id_type_pair to_read;													// variable info for read
		struct {id_type_pair var_info; struct EXPR *assign;} ASSIGNMENT;
	} val;	

} STATEMENT;

typedef struct STATEMENTS {
	STATEMENT *statement;
	struct STATEMENTS *next;
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

id_type_pair *makeDECLARATION(char *identifier, var_type type);
DECLARATIONS *addToDECLARATIONS(DECLARATIONS *decls, id_type_pair *elem);

STATEMENT *makeSTATEMENTwhile(EXPR *condition, STATEMENTS *statements);
STATEMENT *makeSTATEMENTif(EXPR *condition, STATEMENTS *statements, STATEMENTS *else_stmts);
STATEMENT *makeSTATEMENTprint(EXPR *to_print);
STATEMENT *makeSTATEMENTread(char *id_to_read);
STATEMENT *makeSTATEMENTassignment(char *id, EXPR *value);

STATEMENTS *addToSTATEMENTS(STATEMENTS *statements, STATEMENT *statement);

extern PROGRAM program;

#endif