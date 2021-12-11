/********************
 * Auther: Gal Oiring
 * Reviewer: Lior Ben Harosh
 * Status: Approved
 * Date: 1.12.21
 ********************/

#include <stdlib.h>
#include <assert.h>
#include <stdio.h> 

#include "avl.h"

typedef enum children {LEFT = 0, RIGHT = 1, CHILDREN = 2}children_t; 

typedef int (*cmp_func_t)(const void *one, const void *other);

typedef struct avl_node avl_node_t;

typedef int(traversal_func_t)(avl_node_t *node, int (*action_func)(void *data, void *params), void *params);

/*	*	*	*	*	*	*	*	*	*	*	*/

static avl_node_t *IsMatch(avl_node_t *node, const void* data, cmp_func_t ,avl_node_t **p);

static avl_node_t *Min(avl_node_t *node);

static int PreOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int InOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int PostOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int Count(void *data, void *params);

static void DestroyFunc(avl_node_t *node);

static void UpdateHeight(avl_node_t *node);

static avl_node_t *Balance(avl_node_t *root);

static size_t Height(avl_node_t *node);

static int GetBalance(avl_node_t *root);

/*	*	*	*	*	*	*	*	*	*	*	*	*/

traversal_func_t *function_lut[3] = {&PreOrderTraversal, &InOrderTraversal, &PostOrderTraversal};

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
};

/*****************************/

avl_t *AVLCreate(int (*cmp_func) (const void *one, const void *other))
{
	avl_t *tree;
	
	tree = (avl_t*)malloc(sizeof(avl_t));
	
	if(tree == NULL)
	{
		return NULL;
	}
	
	tree->root = NULL;
	tree->cmp_func = cmp_func;
	
	return tree;
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(NULL != tree);

	return (tree->root == NULL);
}

size_t AVLHeight(const avl_t *tree)
{
	assert(NULL != tree);
	
	return tree->root->height;
}

void *AVLFind(const avl_t *tree, const void *data)
{
	avl_node_t *node = NULL;
	
	assert(NULL != tree);
	
    if(NULL == (node = IsMatch(tree->root, data, tree->cmp_func, &node)))
    {
    	return NULL;
    }
   
	return node->data;
}

static avl_node_t *IsMatch(avl_node_t *node, const void* data, cmp_func_t cmp_func, avl_node_t **parent)
{
	int cmp;
	if(node == NULL || 0 == (cmp = cmp_func(node->data, data)))
	{
		return node;
	}
	
	*parent = node;
	
	return IsMatch(node->child[(cmp < 0)], data, cmp_func, parent);
}

static avl_node_t *Insert(int (*cmp_func)(const void *, const void *), 
							  avl_node_t *node, avl_node_t *new_node)
{
	int side = 0;
	
	if(node == NULL)
	{
		return new_node;
	}
	
	side = cmp_func(node->data, new_node->data);
	
	node->child[side < 0] = Insert(cmp_func, node->child[side < 0], new_node);
	node = Balance(node);
	
	return node;
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	
	if(new_node == NULL)
	{
		return 1;
	}
	
	assert(NULL != tree);
	
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->data = data;
	new_node->height = 1;
	
	tree->root = Insert(tree->cmp_func, tree->root, new_node);
	
	return 0;
}

static avl_node_t *Min(avl_node_t *node)
{
	if(node->child[LEFT] == NULL)
	{
		return node;
	}
	
	return Min(node->child[LEFT]);
}

static avl_node_t *Remove(int (*cmp_func)(const void *, const void *), 
								  avl_node_t *node, const void *data)
{
	avl_node_t *tmp_node = node;
	void *tmp_data = node->data;
	int status = 0;
	
	if(node != NULL) 
	{
		status = cmp_func(node->data, data);
		
		if(status == 0)
		{
			if(node->child[LEFT] && node->child[RIGHT])
			{
				node->data = Min(tmp_node->child[RIGHT])->data;/*swap data with next*/
				Min(tmp_node->child[RIGHT])->data = tmp_data;
				
				node->child[RIGHT] = Remove(cmp_func, node->child[RIGHT], data);
				node = Balance(node);
				return node;
			}
			tmp_node = node->child[node->child[RIGHT] != NULL];
			free(node); node = NULL;
			return tmp_node;
		}
		node->child[status < 0] = Remove(cmp_func, node->child[status < 0], data);
		node = Balance(node);
	}
	
	return node;
}

void AVLRemove(avl_t *tree, void *data)
{
	if(AVLIsEmpty(tree))
	{
		return;
	}
	
	tree->root = Remove(tree->cmp_func, tree->root, data);
}

int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params), 
									void *params, traversal_t type)
{
	assert(NULL != tree);

	if(!tree->root)
	{
		return 1;
	}

	return function_lut[type](tree->root, action_func, params);
}

static int Count(void *data, void *params)
{
	(void)data;
	*(size_t*)params += 1;
	
	return 0;
}

size_t AVLCount(const avl_t *tree)
{
	size_t counter = 0;
	
	assert(NULL != tree);
	
	AVLForEach((avl_t*)tree, Count, &counter, PRE);
	return counter;
}

void AVLDestroy(avl_t *tree)
{
	assert(NULL != tree);
	
	if(NULL != tree->root)
	{
		DestroyFunc(tree->root);
		tree->root = NULL;
	}

	free(tree);
}

static void DestroyFunc(avl_node_t *node)
{
    if(NULL == node)
	{
		return;
	}

	if(node->child[LEFT] != NULL)
    {
        DestroyFunc(node->child[LEFT]);
    }
    node->child[LEFT] = NULL;
	
    if(node->child[RIGHT] != NULL)
    {
        DestroyFunc(node->child[RIGHT]);
    }
	node->child[RIGHT] = NULL;

    free(node); node = NULL;
}

static int MaxHeight(avl_node_t* left, avl_node_t* right)
{
	int height_left =  0;
	int height_right = 0;
	
	left == NULL ? (height_left = -1) : (height_left = left->height);
	
	right == NULL ? (height_right = -1) : (height_right = right->height);
	
	return height_left >= height_right ? (height_left) : (height_right);
}

static void UpdateHeight(avl_node_t *node)
{
	if(node->child[LEFT] != NULL)
	{
		UpdateHeight(node->child[LEFT]);
	}
	
	if(node->child[RIGHT] != NULL)
	{
		UpdateHeight(node->child[RIGHT]);
	}
	
	node->height = 1 + MaxHeight(node->child[LEFT], node->child[RIGHT]);
}

static size_t Height(avl_node_t *node)
{
	return node == NULL ? (0) : (node->height);
}

static int GetBalance(avl_node_t *root)
{
	return Height(root->child[LEFT]) - Height(root->child[RIGHT]);
}

static avl_node_t *Balance(avl_node_t *node)
{
	avl_node_t *tmp_node = node;
	avl_node_t *current;
	int balance = GetBalance(node);
	children_t child_side = balance > 0? LEFT : RIGHT;
	children_t grand_child_side;
	
	UpdateHeight(node);
	
	if(abs(balance) <= 1)
	{
		return node;
	}
	balance = GetBalance(node->child[child_side]);
	grand_child_side = balance > 0? LEFT : RIGHT;
	
	if(balance == 0)
	{
		grand_child_side = child_side;
	}
	
	if(child_side != grand_child_side)
	{
		current = node->child[child_side];
		node->child[child_side] = current->child[grand_child_side];
		current->child[grand_child_side] = node->child[child_side]->child[child_side];
		node->child[child_side]->child[child_side] = current;
	}
	
	node = node->child[child_side];
	tmp_node->child[child_side] = node->child[!child_side];
	node->child[!child_side] = tmp_node;
		
	UpdateHeight(node);
	
	return node;
}

/*	*	*	*	*	*	*	*	Traversal	*	*	*	*	*	*	*	*	*/

static int PreOrderTraversal(avl_node_t *node, int (*action_func)
                                        (void *data, void *params),void *params)
{
    int status = 0;
    
    if(!status)
    {
        status = action_func(node->data,params);
    }

    if(!status && node->child[LEFT])
    {
        status = PreOrderTraversal(node->child[LEFT],action_func,params);
    }

    if(!status && node->child[RIGHT])
    {
        status = PreOrderTraversal(node->child[RIGHT],action_func,params);
    }

    return status;
}

static int PostOrderTraversal(avl_node_t *node, int (*action_func)
                                        (void *data, void *params),void *params)
{
    int status = 0;

    if(!status && node->child[LEFT])
    {
        status = PostOrderTraversal(node->child[LEFT],action_func,params);
    }

    if(!status && node->child[RIGHT])
    {
        status = PostOrderTraversal(node->child[RIGHT],action_func,params);
    }

    if(!status)
    {
        status = action_func(node->data,params);
    }

    return status;
}

static int InOrderTraversal(avl_node_t *node, int (*action_func)
                                        (void *data, void *params),void *params)
{
    int status = 0;

    if(!status && node->child[LEFT])
    {
        status = InOrderTraversal(node->child[LEFT],action_func,params);
    }

    if(!status)
    {
        status = action_func(node->data,params);
    }

    if(!status && node->child[RIGHT])
    {
        status = InOrderTraversal(node->child[RIGHT],action_func,params);
    }

    return status;
}

/****	****	 ****	****	Print	 **** ****	****	****	****/
#define COUNT 10
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
		
	printf("%d, (%ld)\n", *(int *)(root->data), root->height);

	print2D(root->child[LEFT], space);
}

void print2DTree(avl_t *tree)
{
    print2D((tree->root), 0);
}

