// Seq (Linked lists) functions taken/modified from cs3650 Fall 2020 video lecture 4
// Author: Nat Tuck

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "seq.h"

seq* cons(char* first, seq* rest)
{
	seq* xs = malloc(sizeof(seq));
	xs->first = strdup(first);
	xs->rest = rest;
	return xs;
}

void free_seq(seq* xs)
{
	if (xs) {
		free_seq(xs->rest);
		free(xs->first);
		free(xs);
	}
}

void print_seq(seq* xs)
{
	seq* ys = xs;
	for (; ys; ys = ys->rest) {
		printf("%s\n", ys->first);
	}
	free_seq(ys);
}

int length(seq* xs)
{
	int nn = 0;
	seq* ys = xs;
	for (; ys; ys = ys->rest) {
		nn++;
	}
	free_seq(ys);
	return nn;
}


seq* reverse(seq* xs)
{
	seq* ys = 0;
	seq* cop = xs;
	for (; xs; xs = xs->rest) {
		ys = cons(xs->first, ys);
	}

	free_seq(xs);
	free_seq(cop);
	return ys;
}
