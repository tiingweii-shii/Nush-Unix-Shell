// Attribution: This code is taken (modified) from professor Tuck's lecture cs3650 05 05 calc code
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

int
streq(const char* aa, const char* bb)
{
	return strcmp(aa, bb) == 0;

}

int
first_index(seq* tokens, const char* tt)
{
	int ii = 0;
	seq* it = tokens;
	for (; it; it = it->rest) {
		if (streq(it->first, tt)) {
			return ii;
		}
		ii++;
	}
	return -1;
}

seq*
slice(seq* xs, int i0, int i1)
{
	seq* ys = 0;
	seq* it = xs;
	for (int ii = 0; ii < i0; ++ii) {
		it = it->rest;
	}
	for (int ii = i0; ii < i1; ++ii) {
		ys = cons(it->first, ys);
		it = it->rest;
	}
	return reverse(ys);
}

int
contains(seq* tokens, const char* tt)
{
	return first_index(tokens, tt) >= 0;
}


ast*
parse(seq* tokens)
{
	char* ops[] = {";", "&&", "||", "|"};

	for (int ii = 0; ii < 4; ii++) {
		char* op = ops[ii];
		if (contains(tokens, op)) {
				int jj = first_index(tokens, op);
				seq* xs = slice(tokens, 0, jj);
				seq* ys = slice(tokens, jj + 1, length(tokens));
				ast* ast = make_ast_op(op, parse(xs), parse(ys));
				return ast; 
		}
	}

	ast* ast = make_ast_cmd(tokens);
	return ast;  	
}
