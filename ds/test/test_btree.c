#include <stdio.h>

#include "btree.h"

int action_func(void *data, void *params)
{
	(void)params;
	printf("%d ", *(int*)data);
	
	return 0;
}

int cmp_func (const void* one, const void *other, void * params)
{
	(void)params;
	
	return (*(int*)one) - (*(int*)other);
}

int main()
{

	int arr[8] = {15, 8, 21, 27, 30, 29, 6, 10};
	
	int x = 15;
	int i = 0;
	
	btree_t *tree;
	btree_iter_t iter;
	
	tree = BTreeCreate(cmp_func, NULL);
	iter = NULL;
		printf("size = %ld\n", BTreeSize(tree));		
	while(i < 8 && iter != BTreeEnd(tree))
	{
		iter = BTreeInsert(tree, &arr[i]);
		++i;
	}
	
	printf("size = %ld\n", BTreeSize(tree));		
	BTreeForEach(BTreeBegin(tree), BTreeEnd(tree), action_func, NULL);
	puts("");
	
	iter = BTreeFind(tree, &arr[0]);
	
	printf("%d\n", *(int*)BTreeGetData(iter));		
	
	BTreeRemove(iter);
	
	BTreeInsert(tree, &x);

	BTreeForEach(BTreeBegin(tree), BTreeEnd(tree), action_func, NULL);
	puts("");	
	
			
	BTreeDestroy(tree);
	return 0;
}

