		/********************
		 * Auther: Dvir Natan
		 * Reviewer: Eli
		 * Status: Approved
		 * Date: 19.10.21
		 ********************/
 
		/* Singly Linked List */

#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include "sllist.h" 

struct sllist_node 
{
    void *data;
    sllist_node_t *next_node;
};

struct sllist
{
    sllist_node_t *head;
    sllist_node_t *tail;
};

sllist_t *SLListCreate(void)
{
    sllist_t *list = malloc(sizeof(sllist_t));
    
    if(NULL != list)
    {
        list->head = malloc(sizeof(sllist_node_t));
        list->tail = malloc(sizeof(sllist_node_t));
        list->head->data = NULL;
        list->tail->data = NULL;
        list->head->next_node = list->tail;
        list->tail->next_node = NULL;
    }
    
    return list;
}

void SLListDestroy(sllist_t *list)
{
	sllist_iter_t runner = list->head;
	sllist_iter_t tmp = list->head;
	
	while(NULL != tmp)
	{
		runner = tmp;
		tmp = runner->next_node;	
		
		free(runner);	
	}
	free(list);
}

sllist_iter_t SLListBegin(const sllist_t *list)
{
	assert (NULL != list);
	return list->head->next_node;
}

sllist_iter_t SLListEnd(const sllist_t *list)
{
	assert (NULL != list);
	return list->tail;    
}

sllist_iter_t SLListNext(const sllist_iter_t iter)
{
	assert (NULL != iter);
	return iter->next_node;
}

int SLListIsSameIter(const sllist_iter_t one, const sllist_iter_t other)
{
	assert(NULL != one);
	assert(NULL != other);
	
	return (one == other);
}

void *SLListGetData(const sllist_iter_t iter)
{
	assert(NULL != iter);
	return iter->data;
}

void SLListSetData(sllist_iter_t iter, void* data)
{
	assert(NULL != iter);
	iter->data = data;
}

int SLListInsertBefore(sllist_t *list, sllist_iter_t iter, void *data)
{    
	sllist_node_t *new_node = NULL;

	assert(NULL != list);
	assert(NULL != iter);
	
	new_node = malloc(sizeof(sllist_node_t));
   
	if(NULL == new_node)
	{
		return 1;
	}
		
	new_node->data = iter->data;
	iter->data = data;
    
	new_node->next_node = iter->next_node;
	iter->next_node = new_node;
     
	if(SLListIsSameIter(iter, SLListEnd(list)))
	{
		list->tail = new_node;
	}
    
    return 0;
}

void SLListRemove(sllist_t *list, sllist_iter_t iter)
{
	sllist_iter_t tmp;
	
	assert(NULL != list);
	assert(NULL != iter);

	tmp = iter->next_node;
	*iter = *tmp;
	
	if(tmp == list->tail)
	{
		list->tail = iter;
	}
	
	free (tmp);
}

sllist_iter_t SLListFind(void* data, 
		   sllist_iter_t from, sllist_iter_t to,
		   int (*is_match)(const void *, const void *))
{
	int is_match_flag = 0;
	
	assert(NULL != from);
	assert(NULL != to);	
	assert(NULL != is_match);
	
	while(from != to)
	{
		is_match_flag = is_match(data, from->data);
		
		if (1 == is_match_flag)
		{
			return from;
		}
		from = SLListNext(from);
	}

	return to;
}

sllist_iter_t SLListForEach(sllist_iter_t from, sllist_iter_t to, 
		   int (*action_func)(void *data, void *params),
		   void *params)
{
	int flag = 0;
	
	assert(NULL != from);
	assert(NULL != to);	
	assert(NULL != action_func);
	
	flag = action_func(from->data, params);
	
	do
	{
		from = SLListNext(from);
		flag = action_func(from->data, params);

	}
	while (to != from && flag == 0);
	
	return from;	
}

size_t SLListCount(const sllist_t *list)
{
	sllist_iter_t runner = NULL;
	size_t cnt = 0;
	
	assert(NULL != list);
	
	runner = SLListBegin(list);
	
	while (list->tail != runner)
	{
		++cnt;
		runner = runner->next_node;
	}
		
	return cnt;
}

int SLListIsEmpty(const sllist_t *list)
{
	assert(NULL != list);
	
	return (SLListBegin(list) == SLListEnd(list));
}

void SLListAppend(sllist_t *dest, sllist_t *src)
{
	assert(NULL != src);
	assert(NULL != dest);
	
	*(dest->tail) = *(SLListBegin(src));
	*(SLListBegin(src)) = *(src->tail);	
	
	dest->tail = SLListEnd(src);
	src->tail = SLListBegin(src);
}

