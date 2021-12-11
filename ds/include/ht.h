#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stddef.h>

typedef size_t (*hash_func_t)(const void *data);
typedef int (*is_match_t)(const void *one, const void *other);
/*
struct hash_table
{
	size_t num_of_buckets;
	hash_func_t hash_func;
	is_match_t is_match_func;
	dllist_t **table;
};
*/
typedef struct hash_table ht_t;

/* Creates a new hash table, num_of_buckets should be the range of hash func`s output
O(1) */
ht_t *HTCreate(hash_func_t hash, is_match_t is_match_func, size_t num_of_buckets);

/* O(n) */
void HTDestroy(ht_t *ht);

/* inserts a new member to the hash table, returns none-zero value if malloc failed
O(1) */
int HTInsert(ht_t *ht, void *data);

/* remove a member that match to data from the hash table
O(1)*/
void HTRemove(ht_t *ht, const void *data);

/* avarage, when hashing is optimal: O(1), worst case: O(n) */
/* Advanced - making the find function do caching as well in the container */
void *HTFind(const ht_t *ht, const void *data);

/*
HTForEach invokes the action_func on all members in the hash table
WARNING: changing parameters that affects hashing may result in undefined behavior
(action_func return status )  O(n) */
int HTForEach(const ht_t *ht, int (*action)(void *data, void *params) ,void *params);

/*
Count the number of members in the hash table O(n) */
size_t HTSize(const ht_t *ht);

/*
return 1 if empty or 0 other O(1) */
int HTIsEmpty(const ht_t *ht);



/* advanced */

/* O(n) */
double HTLoadFactor(const ht_t *ht);

/* Standard Deviation */
/* O(n) */
double HTStandardDeviation(const ht_t *ht); 

#endif /* __HASH_TABLE_H__ */
