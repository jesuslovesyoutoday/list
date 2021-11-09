#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <list>
#include <stdio.h>

static int listCmp(struct List* list1, struct List* list2)
{
	if(list1->capacity != list2->capacity || list1->el_amount != list2->el_amount)
		return 1;
	for (int i = 0; i <= list1->capacity; i++)
	{
		if (list1->data[i] != list2->data[i] || list1->next[i] != list2->next[i] || 
		    list1->prev[i] != list2->prev[i])
		    return 1;
	}
	return 0; 
}

void unitTest()
{
	struct List list1;
	listCtor(&list1, 15);
	
	struct List list2;
	listCtor(&list2, 15);

	for (int i = 1; i <= 10; i++)
	{
		listInsert(&list1, i-1, i);
		listInsert(&list2, i-1, i);
	}
	
	listDelete(&list2, 5);
	listInsert(&list2, 5, list1.data[6]);
	listDelete(&list2, 0);
	listInsert(&list2, 0, list1.data[1]);
	listDelete(&list2, list2.el_amount - 1);
	listInsert(&list2, list2.el_amount, list1.data[list1.el_amount]);
	
	if (listCmp(&list1, &list2) == 0)
	{
		puts("=========================");	
		puts("Delete-insert test passed");
		puts("=========================");
	}
	else
	{
		puts("=========================");	
		puts("      Test failed");
		puts("=========================");
		listDump(&list2);
	}
	
	listResize(&list2, 20);
	listResize(&list2, 15);
	
	if (listCmp(&list1, &list2) == 0)
	{
		puts("=========================");	
		puts("   Resize test passed");
		puts("=========================");
	}
	else
	{
		puts("=========================");	
		puts("      Test failed");
		puts("=========================");
		listDump(&list2);
	}
	listDtor(&list1);
	listDtor(&list2);
	
}

#endif // UNIT_TEST_H
