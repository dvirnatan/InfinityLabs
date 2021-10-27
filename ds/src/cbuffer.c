/**************************
*		Cbuffer		
*	Author: Dvir Natan
*	Status: sent
*	Date: 22.10.21
**************************/

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <unistd.h> /*ssize_t*/

#include "cbuffer.h"

struct cbuffer
{
	size_t password;
    size_t capacity;
    size_t write;
    size_t read;
    char buffer[1];
};

cbuff_t *CBuffCreate(size_t initial_capacity)
{
	cbuff_t *cbuffer = malloc(offsetof(cbuff_t, buffer) + initial_capacity + 1);
	
	if (NULL != cbuffer)
	{
		cbuffer->capacity = initial_capacity;
		cbuffer->write = 0;
		cbuffer->read = 0;
		cbuffer->password = 0XF44EC0DE;
	}
	return cbuffer;
}

void CBuffDestroy(cbuff_t *cbuffer)
{
	assert(NULL != cbuffer);
	
	free(cbuffer); cbuffer = NULL;
}

ssize_t CBuffWrite(cbuff_t *cbuffer, const void *src, size_t nbytes)
{
	size_t counter = 0;
	char *runner;
	runner = (char*)src;
	
	assert(NULL != cbuffer);
	assert(NULL != src);	
				
	if(cbuffer->password != 0XF44EC0DE)
	{
		return -1;
	}

	while(nbytes > 0 && CBuffFreeSpace(cbuffer) > 0)
	{
		cbuffer->buffer[cbuffer->write] = *runner;
		
		++runner;
		--nbytes;
		++counter;
		++cbuffer->write;
		
		if(cbuffer->write == cbuffer->capacity + 1)
		{
			cbuffer->write = 0;
		}
	}	
	return counter;
}

ssize_t CBuffRead(cbuff_t *cbuffer, void *dest, size_t nbytes)
{
	size_t counter = 0;
	char *runner;
	runner = (char*)dest;

	assert(NULL != cbuffer);
	assert(NULL != dest);
	
	if(cbuffer->password != 0XF44EC0DE)
	{
		return -1;
	}
	
	while(nbytes > 0 && !CBuffIsEmpty(cbuffer))
	{
		*runner = cbuffer->buffer[cbuffer->read];
		
		++runner;
		--nbytes;
		++counter;
		++cbuffer->read;
		
		if(cbuffer->read == cbuffer->capacity + 1)
		{
			cbuffer->read = 0;
		}	
	}
	
	return counter; 
}

size_t CBuffSize(const cbuff_t *cbuffer)
{
	size_t size = 0;
	
	assert(NULL != cbuffer);
	
	if(cbuffer->read > cbuffer->write)
	{
		size = cbuffer->capacity + 1 + (cbuffer->write - cbuffer->read);
	}
	else 
	{
		size = cbuffer->write - cbuffer->read;
	}

	return size;
}

size_t CBuffIsEmpty(const cbuff_t *cbuffer)
{
	assert(NULL != cbuffer);

	return (cbuffer->write == cbuffer->read);
}

size_t CBuffFreeSpace(const cbuff_t *cbuffer)
{
	assert(NULL != cbuffer);

	return cbuffer->capacity - CBuffSize(cbuffer);
}

