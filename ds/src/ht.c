/***********************************************
HashTable
Author: Dvir Natan
Reviwer: Israel
Date: 02/12/2021
Status: 
********************************************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "ht.h"
#include "dllist.h"

struct hash_table
{
	size_t num_of_buckets;
	hash_func_t hash_func;
	is_match_t is_match_func;
	dllist_t **table;
};

ht_t *HTCreate(hash_func_t hash, is_match_t is_match_func, size_t num_of_buckets)
{
	ht_t *hash_table;
	dllist_t **table;
	size_t i = 0;

	assert(hash != NULL);
	assert(is_match_func != NULL);

	table = malloc(sizeof(dllist_t*) * num_of_buckets);
	hash_table = malloc(sizeof(ht_t));

	if(hash_table == NULL || table == NULL)
	{
		free(hash_table);
		free(table);
		return NULL;
	}

	for(i = 0; i < num_of_buckets; ++i)
	{
		table[i] = DLListCreate();

		if(table[i] == NULL)
		{
			while(i > 0)
			{
				DLListDestroy(table[i]);
				--i;
			}

			return NULL;
		}
	}

	if(i < num_of_buckets)
	{

		free(table);
		free(hash_table);
		return NULL;
	}

	hash_table->num_of_buckets = num_of_buckets;
	hash_table->hash_func = hash;
	hash_table->is_match_func = is_match_func;
	hash_table->table = table;

	return hash_table;
}

void HTDestroy(ht_t *ht)
{
	size_t i = 0;

	assert(ht != NULL);

	for(i = 0; i < ht->num_of_buckets; ++i)
	{
		DLListDestroy(ht->table[i]);
	}

	free(ht->table);
	free(ht);

	return;
}

int HTInsert(ht_t *ht, void *data)
{
	size_t key = 0;

	assert(ht != NULL);

	key = ht->hash_func(data);

	return DLListPushFront(ht->table[key], data);

}

void *HTFind(const ht_t *ht, const void *data)
{
	size_t key = 0;
	dllist_t *list = NULL;
	dllist_iter_t iter;

	assert(ht != NULL);

	key = ht->hash_func(data);
	list = ht->table[key];

	iter = DLListFind((void*)data, DLListBegin(list), DLListEnd(list), ht->is_match_func);

	if(DLListIsSameIter(iter, DLListEnd(list)))
	{
		return NULL;
	}

	return DLListGetData(iter);
}

void HTRemove(ht_t *ht, const void *data)
{
	size_t key = 0;
	dllist_t *list = NULL;
	dllist_iter_t iter;

	assert(ht != NULL);

	key = ht->hash_func(data);
	list = ht->table[key];
	iter = DLListFind((void*)data, DLListBegin(list), DLListEnd(list), ht->is_match_func);

	if(DLListIsSameIter(iter, DLListEnd(list)))
	{
		return;
	}

	DLListRemove(iter);
}

int HTForEach(const ht_t *ht, int (*action)(void *data, void *params) ,void *params)
{
	int action_func_status = 0;
	size_t i = 0;
	dllist_iter_t iter_status;
	dllist_t *list;

	assert(ht != NULL);
	assert(action);

	for(i = 0; i < ht->num_of_buckets && action_func_status == 1; ++i)
	{
		list = ht->table[i];

		iter_status = DLListForEach(DLListBegin(list), DLListEnd(list), action, params);
		action_func_status = DLListIsSameIter(iter_status, DLListEnd(list));
	}

	return action_func_status;
}

size_t HTSize(const ht_t *ht)
{
	size_t counter = 0, i = 0;

	assert(ht != NULL);

	for(i = 0; i < ht->num_of_buckets; ++i)
	{
		counter += DLListSize(ht->table[i]);
	}

	return counter;
}

int HTIsEmpty(const ht_t *ht)
{
	size_t i = 0;
	int is_empty = 1;

	for(i = 0; i < ht->num_of_buckets && is_empty != 0; ++i)
	{
		is_empty = DLListIsEmpty(ht->table[i]);
	}

	return is_empty;
}

double HTLoadFactor(const ht_t *ht)
{
	return (HTSize(ht) / ht->num_of_buckets);
}




/*____________________EOF____________________*/