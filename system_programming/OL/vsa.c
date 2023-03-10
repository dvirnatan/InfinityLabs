/**************************************************************
	Auotor: Dvir Natan
	Reviwer: Eli
	Date: 9/11/2021
	Status: Approved
**************************************************************/

#include <stddef.h> /* size_t */
#include <sys/types.h>/* ssize_t */
#include <assert.h>
#include <stdlib.h> /*abs()*/

#include "vsa.h"

#define HEADER_SIZE sizeof(vsa_header_t)

struct vsa
{
	ssize_t pool_size;
};

struct vsa_header
{
	ssize_t block_size;
};

typedef struct vsa_header vsa_header_t;

vsa_t *VSAInit(void *pool_start, size_t pool_size)
{
	vsa_header_t *header;
	vsa_t vsa;
	size_t diff;
	
	assert(NULL != pool_start);
	assert(pool_size > HEADER_SIZE * 2);
	
	if((diff = (size_t)pool_start % HEADER_SIZE) > 0)
	{
		pool_start = (void*)((char*)pool_start + (HEADER_SIZE - diff));
		pool_size -= (HEADER_SIZE - diff);
	}
	
	vsa.pool_size = pool_size;
	*(vsa_t*)pool_start = vsa;
	header = (vsa_header_t*)pool_start + 1;
	
	header->block_size = pool_size - 2 * HEADER_SIZE;
	
	return (vsa_t*)pool_start; 
}

static void Defrag(vsa_t *pool)
{
	vsa_header_t *runner;
	vsa_header_t *next;
	ssize_t end;
	
	runner = (vsa_header_t*)pool + 1;
	end = pool->pool_size - 2*HEADER_SIZE;
	
	while(end > 0 && runner->block_size != end)	
	{
		next = runner + (labs(runner->block_size + HEADER_SIZE) / HEADER_SIZE);

		if(runner->block_size > 0 && next->block_size > 0)
		{
			runner->block_size += next->block_size + HEADER_SIZE;
		}
		else
		{
			end -= (labs(runner->block_size) + HEADER_SIZE);
			runner = next;
		}
	}
}

void *VSAAlloc(vsa_t *pool, size_t size)
{
	ssize_t end = 0;
	ssize_t tmp = 0;
	size_t diff = 0;

	vsa_header_t *runner; 
	
	assert(NULL != pool);
	
	runner = (vsa_header_t*)pool + 1; 
	
	Defrag(pool);
	
	if((diff = size % HEADER_SIZE) > 0)
	{
			size -= HEADER_SIZE - diff;
	}
	
	end = pool->pool_size - 2*HEADER_SIZE;
	
	while((runner->block_size < 0 || runner->block_size < (ssize_t)size) && end > 0)
	{
		runner += 1 + labs(runner->block_size) / HEADER_SIZE;
		end -= (runner->block_size + HEADER_SIZE);
	}
	
	if(end <= 0)
	{
		return NULL;
	}
	
	tmp = runner->block_size;
	runner->block_size = -1 * size;
	runner = (vsa_header_t*)((char*)runner + size + HEADER_SIZE);
	
	if(tmp > (ssize_t)(size + HEADER_SIZE))
	{
		runner->block_size = tmp - (size + HEADER_SIZE);
		runner = (vsa_header_t*)((char*)runner - size - HEADER_SIZE);	
	}		
	
	return (runner + 1);	
}

void VSAFree(void *block)
{
	vsa_header_t *header;
	
	assert(NULL != block);
	
	header = (vsa_header_t*)block - 1;
	
	header->block_size *= -1;
}

size_t VSALargestBlockAvailble(vsa_t *pool)
{
	ssize_t max = 0;
	vsa_header_t *runner;
	ssize_t end;
	
	assert(NULL != pool);
	
	end = pool->pool_size - 2*HEADER_SIZE;
	runner = (vsa_header_t*)(pool + 1);
	
	Defrag(pool);
	
	while (end > 0)
	{
		if(runner->block_size > max)
		{
			max = runner->block_size;
		}
		
		end -= (labs(runner->block_size) + HEADER_SIZE);
		runner += (labs(runner->block_size) / HEADER_SIZE + 1);
	}
	return max;
}

/*__________________EOF________________________*/

