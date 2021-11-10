/**************************************************************
	Auotor: Dvir Natan
	Reviwer: Neria
	Date: 9/11/2021
	Status: Send
**************************************************************/

#include <stddef.h> /* size_t */
#include <sys/types.h>/* ssize_t */
#include <assert.h>

#include "vsa.h"

#define WORD_SIZE sizeof(size_t)

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
	assert(pool_size > WORD_SIZE * 2);
	
	if((diff = (size_t)pool_start % WORD_SIZE) > 0)
	{
		pool_start = (void*) ((char*)pool_start + (WORD_SIZE - diff));
		pool_size -= (WORD_SIZE);
	}
	
	vsa.pool_size = pool_size;
	*(vsa_t*)pool_start = vsa;
	header = (vsa_header_t*)pool_start + 1;
	
	header->block_size = pool_size - 2 * WORD_SIZE;
	
	return (vsa_t*)pool_start; 
}


static void dfreg(vsa_header_t *pool)
{    
    vsa_header_t *header = pool;
    vsa_header_t *next_header;
    ssize_t end = pool->block_size;

	assert(NULL != pool);

    while(end > 0)
    {  
        if(header->block_size > 0)
        {	  
            next_header = header + (header->block_size / WORD_SIZE) + 1;
            if(next_header->block_size > 0)
            {
                header->block_size += next_header->block_size + WORD_SIZE;
            }
            else
            {
                header = next_header;        
                end -= ((-1 * header->block_size) + WORD_SIZE);       
            }
        }
        else
        {
        	header += ((-1 * header->block_size / WORD_SIZE) + 1);
            end -= (-1 * header->block_size + WORD_SIZE);              
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
	
	dfreg(runner);
	
	if((diff = size % WORD_SIZE) > 0)
	{
			size += WORD_SIZE - diff;
	}
	
	end = pool->pool_size - 2*WORD_SIZE;
	
	while((runner->block_size < 0 || runner->block_size < (ssize_t)size) && end > 0)
	{
		runner = (vsa_header_t*) ((char*)runner + runner->block_size * -1 + WORD_SIZE);
		end -= (runner->block_size + WORD_SIZE);
	}
	
	if(end <= 0)
	{
		return NULL;
	}
	
	tmp = runner->block_size;
	runner->block_size = -1 * size;
	runner = (vsa_header_t*)((char*)runner + size + WORD_SIZE);
	
	if(tmp > (ssize_t)(size + WORD_SIZE))
	{
		runner->block_size = tmp - (size + WORD_SIZE);
		runner = (vsa_header_t*)((char*)runner - size - WORD_SIZE);	
	}		
	
	return ++runner;	
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
	ssize_t size = 0;
	vsa_header_t *runner;
	ssize_t end;
	
	assert(NULL != pool);
	
	end = pool->pool_size;
	runner = (vsa_header_t*)(pool + 1);
	
	dfreg(runner);

	while (end > 0)
	{
		if(runner->block_size > max)
		{
			max = runner->block_size;
		}
		
		size = runner->block_size;
		if(size < 0)
		{
			size = -size;
		}
		
		runner = (vsa_header_t*)((char*)runner + size + WORD_SIZE);
		end = end - (runner->block_size + WORD_SIZE);
	}
	return max;
}


