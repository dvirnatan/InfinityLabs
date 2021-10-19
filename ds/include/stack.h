#ifndef __STACK_H__OL111
#define __STACK_H__OL111

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/*
Create new stack of given capacity 
Time Complexity: O(1)
return type: stack_t *
*/
stack_t *StackCreate(size_t capacity);

/* 
Destroy the whole stack
error: Stack doesn't exist
Time Complexity: O(1)
return type: void
*/
void StackDestroy(stack_t *stack);

/*
Add an element to the top of the stack 
error: Stack doesn't exist, element doesn't exist
Time Complexity: O(1)
return type: void
*/
void StackPush(stack_t *stack, void *element);

/* 
Remove the top element from the stack 
error: Stack doesn't exist
Time Complexity: O(1)
return type: void
*/
void StackPop(stack_t *stack);

/*
Returns last element without Popping
error: Stack doesn't exist
Time Complexity: O(1)
return type: void *
*/
void *StackPeek(const stack_t *stack);

/*
Return number of elements in the stack 
error: Stack doesn't exist
Time Complexity: O(1)
return type: size_t
*/
size_t StackSize(const stack_t *stack);

/* 
Returns stack capacity 
error: Stack doesn't exist
Time Complexity: O(1)
return type: size_t
*/
size_t StackCapacity(const stack_t *stack);

/*
Return if stack is empty or not 
error: Stack doesn't exist
Time Complexity: O(1)
return type: int (bool)
*/
int IsStackEmpty(const stack_t *stack);


#endif /* __STACK_H__OL111 */


