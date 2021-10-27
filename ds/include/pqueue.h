/***************************
 *       PQueue API
 * *************************/

#ifndef	__PQUEUE_H__OL111__ 
#define	__PQUEUE_H__OL111__

#include <stddef.h> /* size_t */
/*
struct pqueue 
{
    sorted_list_t *sorted_list;
}
*/
typedef struct pqueue pqueue_t;

/* Create new PQueue and return pointer to PQueue
return values of compare func:
    -priority of one lower then other: lower then zero.
    -priority of one equals to other: zero.
    -priotiry of one greater then other: greater then zero.
Error: failed malloc returns NULL pointer
Time complexity O(1) */
pqueue_t *PQCreate(int (*priority_func)(const void *one,const void *other));

/*Free all the dynamic allocated memory
If PQueue is invalidated, the behavior is undefined.
Time complexity O(n)*/
void PQDestroy(pqueue_t *pqueue);

/*  Insert element to the PQ according to its priority.
Returns: 0 - on success, 1 - otherwise
PQueue should be valid.
Time complexity O(n)    */
int PQEnqueue(pqueue_t *pqueue, void *data);

/*Remove the element from the head of the priority queue.
PQueue should be valid.
Time complexity O(1)*/
void PQDequeue(pqueue_t *pqueue);

/*remove all alements of PQueue 
Time complexity O(n)*/
void PQFlush(pqueue_t *pqueue);

/*Return 1 if empty, and 0 if not.
PQueue should be valid.
Time complexity O(1) */
int PQIsEmpty(const pqueue_t *pqueue);

/*Returns the number of elemenets in the PQueue.
PQueue should be valid.
Time complexity O(n)*/
size_t PQSize(const pqueue_t *pqueue);

/* Returns the element with the highest priority.
PQueue should be valid.
Time complexity O(1) */
void *PQPeek(const pqueue_t *pqueue);

/* the function removes the first element (from the tail of queue - the lowest priority) where is_match function returns 1.
returns the deleted element, or NULL when not found*/
void *PQErase(pqueue_t *pqueue, void *data, int (*is_match)(const void *, const void *));

#endif /*__PQUEUE_H__OL111__*/
