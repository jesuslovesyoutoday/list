#ifndef LIST_H
#define LIST_H

struct List {
	int* data;     // pointer to the beginning of the buffer
    int* head;     // pointer to the first element of list
    int* tail;     // pointer to the last element of list
    int* next;     // pointer to the array storing the
    		       // next physical number for each element
    int* prev;     // pointer to the array storing the 
    		       // previous physical number
    int* free;     // pointer to the "list" of free elements
    int capacity;  // size of buffer
    int el_amount; // amount of elements in list
};

//-------------------------------------------
//!
//! List constructor
//!
//! @param[out] list - pointer to the list
//! @param[in]  size - size of list buffer
//!
//! @note physical size of buffer is size + 1
//!       to store 0 element
//!
//-------------------------------------------

void listCtor(struct List* list, int size);

//-------------------------------------------
//!
//! List destructor
//!
//! @param[out] list - pointer to the list
//!
//-------------------------------------------

void listDtor(struct List* list);

//-------------------------------------
//!
//! Insert element to the list AFTER the
//! given place
//!
//! @param[in] num     - where to insert
//! @param[in] element - what to insert
//!
//! @note munbering starts from 1
//!
//-------------------------------------

void listInsert(struct List* list, int num, int element);

#endif // LIST_H
