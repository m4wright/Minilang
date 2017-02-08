#include "code_generation.h"
#include <stdio.h>
#include <stdlib.h>


/*
	NEED TO ADD INDENTATIONS
	IDEA: PASS num_tabs parameter
*/

void print_num_tabs(int num_tabs){
	char *s = malloc(num_tabs+1);
	int i;
	for (i = 0; i < num_tabs; i++){
		s[i] = '\t';
	}
	s[i] = '\0';
	fprintf(output_pretty, "%s", s);
	free(s);
}

char *type_to_string(var_type type);

void pretty_print_statements(STATEMENTS *statements, int num_tabs);

void pretty_print_declaration(id_type_pair *declaration){
	fprintf(output_pretty, "var %s: %s;\n", declaration->identifier, type_to_string(declaration->type));
}


void pretty_print_declarations(DECLARATIONS *declarations){		
	while (declarations){ 						
		pretty_print_declaration(declarations->decl);
		declarations = declarations->next;
	}
}

void pretty_print_expression(EXPR *e){
	switch (e->expression_type){
		case variable_type:
			fprintf(output_pretty, "%s", e->val.id);
			break;
		case int_literal:
			fprintf(output_pretty, "%d", e->val.int_num);
			break;
		case float_literal:
			fprintf(output_pretty, "%f", e->val.float_num);
			break;
		case string_literal:
			fprintf(output_pretty, "%s", e->val.string);
			break;
		case uminus_type:
			fprintf(output_pretty, "-");
			pretty_print_expression(e->val.uminus.child);
			break;
		case times_type:
			fprintf(output_pretty, "(");
			pretty_print_expression(e->val.times.left);
			fprintf(output_pretty, "*");
			pretty_print_expression(e->val.times.right);
			fprintf(output_pretty, ")");
			break;
		case plus_type:
			fprintf(output_pretty, "(");
			pretty_print_expression(e->val.plus.left);
			fprintf(output_pretty, "+");
			pretty_print_expression(e->val.plus.right);
			fprintf(output_pretty, ")");
			break;
		case div_type:
			fprintf(output_pretty, "(");
			pretty_print_expression(e->val.div.left);
			fprintf(output_pretty, "/");
			pretty_print_expression(e->val.div.right);
			fprintf(output_pretty, ")");
			break;
		case minus_type:
			fprintf(output_pretty, "(");
			pretty_print_expression(e->val.minus.left);
			fprintf(output_pretty, "-");
			pretty_print_expression(e->val.minus.right);
			fprintf(output_pretty, ")");
			break;
	}
}

void pretty_print_while(STATEMENT *statement, int num_tabs){
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "while ");
	pretty_print_expression(statement->val.WHILE.condition);
	fprintf(output_pretty, " do\n");
	pretty_print_statements(statement->val.WHILE.statements, num_tabs+1);
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "done\n");
}


void pretty_print_else(STATEMENTS *statements, int num_tabs){
	if (statements != NULL){						// NULL means that there is no else part
		print_num_tabs(num_tabs);
		fprintf(output_pretty, "else\n");
		pretty_print_statements(statements, num_tabs+1);
	}
}

void pretty_print_if(STATEMENT *statement, int num_tabs){
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "if ");
	pretty_print_expression(statement->val.IF.condition);
	fprintf(output_pretty, " then\n");
	pretty_print_statements(statement->val.IF.statements, num_tabs+1);
	pretty_print_else(statement->val.IF.else_stmts, num_tabs);
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "endif\n");
}

void pretty_print_print_stmt(STATEMENT *statement, int num_tabs){
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "print ");
	pretty_print_expression(statement->val.PRINT.to_print);
	fprintf(output_pretty, ";\n");
}

void pretty_print_read_stmt(STATEMENT *statement, int num_tabs){
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "read %s;\n", statement->val.to_read.identifier);
}

void pretty_print_assignment(STATEMENT *statement, int num_tabs){
	print_num_tabs(num_tabs);
	fprintf(output_pretty, "%s = ", statement->val.ASSIGNMENT.var_info.identifier);
	pretty_print_expression(statement->val.ASSIGNMENT.assign);
	fprintf(output_pretty, ";\n");
}


void pretty_print_statement(STATEMENT *statement, int num_tabs){
	switch (statement->statement_type){
		case WHILE_STMT:
			pretty_print_while(statement, num_tabs);
			break;
		case IF_STMT:
			pretty_print_if(statement, num_tabs);
			break;
		case PRINT_STMT:
			pretty_print_print_stmt(statement, num_tabs);
			break;
		case READ_STMT:
			pretty_print_read_stmt(statement, num_tabs);
			break;
		case ASSIGNMENT_STMT:
			pretty_print_assignment(statement, num_tabs);
			break;
		default:
			// this should never happen
			printf("ERROR: Unkown statement type\n");
			exit(EXIT_FAILURE);
	}
}

void pretty_print_statements(STATEMENTS *statements, int num_tabs){
	while (statements){
		pretty_print_statement(statements->statement, num_tabs);
		statements = statements->next;
	}
}

void pretty_print(PROGRAM program){
	pretty_print_declarations(program.declarations);
	if (program.declarations != NULL){ 					// if there are declarations, print a new line between
		fprintf(output_pretty, "\n"); 					// them and the statements
	}
	pretty_print_statements(program.statements, 0);
	fprintf(output_pretty, "\n");
}


char *type_to_string(var_type type){
	switch (type){
		case int_type:
			return "int";
		case float_type:
			return "float";
		case string_type:
			return "string";
		default:
			// this should never happen
			printf("Invalid type\n");
			exit(EXIT_FAILURE);
			return NULL;
	}
}