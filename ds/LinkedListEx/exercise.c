/***************
*	Flip * HasLoop * HasIntersection 
****************/

#include <stdio.h>
#include <stdlib.h>
#include "/home/dvir/git/ds/include/sllist.h"

struct sllist
{
    sllist_node_t *head;
    sllist_node_t *tail;
};

struct sllist_node 
{
    void *data;
    sllist_node_t *next_node;
};


void PrintList(sllist_iter_t);
void FillList(sllist_t *list, char* src);
void Flip(sllist_t *list);
int HasLoop (const sllist_iter_t head);
void CreatLoop (sllist_iter_t head);
static sllist_iter_t JumpStart(sllist_iter_t iter, size_t n);
static size_t ListLen(sllist_iter_t iter);
sllist_iter_t FindIntersection(sllist_iter_t node1, sllist_iter_t node2);

int main()
{

	sllist_t list2;
	sllist_t *list1;
	sllist_iter_t iter1, iter2;
	char str1[] = "123456789";
	
	list1 = SLListCreate();
	
	FillList(list1, str1);
	
	iter1 = SLListBegin(list1);
	iter2 = iter1->next_node;
	iter2 = iter2->next_node;
	/*Flip(list1);*/
	PrintList(iter1);
	PrintList(iter2);
	
	iter1 = FindIntersection(iter1, iter2);
	if (iter1 == NULL)
	{
		puts("No Intersection");
	}
	else 
	{
		puts("Found intersection");
	}
	
	PrintList(iter1);
	PrintList(iter2);
	
	printf("%d\n", HasLoop(SLListBegin(list1)));
	
	return 0;
}

void FillList(sllist_t *list, char* src)
{
	size_t i = 0;	
	
	for(i = 0 ; '\0' != src[i] ; ++i)
	{
		SLListInsertBefore(list, SLListEnd(list), &src[i]);
	}
}

void PrintList(sllist_iter_t iter)
{		
	for( ; iter->data != NULL; iter = iter->next_node)
	{
		printf("%c", *(char*)iter->data);
	}
	puts("");
}

void Flip(sllist_t *list)
{
	sllist_iter_t prev, curr, next, temp;
	
	prev = NULL;
	next = NULL;
	curr = list->head;
	temp = list->head;
	while (list->tail != curr)
	{
		next = curr->next_node;
		curr->next_node = prev;
		prev = curr;
		curr = next;
	}
	
	
	list->tail = temp;
	list->head->next_node = prev;
}

int HasLoop (const sllist_iter_t head)
{
	sllist_iter_t slow, fast;
	
	slow = head;
	fast = slow->next_node;
	
	while(NULL != fast->next_node)
	{
		if( fast == slow)
		{
			return 1;
		}
		slow = slow->next_node;
		fast = fast->next_node;
		fast = fast->next_node;
	}
	return 0;
}

sllist_iter_t FindIntersection(sllist_iter_t node1, sllist_iter_t node2)
{
	size_t len1, len2, diff;
	len1 = ListLen(node1);
	len2 = ListLen(node2);
	
	if (len1 > len2)
	{
		diff = len1 - len2;
		node1 = JumpStart(node1, diff);
	}
	else if (len2 > len1)
	{
		diff = len2 - len1;
		node2 = JumpStart(node2, diff);
	}
	
	while (node1 && node2)
	{
		if (node1 == node2)
		{
			return node1;
		}
		node1 = node1->next_node;
		node2 = node2->next_node;
	}
	return NULL;
}

static size_t ListLen(sllist_iter_t iter)
{
	size_t counter = 0;
	
	while (iter != NULL)
	{
		iter = iter->next_node;
		++counter;
	}
	return counter;
}

static sllist_iter_t JumpStart(sllist_iter_t iter, size_t n)
{
	while (n > 0)
	{
		iter = iter->next_node;
		--n;
	}
	return iter;
}




