#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include <math.h> /* max */
#include <assert.h>
#include "avl.h"
#define COUNT 10

typedef enum children {LEFT = 0, RIGHT = 1, CHILDREN = 2}children_t; 

typedef struct avl_node avl_node_t;
struct avl_node
{
	void *data;
	size_t height;
	avl_node_t *child[CHILDREN]; 
};

struct avl
{
    avl_node_t *root;
    int (*cmp_func)(const void *one, const void *other);
};

/**************************************************************/

static void print2D(avl_node_t *root, int space)
{
	int i = 0;
    if (root == NULL)
        return;

    space += COUNT;

    print2D(root->child[RIGHT], space);

    printf("\n");
    for (i = COUNT; i < space; ++i)
        printf(" ");
    printf("%d, %lu\n", *(int *)(root->data), *(size_t *)&root->height);


    print2D(root->child[LEFT], space);
}

void print2DTree(avl_t *tree)
{
	print2D((tree->root), 0);
}

static void UpdateHeight(avl_node_t *root);

static int max(int a, int b)
{
	return (a > b)? a : b;
}

avl_t *AVLCreate(int (*cmp_func)(const void *, const void *))
{
	avl_t *tree = (avl_t *)malloc(sizeof(avl_t));
	if(tree)
	{
		tree->root = NULL;
		tree->cmp_func = cmp_func;
	}
	return tree;
}

static void DestroyRoot(avl_node_t *root)
{
	if(!root)
	{
		return;
	}
	DestroyRoot(root->child[LEFT]);
	DestroyRoot(root->child[RIGHT]);
	free(root); root = NULL;
}

void AVLDestroy(avl_t *tree)
{
	DestroyRoot(tree->root);
	free(tree); tree = NULL;
}

static size_t Height(avl_node_t *root)
{
	if(!root)
	{
		return 0;
	}
	return root->height;
}

static int GetBalance(avl_node_t *root)
{
	return Height(root->child[LEFT]) - Height(root->child[RIGHT]);
}

static avl_node_t *Balance(avl_node_t *root)
{
	avl_node_t *old_root = root;
	avl_node_t *cur_root;
	int balance = GetBalance(root);
	children_t child = balance > 0? LEFT : RIGHT;
	children_t grand_child;
	UpdateHeight(root);
	if(abs(balance) <= 1)
	{
		return root;
	}
	balance = GetBalance(root->child[child]);
	grand_child = balance > 0? LEFT : RIGHT;
	if(balance == 0)
	{
		grand_child = child;
	}
	if(child != grand_child)
	{
		cur_root = root->child[child];
		root->child[child] = cur_root->child[grand_child];
		cur_root->child[!child] = root->child[child]->child[child];
		root->child[child]->child[child] = cur_root;
	}
	root = root->child[child];
	old_root->child[child] = root->child[!child];
	root->child[!child] = old_root;
	
	UpdateHeight(root->child[child]);
	UpdateHeight(root->child[!child]);
	UpdateHeight(root);
	
	return root;
}

static void UpdateHeight(avl_node_t *root)
{
	root->height = 1 + max((root->child[LEFT]? root->child[LEFT]->height : 0), 
						(root->child[RIGHT]? root->child[RIGHT]->height : 0));
}

static avl_node_t *Insert(int (*cmp_func)(const void *, const void *), 
			avl_node_t *root, avl_node_t *new_node)
{
	int status;
	if(!root)
	{
		return new_node;
	}
	status = cmp_func(root->data, new_node->data);
	root->child[status < 0] = Insert(cmp_func, root->child[status < 0], new_node);
	root = Balance(root);
	return root;
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if(!new_node)
	{
		return 1;
	}
	new_node->data = data;
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->height = 1;
	tree->root = Insert(tree->cmp_func, tree->root, new_node);
	return 0;
}

static avl_node_t *Next(avl_node_t *root)
{
	if(!root->child[LEFT])
	{
		return root;
	}
	return Next(root->child[LEFT]);
}

static void *Find(int (*cmp_func)(const void *, const void *), 
			avl_node_t *root, const void *data)
{
	int status;
	if(!root)
	{
		return NULL;
	}
	status = cmp_func(root->data, data);
	if(status == 0)
	{
		return root->data;
	}
	return Find(cmp_func, root->child[status < 0], data);
}

static avl_node_t *Remove(int (*cmp_func)(const void *, const void *), 
			avl_node_t *root, const void *data)
{
	avl_node_t *node = root;
	void *old_data = root->data;
	int status;
	if(root)
	{
		status = cmp_func(root->data, data);
		if(status == 0)
		{
			if(root->child[LEFT] && root->child[RIGHT])
			{
				root->data = Next(node->child[RIGHT])->data;
				Next(node->child[RIGHT])->data = old_data;
				root->child[RIGHT] = Remove(cmp_func, root->child[RIGHT], data);
				root = Balance(root);
				return root;
			}
			node = root->child[root->child[RIGHT] != NULL];
			free(root); root = NULL;
			return node;
		}
		root->child[status < 0] = Remove(cmp_func, root->child[status < 0], data);
		root = Balance(root);
	}
	return root;
}

void AVLRemove(avl_t *tree, void *data)
{
	if(AVLIsEmpty(tree))
	{
		return;
	}
	tree->root = Remove(tree->cmp_func, tree->root, data);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	return Find(tree->cmp_func, tree->root, data);
}

static size_t Count(avl_node_t *root)
{
	if(!root)
	{
		return 0;
	}
	return 1 + Count(root->child[LEFT]) + Count(root->child[RIGHT]);
}

size_t AVLCount(const avl_t *tree)
{
	return Count(tree->root);
}

int AVLIsEmpty(const avl_t *tree)
{
	return tree->root == NULL;
}

size_t AVLHeight(const avl_t *tree)
{
	return tree->root->height;
}

static int PreForEach(avl_node_t *root, int (*action_func)(void *data, void *params), 
									void *params)
{
	if(!root)
	{
		return 1;
	}
	action_func(root->data, params); 
	PreForEach(root->child[LEFT], action_func, params);
	PreForEach(root->child[RIGHT], action_func, params);
	return 0;
}

static int InForEach(avl_node_t *root, int (*action_func)(void *data, void *params), 
									void *params)
{
	if(!root)
	{
		return 1;
	}
	InForEach(root->child[LEFT], action_func, params);
	action_func(root->data, params);
	InForEach(root->child[RIGHT], action_func, params);
	return 0;
}
static int PostForEach(avl_node_t *root, int (*action_func)(void *data, void *params), 
									void *params)
{
	if(!root)
	{
		return 1;
	}
	PostForEach(root->child[LEFT], action_func, params);
	PostForEach(root->child[RIGHT], action_func, params);
	action_func(root->data, params);
	return 0;
}

int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params), 
									void *params, traversal_t type)
{
	switch(type)
	{
		case PRE:
			return PreForEach(tree->root, action_func, params);
			break;
		case IN:
			return InForEach(tree->root, action_func, params);
			break;
		case POST:
			return PostForEach(tree->root, action_func, params);
			break;
	}
	return 0;
}

