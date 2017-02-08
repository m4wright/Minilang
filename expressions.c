#include "tree.h"
#include <stdio.h>

EXPR *makeEXPRvariable(char *var_name){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = get_type(var_name);
	if (e->expression_type == error_type){ 							// var_name is not in the hash table. might want to remove this for 
		printf("ERROR: %s has not been declared\n", var_name);    			// pretty printing
		exit(EXIT_FAILURE);
		return NULL;
	}
	e->type = variable_type;
	e->val.id = var_name;
	return e;
}

EXPR *makeEXPRint(int value){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = int_literal;
	e->type = int_type;
	e->val.int_num = value;
	return e;
}

EXPR *makeEXPRfloat(float value){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = float_literal;
	e->type = float_type;
	e->val.float_num = value;
	return e;
}

EXPR *makeEXPRstring(char *string){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = string_literal;
	e->type = string_type;
	e->val.string = string;
	return e;
}


var_type get_type_from_op(var_type type1, var_type type2, exp_type op){
	/*
		returns error_type if it cannot be typed rather than throwing an error,
		since we still want to be able to pretty print it
		error_type will tell the type checker that the types don't match
	*/

	// we only check for these operations. the others
	// are handled in their makeEXPR functions
	// in the case of uminus, type2 is irrelevant
	switch (op){
		case uminus_type:
			if (type1 == float_type || type2 == int_type){
				return type1;
			}else{
				return error_type;
			}
		case times_type:
		case plus_type:
		case div_type:
		case minus_type:
			break;
		default:
			return error_type; 	 	
	}
	if (type1 == int_type){
		if (type2 == int_type){
			return int_type;
		}else if (type2 == float_type){
			return float_type;
		}else if (type2 == string_type){
			if (op == times_type){
				return string_type;
			}else{
				return error_type;
			}
		}else{
			return error_type;
		}
	}else if (type1 == float_type){
		if (type2 == float_type || type2 == int_type){
			return float_type;
		}else{
			return error_type;
		}
	}else if (type1 == string_type){
		if (type2 == int_type){
			if (op == times_type){
				return string_type;
			}else{
				return error_type;
			}
		}else if (type2 == string_type){
			if (op == plus_type){
				return string_type;
			}else{
				return error_type;
			}
		}
	}
	return error_type;
}

EXPR *makeEXPRuminus(EXPR *child){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = uminus_type;
	e->type = get_type_from_op(child->type, int_type, uminus_type); 		// second argument is irrelevant for uminus
	e->val.uminus.child = child;
	return e;
}

EXPR *makeEXPRtimes(EXPR *left, EXPR *right){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = times_type;
	e->type = get_type_from_op(left->type, right->type, times_type);
	e->val.times.left = left;
	e->val.times.right = right;
	return e;
}

EXPR *makeEXPRplus(EXPR *left, EXPR *right){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = plus_type;
	e->type = get_type_from_op(left->type, right->type, plus_type);
	e->val.plus.left = left;
	e->val.plus.right = right;
	return e;
}

EXPR *makeEXPRdiv(EXPR *left, EXPR *right){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = div_type;
	e->type = get_type_from_op(left->type, right->type, div_type);
	e->val.div.left = left;
	e->val.div.right = right;
	return e;
}

EXPR *makeEXPRminus(EXPR *left, EXPR *right){
	EXPR *e = malloc(sizeof(EXPR));
	e->expression_type = minus_type;
	e->type = get_type_from_op(left->type, right->type, minus_type);
	e->val.minus.left = left;
	e->val.minus.right = right;
	return e;
}

