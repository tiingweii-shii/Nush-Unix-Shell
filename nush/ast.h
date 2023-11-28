// Attribution: This code is from professor Tuck's lecture CS3650 05 04 caculator code
#ifndef AST_H
#define AST_H

#include "seq.h"

typedef struct ast {
	char* op;
	seq* value;
	struct ast* arg1;
	struct ast* arg2;
} ast;

ast* make_ast_cmd(seq* cmd);
ast* make_ast_op(char* op, ast* arg1, ast* arg2);
void free_ast(ast* ast);
//void ast_eval(ast* ast);
void print_ast(ast* ast);

#endif
