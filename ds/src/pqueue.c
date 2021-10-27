/**************************************	
			Priorety Queue
			Author: Dvir Natan
			Reviewer: 
			Status: 
			Date: 
***************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "pqueue.h"
#include "sorted_list.h"

struct pqueue 
{
    sorted_list_t *sorted_list;
};

pqueue_t *PQCreate(int (*priority_func)(const void *one,const void *other))
{
	pqueue_t *pqueue = malloc(sizeof(pqueue_t));
	
	assert(NULL != priority_func);
	
	if(NULL != pqueue)
	{
		pqueue->sorted_list = SortedListCreate(priority_func);
		
		if(NULL == pqueue->sorted_list)
		{
			free(pqueue); pqueue = NULL;
		}
	}
	
	return pqueue;
}

void PQDestroy(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	SortedListDestroy(pqueue->sorted_list);
	free(pqueue); pqueue = NULL;
}

int PQEnqueue(pqueue_t *pqueue, void *data)
{
	assert(NULL != pqueue);
	
	return SortedListInsert(pqueue->sorted_list, data);
}

void PQDequeue(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	SortedListRemove(SortedListPrev(SortedListEnd(pqueue->sorted_list)));
}

void PQFlush(pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	while(!SortedListIsEmpty(pqueue->sorted_list))
	{
		PQDequeue(pqueue);
	}
}

int PQIsEmpty(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SortedListIsEmpty(pqueue->sorted_list);
}

size_t PQSize(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SortedListSize(pqueue->sorted_list);
}

void *PQPeek(const pqueue_t *pqueue)
{
	assert(NULL != pqueue);
	
	return SortedListGetData(SortedListPrev(SortedListEnd(pqueue->sorted_list)));
}

void *PQErase(pqueue_t *pqueue, 
			void *data, int (*is_match)(const void *, const void *))
{
	void *temp;
	
	assert(NULL != pqueue);
	assert(NULL != is_match);
	
	temp = SortedListGetData(SortedListFindIf(SortedListBegin(pqueue->sorted_list), SortedListEnd(pqueue->sorted_list), data, is_match));

	if (!SortedListIsSameIter(SortedListFindIf(SortedListBegin(pqueue->sorted_list), SortedListEnd(pqueue->sorted_list), data, is_match), SortedListEnd(pqueue->sorted_list)))
	{
		SortedListRemove(SortedListFindIf(SortedListBegin(pqueue->sorted_list), SortedListEnd(pqueue->sorted_list), data, is_match));
	}
		return temp;
}















