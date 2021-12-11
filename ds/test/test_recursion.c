
#include "recursion.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	/************Fibonacci***************
	
	
		
	printf("%ld\n",FibonacciIterativ(10));
	printf("%ld\n",FibonacciRecursive(10));	
	
	/**************FlipList**************/
	
	int arr[5] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	node_t *iter;
	node_t one, two, three, four, five;
	one.next_node = &two;
	two.next_node = &three;
	three.next_node = &four;
	four.next_node = &five;
	five.next_node = NULL;
	
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
	
	iter = FlipListRecursive(&one);
	
	while(iter != NULL)
	{
		printf("%d ", iter->data);
		iter = iter->next_node;
	}
	puts("");



/********STR***********************	
	char *str2 = "abcd";
	char *str = "1234";
	char *needle = "p";
	char *dest = malloc(50); 
	/*char* res = StrStr(str, needle);*/
	
	
	
	
	/*StrCpy(dest, str2);*/
	

	
/*	printf("%ld\n", StrLen(str));	*/

/*	printf("%d\n", StrCmp(str,str2)); */ 

/*	printf("%s\n", StrCpy(dest, str)); 

	StrCpy(dest, str);

	StrCat(dest, str2);  

	printf("%s\n", dest);

	if(res != NULL)
	{
		printf("%s\n", res);	
	}
	else
	{
		puts("OK");
	}
*/
/*
	size_t i = 0, capacity = 20;
    stack_t *test_stack = StackCreate(capacity);
   
    int num_arr[10] = {1, 5, 2, 3, 7};
 
    void *data = NULL;
    
    for(i = 0; i < 5; ++i)
    {
        StackPush(test_stack, &num_arr[i]);
    }
    
    SortStackRecEmpty(test_stack); 

    for(i = 0; i < 5; ++i)
    {
        data = StackPeek(test_stack);
        printf("%d  ", *(int*)data);
        StackPop(test_stack);
    }
    
    StackDestroy(test_stack);
*/
	return 0;
}

