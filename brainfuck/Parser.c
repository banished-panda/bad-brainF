#include "parser.h"
#include "util.h"
#include "linkedlist.h"
#include "stack.h"
#include <stdio.h>

void testStack();
void testList();

PCODE parse_program()
{
	/*printf("Program: %s\n",program);*/
	/*
	* TODO:
	* Add support for reporting line numbers in errors
	*/

	initList();
	initStack();
	int i;
	for (i = 0; i < strlen(program); i++)
	{
		char ch = *(program+i);
		if (ch == '[')
			push(i);
		if (ch == ']')
		{
			int returned = pop();
			if (returned == -1)
			{
				/*There isn't a '[' for this ']'*/
				printf("Excess ']' at location: %d\n",i);
				deleteStack();
				return FALIURE;
			}
			addPair(returned,i);
		}
	}
	int returned = pop();
	if (returned != -1)
	{
		printf("Excess '[' at location: %d\n", returned);
		deleteStack();
		return FALIURE;
	}
	deleteStack();
	return SUCCESS;
}

void testStack()
{
	printf("Testing Stack...\n");
	initStack();
	push(1);
	push(2);
	push(3);
	push(4);
	printf("%d\n",pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
	printf("%d\n", pop());
}

void testList()
{
	initList();
	addPair(0,1);
	addPair(2,3);
	addPair(4,5);
	printf("%d\n",searchCloseIndex(0));
	printf("%d\n", searchCloseIndex(2));
	printf("%d\n", searchCloseIndex(99));
	printf("%d\n", searchOpenIndex(1));
	printf("%d\n", searchOpenIndex(3));
	printf("%d\n", searchOpenIndex(7));
	deleteList();
	printf("%d\n", searchCloseIndex(0));
	printf("%d\n", searchCloseIndex(2));
	printf("%d\n", searchCloseIndex(4));
	printf("%d\n", searchOpenIndex(1));
	printf("%d\n", searchOpenIndex(3));
	printf("%d\n", searchOpenIndex(5));
}
