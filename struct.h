#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SYMBOL_SIZE 8

typedef struct node_t
{
	void* data;
	struct node_t *next, *prev;
} node_t;

typedef struct ll_t
{
	node_t *head;
	int data_size;
	int size;
} ll_t;

typedef struct card_t
{
	int value;
	char symbol[MAX_SYMBOL_SIZE];
} card_t;

#endif  //  _STRUCT_H_
