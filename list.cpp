#include "list.h"
#include <stdio.h>
#include <cstdlib>

void listCtor(struct List* list, int size)
{
    list->capacity = size;
    list->data     = (int*)calloc(size + 1, sizeof(int));
    list->head     = list->data;
    list->tail     = list->data;
    list->next     = (int*)calloc(size + 1, sizeof(int));
    list->prev     = (int*)calloc(size + 1, sizeof(int));
    list->free     = list->next + 1;
    for (int i = 1; i < size; i++)
    {
    	list->next[i] = i + 1;
    }
    for (int i = 1; i <= size; i++)
    {
    	list->prev[i] = - 1;
    }
    list->el_amount = 0;
}

void listDtor(struct List* list)
{
    free(list->data);
    free(list->next);
    free(list->prev);
    list->capacity = 0;
}

void listInsert(struct List* list, int num, int element)
{
	int place = list->free - list->next;
	if(num <= list->el_amount && list->el_amount < list->capacity)
	{
		list->data[place] = element;
		int temp = *(list->free);
		if (num == 0)
		{
			if (list->el_amount == 0)
			{
				list->tail = list->data + place;
				*(list->free) = 0;
			}
			else
			{
				int next = list->head - list->data;
				*(list->free) = next;
				list->prev[next] = place;
			}
			list->head = list->data + place;
			list->free += temp - place;
			list->prev[place] = 0;
		}
		else if (num == list->el_amount)
		{
			*(list->free) = 0;
			int prev = list->tail - list->data;
			list->prev[place] = prev;
			list->next[prev] = place;
			list->tail = list->data + place;
			list->free += temp - place;
		}
		else
		{
			int prev = num;
			int next = list->next[prev];
			*(list->free) = next;
			list->free += temp - place;
			list->prev[place] = prev;
			list->next[prev]  = place;
			list->prev[next]  = place;  
		}
		list->el_amount ++;
		
	}
	else if (list->el_amount == list->capacity)
	{
		printf("Buffer is over, need reallocation first\n");
	}
	else
	{
		printf("Your list is smaller than %d, cannot put element %d\n", num, element);
	}
}
