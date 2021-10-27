/***********
*DLList API*
************/

#ifndef __DLLIST_H__OL111__
#define __DLLIST_H__OL111__

#include <stddef.h> /*size_t*/

/*
struct dllist
{
    dllist_node_t head;
    dllist_node_t tail;
};

struct dllist_node 
{
    void *data;
    dllist_node_t *next_node;
    dllist_node_t *prev_node;
};
*/

typedef struct dllist_node dllist_node_t; 
typedef struct dllist dllist_t;
typedef dllist_node_t* dllist_iter_t;

/*Creat new list and return pointer to this list
Error:failed malloc return NULL pointer*/
dllist_t *DLListCreate();

/*Free all the dynamic allocated memory*/
void DLListDestroy(dllist_t *list);

/*
DLListBegin returns the first valid iterator
if list is empty, DLListEnd iterator will be returned
Error: invalid list*/
dllist_iter_t DLListBegin(const dllist_t *list); 

/*Return the first invalid iterator
Error: invalid list*/
dllist_iter_t DLListEnd(const dllist_t *list); 

/*Step to next node from iter in the link list.
The iterator should be valid*/
dllist_iter_t DLListNext(const dllist_iter_t iter);

/*Step to prev node from iter in the link list.
The iterator should be valid)*/
dllist_iter_t DLListPrev(const dllist_iter_t iter);

/*Insert a new node before iter with the data.
Error: if list or iterator isn't valid or malloc failed return 1 */
int DLListInsertBefore(dllist_iter_t iter, void *data);

/*Remove the node pointed to by iter
removing DLListEnd results in undefined behavior */
void DLListRemove(dllist_iter_t iter);

/*Return 0 if false, 1 if true*/
int DLListIsSameIter(const dllist_iter_t one, const dllist_iter_t other);

/*Insert a new node with the data in the head of the list (using DLListBegin).
Error: if list or iterator isn't valid or malloc failed return 1*/
int DLListPushFront(dllist_t *list, void *data);

/*Insert a new node with the data in the tail of the list .
Error: if list or iterator isn't valid or malloc failed return 1*/
int DLListPushBack(dllist_t *list, void *data);

/*Remove node from front 
Error: if list isn't valid, or is empty*/
void DLListPopFront(dllist_t *list);

/*Remove node from front 
Error: if list isn't valid, or is empty */
void DLListPopBack(dllist_t *list);

/*Error: if iterator isn't valid return NULL*/
void *DLListGetData(const dllist_iter_t iter);

/*Overwrite current data in node*/
void DLListSetData(dllist_iter_t iter, void *data);

/*Count the number of elements in the dllist.
Error: if list isn't valid undefind behavior*/
size_t DLListSize(const dllist_t *list);

/* return 1 if empty and 0 if not */
int DLListIsEmpty(const dllist_t *list);

/*
ForEach invokes the action_func on all data between from and to iterators.
from has to be before to.
Usage: If succeed, to iterator will be returned, else, an iterator from the range will be returned
action_func - should return 0 (success) or non-zero value (failure)
Error: returns the iterator in the place that failed to preform
*/

dllist_iter_t DLListForEach(dllist_iter_t from, dllist_iter_t to,
			  int (*action)(void *data, void *params), void *params);

/*Search for a match between from and to (exclude to)
from has to be before to.
If data is not in the list, to iterator will be returned
Error: from and to and is_match function are invalidated 
DLListFind returns iterator where it stopped  */
dllist_iter_t DLListFind(void *data, dllist_iter_t from, dllist_iter_t to,
		   				int (*is_match)(const void *, const void *));

/*  Returns the number of elements found, or -1 on malloc failure.
    Copy the found elements to the end of dest. */
int DLListMultiFind(const void *data, dllist_t *dest, 
            dllist_iter_t from, dllist_iter_t to,
            int (*is_match)(const void *one, const void *other));

/* After the splice, from until to (exclude to), will not be in src
Splice splices before dest*/
void DLListSplice(dllist_iter_t src_from, dllist_iter_t src_to, dllist_iter_t dest);



#endif /*__DLLIST_H_HOL111__*/



