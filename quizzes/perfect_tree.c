#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define max(a,b) ((a > b) ? (a) : (b))

typedef struct Node
{
    struct Node *right;
    struct Node *left;
	int hight;
}Node_t;

static void BuildPerfectTree(Node_t *root)
{
	if(root->hight == 0)
	{
		return;
	}

	Node_t *left = calloc(1, sizeof(Node_t));
	Node_t *right = calloc(1, sizeof(Node_t));

	root->left = left;
	root->right = right;

	left->hight = root->hight - 1;
	right->hight = root->hight - 1;

	BuildPerfectTree(left);
	BuildPerfectTree(right);
	return;
}

static int CountNodes(Node_t * root)
{
	if(root == NULL)
	{
		return 0;
	}

	return CountNodes(root->left) + CountNodes(root->right)  + 1;
}

static int CheckHight(Node_t * root)
{
	if(root == NULL)
	{
		return 0;
	}

	return max(CheckHight(root->left), CheckHight(root->right))  + 1;
}

static int IsPerfectTree(Node_t * root)
{
	int hight = CheckHight(root);
	int num_of_nodes = CountNodes(root);
	if(num_of_nodes == pow(2, hight) - 1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int main()
{
	Node_t root;
	root.left = NULL;
	root.right = NULL;
	root.hight =  4;

	BuildPerfectTree(&root);
	
	printf("Nodes: %d\n", CountNodes(&root));
	printf("Side: %d\n", CheckHight(&root));

	printf("IsPerfect: %d\n",IsPerfectTree(&root));

	return 0;
}