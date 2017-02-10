#include <stdio.h>
#include <stdlib.h>
#include "code_generation.h"


void c_print_statements(STATEMENTS *statements, int num_tabs);
void c_print_statement(STATEMENT *statement, int num_tabs);
void c_print_declarations(DECLARATIONS *declarations);
void c_print_declaration(id_type_pair *declaration);
void c_print_while(STATEMENT *statement, int num_tabs);
void c_print_if(STATEMENT *statement, int num_tabs);
void c_print_else(STATEMENTS *statements, int num_tabs);
void c_print_print_stmt(STATEMENT *statement, int num_tabs);
void c_print_read_stmt(STATEMENT *statement, int num_tabs);
void c_print_assignment(STATEMENT *statement, int num_tabs);
void c_print_expression(EXPR *e);
char *type_to_c_string(var_type type);

void c_print_declaration(id_type_pair *declaration){
	fprintf(c_file, "%s %s = ", 
		type_to_c_string(declaration->type), declaration->identifier
	);
	switch (declaration->type){
		case int_type:
		case float_type:
			fprintf(c_file, "0;\n");
			break;
		case string_type:
			fprintf(c_file, "\"\";\n");
			break;
	}
}

void c_print_declarations(DECLARATIONS *declarations){
	while (declarations){
		putc('\t', c_file);
		c_print_declaration(declarations->decl);
		declarations = declarations->next;
	}
}

void c_print_statements(STATEMENTS *statements, int num_tabs){
	while (statements){
		c_print_statement(statements->statement, num_tabs);
		statements = statements->next;
	}
}

void c_print_statement(STATEMENT *statement, int num_tabs){
	switch (statement->statement_type){
		case WHILE_STMT:
			c_print_while(statement, num_tabs);
			break;
		case IF_STMT:
			c_print_if(statement, num_tabs);
			break;
		case PRINT_STMT:
			c_print_print_stmt(statement, num_tabs);
			break;
		case READ_STMT:
			c_print_read_stmt(statement, num_tabs);
			break;
		case ASSIGNMENT_STMT:
			c_print_assignment(statement, num_tabs);
			break;
		default:
			// this should never happen
			printf("ERROR: Unkown statement type\n");
			exit(EXIT_FAILURE);
	}
}

void c_print_while(STATEMENT *statement, int num_tabs){
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "while (");
	c_print_expression(statement->val.WHILE.condition);
	fprintf(c_file, "){\n");
	c_print_statements(statement->val.WHILE.statements, num_tabs+1);
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "}\n");
}

void c_print_if(STATEMENT *statement, int num_tabs){
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "if (");
	c_print_expression(statement->val.IF.condition);
	fprintf(c_file, "){\n");
	c_print_statements(statement->val.IF.statements, num_tabs+1);
	c_print_else(statement->val.IF.else_stmts, num_tabs);
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "}\n");
}

void c_print_else(STATEMENTS *statements, int num_tabs){
	if (statements != NULL){
		print_num_tabs(c_file, num_tabs);
		fprintf(c_file, "}else{\n");
		c_print_statements(statements, num_tabs+1);
	}
}

void c_print_print_stmt(STATEMENT *statement, int num_tabs){
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "printf(\"");
	switch (statement->val.PRINT.to_print->type){
		case int_type:
			fprintf(c_file, "%%d\", ");
			break;
		case float_type:
			fprintf(c_file, "%%f\", ");
			break;
		case string_type:
			fprintf(c_file, "%%s\", ");
			break;
	}
	c_print_expression(statement->val.PRINT.to_print);
	fprintf(c_file, ");\n");
}

void c_print_read_stmt(STATEMENT *statement, int num_tabs){
	print_num_tabs(c_file, num_tabs);
	if (statement->val.to_read.type == string_type){
		fprintf(c_file, "%s = string_read(%s);\n", statement->val.to_read.identifier, statement->val.to_read.identifier);
		return;
	}
	fprintf(c_file, "scanf(\"");
	switch (statement->val.to_read.type){
		case int_type:
			fprintf(c_file, "%%d\", &");
			break;
		case float_type:
			fprintf(c_file, "%%f\", &");
			break;
	}
	fprintf(c_file, "%s);\n", statement->val.to_read.identifier);
}

void c_print_assignment(STATEMENT *statement, int num_tabs){
	print_num_tabs(c_file, num_tabs);
	fprintf(c_file, "%s = ", statement->val.ASSIGNMENT.var_info.identifier);
	c_print_expression(statement->val.ASSIGNMENT.assign);
	fprintf(c_file, ";\n");
}


void c_print_expression(EXPR *e){
	switch (e->expression_type){
		case variable_type:
			fprintf(c_file, "%s", e->val.id);
			break;
		case int_literal:
			fprintf(c_file, "%d", e->val.int_num);
			break;
		case float_literal:
			fprintf(c_file, "%f", e->val.float_num);
			break;
		case string_literal:
			fprintf(c_file, "\"%s\"", e->val.string);
			break;
		case uminus_type:
			fprintf(c_file, "(-");
			c_print_expression(e->val.uminus.child);
			fprintf(c_file, ")");
			break;
		case times_type:
			if (e->type == string_type){
				// int * string
				fprintf(c_file, "string_mult(");
				if (e->val.times.left->type == string_type){
					c_print_expression(e->val.times.left);
					fprintf(c_file, ", ");
					c_print_expression(e->val.times.right);
				}else{
					c_print_expression(e->val.times.right);
					fprintf(c_file, ", ");
					c_print_expression(e->val.times.left);
				}
				fprintf(c_file, ")");
				
			}else{
				// float or int multiplication
				fprintf(c_file, "(");
				c_print_expression(e->val.times.left);
				fprintf(c_file, " * ");
				c_print_expression(e->val.times.right);
				fprintf(c_file, ")");
			}
			break;
		case plus_type:
			if (e->type == string_type){
				// string addition
				fprintf(c_file, "string_add(");
				c_print_expression(e->val.plus.left);
				fprintf(c_file, ", ");
				c_print_expression(e->val.plus.right);
				fprintf(c_file, ")");
			}else{
				// float or int addition
				fprintf(c_file, "(");
				c_print_expression(e->val.plus.left);
				fprintf(c_file, " + ");
				c_print_expression(e->val.plus.right);
				fprintf(c_file, ")");
			}
			break;
		case div_type:
			fprintf(c_file, "(");
			c_print_expression(e->val.div.left);
			fprintf(c_file, " / ");
			c_print_expression(e->val.div.right);
			fprintf(c_file, ")");
			break;
		case minus_type:
			fprintf(c_file, "(");
			c_print_expression(e->val.minus.left);
			fprintf(c_file, " - ");
			c_print_expression(e->val.minus.right);
			fprintf(c_file, ")");
			break;
	}
}




void c_print(PROGRAM program){
	FILE *template = fopen("template.c", "r");
	if (!template){
		printf("ERROR: could not read file template.c\n");
		exit(EXIT_FAILURE);
	}
	char template_ch;
	while ((template_ch = fgetc(template)) != EOF){
		putc(template_ch, c_file);
	}
	fclose(template);
	fprintf(c_file, "\n\nint main(){\n");
	c_print_declarations(program.declarations);
	if (program.declarations != NULL){
		fprintf(c_file, "\n");
	}
	c_print_statements(program.statements, 1);
	fprintf(c_file, "\n\tprintf(\"\\n\");\n\treturn 0;\n}\n");
}


char *type_to_c_string(var_type type){
	switch (type){
		case int_type:
			return "int";
		case float_type:
			return "float";
		case string_type:
			return "char *";
		default:
			// this should never happen
			printf("Invalid type\n");
			exit(EXIT_FAILURE);
			return NULL;
	}
}