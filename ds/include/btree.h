/***********************
*API_BINARY_SEARCH_TREE*
************************/

#ifndef __BTREE_H__
#define __BTREE_H__

#include <stddef.h>

/*
struct btree
{
    btree_node_t root;
    int (*cmp_func)(const void *one, const void *other, void *params);
    void *params;
};

struct btree_node
{
	void *data;
	btree_node_t *parent;
	btree_node_t *child[2];//should use macro or enum
}
typedef struct btree_node btree_node_t;

*/

typedef struct btree btree_t;
typedef struct btree_node* btree_iter_t;

/*compare func should return a vlaue less, equal or greater then zero
if one is less, equal or greater then other respectivly*/
btree_t *BTreeCreate(int (*cmp_func)
			(const void *one, const void *other, void *params), void *params);

void BTreeDestroy(btree_t *tree);

/* Should not enter number already exist in the list.
return iter to the value inserted, or iter to end if failed
time complexity of O(n) */
btree_iter_t BTreeInsert(btree_t *tree, void *data);

/* remove the node of iter
remove of end or prev to begin is undefined
time complexity of O(n) */
void BTreeRemove(btree_iter_t iter);

/* return iter to the smallest value
time complexity of O(n) */
btree_iter_t BTreeBegin(const btree_t *tree);

/* return iter to the the node next to the largest value 
time complexity of O(1) */
btree_iter_t BTreeEnd(const btree_t *tree);

/* return the closest biger value to iter- Depends on your cmp function
next to end is undefined
time complexity of O(n) */
btree_iter_t BTreeNext(btree_iter_t iter);

/* return the closest smaller value to iter - Depends on your cmp function
prev to the previus node of begin is undefined
time complexity of O(n) */
btree_iter_t BTreePrev(btree_iter_t iter);

/* return 1 if same, 0 if not */
int BTreeIsSameIter (btree_iter_t one, btree_iter_t other);

/* return 1 if empty, 0 if not
Time complexity of O(1) */
int BTreeIsEmpty (const btree_t *tree);

/* return the number of valid nodes in the tree*/
size_t BTreeSize(const btree_t *tree);

void *BTreeGetData (btree_iter_t iter);

/*time complexity of average O(h)*/
btree_iter_t BTreeFind(const btree_t *tree, void *data);

/**/
btree_iter_t BTreeForEach(btree_iter_t from, btree_iter_t to,
				 int (*action_func)(void *data, void *params), void *params);

#endif /* __BTREE_H__*/


