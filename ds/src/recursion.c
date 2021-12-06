
/*************************************************
*		Ricursion
*		Author: Dvir Natan
*		Reviewer: Eli
*		Date: 25/11/21
*		Status: Send
**************************************************/

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>

#include "recursion.h"

static node_t *WrapFlipList(node_t* node, node_t* next);
static char *WrapStrCpy(char *dest, const char *src, char *runner);
static size_t WrapFibonacciRecursive(size_t element_index, size_t fa, size_t fb);


size_t FibonacciIterativ (size_t element_index)
{
	size_t fa = 0, fb = 1, fn = 0, i = 1;
	
	while(i < element_index)
	{
		fn = fa + fb;
		fa = fb;
		fb = fn;
		++i;
	}
	
	return fn;
}

static size_t WrapFibonacciRecursive(size_t element_index, size_t fa, size_t fb)
{			
	if(0 == element_index)
	{
		return fa;
	}
	
	fa = fa + fb;

	return WrapFibonacciRecursive(element_index - 1, fb, fa);
}

size_t FibonacciRecursive(size_t element_index)
{
	return WrapFibonacciRecursive(element_index, 0, 1);
}

node_t *FlipListIterativ(node_t* head)
{
	node_t *prev = NULL;
	node_t *curr = head;
	node_t *next = head->next_node;
	
	while(curr != NULL)
	{
		next = curr->next_node;
		curr->next_node = prev;
		prev = curr;
		curr = next;
	}
	
	return prev;
}

node_t *FlipListRecursive(node_t *head)
{
	node_t *new_head = NULL;

    if (head == NULL || head->next_node == NULL)
    {
        return head;
    }

    /* reverse the rest list and put
      the first element at the end */
    new_head = FlipListRecursive(head->next_node);
    head->next_node->next_node = head;

    /* tricky step -- see the diagram */
    head->next_node = NULL;

    /* fix the head pointer */
    return new_head;
}



size_t StrLen (const char *s)
{
	if(*s == '\0')
	{
		return 0;
	}

	return StrLen(s + 1) + 1;
}


int StrCmp(const char *str1, const char *str2)
{
	assert(str1);
	assert(str2);

    if('\0' != *str1 && *str1 == *str2)
    {
        ++str1;
        ++str2;
        
        return StrCmp(str1, str2);
    }
    
    return (*str1-*str2); 
}

int StrnCmp(const char *str1, const char *str2, size_t n)
{
	assert(str1);
	assert(str2);
	
    if('\0' != *str1 && n > 1 && *str1 == *str2)
    {
        ++str1;
        ++str2;
        
        return StrnCmp(str1, str2, n - 1);
    }
    
    return (*str1-*str2); 
}

char *StrCpy(char *dest, const char *src)
{
	assert(dest);
	assert(src);
	
	return WrapStrCpy(dest,src, dest);
}

static char *WrapStrCpy(char *dest, const char *src, char *runner)
{
	if(*src == '\0')
	{
		*runner = '\0';
		
		return dest;
	}
	
	*runner = *src;
	
	return (WrapStrCpy(dest, src + 1, runner + 1));
}

char *StrCat(char *dest, const char *src)
{
	if(*src != '\0')
	{
		if(*dest != '\0')
		{
			StrCat(dest + 1, src);
			return dest;
		}
		*dest = *src;
		StrCat(dest + 1, src + 1);	
	}
}

char *StrStr(const char *haystack, const char *needle)
{
	assert(haystack);
	assert(needle);

	if(*haystack == '\0')
	{
		return NULL;
	}

	if(*haystack == *needle)
	{
		if(0 == StrnCmp(haystack, needle, StrLen(needle)))
		{
			return (char*)haystack;
		}
	}
	
	return StrStr(haystack + 1, needle);
}
/*
void SortStackRecEmpty(stack_t *stack)
{
    void *temp = NULL;
    
	assert(stack);	
	
    if (!IsStackEmpty(stack))
    {
        temp = StackPeek(stack);
        StackPop(stack);
        SortStackRecEmpty(stack);
        SortStackRecInsert(stack, temp);
    } 
 }

void SortStackRecInsert(stack_t *stack, void * temp)
{
    void *tmp2;
    
    if (IsStackEmpty(stack) || *(int*)temp > *(int*)StackPeek(stack)) 
    {
        StackPush(stack, temp);
    }
	else
	{
		tmp2 = StackPeek(stack);
		StackPop(stack);
		SortStackRecInsert(stack, temp);
		StackPush(stack, tmp2);
	}
}

*/
/*________________EOF__________________*/
