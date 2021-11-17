/*************************************************
*		BTree
*		Author: Dvir Natan
*		Reviewer: Yair
*		Date: 17/11/21
*		Status: Send
**************************************************/

#include <stdlib.h>
#include <assert.h>

#include "btree.h"

#define CHILDRENS 2

enum CHILD
{
	left,
	right
};

typedef struct btree_node btree_node_t;

struct btree_node
{
	void *data;
	btree_node_t *parent;
	btree_node_t *child[CHILDRENS];
};

struct btree
{
    btree_node_t root;
    int (*cmp_func)(const void *one, const void *other, void *params);
    void *params;
};

static btree_iter_t BTreeMin(btree_iter_t iter)
{
	assert(iter);	
	
	while(iter->child[left] != NULL)
	{
		iter = iter->child[left];
	}
	return iter;
}

static btree_iter_t BTreeMax(btree_iter_t iter)
{
	assert(iter);	
	
	while(iter->child[right] != NULL)
	{
		iter = iter->child[right];
	}
	return iter;
}

btree_t *BTreeCreate(int (*cmp_func)
			(const void *one, const void *other, void *params), void *params)
{

	btree_t *tree;
	
	
	assert(NULL != cmp_func);
	
	tree = malloc(sizeof(btree_t));
	
	if(NULL == tree)
	{
		return NULL;
	}
	
	tree->cmp_func = cmp_func;
	tree->root.data = (void*)0XF44EC0DE;
	tree->root.parent = NULL;
	tree->root.child[left] = NULL;
	tree->root.child[right] = NULL;
	tree->params = params;
	
	return tree;
}

btree_iter_t BTreeBegin(const btree_t *tree)
{
	assert(tree);
	
	if(BTreeIsEmpty(tree))
	{
		return BTreeEnd(tree);
	}

	return BTreeMin(tree->root.child[left]);
}

btree_iter_t BTreeEnd(const btree_t *tree)
{	
	assert(tree);

	return (btree_iter_t)&tree->root;
}

btree_iter_t BTreeNext(btree_iter_t iter)
{
	assert(iter);
	
	if(iter->child[right] != NULL)
	{
		return BTreeMin(iter->child[right]);
	}
	
	while(iter->parent != NULL && iter == iter->parent->child[right])
	{
		iter = iter->parent;
	}
		
	return iter->parent;
}

btree_iter_t BTreePrev(btree_iter_t iter)
{
	assert(iter);
	
	if(iter->child[left] != NULL)
	{
		return BTreeMax(iter->child[left]);
	}
	
	while(iter->parent != NULL && iter == iter->parent->child[left])
	{
		iter = iter->parent;
	}
	
	return iter->parent;
}

int BTreeIsSameIter (btree_iter_t one, btree_iter_t other)
{
	assert(one);
	assert(other);
	
	return (one == other);
}

int BTreeIsEmpty (const btree_t *tree)
{
	assert(tree);
	
	return(tree->root.child[left] == NULL);
}

void *BTreeGetData (btree_iter_t iter)
{
	assert(iter);	
	
	return iter->data;
}

btree_iter_t BTreeInsert(btree_t *tree, void *data)
{
	btree_node_t *new_node;
	btree_iter_t runner, runner_parent;
	
	assert(tree);
	
	new_node = malloc(sizeof(btree_node_t));
	
	if(new_node == NULL)
	{
		return BTreeEnd(tree);
	}
	
	new_node->data = data;
	new_node->parent = NULL;
	new_node->child[left] = NULL;
	new_node->child[right] = NULL;
	
	runner = tree->root.child[left];
	runner_parent = NULL;
	
	while(runner != NULL)
	{
		runner_parent = runner;
		
		if(tree->cmp_func(runner->data, new_node->data, NULL) > 0)
		{
			runner = runner->child[left];
		}
		else
		{
			runner = runner->child[right];
		}
	}
	
	new_node->parent = runner_parent;
	
	if(NULL == runner_parent) /*empty tree*/
	{
		tree->root.child[left] = new_node;
		new_node->parent = &tree->root;
	}
	else
	{
		if(tree->cmp_func(runner_parent->data, new_node->data, NULL) > 0)
		{
			runner_parent->child[left] = new_node;
		}
		else
		{
			runner_parent->child[right] = new_node;
		}
	}
	
	return new_node;
}

void BTreeRemove(btree_iter_t iter)
{
	btree_iter_t child,to_remove;
	
	if(iter->child[left] == NULL || iter->child[right] == NULL)
	{
		to_remove = iter;
	}
	else
	{
		to_remove = BTreeNext(iter);
	}
	
	if(to_remove->child[left] != NULL) /* child = the child that is not NULL if both NULL */
	{									/* child = NULL */
		child = to_remove->child[left];
	}
	
	else
	{
		child = to_remove->child[right];
	}
	
	if(child != NULL) /* to_remove is not a leaf and not the root */
	{
		child->parent = to_remove->parent; /* firt step to delete to_remove, pointing child parent
								  				to to_remove parent */
	}								
	
	to_remove->parent->child[to_remove == to_remove->parent->child[right]] = child; /*second step */
												 
	if(to_remove != iter)
	{
		iter->data = to_remove->data;
	}	
	
	free(to_remove);
}


void BTreeDestroy(btree_t *tree)
{
	btree_iter_t runner = BTreeBegin(tree);
	btree_iter_t tmp;
	
	while(!BTreeIsEmpty(tree))
	{
		tmp = BTreeNext(runner);
		BTreeRemove(runner);
		runner = tmp;
	}
	free(tree); tree = NULL;
}

btree_iter_t BTreeFind(const btree_t *tree, void *data)
{
	btree_iter_t iter;
	int diff = 0;
	
	iter = tree->root.child[left];
	while(iter != NULL && (diff = tree->cmp_func(data, BTreeGetData(iter), NULL)))
	{
		if(diff > 0)
		{
			iter = iter->child[right];
		}
		else
		{
			iter = iter->child[left];
		}
	}
	
	return iter;
}

btree_iter_t BTreeForEach(btree_iter_t from, btree_iter_t to,
			int (*action_func)(void *data, void *params), void *params)
{
	assert(action_func);

	while(from != to)
	{
		if(action_func(from->data, params))
		{
			return from;
		}
		from = BTreeNext(from);
	}
	return to;
}

size_t BTreeSize(const btree_t *tree)
{
	btree_iter_t iter;
	size_t counter = 0;
	
	assert(tree);
	
	iter = BTreeBegin(tree);
	
	while(iter != BTreeEnd(tree))
	{
		iter = BTreeNext(iter);
		++counter;
	}
	
	return counter;
}





