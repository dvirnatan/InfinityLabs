/********************************************
 *          Queue API
 * *****************************************/

#ifndef	__QUEUE_H__OL111__ 
#define	__QUEUE_H__OL111__

#include <stddef.h> /* size_t */

/*
struct queue 
{
    sllist_t *sllist;
};
*/
typedef struct queue queue_t;

/*Create new queue and return pointer to this list
Error:failed malloc return NULL pointer*/
queue_t *QCreate();

/*Free all the dynamic allocated memory
If queue is Invalidated, the behavior is undefind.
Time complexity O(n)*/
void QDestroy(queue_t *queue);

/* Returns the element at the head of the queue.
queue should be valid.
Time complexity O(1)*/
void *QPeek(const queue_t *queue);

/*Insert element to the end of the queue.
Returns status of malloc: 0 - success, 1 - failure
queue should be valid.
Time complexity O(1)*/
int QEnqueue(queue_t *queue, void *data);


/*Remove the element at the head of the queue.
queue should be valid.
Time complexity O(1)*/
void QDequeue(queue_t *queue);


/*Returns the number of elemenets in the queue.
queue should be valid.
Time complexity O(n)*/
size_t QSize(const queue_t *queue);


/*Return 1 if empty, and 0 if not.
queue should be valid.
Time complexity O(1)*/
int QIsEmpty(const queue_t *queue);


/*All of src elements will be appended to dest.
src will become a valid empty queue
dest src should be valid.
Time complexity O(1)*/
void QAppend(queue_t *dest, queue_t *src);

#endif /*__QUEUE_H__OL111__*/
