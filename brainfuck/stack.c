#include "stack.h"
#include <stdlib.h>

typedef struct stackNode {
	int n;
	struct stackNode* prev;
} stackNode;

static stackNode* start;
static stackNode* top;

int initStack()
{
	start = top = 0;
	return 0;
}

int push(int n)
{
	stackNode* tmp = (stackNode*)malloc(sizeof(stackNode));
	if (!tmp)
		return 1;
	tmp->n = n;
	tmp->prev = 0;
	if (!start) {
		start = top = tmp;
		return 0;
	}

	tmp->prev = top;
	top = tmp;
	return 0;
}

int pop()
{
	/*
	In the context where the stack is being used, -1 is not
	a value that can be added to the stack.
	We therefore use -1 to indicate underflow
	*/
	if (!top)
		return -1;

	if (top == start) {
		int result = top->n;
		free(start);
		top = start = 0;
		return result;
	}
	
	int result = top->n;
	stackNode* tmp = top->prev;
	free(top);
	top = tmp;

	return result;
}

int deleteStack()
{
	while (pop() != -1);
	return 0;
}
