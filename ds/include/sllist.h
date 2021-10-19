/*****************************************************************************/
/*                            SLList API                       			     */
/*****************************************************************************/
#ifndef __SLList_H__OL111__
#define __SLList_H__OL111__

/*
struct sllist
{
    sllist_node_t *head;
    sllist_node_t *tail;
};

struct sllist_node 
{
    void *data;
    sllist_node_t *next_node;
};
*/

typedef struct sllist_node sllist_node_t; 
typedef struct sllist sllist_t;
typedef sllist_node_t* sllist_iter_t;

/*Creat new list and return pointer to this list
Error:failed malloc return NULL pointer*/
sllist_t *SLListCreate();

/*Free all the dynamic allocated memory*/
void SLListDestroy(sllist_t *list);

/*
SLListBegin returns the first valid iterator
if list is empty, SLListEnd iterator will be returned
Error: if list isn't valid return NULL
*/
sllist_iter_t SLListBegin(const sllist_t *list); 

/*Return the first invalid iterator
Error: if list isn't valid return NULL*/
sllist_iter_t SLListEnd(const sllist_t *list); 

/*Step to next node from iter in the link list.
Error: if iterator isn't valid return NULL (iterator isn't valid if iter > SLListEnd(list)*/
sllist_iter_t SLListNext(const sllist_iter_t iter);

/*Return 0 if false, 1 if true*/
int SLListIsSameIter(const sllist_iter_t one, const sllist_iter_t other);

/*Error: if iterator isn't valid return NULL*/
void *SLListGetData(const sllist_iter_t iter);

/*Overwrite current data in node*/
void SLListSetData(sllist_iter_t iter, void* data);

/*Insert a new node before iter with the data.
Error: if list or iterator isn't valid or malloc failed return NULL*/
int SLListInsertBefore(sllist_t *list, sllist_iter_t iter, void* data);

/*Remove the node pointed to by iter*/
void SLListRemove(sllist_t *list, sllist_iter_t iter);

/*Search for a match between from and to (exclude to)
from has to be before to.
If data is not in the list, to iterator will be returned
Error: from and to and is_match function are invalidated*/
sllist_iter_t SLListFind(void* data, 
		   sllist_iter_t from, sllist_iter_t to,
		   int (*is_match)(const void *, const void *));

/*
ForEach invokes the action_func on all data between from and to iterators.
from has to be before to.
Usage: If succeed, to iterator will be returned, else, an iterator from the range will be returned
action_func - should return 0 (success) or non-zero value (failure)
Error: returns the iterator in the place that failed to preform
*/
sllist_iter_t SLListForEach(sllist_iter_t from, sllist_iter_t to, 
		   int (*action_func)(void *data, void *params),
		   void *params);

/*Count the number of elements in the link list.
Error: if list isn't valid undefind behavior*/
size_t SLListCount(const sllist_t *list);

/* return 1 if empty and 0 if not */
int SLListIsEmpty(const sllist_t *list);


/* After the Append the src list stays empty (not destroyed) */
void SLListAppend(sllist_t *dest, sllist_t *src);


#endif /*__SLList_H_HOL111__*/
