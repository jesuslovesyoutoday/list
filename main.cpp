#include "list.h"
#include "unit_test.h"
#include <stdio.h>

void listPrint(struct List* list)
{
	puts("-------------------");
	puts("num data next prev");
	puts("-------------------");
	for (int i = 0; i <= list->capacity; i ++)
    {
    	printf("[%d] [%d] [%d] [%d]\n", i, list->data[i], list->next[i], list->prev[i]);
	}
}

int main()
{
	unitTest();
}
