#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "sllist.h"
#include "queue.h"

struct queue 
{
    sllist_t *sllist;
};


queue_t *QCreate()
{
	queue_t *queue = malloc (sizeof(queue_t));
	
	if(NULL != queue)
	{
		queue->sllist = SLListCreate();
	}
	
	return queue;
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	
	SLListDestroy(queue->sllist);
	free(queue); queue = NULL;
}

void *QPeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLListGetData(SLListBegin(queue->sllist));
}

int QEnqueue(queue_t *queue, void *data)
{
	assert(NULL != queue);
	
	return SLListInsertBefore(queue->sllist,SLListEnd(queue->sllist),data);
}

void QDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SLListRemove(queue->sllist, SLListBegin(queue->sllist));
}

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SLListCount(queue->sllist);
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);

	return SLListIsEmpty(queue->sllist);
}

void QAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);	
	
	SLListAppend(dest->sllist, src->sllist);
}

