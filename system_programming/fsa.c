/**************************************************************
	Auotor: Dvir Natan
	Reviwer: Eli
	Date: 7.11.2021
	Status: Approved
**************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h>

#include "fsa.h"

#define WORD_SIZE sizeof(size_t)

struct fsa
{
	size_t *next_free;
};

size_t FSASuggestSize(size_t block_number, size_t block_size)
{	
return(block_size + (WORD_SIZE - block_size % WORD_SIZE)) * block_number + WORD_SIZE;
}

fsa_t *FSAInit(void *pool_start, size_t pool_size, size_t block_size)
{
	fsa_t fsa;
	size_t offset;
	size_t *next_free;
	size_t *free_cell;

	assert(pool_start != NULL);
		
	while((size_t)pool_start % WORD_SIZE)
	{
		pool_start = (char*)pool_start + 1;
	}
	
	if((offset = block_size % WORD_SIZE))
	{
		block_size += WORD_SIZE - offset;
	}
	
	*next_free = pool_start;
	*free_cell = next_free + 1;	
	
	while(free_cell < (size_t*)((char*)pool_start + pool_size))
	{
		*next_free = (size_t)free_cell;
		next_free = free_cell;
		free_cell = (size_t*)((char*)free_cell + block_size);
	}
	
	*next_free = 0;
	
	fsa.next_free = *(size_t**)pool_start;
	*(fsa_t*)pool_start = fsa;
	
	return (fsa_t*)pool_start;
}

void *FSAAlloc(fsa_t *pool)
{
	size_t *tmp;
	
	assert(pool != NULL);
		
	tmp = pool->next_free;	

	if(pool->next_free == NULL)
	{
		return NULL;
	}
	
	pool->next_free = (size_t*)(*pool->next_free);

	return tmp;
}

void FSAFree(fsa_t *pool, void *block)
{
	assert(pool != NULL);
	assert(block != NULL);

	*(size_t*)block = (size_t)pool->next_free;	
	pool->next_free = (size_t*)block;
}

size_t FSACountFree(const fsa_t *pool)
{
	size_t *next_free;
	size_t counter = 0;
	
	assert(pool != NULL);
	
	next_free = pool->next_free;
	
	while(next_free != NULL)
	{
		next_free = (size_t*)*next_free;
		++counter;
	}
	return counter;
}

/*_____________________EOF________________________*/

