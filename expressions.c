#include <stdlib.h>
#include "hash.h"
#include "tree.h"

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

EXPR *makeEXPRvariable(char *var_name){
	EXPR *e = malloc(sizeof(EXPR));
	e->type = variableT;
	e->val.variable.identifier = var_name;
	e->val.variable.type = get_variable_type(var_name);
	return e;
}

EXPR *makeEXPRint(int value){
	EXPR *e = malloc(sizeof(EXPR));
	e->type = intT;
	e->val.int_num = value;
	return e;
}

EXPR *makeEXPRfloat(float value){
	EXPR *e = malloc(sizeof(EXPR));
	e->type = floatT;
	e->val.float_num = value;
	return e;
}

EXPR *makeEXPRstring(char *string){
	EXPR *e = malloc(sizeof(EXPR));
	e->type = stringT;
	e->val.string = string;
	return e;
}

EXPR *makeEXPRuminus(EXPR *child){
	EXPR *e = malloc(sizeof(EXPR));
	e->val.uminus.child = child;
	if (child->val.variable.type == stringType){
		printf("ERROR: %s is not of type int or float\n", child->val.variable.identifier);
		EXIT(EXIT_FAILURE);
		return NULL;
	}
	e->type = child->val.variable.type;
	return e;
}

EXPR *makeEXPRtimes(EXPR *left, EXPR *right){
	EXPR *e = malloc(sizeof(EXPR));
	e->val.times.left = left;
	e->val.times.right = right;
	var_type type_left;
	var_type type_right;
	switch (left->type){
		case variableT:

	}
}




#endif