#include "list.h"
#include <stdio.h>

int main()
{
    struct List list;
    listCtor(&list, 6);
    listInsert(&list, 0, 10);
    listInsert(&list, 1, 20);
    listInsert(&list, 0, 5);
    listInsert(&list, 3, 30);
    listInsert(&list, 1, 15);
    listInsert(&list, 2, 16);
    listInsert(&list, 3, 17);
    listInsert(&list, 4, 18);
    for (int i = 0; i <= list.capacity; i ++)
    {
    	printf("[%d] [%d] [%d] [%d]\n", i, list.data[i], list.next[i], list.prev[i]);
	}
    listDtor(&list);
}
