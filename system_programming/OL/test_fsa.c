#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "fsa.h"

int main ()
{
	fsa_t *fsa;
	size_t i = 0;
	size_t counter = 0;
	void *pool;

	size_t size = FSASuggestSize(10, 100);
	void *arr[1000];
	
	pool = malloc(size);
	
	fsa = FSAInit(pool, 1000, 15);
	
	counter = FSACountFree(pool);
	printf("FIRST SIZE = %ld\n", counter);	
	
	counter = 0;
	while(arr[counter - 1] != NULL)
	{
		arr[counter] = FSAAlloc(fsa);
		++counter;	
	}
	counter = FSACountFree(pool);
	printf("AFTER ALL ALOCATION %ld\n", counter);	
	
	while(arr[i] != NULL)
	{	
		FSAFree(pool, arr[i]);
		++i;
	}
	
	counter = FSACountFree(pool);
	printf("AFTER FREE %ld\n", counter);
	
	
	counter = 0;
	while(arr[counter - 1] != NULL)
	{
		arr[counter] = FSAAlloc(fsa);
		++counter;	
	}
	counter = FSACountFree(pool);
	printf("!AFTER ALL ALOCATION %ld\n", counter);	
	
	
	free(pool);	
	
	
	
	return 0;
}

