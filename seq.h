// Seq (Linked lists) structure taken from cs3650 Fall 2020 video lecture 4
// Author: Nat Tuck
#ifndef SEQ_H
#define SEQ_H

typedef struct seq {
	char* first;
	struct seq* rest;
} seq;

seq* cons(char* first, seq* rest);
void free_seq(seq* xs);
void print_seq(seq* xs);
int length(seq* xs);
seq* reverse(seq* xs);

#endif

