/**************************************
Author: Dvir Natan
Reviewer: Or Shoham
Status: Sent
Date: 26.10.21
***************************************/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#include "sorted_list.h"

struct sorted_list
{
    dllist_t *list;
    int (*cmp_func_t)(const void *one, const void *other);
};

sorted_list_t *SortedListCreate(int (*cmp_func_t)(const void *one, const void *other))
{
	sorted_list_t *solist;
	solist = malloc(sizeof(sorted_list_t));
	
	assert(NULL != cmp_func_t);
	
	if(NULL != solist)
	{
		solist->list = DLListCreate();
		solist->cmp_func_t = cmp_func_t;
		
		if(NULL == solist->list)
		{
			free(solist); solist = NULL;
		}
	}
	return solist;		
}

void SortedListDestroy(sorted_list_t *list)
{
	assert(NULL != list);	
	
	DLListDestroy(list->list);
	free(list); list = NULL;
}

sorted_list_iter_t SortedListBegin(const sorted_list_t *list)
{
	sorted_list_iter_t soliter;	
	
	assert(NULL != list);	
	
	soliter.inner_iter = DLListBegin(list->list);
	#ifndef NDEBUG
	soliter.list = (sorted_list_t*)list;
	#endif
	
	return soliter;
}

sorted_list_iter_t SortedListEnd(const sorted_list_t *list)
{
	sorted_list_iter_t soliter;	
	
	assert(NULL != list);
	
	soliter.inner_iter = DLListEnd(list->list);
	#ifndef NDEBUG
	soliter.list = (sorted_list_t*)list;
	#endif
	return soliter;
}

sorted_list_iter_t SortedListNext(const sorted_list_iter_t iter)
{
	sorted_list_iter_t soliter;	
	soliter.inner_iter = DLListNext(iter.inner_iter);
	#ifndef NDEBUG
	soliter.list = iter.list;
	#endif
	return 	soliter;
}

sorted_list_iter_t SortedListPrev(const sorted_list_iter_t iter)
{
	sorted_list_iter_t soliter;	
	soliter.inner_iter = DLListPrev(iter.inner_iter);
	#ifndef NDEBUG
	soliter.list = iter.list;
	#endif
	return soliter;	
}

int SortedListInsert(sorted_list_t *list, void *data)
{
	sorted_list_iter_t soliter;
	int sort = 0;

	assert(NULL != list);

	for(soliter.inner_iter = DLListBegin(list->list); 
		!DLListIsSameIter(soliter.inner_iter, DLListEnd(list->list)) &&
		(sort = list->cmp_func_t(DLListGetData(soliter.inner_iter), data)) <= 0;
		soliter = SortedListNext(soliter))
			;
			
	return DLListInsertBefore(soliter.inner_iter, data);
}

void SortedListRemove(sorted_list_iter_t iter)
{
	DLListRemove(iter.inner_iter);
}

void *SortedListGetData(const sorted_list_iter_t iter)
{
	return DLListGetData(iter.inner_iter);
}

size_t SortedListSize(const sorted_list_t *list)
{
	assert(NULL != list);

	return DLListSize(list->list);
}

int SortedListIsEmpty(const sorted_list_t *list)
{
	assert(NULL != list);

	return DLListIsEmpty(list->list);
}

int SortedListIsSameIter(const sorted_list_iter_t one, const sorted_list_iter_t other)
{
	assert(one.list == other.list);
	
	return DLListIsSameIter(one.inner_iter, other.inner_iter);
}

void *SoretdListPopBack(sorted_list_t *list)
{
	void *ret = NULL;
	sorted_list_iter_t soliter;
	
	assert(NULL != list);
	
	soliter = SortedListEnd(list);
	soliter = SortedListPrev(soliter);
	
	ret = SortedListGetData(soliter);
	DLListPopBack(list->list);
	
	return ret;
}

void *SoretdListPopFront(sorted_list_t *list)
{
	void *ret;
	sorted_list_iter_t soliter;
	
	assert(NULL != list);
	
	soliter = SortedListBegin(list);
	
	ret = SortedListGetData(soliter);
	DLListPopFront(list->list);
	
	return ret;
}

sorted_list_iter_t SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to,
			  int (*action)(void *data, void *params), void *params)
{
	sorted_list_iter_t soliter;
	
	assert(from.list == to.list);
	assert(NULL != action);
	
	soliter.inner_iter = DLListForEach(from.inner_iter, to.inner_iter, action, params);
	#ifndef NDEBUG
	soliter.list = from.list;
	#endif
	
	return soliter;
}

sorted_list_iter_t SortedListFind(const sorted_list_t *list,
		   sorted_list_iter_t from, sorted_list_iter_t to, void *data)
{
	sorted_list_iter_t soliter;
	
	assert(NULL != list);
	assert(from.list == to.list);
	
	for(soliter = from; !SortedListIsSameIter(soliter, to); soliter = SortedListNext(soliter))
	{
		if(0 == list->cmp_func_t(SortedListGetData(soliter), data))
		{
			return soliter;
		}
	}
	#ifndef NDEBUG
	soliter.list = from.list;
	#endif
	
	return soliter;
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to,
		   void *data, int (*is_match)(const void *, const void *))
{
	sorted_list_iter_t soliter;
	
	assert(NULL != is_match);
	assert(from.list == to.list);
	
	soliter.inner_iter = DLListFind(data, from.inner_iter, to.inner_iter, is_match);

	#ifndef NDEBUG
	soliter.list = from.list;
	#endif
	
	return soliter;
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	dllist_iter_t dest_runner;
	dllist_iter_t src_runner;
	
	assert(NULL != src);
	assert(NULL != dest);
	assert(src->cmp_func_t == dest->cmp_func_t);
	
	dest_runner = DLListBegin(dest->list);
	while (!DLListIsEmpty(src->list))
	{
		for (; !DLListIsSameIter(dest_runner, DLListEnd(dest->list)) &&
			 0 >= dest->cmp_func_t(DLListGetData(dest_runner), DLListGetData(DLListBegin(src->list)));
			 dest_runner = DLListNext(dest_runner))
			 ;
		if (DLListIsSameIter(dest_runner, DLListEnd(dest->list)))
		{
			DLListSplice(DLListBegin(src->list), DLListEnd(src->list), dest_runner);
			return;
		}
		for (src_runner = DLListBegin(src->list);
			 !DLListIsSameIter(src_runner, DLListEnd(src->list)) &&
			 0 < dest->cmp_func_t(DLListGetData(dest_runner), DLListGetData(src_runner));
			 src_runner = DLListNext(src_runner))
			 ;
		DLListSplice(DLListBegin(src->list), src_runner, dest_runner);
	}
}


