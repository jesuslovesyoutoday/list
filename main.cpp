#include "list.h"
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
    struct List list;
    listCtor(&list, 10);
    listInsert(&list, 0, 10);
    listInsert(&list, 1, 20);
    listInsert(&list, 2, 30);
    listInsert(&list, 3, 40);
    listInsert(&list, 4, 50);
    listInsert(&list, 5, 60);
    listInsert(&list, 6, 70);
    listInsert(&list, 7, 80);
    listInsert(&list, 4, 45);
 	
 	listPrint(&list);
	listDelete(&list, 0);

	listPrint(&list);
	listDelete(&list, 7);

	listPrint(&list);
	listDelete(&list, 4);
	listPrint(&list);
	
    listDtor(&list);
}
