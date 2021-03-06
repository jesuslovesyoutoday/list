#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <list>
#include <stdio.h>

static int listCmp(struct List* list1, struct List* list2)
{
	if(list1->capacity != list2->capacity || 
	   list1->el_amount != list2->el_amount)
		return 1;
	for (int i = 0; i <= list1->capacity; i++)
	{
		if (list1->data[i].element != list2->data[i].element || 
		    list1->data[i].next != list2->data[i].next || 
		    list1->data[i].prev != list2->data[i].prev)
		    return 1;
	}
	return 0; 
}

void unitTest()
{

//-----------------------INIT--------------------------//

	struct List list1;
	listCtor(&list1, 15);
	
	struct List list2;
	listCtor(&list2, 15);

	for (int i = 1; i <= 10; i++)
	{
		listInsert(&list1, i-1, i);
		listInsert(&list2, i-1, i);
	}
	
//------------------DELETE-INSERT---------------------//	
	
	listDelete(&list2, 5);
	listInsert(&list2, 5, list1.data[6].element);
	listDelete(&list2, 0);
	listInsert(&list2, 0, list1.data[1].element);
	listDelete(&list2, list2.el_amount - 1);
	listInsert(&list2, list2.el_amount, 
	           list1.data[list1.el_amount].element);
	
	if (listCmp(&list1, &list2) == 0)
	{
		puts("=========================");	
		puts("Delete-insert test passed");
		puts("=========================");
	}
	else
	{
		puts("=========================");	
		puts("Delete-insert test failed");
		puts("=========================");
		listDump(&list2);
	}

//----------------------RESIZE-------------------------//
	
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
		puts("   Resize test failed");
		puts("=========================");
		listDump(&list2);
	}
	
//-------------------PHY_BY_LOG-----------------------//

	listDelete(&list2, 5);
	if (listPhyByLog(&list2, 6) == 7)
	{
		puts("=========================");	
		puts(" Phy_by_log test passed");
		puts("=========================");
	}
	else
	{
		puts("=========================");	
		puts(" Phy_by_log test failed");
		puts("=========================");
	}
	
//--------------------LINEARIZING---------------------//

	listDelete(&list1, 3);
	listInsert(&list1, 2, 45);
	listInsert(&list1, 1, 58);
	listDump(&list1);
	listLinearize(&list1);
	listDump(&list1);
	
//-----------------------DTORS------------------------//	
	
	listDtor(&list1);
	listDtor(&list2);
	
}

#endif // UNIT_TEST_H
