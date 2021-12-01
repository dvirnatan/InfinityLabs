/*************************************************
*		AVL
*		Author: Dvir Natan
*		Reviewer: Matan
*		Date: 30/11/21
*		Status: 
**************************************************/

#include <stdlib.h> /* size_t */
#include <assert.h>
#include <stdio.h>/*DEBUG*/

#include "avl.h"


typedef enum children {LEFT = 0, RIGHT = 1, CHILDREN = 2} children_t; 

typedef int (*cmp_func_t)(const void *one, const void *other);

typedef struct avl_node avl_node_t;

typedef int(traversal_func_t)(avl_node_t *node, int (*action_func)(void *data, void *params), void *params);

static avl_node_t *IsMatch(avl_node_t *node, const void* data, cmp_func_t ,avl_node_t **p);

static avl_node_t *Min(avl_node_t *node);

static int PreOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int InOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int PostOrderTraversal(avl_node_t *node, int (*action_func)(void *data, void *params), void* params);

static int Count(void *data, void *params);

static void DestroyAux(avl_node_t *node);

static void UpdateHeight(avl_node_t *node);

static avl_node_t *Balance(avl_node_t *root);

static size_t GetHeight(avl_node_t *node);

static int GetBalance(avl_node_t *root);

static avl_node_t *RemoveAux(int (*cmp_func)(const void *, const void *), 
								     avl_node_t *node, const void *data);

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


avl_t *AVLCreate(int (*cmp_func) (const void *one, const void *other))
{
	avl_t *tree;
	
	assert(cmp_func != NULL);
	
	tree = malloc(sizeof(avl_t));
	
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
	assert(tree);

	return (tree->root == NULL);
}

size_t AVLHeight(const avl_t *tree)
{
	assert(tree);
	
	return tree->root->height;
}

void *AVLFind(const avl_t *tree, const void *data)
{
	avl_node_t *node = NULL;

	assert(tree);
	
    if(NULL == (node = IsMatch(tree->root, data, tree->cmp_func, &node)))
    {
    	return NULL;
    }
   
	return node->data;
}

static avl_node_t *IsMatch(avl_node_t *node, const void* data, cmp_func_t cmp_func, avl_node_t **p)
{
	int cmp;
	
	if(node == NULL || 0 == (cmp = cmp_func(node->data, data)))
	{
		return node;
	}
	
	*p = node;
	
	return IsMatch(node->child[(cmp < 0)], data, cmp_func, p);
}

static avl_node_t *InsertAux(int (*cmp_func)(const void *, const void *), 
							  avl_node_t *node, avl_node_t *new_node)
{
	int side = 0;
	
	if(node == NULL)
	{
		return new_node;
	}
	
	side = cmp_func(node->data, new_node->data);
	node->child[side < 0] = InsertAux(cmp_func, node->child[side < 0], new_node);
	node = Balance(node);
	return node;
}

int AVLInsert(avl_t *tree, void *data)
{
	avl_node_t *new_node;
	
	assert(tree);
	
	new_node = (avl_node_t *)malloc(sizeof(avl_node_t));
	
	if(new_node == NULL)
	{
		return 1;
	}
	
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->data = data;
	new_node->height = 1;
	
	tree->root = InsertAux(tree->cmp_func, tree->root, new_node);
	
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

static avl_node_t *RemoveAux(int (*cmp_func)(const void *, const void *), 
								     avl_node_t *node, const void *data)
{
	avl_node_t *tmp_node = node;
	void *tmp_data = node->data;
	int status = 0;
	
	if(node == NULL) 
	{
		return node;
	}
	
	status = cmp_func(node->data, data);
	
	if(status != 0)
	{
		node->child[status < 0] = RemoveAux(cmp_func, node->child[status < 0], data);
		node = Balance(node);
		
		return node;
	}
	
	if(NULL != node->child[LEFT] && NULL != node->child[RIGHT])
	{
		node->data = Min(tmp_node->child[RIGHT])->data;/*swap data with next*/
		Min(tmp_node->child[RIGHT])->data = tmp_data;
		
		node->child[RIGHT] = RemoveAux(cmp_func, node->child[RIGHT], data);
		node = Balance(node);
		
		return node;
	}
		
	tmp_node = node->child[node->child[RIGHT] != NULL];
	free(node); node = NULL;
	
	return tmp_node;
}

void AVLRemove(avl_t *tree, void *data)
{
	assert(tree != NULL);	
	
	if(!AVLIsEmpty(tree))
	{
		tree->root = RemoveAux(tree->cmp_func, tree->root, data);;
	}
}

int AVLForEach(avl_t *tree, int (*action_func)(void *data, void *params), 
									void *params, traversal_t type)
{
	assert(tree != NULL);	
	assert(action_func != NULL);
	
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
	
	assert(tree != NULL);	
	
	AVLForEach((avl_t*)tree, Count, &counter, PRE);
	return counter;
}

void AVLDestroy(avl_t *tree)
{
	assert(tree != NULL);		
	
	DestroyAux(tree->root);
	tree->root = NULL;
	
	free(tree);
}

static void DestroyAux(avl_node_t *node)
{
    if(node->child[LEFT] != NULL)
    {
        DestroyAux(node->child[LEFT]);
    }
    node->child[LEFT] = NULL;
	
    if(node->child[RIGHT] != NULL)
    {
        DestroyAux(node->child[RIGHT]);
    }
	node->child[RIGHT] = NULL;

    free(node); node = NULL;
}

static int MaxHeight(avl_node_t* left, avl_node_t* right)
{
	int height_left =  0;
	int height_right = 0;
	
	left == NULL ? (height_left = 0) : (height_left = left->height);
	
	right == NULL ? (height_right = 0) : (height_right = right->height);
	
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

static size_t GetHeight(avl_node_t *node)
{
	return node == NULL ? (0) : (node->height);
}

static int GetBalance(avl_node_t *root)
{
	return GetHeight(root->child[LEFT]) - GetHeight(root->child[RIGHT]);
}

static avl_node_t *Balance(avl_node_t *node)
{
	int balance = GetBalance(node);
	avl_node_t *tmp_node = node;
	avl_node_t *current = NULL;
	children_t grandson_to_balance = 0;
	children_t child_side_to_balance = balance > 0 ? LEFT : RIGHT;
	
	UpdateHeight(node);
	
	if(abs(balance) <= 1)
	{
		return node;
	}
	
	balance = GetBalance(node->child[child_side_to_balance]);
	grandson_to_balance = balance > 0 ? LEFT : RIGHT;
	
	if(balance == 0)
	{
		grandson_to_balance = child_side_to_balance;
	}
	
	if(child_side_to_balance != grandson_to_balance)
	{
		current = node->child[child_side_to_balance];
		node->child[child_side_to_balance] = current->child[grandson_to_balance];
		current->child[!child_side_to_balance] = node->child[child_side_to_balance]->child[child_side_to_balance];
		node->child[child_side_to_balance]->child[child_side_to_balance] = current;
	}
	
	node = node->child[child_side_to_balance];
	tmp_node->child[child_side_to_balance] = node->child[!child_side_to_balance];
	node->child[!child_side_to_balance] = tmp_node;

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

/*________________EOF________________________*/

