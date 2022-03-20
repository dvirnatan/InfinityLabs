#include <stdio.h>
#include <stddef.h> /*size_t*/
#include <stdlib.h>
#include <sys/types.h>

#include "vsa.h"

int main()
{


	vsa_t *vsa;
	void* block1, *block2, *block = NULL;
	void* pool_start = calloc(1, 1000);
	size_t max = 1;
	
	vsa = VSAInit(pool_start, 104);

	max = VSALargestBlockAvailble(vsa);
	printf("MAX = %ld\n", max);
		
	block = VSAAlloc(vsa, 8);
	VSAFree(block);
	/*
	block = (size_t*)block - 1;
	printf("!%ld\n", *(size_t*)block);	
		*/
	
	block = VSAAlloc(vsa, 8);		
	block1 = VSAAlloc(vsa, 8);	
	block2 = VSAAlloc(vsa, 16);	
	max = VSALargestBlockAvailble(vsa);
	printf("MAX = %ld\n", max);
	puts("*");	

	VSAFree(block);
	VSAFree(block1);
	VSAFree(block2);
	VSAAlloc(vsa,8);
	
	max = VSALargestBlockAvailble(vsa);
	printf("MAX = %ld\n", max);
	printf("%lu\n", *(size_t*)block1);	
	puts("*");
	block = VSAAlloc(vsa, 16);	
	block = VSAAlloc(vsa, 8);			
	
	if(block == NULL)
	{
		puts("null");
	}
	


	
	free(pool_start);

	return 0;
}


