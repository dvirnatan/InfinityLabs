/**************************************
Author: Dvir Natan
Reviewer: Alon
Status: Approved
Date: 24/10
***************************************/
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "dllist.h"

struct dllist_node 
{
    void *data;
    dllist_node_t *next_node;
    dllist_node_t *prev_node;
};

struct dllist
{
    dllist_node_t head;
    dllist_node_t tail;
};

dllist_t *DLListCreate()
{
	dllist_t *list = malloc(sizeof(dllist_t));
	
	if (NULL != list)
	{
		list->head.data = NULL;
		list->head.next_node = &list->tail;
		list->head.prev_node = NULL;
		
		list->tail.data = NULL;
		list->tail.next_node = NULL;
		list->tail.prev_node = &list->head;
	}
	
	return list;
}

void DLListDestroy(dllist_t *list)
{
dllist_iter_t current, next;
	
	assert(NULL != list);
	
	if(!DLListIsEmpty(list))
	{
		current = DLListBegin(list);
		
		while (current != DLListEnd(list))
		{
			next = current->next_node;	
			free(current); current = NULL;
			current = next;
		}
	}
	free(list); list = NULL;
	
}

dllist_iter_t DLListBegin(const dllist_t *list)
{
	assert(NULL != list);
	
	return list->head.next_node;
}

dllist_iter_t DLListEnd(const dllist_t *list)
{
	assert(NULL != list);
	
	return (dllist_iter_t)&list->tail;
}

dllist_iter_t DLListNext(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->next_node;
}

dllist_iter_t DLListPrev(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->prev_node;
}

int DLListInsertBefore(dllist_iter_t iter, void *data)
{
	dllist_node_t *new_node = malloc(sizeof(dllist_node_t));
	
	assert(NULL != iter);
	
	if(NULL != new_node)
	{
		new_node->data = data;
		new_node->next_node = iter;
		new_node->prev_node = iter->prev_node;
		iter->prev_node = new_node;
		new_node->prev_node->next_node = new_node;
		new_node = NULL;
		return 0;
	}
	return 1;
}

void DLListRemove(dllist_iter_t iter)
{
	assert(NULL != iter);	
	
	iter->prev_node->next_node = iter->next_node;
	iter->next_node->prev_node = iter->prev_node;
	
	free(iter); iter = NULL;
}

void *DLListGetData(const dllist_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->data;
}

int DLListIsSameIter(const dllist_iter_t one, const dllist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);

	return (one == other);
}

int DLListPushFront(dllist_t *list, void *data)
{
	return DLListInsertBefore(DLListBegin(list), data);
}

int DLListPushBack(dllist_t *list, void *data)
{
	return DLListInsertBefore(DLListEnd(list), data);
}

void DLListPopFront(dllist_t *list)
{
	 DLListRemove(DLListBegin(list));
}

void DLListPopBack(dllist_t *list)
{
	 DLListRemove(DLListEnd(list)->prev_node);	
}

void DLListSetData(dllist_iter_t iter, void *data)
{
	assert(NULL != iter);	
	
	iter->data = data;
}

size_t DLListSize(const dllist_t *list)
{
	size_t counter = 0;
	dllist_iter_t iter = NULL;
	
	assert(NULL != list);

	iter = DLListBegin(list);
	
	
	while(iter != DLListEnd(list))
	{
		iter = DLListNext(iter);
		++counter;
	}
	
	return counter;
}

int DLListIsEmpty(const dllist_t *list)
{
	return !DLListSize(list);
}

dllist_iter_t DLListForEach(dllist_iter_t from, dllist_iter_t to,
			  int (*action)(void *data, void *params), void *params)
{		
    assert(NULL != action);
    assert(NULL != from);
    assert(NULL != to);    
    
	while (from != to)
	{
		if (action(from->data, params))
		{
			return from;
		}
		from = DLListNext(from);
	}			  
	return to;
}

dllist_iter_t DLListFind(void *data, dllist_iter_t from, dllist_iter_t to,
		   				int (*is_match)(const void *, const void *))
{
    assert(NULL != is_match);
    assert(NULL != from);
    assert(NULL != to);    

	while (from != to)
	{
		if (is_match(from->data, data))
		{
			return from;
		}
		from = DLListNext(from);
	}
	return from;
}

int DLListMultiFind(const void *data, dllist_t *dest, 
            dllist_iter_t from, dllist_iter_t to,
            int (*is_match)(const void *one, const void *other))
{
	size_t counter = 0;
	int flag = 0;
    
    assert(NULL != dest);
    assert(NULL != is_match);
    assert(NULL != from);
    assert(NULL != to);    
    
        
	while (from != to && flag != 1)
    {
       from = DLListFind((void*)data, from, to, is_match);
       if (from != to)
       {
  	       flag = DLListInsertBefore(DLListEnd(dest) ,from->data);
	       from = DLListNext(from);
	       ++counter;
       }
    }
    if(flag == 1)
    {
    	return -1;
    }
    else
    { 
    	return counter;
    }
}
 
void DLListSplice(dllist_iter_t src_from, dllist_iter_t src_to,
 				  dllist_iter_t dest)
{
	dllist_iter_t temp = NULL;
	
	assert(src_from);
	assert(src_to);
	assert(dest);
	
	temp = src_from->prev_node;
	dest->prev_node->next_node = src_from;
	src_to->prev_node->next_node = dest;
	src_from->prev_node->next_node = src_to;
	src_from->prev_node = dest->prev_node;
	dest->prev_node = src_to->prev_node;
	src_to->prev_node = temp;
}



