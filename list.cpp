#include "list.h"
#include <cstdio>
#include <cstdlib>

void listCtor(struct List* list, int size)
{
    list->data = (struct listElement*)calloc(size + 1, 
           sizeof(struct listElement));
    list->data[0].element = 0;
    list->data[0].next    = 0;
    list->data[0].prev    = 0;
    for (int i = 1; i < size; i++)
    {
    	list->data[i].element = 0;
    	list->data[i].next    = i + 1;
    	list->data[i].prev    = -1;
    }
    list->data[size].element = 0;
    list->data[size].next    = 0;
    list->data[size].prev    = -1;
    list->capacity  = size;
    list->el_amount = 0;
    list->head = list->data;
    list->tail = list->data;
    list->free = list->data + 1;
}

void listDtor(struct List* list)
{
    free(list->data);
    list->capacity = 0;
    list->head = NULL;
    list->tail = NULL;
    list->free = NULL;
}

void listInsert(struct List* list, int num, int element)
{
	int place = list->free - list->data;
	if(num <= list->el_amount && list->el_amount < list->capacity)
	{
		list->data[place].element = element;
		struct listElement temp = *(list->free);
		if (num == 0)
		{
			if (list->el_amount == 0)
			{
				list->tail = list->data + place;
				list->free->next = 0;
			}
			else
			{
				int next = list->head - list->data;
				list->free->next = next;
				list->data[next].prev = place;
			}
			list->head = list->data + place;
			list->free += temp.next - place;
			list->data[place].prev = 0;
		}
		else if (num == list->el_amount)
		{
			list->free->next = 0;
			int prev = list->tail - list->data;
			list->data[place].prev = prev;
			list->data[prev].next = place;
			list->tail = list->data + place;
			list->free += temp.next - place;
		}
		else
		{
			int prev = num;
			int next = list->data[prev].next;
			list->free->next = next;
			list->free += temp.next - place;
			list->data[place].prev = prev;
			list->data[prev].next  = place;
			list->data[next].prev  = place;  	
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
	list->head->element     = 0;
	int place         = list->head - list->data;
	int temp          = list->data[place].next;
	list->data[place].next = list->free - list->data;
	list->data[place].prev = -1;
	list->free        = list->data + place;
	list->head        = list->data + temp;
	list->data[temp].prev  = 0;
	}
	else if (list->data + num + 1 == list->tail)
	{
		list->tail->element = 0;
		int place         = list->tail - list->data;
		int temp = list->data[place].prev;
		list->data[place].prev = -1;
		list->data[place].next = list->free - list->data;
		list->free = list->data + place;
		list->tail = list->data + temp;
		list->data[temp].next  = 0; 
	}
	else
	{
		list->data[num + 1].element = 0;
		list->data[list->data[num + 1].prev].next = list->data[num + 1].next;
		list->data[list->data[num + 1].next].prev = list->data[num + 1].prev;
		list->data[num + 1].next                  = list->free - list->data;
		list->free                                = list->data + num + 1;
		list->data[num + 1].prev                  = -1; 
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
	
	if (new_capacity > list->capacity)
	{
		list->data = (struct listElement*)realloc(list->data, 
		((new_capacity + 1) * 3) * sizeof(struct listElement));
		
		for (int i = list->capacity + 1; i < new_capacity; i++)
		{
			list->data[i].element = 0;
			list->data[i].next    = i + 1;
			list->data[i].prev    = -1;
		}
		list->data[new_capacity].element = 0;
		list->data[new_capacity].next    = 0;
		list->data[new_capacity].prev    = -1;
	}
	else if (new_capacity < list->capacity);
	else 
	{
		puts("Invalid capacity");
		return;
	}
	list->head = list->data + head_place;
	list->tail = list->data + tail_place;
	list->free = list->tail + 1;
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
		if (list->data[i].element == 0)
		{
			need_compact = 1;
			break;
		}
	}
	if (need_compact == 1)
	{
		int head_place = list->head - list->data;
		int tail_place = list->tail - list->data;
		int free_place = list->free - list->data;
		for (int i = 1; i <= list->el_amount; i++)
		{
			int j = i;
			while (list->data[i].element == 0)
			{
				list->data[i].element = list->data[j+1].element;
				list->data[i].next = list->data[j+1].next;
				list->data[i].prev = list->data[j+1].prev;
				list->data[j+1].element = 0;
				if (j != 1)
					list->data[j-1].next = j;
				j++;
				if (i + 1 == head_place)
					list->head ++;
				else if (i + 1 == tail_place)
					list->tail ++;
				list->capacity --;
			}
		}
		list->free = NULL;
		list->capacity = list->el_amount;
	}
	#ifdef DEBUG
		enum LIST_STATUS status = listVerify(list);
		if (status != LIST_IS_OK)
		{
			printf("ERROR %d occured while compacting list\n", status);
		}
	#endif
}

int listPhyByLog(struct List* list, int log)
{
	int tmp = 0;
	for (int i = 1; i < log; i++)
	{
		tmp = list->data[i].next;
	}
	return tmp;
}

enum LIST_STATUS listVerify(struct List* list)
{
	int place = list->head - list->data;
	if (list->data[place].prev != 0)
	{
		listDump(list);
		return FIRST_EL_ERROR;
	}
		
	for (int i = 1; i < list->el_amount; i ++)
	{
		if (list->data[place].element != 0)
		{
			if (place == list->tail - list->data && list->data[place].next != 0)
				return LAST_EL_ERROR;
			else if (list->data[place].next != 0)	
			{
				int next = list->data[place].next;
				int prev = list->data[next].prev;
				if (prev != place)
					return NEXT_PREV_ERROR;
			}
		}
		else 
		{
			if (list->data[place].prev != -1)
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
					     i - 1, list->data[i-1].element, list->data[i-1].next, list->data[i-1].prev);
		fprintf(fin, "	%d [shape = \"rectangle\", style = \"rounded\", label =\" %d | %d | %d\"]\n", 
		                 i, list->data[i].element, list->data[i].next, list->data[i].prev);
	}
	if (list->capacity % 2 == 0)
	{
		fprintf(fin, "	%d [shape = \"rectangle\", style = \"rounded\", label =\" %d | %d | %d\"]\n", 
			             list->capacity, list->data[list->capacity].element, list->data[list->capacity].next, 
			             list->data[list->capacity].prev);
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
