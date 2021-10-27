/******************
*Sorted List API*
******************/

#ifndef __SORTED_LIST_H__OL111__
#define __SORTED_LIST_H__OL111__

#include <stddef.h> /*size_t*/
#include "dllist.h"

typedef struct sorted_list sorted_list_t;
typedef struct sorted_list_iter sorted_list_iter_t;

struct sorted_list_iter
{
    dllist_iter_t inner_iter;
    #ifndef NDEBUG
    sorted_list_t *list;
    #endif
};

/*Creat new list and return pointer to this list
Error:failed malloc return NULL pointer*/
sorted_list_t *SortedListCreate(int (*cmp_func_t)(const void *one, const void *other));

/*Free all the dynamic allocated memory*/
void SortedListDestroy(sorted_list_t *list);

/*
SListBegin returns the first valid iterator
if list is empty, SListEnd iterator will be returned
Error: invalid list*/
sorted_list_iter_t SortedListBegin(const sorted_list_t *list); 

/*Return the first invalid iterator
Error: invalid list*/
sorted_list_iter_t SortedListEnd(const sorted_list_t *list); 

/*return the next iterator after iter in the link list.
Next on SortedListEnd is undefined.
The iterator should be valid*/
sorted_list_iter_t SortedListNext(const sorted_list_iter_t iter);

/*return the previous iter from iter in the link list.
Prev on SortedListBegin is undefined
The iterator should be valid)*/
sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iter);

/*Insert a new node in the correct place according to cmp_func().
insert before the first element that cmp_func returns value greater than 0 
Error: if list or iterator isn't valid or malloc failed return 1 */
int SortedListInsert(sorted_list_t *list, void *data);

/*Remove the node pointed to by iter
removing SListEnd results in undefined behavior */
void SortedListRemove(sorted_list_iter_t iter);

/*Return 0 if false, 1 if true*/
int SortedListIsSameIter(const sorted_list_iter_t one, const sorted_list_iter_t other);

/*Remove node from front 
return data
Error: if list isn't valid, or is empty*/
void *SoretdListPopFront(sorted_list_t *list);

/*Remove node from back
return data
Error: if list isn't valid, or is empty*/
void *SoretdListPopBack(sorted_list_t *list);

/*Error: undefind behavior for invalid iterator
return data*/
void *SortedListGetData(const sorted_list_iter_t iter);

/*Count the number of elements in the sorted_list.
Error: if list isn't valid undefind behavior*/
size_t SortedListSize(const sorted_list_t *list);

/* return 1 if empty and 0 if not */
int SortedListIsEmpty(const sorted_list_t *list);

/* ForEach invokes the action_func on all data between from and to iterators.
from has to be before to.
Usage: If succeed, to iterator will be returned, else, an iterator from the range will be returned
action_func - should return 0 (success) or non-zero value (failure)
Error: returns the iterator in the place that failed to preform
DO NOT CHANGE THE FIELD BY WHICH THE DATA IS SORTED IN THE LIST
modifying the data may result in an unsorted list*/
sorted_list_iter_t SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
			  int (*action)(void *data, void *params), void *params);

/*Search for a match according to cmp_func() between from and to (exclude to)
from has to be before to.
If data is not in the list, to iterator will be returned
Error: from and to and is_match function are invalidated 
SListFind returns iterator where it stopped  */
sorted_list_iter_t SortedListFind(const sorted_list_t *list,
		   sorted_list_iter_t from, sorted_list_iter_t to, void *data);

/*Search for a match according to is_match() between from and to (exclude to)
from has to be before to.
If data is not in the list, to iterator will be returned
Error: from and to and is_match function are invalidated 
SListFind returns iterator where it stopped*/
sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to,
		   void *data, int (*is_match)(const void *, const void *));

/* Merges both lists into a sorted list pointed by dest
both lists should be sorted by the same cmp function
After the Merge, src will be empty 
Error: if list dest/src isn't valid */
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

#endif /*__SORTED_LIST_H_HOL111__*/
