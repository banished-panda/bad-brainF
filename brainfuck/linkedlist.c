#include "linkedlist.h"
#include <stdlib.h>

/*Parser progresssively stores [ ] pair locations
  when it finds new ones*/

typedef struct NODE {
	/*position of '['*/
	int open;
	/*position of ']'*/
	int close;

	struct NODE* link;
} NODE;

/*
                            temp
                             |
      X -- [] -- [] -- [] -- [] -- [] -- X
	       |                       |
          start                   end

		  start -> locates the List in the memory
		  end   -> serves to add new NODE
		  temp  -> serves for searching (+other purpose)

*/

static NODE* temp;
static NODE* start;
static NODE* end;

int initList(void)
{
	temp = start = end = 0;
	return 0;
}

int addPair(int openIndex, int closeIndex)
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	if (!tmp)
		return 1;
	tmp->close = closeIndex;
	tmp->open = openIndex;
	tmp->link = 0;

	if (!start) {
		start = end = temp = tmp;
		return 0;
	}

	end->link = tmp;
	end = tmp;

	return 0;
}

int searchOpenIndex(int closeIndex)
{
	if (!start)
		return -99;
	temp = start;
	do{
		if (temp->close == closeIndex)
			return temp->open;
		temp = temp->link;
	}
	while (temp != end->link);
	return -1;
}

int searchCloseIndex(int openIndex)
{
	if (!start)
		return -99;
	temp = start;
	do {
		if (temp->open == openIndex)
			return temp->close;
		temp = temp->link;
	} while (temp != end->link);
	return -1;
}

int deleteList()
{
	if (!start)
		return 0;
	if (start == end)
	{
		free(start);
		temp = start = end = 0;
		return 0;
	}

	while (start != end) {
		temp = start->link;
		free(start);
		start = temp;
	}
	deleteList();	/*this should call the if(start==end) clause*/
	return 0;
}
