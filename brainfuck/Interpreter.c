#include "interpreter.h"
#include "util.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void init();
static void deleteMEM();
static char* memory;
static int ptr;

int interpret()
{
	init();
	/*
	* intepret here
	*/
	int i = 0;		/*program pointer*/
	int program_length = strlen(program);
	char OP;		/*current instruction/operatoin */
	while (i < program_length) {
		OP = *(program + i);
		switch (OP)
		{
		case '+':
			memory[ptr]++;
			i++;
			break;

		case '-':
			memory[ptr]--;
			i++;
			break;

		case '>':
			if (ptr < MEM_SIZE - 1)
				ptr++;
			i++;
			break;

		case '<':
			if (ptr >= 1)
				ptr--;
			i++;
			break;

		case '.':
			putchar(memory[ptr]);
			i++;
			break;

		case ',':
			memory[ptr] = getchar();
			i++;
			break;

		case '[':
			if (memory[ptr] == 0)
				i = searchCloseIndex(i);
			i++;
			break;
		case ']':
			if (memory[ptr] != 0)
				i = searchOpenIndex(i);
			i++;
			break;
		default:
			i++;
		}
	}

	deleteMEM();
	return 0;
}

static void init() {
	if (!MEM_SIZE)
		MEM_SIZE = 30000;
	memory =(char*) calloc(MEM_SIZE + 32, 1);
	ptr = 0;
}

void deleteMEM() {
	free(memory);
}
