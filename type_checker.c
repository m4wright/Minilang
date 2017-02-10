#include <stdlib.h>
#include "type_checker.h"

var_type type_check_expression(EXPR *e);
void type_check_statements(STATEMENTS *statements);

void type_check(PROGRAM program){
	if (duplicate != NULL){
		printf("%s has already been declared\n", duplicate);
		exit(EXIT_FAILURE);
	}
	type_check_statements(program.statements);  		// duplicates are found while creating the AST
}

void type_check_statements(STATEMENTS *statements){
	while (statements){
		switch (statements->statement->statement_type){
			case WHILE_STMT:
				if (type_check_expression(statements->statement->val.WHILE.condition) != int_type){
					printf("ERROR: expression in while loop does not have integer type\n");
					exit(EXIT_FAILURE);
				}
				type_check_statements(statements->statement->val.WHILE.statements);
				break;
			case IF_STMT:
				if (type_check_expression(statements->statement->val.IF.condition) != int_type){
					printf("ERROR: expression in if statement does not have integer type\n");
					exit(EXIT_FAILURE);
				}
				type_check_statements(statements->statement->val.IF.statements);
				type_check_statements(statements->statement->val.IF.else_stmts);
				break;
			case PRINT_STMT:
				type_check_expression(statements->statement->val.PRINT.to_print);
				break;
			case READ_STMT:
				if (!declared(statements->statement->val.to_read.identifier)){
					printf("ERROR: %s has not been declared\n", statements->statement->val.to_read.identifier);
					exit(EXIT_FAILURE);
				}
				break;
			case ASSIGNMENT_STMT:
				if (!declared(statements->statement->val.ASSIGNMENT.var_info.identifier)){
					printf("ERROR: %s has not been declared\n", statements->statement->val.ASSIGNMENT.var_info.identifier);
					exit(EXIT_FAILURE);
				}
				type_check_expression(statements->statement->val.ASSIGNMENT.assign);
				if (statements->statement->val.ASSIGNMENT.var_info.type == error_type){
					printf("ERROR: %s has type %s but the expression has type %s", 
						statements->statement->val.ASSIGNMENT.var_info.identifier, 
						type_to_string(get_type(statements->statement->val.ASSIGNMENT.var_info.identifier)),
						type_to_string(statements->statement->val.ASSIGNMENT.assign->type)
					);
					exit(EXIT_FAILURE);
				}
				break;
				// no need for a default case, there can't be any other type of statement
		}
		statements = statements->next;
	}
}

var_type type_check_expression(EXPR *e){
	switch (e->expression_type){
		case int_literal:
		case float_literal:
		case string_literal:
		case variable_type:
			return e->type;
		case uminus_type:
			type_check_expression(e->val.uminus.child);
			if (e->type == error_type){
				printf("ERROR: unary minus cannot be applied to type %s\n", type_to_string(e->val.uminus.child->type));
				exit(EXIT_FAILURE);
			}
			return e->type;
		case times_type:
			type_check_expression(e->val.times.left);
			type_check_expression(e->val.times.right);
			if (e->type == error_type){
				printf("ERROR: '*' cannot be applied to types %s and %s\n", 
					type_to_string(e->val.times.left->type), type_to_string(e->val.times.right->type));
				exit(EXIT_FAILURE);
			}
			return e->type;
		case plus_type:
			type_check_expression(e->val.plus.left);
			type_check_expression(e->val.plus.right);
			if (e->type == error_type){
				printf("ERROR: '+' cannot be applied to types %s and %s\n", 
					type_to_string(e->val.plus.left->type), type_to_string(e->val.plus.right->type));
				exit(EXIT_FAILURE);
			}
			return e->type;
		case div_type:
			type_check_expression(e->val.div.left);
			type_check_expression(e->val.div.right);
			if (e->type == error_type){
				printf("ERROR: '/' cannot be applied to types %s and %s\n", 
					type_to_string(e->val.div.left->type), type_to_string(e->val.div.right->type));
				exit(EXIT_FAILURE);
			}
			return e->type;
		case minus_type:
			type_check_expression(e->val.minus.left);
			type_check_expression(e->val.minus.right);
			if (e->type == error_type){
				printf("ERROR: '-' cannot be applied to types %s and %s\n", 
					type_to_string(e->val.minus.left->type), type_to_string(e->val.minus.right->type));
				exit(EXIT_FAILURE);
			}
			return e->type;
	}
}


