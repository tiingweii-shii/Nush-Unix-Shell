// Attribution: This code is taken (modified) from professor Tuck's lecture
// AST functions taken from cs3650 Fall 2020 video lecture
// Author: Nat Tuck
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"

ast*
make_ast_cmd(seq* cmd)
{
	ast* a = malloc(sizeof(ast));
	a->op = 0;
	a->value = cmd;
	a->arg1 = 0;
	a->arg2 = 0;
	return a;
}

ast*
make_ast_op(char* op, ast* arg1, ast* arg2)
{
	ast* a = malloc(sizeof(ast));
	a->op = strdup(op);
	a->value = 0;
	a->arg1 = arg1;
	a->arg2 = arg2;
	return a;
}

void
free_ast(ast* ast) 
{
	if (ast) {
		free(ast->op);
		free_seq(ast->value);
		free_ast(ast->arg1);
		free_ast(ast->arg2);
		free(ast);
	}
}

char*
ast_string(ast* ast)
{	
	if (ast->op == 0) {
		char* tmp = malloc(128);
		seq* xs = ast->value;
		seq* cp = xs;
		int len = 0;
		for (; cp; cp = cp->rest) {
			len += sprintf(tmp + len, "%s ", cp->first);
		}
		free_seq(cp);
		return tmp;
	} else {
		char* aa = ast_string(ast->arg1);
		char* bb = ast_string(ast->arg2);
		char* cc = malloc(128);
		sprintf(cc, "(arg1: %s, op: %s, arg2: %s)", aa, ast->op, bb);
		free(aa);
		free(bb);
		return cc;
	}
}


void
print_ast(ast* ast)
{
	char* text = ast_string(ast);
	printf("%s\n", text);
	free(text);
}

