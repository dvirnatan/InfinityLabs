/********************************************
	Author: Dvir Natan
	Reviewer: Mickey
	Status: send
	Date: 13/10/21
********************************************/
#include <stddef.h> /* size_t */
#include <assert.h>
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include "dvector.h"

#define REDUCE_FACTOR 4
#define RESIZE_FACTOR 2

struct dvector{
	size_t capacity;
	size_t size;
};

dvector_t *DVectorCreate(size_t initial_capacity)
{
	dvector_t *dvector_ptr;
		
	dvector_ptr = (dvector_t*)malloc(sizeof(dvector_t) + sizeof(void*) * 		initial_capacity);
	
	if (NULL == dvector_ptr)
	{
		puts("Malloc has failed");
		return NULL;
	}
	
	dvector_ptr -> capacity = initial_capacity;
	dvector_ptr -> size = 0;
	return dvector_ptr;
}

void DVectorDestroy(dvector_t *dvector)
{
	assert (NULL != dvector);
	
	free(dvector); dvector = NULL;
}

void DVectorSetElement(dvector_t *dvector, void *element, size_t index)
{
	void **element_ptr;
		
	assert (NULL != dvector);
	assert (index < (dvector -> size));
	
	element_ptr = (void**)(dvector + 1);
	element_ptr[index] = element;
}

void *DVectorGetElement(const dvector_t *dvector, size_t index)
{
	void **element_ptr;
	
	assert(NULL != dvector);
	assert (index < dvector -> size);
	
	element_ptr = (void**)(dvector + 1);
	return element_ptr[index];
}

dvector_t *DVectorPushBack(dvector_t *dvector, void *element)
{
	void **element_ptr; 
	
	assert(NULL != dvector);
	
	if((dvector -> capacity) <= (dvector -> size) + 1)
	{
	    dvector = DVectorResize(dvector, 1+(dvector -> size)*RESIZE_FACTOR);
	}
	
	element_ptr = (void**)(dvector + 1);
	element_ptr[dvector -> size] = element;

	++(dvector -> size);	
	return dvector;
}

dvector_t *DVectorPopBack(dvector_t *dvector)
{
	void *null_ptr = NULL;
	
	assert(NULL != dvector);
	
	if (dvector -> size == 0)
	{
		puts("Vector is empty");
		return dvector;
	}
		
	DVectorSetElement(dvector, null_ptr, (dvector -> size - 1));
	
	--(dvector -> size);
 
	if((dvector -> capacity) > (dvector -> size) * REDUCE_FACTOR)
	{
	    dvector = DVectorResize(dvector, 1+(dvector -> size)*RESIZE_FACTOR);
	}
	
	return dvector;
}

size_t DVectorSize(const dvector_t *dvector)
{
	assert(NULL != dvector);
	
	return dvector -> size;
}

size_t DVectorCapacity(const dvector_t *dvector)
{
	assert(NULL != dvector);
	
	return dvector -> capacity;
}

dvector_t *DVectorResize(dvector_t *dvector, size_t size)
{
	assert(NULL != dvector);
	assert(size >= (dvector -> size));
	
	dvector = realloc(dvector, sizeof(dvector_t) + sizeof(void*) * size);
	
	if (NULL == dvector)
	{
		puts("Realloc has failed\n");
		return NULL;
	}
	
	dvector -> capacity = size;
	
	return dvector;
}

dvector_t *ShrinkToFit(dvector_t *dvector)
{
	assert(NULL != dvector);
	
	dvector = DVectorResize(dvector, dvector -> size);
	
	return dvector;
}
	

