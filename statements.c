#include "tree.h"
#include <stdio.h>

STATEMENT *makeSTATEMENTwhile(EXPR *condition, STATEMENTS *statements){
	// note that condition should be of int type
	// need to check in type checking
	STATEMENT *statement = malloc(sizeof(STATEMENT));
	statement->statement_type = WHILE_STMT;
	statement->val.WHILE.condition = condition;
	statement->val.WHILE.statements = statements;
	return statement;
}

STATEMENT *makeSTATEMENTif(EXPR *condition, STATEMENTS *statements, STATEMENTS *else_stmts){
	// note that condition should be of int type
	// need to check in type checking
	STATEMENT *statement = malloc(sizeof(STATEMENT));
	statement->statement_type = IF_STMT;
	statement->val.IF.condition = condition;
	statement->val.IF.statements = statements;
	statement->val.IF.else_stmts = else_stmts;
	return statement;
}

STATEMENT *makeSTATEMENTprint(EXPR *to_print){
	STATEMENT *statement = malloc(sizeof(STATEMENT));
	statement->statement_type = PRINT_STMT;
	statement->val.PRINT.to_print = to_print;
	return statement;
}

STATEMENT *makeSTATEMENTread(char *id_to_read){
	STATEMENT *statement = malloc(sizeof(STATEMENT));
	statement->statement_type = READ_STMT;
	statement->val.to_read.identifier = id_to_read;
	statement->val.to_read.type = get_type(id_to_read);
	return statement;
}

STATEMENT *makeSTATEMENTassignment(char *id, EXPR *value){
	// need to type check later
	// note that a float id can have an int EXPR. 
	var_type id_type = get_type(id);
	if (!(id_type == value->type || (id_type == float_type && value->type == int_type))){
		// badly typed
		id_type = error_type;
	}
	STATEMENT *statement = malloc(sizeof(STATEMENT));
	statement->statement_type = ASSIGNMENT_STMT;
	statement->val.ASSIGNMENT.var_info.identifier = id;
	statement->val.ASSIGNMENT.var_info.type = id_type;	
	statement->val.ASSIGNMENT.assign = value;
	return statement;
}

STATEMENTS *addToSTATEMENTS(STATEMENTS *statements, STATEMENT *statement){
	STATEMENTS *to_add = malloc(sizeof(STATEMENTS));
	to_add->next = statements;
	to_add->statement = statement;
	return to_add;
}

