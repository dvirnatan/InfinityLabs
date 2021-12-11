#include <stdio.h>

#include "avl.h"


int cmp_func (const void* one, const void *other)
{
	return (*(int*)one) - (*(int*)other);
}

int action_func(void *data, void *params)
{
	(void)params;
	printf("%d ", *(int*)data);
	return 0;
}

int main()
{

	int arr[10] = {30, 20, 10, 5, 15, 1, 0, 13, 16, 19};
	
	int i = 0;
	avl_t *tree;
	
	tree = AVLCreate(cmp_func);

	for(i = 0; i < 10; ++i)
	{	
		AVLInsert(tree,&arr[i]);
	}
	
	print2DTree(tree);

	puts("------------------------------------------------");
	
	AVLRemove(tree, &arr[1]);
	AVLRemove(tree, &arr[2]);
	AVLRemove(tree, &arr[3]);
	AVLRemove(tree, &arr[4]);
	AVLRemove(tree, &arr[5]);
	AVLRemove(tree, &arr[6]);
	
		
	print2DTree(tree);
	AVLDestroy(tree);
	
	

	return 0;
}



