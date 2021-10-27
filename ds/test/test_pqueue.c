#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <stdio.h>

#include "pqueue.h"

int priority_func (const void *one,const void *other);

int main()
{
	pqueue_t *pqueue = PQCreate(priority_func);
	
	if(pqueue == NULL)
	{
		puts("null");
	}
	
	PQDestroy(pqueue);
	
	return 0;

}


int priority_func (const void *one,const void *other)
{
	const int *a  = one;
	const int *b = other;
	
	return *a - *b;
}
