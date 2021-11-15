#include "list2.h"
#include "unit_test.h"
#include <stdio.h>

void listPrint(struct List* list)
{
	puts("-------------------");
	puts("num data next prev");
	puts("-------------------");
	for (int i = 0; i <= list->capacity; i ++)
    {
    	printf("[%d] [%d] [%d] [%d]\n", i, list->data[i].element, list->data[i].next, list->data[i].prev);
	}
}

int main()
{
	unitTest();
}
