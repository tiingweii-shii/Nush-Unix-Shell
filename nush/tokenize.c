// Attribution: tokenize function taken from Professor Tuck's lecture on calc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tokenize.h"

char OPS[5] = {'<', '>', '|', '&', ';'};

int
isop(char c)
{
	for (int ii = 0; ii < 5; ii++) {
		if (c == OPS[ii]) {
			return 1;
		}
	}
	return 0;
}

char*
read_tok(const char* text, int ii)
{
	int nn = 0;

	// stop when hit space or operator
	while (!isspace(text[ii + nn]) &&  isop(text[ii + nn]) == 0) {
		++nn;
	}

	char* tok = calloc(nn + 1, sizeof(char));
	memcpy(tok, text + ii, nn);
	tok[nn] = 0;
	return tok;
}

char*
read_op(const char* text, int ii)
{
	if (text[ii] == '&' || text[ii] == '|') {
		if (text[ii + 1] == text[ii]) {
			char* op = calloc(3, sizeof(char));
			memcpy(op, text + ii, 2);
			op[2] = 0;
			return op;
		}
	}

	char* op = calloc(2, sizeof(char));
	memcpy(op, text + ii, 1);
	op[1] = 0;
	return op;
}

seq*
tokenize(const char* text)
{
	seq* xs = 0;
	char* op;
	char* tok;

	int nn = strlen(text);
	int ii = 0;

	while ( ii < nn ) {
		if (isspace(text[ii])) {
			ii++;
		} else if (isop(text[ii])) {
			op = read_op(text, ii);
			xs = cons(op, xs);
			ii += strlen(op);
			free(op);
		} else {
			tok = read_tok(text, ii);
			xs = cons(tok, xs);
			ii += strlen(tok);
			free(tok);
		}
	}
	
	return reverse(xs);
}
