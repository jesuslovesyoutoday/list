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
	enum LIST_STATUS status = listVerify(list);
	if (status == LIST_IS_OK)
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
		else if (list->el_amount >= list->capacity)
		{
			printf("Buffer is over, need reallocation first\n");
		}
		else
		{
			printf("Your list is smaller than %d, cannot put element %d\n", num, element);
		}
	}
	else
	{
		printf("ERROR %d\n occured while inserting element %d on the place after %dth\n", status, element, num);
	}
}

void listDelete(struct List* list, int num)
{
	enum LIST_STATUS status = listVerify(list);
	if (status == LIST_IS_OK)
	{
		if (list->data + num + 1 == list->head)
		{
			*(list->head)     = 0;
			int place         = list->head - list->data;
			int temp          = list->next[place];
			list->next[place] = list->free - list->next;
			list->prev[place] = -1;
			list->free        = list->next + place;
			list->head        = list->data + temp;
			list->prev[temp]  = 0;
		}
		else if (list->data + num + 1 == list->tail)
		{
			*(list->tail) = 0;
			int place         = list->tail - list->data;
			int temp          = list->prev[place];
			list->prev[place] = -1;
			list->next[place] = list->free - list->next;
			list->free = list->next + place;
			list->tail = list->data + temp;
			list->next[temp]  = 0; 
		}
		else
		{
			list->data[num + 1] = 0;
			list->next[list->prev[num + 1]] = list->next[num + 1];
			list->prev[list->next[num + 1]] = list->prev[num + 1];
			list->next[num + 1]             = list->free - list->next;
			list->free                      = list->next + num + 1;
			list->prev[num + 1]             = -1; 
		}
	}
	else
	{
		printf("ERROR %d\n occured while deleting element on the place after %dth\n", status, num);
	}
}

enum LIST_STATUS listVerify(struct List* list)
{
	int place = list->head - list->data;
	if (list->prev[place] != 0)
		return FIRST_EL_ERROR;
		
	for (int i = 0; i < list->el_amount; i ++)
	{
		if (list->data[place] != 0)
		{
			if (place == list->tail - list->data && list->next[place] != 0)
				return LAST_EL_ERROR;
			else if (list->next[place] != 0)	
			{
				int next = list->next[place];
				int prev = list->prev[next];
				if (prev != place)
					return NEXT_PREV_ERROR;
			}
		}
		else 
		{
			if (list->prev[place] != -1)
				return FREE_EL_PREV_ERROR;
		}
		place ++;
	}
	return LIST_IS_OK;
}
