#include "list.h"
#include <cstdio>
#include <cstdlib>

void listCtor(struct List* list, int size)
{
    list->capacity = size;
    list->data     = (int*)calloc((size + 1)*3, sizeof(int));
    list->head     = list->data;
    list->tail     = list->data;
    list->next     = list->data + size + 1;
    list->prev     = list->next + size + 1;
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
	else if (list->el_amount >= list->capacity)
	{
		printf("Buffer is over, need reallocation first\n");
	}
	else
	{
		printf("Your list is smaller than %d, cannot put element %d\n", num, element);
	}
	#ifdef DEBUG
		enum LIST_STATUS status = listVerify(list);
		if (status != LIST_IS_OK)
		{
			printf("ERROR %d occured while inserting element %d on the place after %dth\n", status, element, num);
		}
	#endif
}

void listDelete(struct List* list, int num)
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
	list->el_amount--;
	#ifdef DEBUG
		enum LIST_STATUS status = listVerify(list);
		if (status != LIST_IS_OK)
		{
			printf("ERROR %d occured while deleting element on the place after %dth\n", status, num);
		}
	#endif
}

void listResize(struct List* list, int new_capacity)
{
	listCompact(list);
	int head_place = list->head - list->data;
	int tail_place = list->tail - list->data;
	int free_place = 0;
	if (list->free != NULL)
		free_place = list->free - list->next;
	int* tmp       = list->data;
	if (new_capacity > list->capacity)
	{
		list->data = (int*)calloc((new_capacity + 1) * 3, sizeof(int));
		for (int i = 0; i <= list->capacity; i++)
		{
			list->data[i] = tmp[i];
		}
		for (int i = list->capacity + 1; i <= new_capacity; i++)
		{
			list->data[i] = 0;
		}
		for (int i = 0; i < list->capacity; i++)
		{
			list->data[i + new_capacity + 1] = tmp[i + list->capacity + 1];
		}
		for (int i = list->capacity; i < new_capacity; i++)
		{
			list->data[i + new_capacity + 1] = i + 1;
		}
		list->data[new_capacity] = 0;
		for (int i = 0; i <= list->capacity; i++)
		{
			list->data[i + 2*(new_capacity + 1)] = tmp[i + 2*(list->capacity + 1)];
		}
		for (int i = list->capacity + 1; i <= new_capacity; i++)
		{
			list->data[i + 2*(new_capacity)] = -1;
		}
	}
	else if (new_capacity < list->capacity && new_capacity >= list->el_amount)
	{
		list->data = (int*)calloc((new_capacity + 1) * 3, sizeof(int));
		int frees = new_capacity - list->el_amount;
		int i = 0;
		for (i = 0; i <= list->el_amount; i++)
		{
			list->data[i] = tmp[i];
		}
		for (i = 0; i < frees; i++)
		{
			list->data[i + list->el_amount + 1] = 0;
		}
		for (i = 0; i <= list->el_amount; i++)
		{
			list->data[i + new_capacity + 1] = list->next[i];
		}
		for (i = 0; i <= frees - 1; i++)
		{
			list->data[i + 2 + list->el_amount + new_capacity] = list->el_amount + i + 2;
		}
		list->data[frees + list->el_amount + new_capacity + 1] = 0;
		for (i = 0; i <= list->el_amount; i++)
		{
			list->data[i + 2 * (new_capacity + 1)] = list->prev[i];
		}
		for (i = 0; i < frees; i++)
		{
			list->data[i + 2 * (new_capacity + 1) + list->el_amount + 1] = -1;
		}
	}
	else 
	{
		puts("Invalid capacity");
		return;
	}
	list->next = list->data + new_capacity + 1;
	list->prev = list->next + new_capacity + 1;
	list->head = list->data + head_place;
	list->tail = list->data + tail_place;
	list->free = list->next + free_place;
	free(tmp);
	list->capacity = new_capacity;
	#ifdef DEBUG
		enum LIST_STATUS status = listVerify(list);
		if (status != LIST_IS_OK)
		{
			printf("ERROR %d occured while resizing list\n", status);
		}
	#endif
}

void listCompact(struct List* list)
{
	int need_compact = 0;
	for (int i = 1; i <= list->el_amount; i ++)
	{
		if (list->data[i] == 0)
		{
			need_compact = 1;
			break;
		}
	}
	if (need_compact == 1)
	{
		int head_place = list->head - list->data;
		int tail_place = list->tail - list->data;
		int free_place = list->free - list->next;
		for (int i = 1; i < list->capacity; i++)
		{
			int j = i;
			while (list->data[i] == 0)
			{
				list->data[i] = list->data[j+1];
				list->next[i] = list->next[j+1];
				list->prev[i] = list->prev[j+1];
				list->data[j+1] = 0;
				j++;
				if (i + 1 == head_place)
					list->head ++;
				else if (i + 1 == tail_place)
					list->tail ++;
				list->capacity --;
			}
			if (i > 1 && list->data[i - 1] == 0)
			{
				i--;
			}
		}
	}
}

enum LIST_STATUS listVerify(struct List* list)
{
	int place = list->head - list->data;
	if (list->prev[place] != 0)
	{
		listDump(list);
		return FIRST_EL_ERROR;
	}
		
	for (int i = 1; i < list->el_amount; i ++)
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

void listDump(struct List* list)
{
	FILE* fin = fopen("list.txt", "w");
    setbuf(fin, NULL);
	fprintf(fin, "digraph list{\n");
	fprintf(fin, "	rankdir = TB\n");
	for (int i = 1; i <= list->capacity; i+=2)
	{	
		fprintf(fin, "	%d [shape = \"rectangle\", style = \"rounded\", label =\" %d | %d | %d\"]\n", 
					     i - 1, list->data[i-1], list->next[i-1], list->prev[i-1]);
		fprintf(fin, "	%d [shape = \"rectangle\", style = \"rounded\", label =\" %d | %d | %d\"]\n", 
		                 i, list->data[i], list->next[i], list->prev[i]);
	}
	if (list->capacity % 2 == 0)
	{
		fprintf(fin, "	%d [shape = \"rectangle\", style = \"rounded\", label =\" %d | %d | %d\"]\n", 
			             list->capacity, list->data[list->capacity], list->next[list->capacity], list->prev[list->capacity]);
	}
	int i = 0;
	fprintf(fin, "	%d -> ", i);
	for (int i = 1; i < list->capacity; i++)
	{
		fprintf(fin, "%d -> ", i);
	}
	fprintf(fin, "%d\n", list->capacity);
	fprintf(fin, "}");
	fflush(fin);
	fclose(fin);
}
