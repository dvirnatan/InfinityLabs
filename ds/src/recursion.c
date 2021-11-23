#include <stdio.h>


size_t FibonacciIterativ (size_t element_index);
size_t FibonacciRecursive(size_t element_index);
static size_t WrapFibonacciRecursive(size_t element_index, size_t fa, size_t fb);

typedef struct node node_t;

node_t *FlipList(node_t *node);
static node_t *WrapFlipList(node_t* node, node_t* next);

struct node
{
	int data;
	node_t *next_node;
};

int main()
{
	int arr[5] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	node_t *iter;
	node_t one, two, three, four, five;
	one.next_node = &two;
	two.next_node = &three;
	three.next_node = &four;
	four.next_node = &five;
	five.next_node = NULL;
	
	/*
	
	for(i = 0; i < 51; ++i)
	{	
		printf("%ld = %ld\n",i ,FibonacciIterativ(i));
	}
		
	printf("%ld\n",FibonacciRecursive(10));
	*/

	iter = &one;
	i = 0;
	while(iter != NULL)
	{
		iter->data = arr[i];
		iter = iter->next_node;
		++i;
	}
	
	iter = &one;	
	while(iter != NULL)
	{
		printf("%d ", iter->data);
		iter = iter->next_node;
	}
	puts("");
	
	iter = FlipList(&one);
	
	while(iter != NULL)
	{
		printf("%d ", iter->data);
		iter = iter->next_node;
	}
	puts("");
	

	

	return 0;
}

size_t FibonacciIterativ (size_t element_index)
{
	size_t fa = 0, fb = 1, fn = 0, i = 0;
	
	while(i < element_index)
	{
		fn = fa + fb;
		fa = fb;
		fb = fn;
		++i;
	}
	
	return fa;
}

static size_t WrapFibonacciRecursive(size_t element_index, size_t fa, size_t fb)
{			
	if(0 == element_index)
	{
		return fa;
	}
	
	fa = fa + fb;

	return WrapFibonacciRecursive(element_index - 1, fb, fa);
}

size_t FibonacciRecursive(size_t element_index)
{
	return WrapFibonacciRecursive(element_index, 0, 1);
}


static node_t *WrapFlipList(node_t* node, node_t* next)
{
	node_t *temp = next->next_node;
	next->next_node = node;
	
	if(temp == NULL)
	{
		return node;
	}
	
	return WrapFlipList(next, temp);
}


node_t *FlipList(node_t *node)
{
	return WrapFlipList(NULL, node);
}






