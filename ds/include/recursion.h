#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>
#include "stack.h"

typedef struct node node_t;

struct node
{
	int data;
	node_t *next_node;
};

node_t *FlipListRecursive(node_t *head);
size_t FibonacciIterativ (size_t element_index);
size_t FibonacciRecursive(size_t element_index);
size_t StrLen (const char *s);
int StrCmp(const char *str1, const char *str2);
char *StrCat(char *dest, const char *src);
char *StrCpy(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);
int StrnCmp(const char *str1, const char *str2, size_t n);
void SortStackRecInsert(stack_t *stack, void * temp);
void SortStackRecEmpty(stack_t *stack);
node_t *FlipListIterativ(node_t* head);
#endif /* __RECURSION_H__ */
