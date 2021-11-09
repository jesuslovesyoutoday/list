#ifndef LIST_H
#define LIST_H
#define DEBUG

struct List {
    int* data;     //< pointer to the beginning of the buffer
    int* head;     //< pointer to the first element of list
    int* tail;     //< pointer to the last element of list
    int* next;     //< pointer to the array storing the
                   //  next physical number for each element
    int* prev;     //< pointer to the array storing the 
                   //  previous physical number
    int* free;     //< pointer to the "list" of free elements
    int capacity;  //< size of buffer
    int el_amount; //< amount of elements in list
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
//! Alloc more memory and move the list
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
//! @param[out] list - poinetr to list
//!
//-------------------------------------------

enum LIST_STATUS listVerify(struct List* list);

void listDump(struct List* list);

#endif // LIST_H
