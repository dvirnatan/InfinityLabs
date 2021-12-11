/*******************************
	Author: Dvir Natan
	Date:12/11/2021
	
********************************/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "sorts.h"


static void printArr(int *arr, size_t size);

static void Swap (int *a, int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


static int CmpFunc(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

int CountingSort(int *array, size_t size)
{
	int *B;
	size_t *C;
	int i = 0;
	int max = array[0];
	int j = 0;
	
	for(i = 0; i < (int)size; ++i)
	{
		if(max < array[i])
		{
			max = array[i];
		}
	}
	
	B = malloc(sizeof(int) * size);
	C = calloc(max + 1, sizeof(size_t));
	
	if(NULL == C || NULL == B)
	{
		puts("Malloc has failed");
		
		free(C);
		free(B);
		
		return 1;
	}
	
	for(i = 0; i < (int)size; ++i)
	{
		j = array[i];
		C[j] += 1;
	}
	
	for(i = 1; i <= max; ++i)
	{
		C[i] +=  C[i - 1];
	}
	
	for(i = (int)size - 1; i >= 0; --i)
	{
		j = array[i];
		C[j] -= 1;
		B[C[j]] = array[i];
	}
	
	for(i = 0; i < (int)size; ++i)
	{
		array[i] = B[i];
	}

	free(B);
	free(C);
	
	return 0;
}


int RadixSort(int *array, size_t size)
{
	int max, i  = 0, digit_place = 1;
	int *res = malloc(sizeof(int) * size);
	
	if(res == NULL)
	{
		puts("Malloc has failed");
		return 1;
	}
	
	max = array[i];
	
	for(i = 0; i < (int)size; ++i)
	{
		if(max < array[i])
		{
			max = array[i];
		}		
	}
	
	while(max / digit_place > 0)
	{
		int count[10] = {0};
		
		for(i = 0; i < (int)size; ++i)
		{
			count[(array[i]/digit_place) % 10] += 1;
		}
		
		for(i = 1; i < 10; ++i)
		{
			count[i] += count[i - 1];
		}
		
		for(i = size - 1; i >= 0; --i)
		{
			res[count[(array[i] / digit_place) % 10] - 1] = array[i];
			count[(array[i] / digit_place) % 10] -= 1;
		}
		
		for(i = 0; i < (int)size; ++i)
		{
			array[i] = res[i];
		}
		
		digit_place *= 10;
	}
	free(res);
	
	return 0;
}


void BubbleSort(int *array,size_t size)
{
	size_t i = 0, swapped = 1;
		
	while(swapped > 0)
	{
		swapped = 0;

		for(i = 0 ; i + 1 < size; ++i)
		{
			if(array[i] > array[i+1])
			{
				Swap(&array[i], &array[i + 1]);
				swapped = 1;
			}
		}
	}
}


void SelectionSort(int *array, size_t size)
{
	size_t i = 0, j = 0, min_index = 0;
	int min = 0;
	
	for(i = 0; i < size; ++i)
	{
		
		min = array[i];
		
		for(j = i + 1; j < size; ++j)
		{
			if(array[j] < min)
			{
				min = array[j];
				min_index = j;
			}
		}
		
		Swap(&array[i], &array[min_index]);
	}
}

void InsertionSort(int * array, size_t size)
{
	size_t i = 0, j = 0;
	
	while(i < size)
	{
		j = i;
		
		while(j > 0 && array[j-1] > array[j])
		{
			Swap(&array[j], &array[j-1]);
			--j;
		}		
		++i;
	}
}

static void printArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		printf("%d ",arr[i]);
	}
	puts("");
}

#define size 20
int main ()
{
	size_t i = 0;
	clock_t start_t ,end_t;
	int ret = 0;
	int *array = malloc (size * sizeof(int));
	
	srand(time(0));
	
	while(i < size)
	{
		array[i] = rand() % 100;
		++i;
	}

	printArr(array, size);
	
	start_t = clock();	
	
	RadixSort(array, size);
	
	end_t = clock();
	
	printArr(array,size);

	printf("ret = %d time = %f\n",ret,(double)(end_t - start_t) / CLOCKS_PER_SEC);
	
	free(array);
	
	return 0;
}


