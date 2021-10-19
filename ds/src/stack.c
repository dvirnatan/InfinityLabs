#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */


typedef struct stack 
{
	void **head;
	size_t size;
	size_t capacity;
}stack_t;


stack_t *StackCreate(size_t capacity)
{
	stack_t *stack = (stack_t*)malloc(sizeof(stack_t));
	assert (NULL != stack);
	
	stack -> head = (void**)malloc ( (sizeof(void*)) * capacity );
	assert (NULL != stack -> head);
	
	stack -> size = 0;
	stack -> capacity = capacity;
	return stack;
}

void StackDestroy(stack_t *stack)
{
	assert (NULL != stack);
	assert (NULL != stack -> head);
	
	free(stack -> head);
	free(stack); 
}

void StackPush(stack_t *stack, void *element)
{
	assert (NULL != stack);
	
	stack -> head[stack -> size] = element;
	++(stack -> size);
}

void StackPop(stack_t *stack)
{
	assert (NULL != stack);
	
	--(stack -> size);
}

void *StackPeek(const stack_t *stack)
{
	assert (NULL != stack);
	
	return stack -> head[stack -> size - 1];
}

size_t StackSize(const stack_t *stack)
{
	assert (NULL != stack);
	
	return stack -> size;
}

size_t StackCapacity(const stack_t *stack)
{
	assert (NULL != stack);
	
	return stack -> capacity;
}

int IsStackEmpty(const stack_t *stack)
{
	assert (NULL != stack);
	
	return !(stack -> size);
}


