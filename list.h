#ifndef LIST_H
#define LIST_H

#define DEBUG

struct listElement {
	int element;              //< element of list
	int next;                 //< element after this
	int prev;                 //< element before this
};

struct List {
	struct listElement* data; //< pointer to the struct array
	int capacity;             //< size of list buffer
	int el_amount;            //< amount of element
	listElement* head;        //< pointer to the first element of list
    listElement* tail;        //< pointer to the last element of list
    listElement* free;        //< pointer to the "list" of free elements
};

enum LIST_STATUS {
	LIST_IS_OK         = 0,
	NEXT_PREV_ERROR    = 1,
	FREE_EL_PREV_ERROR = 2,
	FIRST_EL_ERROR     = 3,
	LAST_EL_ERROR      = 4
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

//-------------------------------------------
//!
//! Insert element to the list AFTER the
//! given place
//!
//! @param[out] list    - pointer to list
//! @param[in]  num     - where to insert
//! @param[in]  element - what to insert
//!
//! @note numbering starts from 1
//!
//-------------------------------------------

void listInsert(struct List* list, int num, int element);

//-------------------------------------------
//! 
//! Delete element AFTER the given place
//!
//! @param[out] list - pointer to list
//! @param[in]  num  - where to delete
//!
//! @note numbering starts from 1
//!
//-------------------------------------------

void listDelete(struct List* list, int num);

//-------------------------------------------
//!
//! Deletes free elements in the list and 
//! makes it continuous
//!
//! @param[out] list - pointer to list
//!
//-------------------------------------------

void listCompact(struct List* list);

//-------------------------------------------
//!
//! Returns physical number of element in the
//! list by it's logical number
//!
//! @param[in] list - pointer to list
//! @param[in] log  - logical number
//! @return physical number
//!
//-------------------------------------------

int listPhyByLog(struct List* list, int log);

void listLinearize(struct List* list); 

//-------------------------------------------
//!
//! Allocs more memory and moves the list
//!
//! @param[out] list - pointer to list
//! @param[in] new_capacity - new capacity :^)
//!
//-------------------------------------------

void listResize(struct List* list, int new_capacity);

//-------------------------------------------
//!
//! Check list for errors
//!
//! @param[out] list - pointer to list
//! @return number of error
//!
//-------------------------------------------

enum LIST_STATUS listVerify(struct List* list);

//-------------------------------------------
//!
//! Prepares txt file for graphviz with
//! information about list to print it
//!
//! @param[out] list -  pointer ro list
//! 
//------------------------------------------

void listDump(struct List* list);

#endif // LIST_H


