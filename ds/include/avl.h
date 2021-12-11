/***********************
*API_AVL_TREE*
************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>

/*

enum children {LEFT = 0, RIGHT = 1, CHILDREN = 2}; 

struct avl
{
    avl_node_t *root;
    int (*cmp_func)(const void *one, const void *other);
};

struct avl_node
{
	void *data;
	size_t height;
	avl_node_t *child[CHILDREN]; 
}

typedef struct avl_node avl_node_t;

*/

typedef struct avl avl_t;

typedef enum {PRE = 0, IN = 1, POST = 2} traversal_t;

/* compare func should return a vlaue less, equal or greater then zero, if "one"
** is less, equal or greater then "other" respectively */
avl_t *AVLCreate(int (*cmp_func) (const void *one, const void *other));

/* time complexity O(n)*/
void AVLDestroy(avl_t *tree);

/* index of inserted element should not already exist in tree.
** return success or failure of allocation. 
** time complexity of Find [O(logn) or O(h)] + tree re-organization */
int AVLInsert(avl_t *tree, void *data);

/* remove the node that holds data.
** time complexity of Find [O(logn) or O(h)] + tree re-organization */
void AVLRemove(avl_t *tree, void *data);

/* return 1 if empty, 0 if not.
** Time complexity of O(1) */
int AVLIsEmpty(const avl_t *tree);

/* return the number of valid nodes in the tree. Time complexity O(n) */
size_t AVLCount(const avl_t *tree);

/* return the height of the tree. Time complexity of O(1) */
size_t AVLHeight(const avl_t *tree);

/* returns searched element or NULL for failure. 
** time complexity of O(h) [O(logn)] 
** can use its own IsMatch service func for more funcionality */
void *AVLFind(const avl_t *tree, const void *data);

/* perform action on every node, traversal as user chooses
** complexity O(n) */
int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params), 
									void *params, traversal_t type);


void print2DTree(avl_t *tree);

#endif /* __AVL_H__*/

