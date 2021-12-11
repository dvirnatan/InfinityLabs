/*****************************
*****Memory Mapping Part 1 (System Programming)
*****Author: Lior Ben Harosh
*****Date: 04/11/2021 
******************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc() */

/* Function declarations */
extern void extern_fun(void);
void local_fun(void);
static void static_fun (void);

/* Global Variables */
const int global_const_x = 4;
int global_x = 5;
int global_unintialized;

static const int static_global_const_x = 8;
static int static_global_x = 9;

void HeapAndStackGrowth()
{
	int x;
	static size_t counter = 0;
	char *arr = (char *)malloc(sizeof(char) * 1);
	
	printf("&heap_var #%lu = %p\n", counter + 1, (void *)arr);
	printf("&stack_var #%lu = %p\n", counter + 1, (void *)&x);
	++counter;
	
	if(counter < 10) /* max size without core dump 174637 */
	{
		HeapAndStackGrowth();
	}
}

/* Main */
int main(int argc, char *argv[], char *envp[]) 
{
	int *heap_var = (int *)malloc(1 * sizeof(int));
	char *str_lit = "hey";
	(void)argc;
	
	printf("Order of addresses (low to high):\n");
	printf("code->rodata->data->BSS->Heap->stack\n");
	printf("(below the code segment and above the stack segment - kernel segments probably)\n\n");
	printf("\nheap memory segment:\n");
	printf("&heap_var = %p\n", (void *)&(*heap_var));
	
	printf("\nstack memory segment:\n");
	printf("&str_lit = %p \n", (void *)&str_lit);
	printf("&argv[1] = %p , &envp = %p\n", (void *)&argv[1], (void *)&envp);
	
	static_fun();
	extern_fun();
	local_fun();
	
	printf("\ncode memory segment:\n");
	printf("&static_fun = %p , &extern_fun = %p\n", static_fun, extern_fun);
	printf("&local_fun = %p\n", &local_fun);
	
	printf("\ndata memory segment:\n");
	printf("&global_const_x (rodata) = %p , &global_x = %p\n", (void *)&global_const_x, 
															(void *)&global_x);
	printf("&static_global_const_x (rodata) = %p , &static_global_x = %p\n",
					 (void *)&static_global_const_x, (void *)&static_global_x);
	
	printf("\nBSS memory segment:\n");
	printf("&global_unintialized = %p\n", (void *)&global_unintialized);
	
	printf("\nStack and Heap growth:\n");
	HeapAndStackGrowth();
	printf("\nHeap grows up (in addresses) \n");
	printf("Stack grows down (in addresses) \n");
	
	
	free(heap_var);
	return 0;
}
/***********************************************************************/
static void static_fun (void)
{
	int x;
	printf("&x = %p\n", (void *)&x);
}

void local_fun (void)
{
	const int const_local_x = 2;
	int local_x = 3;
	
	static const int static_const_local_x = 6;
	static int static_local_x = 7;
	printf("&const_local_x = %p , &local_x = %p\n", (void *)&const_local_x, (void *)&local_x);
	printf("\ndata memory segment: \n");
	printf("&static_const_local_x (rodata) = %p , &static_local_x = %p\n",
									 (void *)&static_const_local_x, (void *)&static_local_x);
}

