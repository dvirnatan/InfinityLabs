#include <stdio.h>
#include <stdlib.h>
int *SortArr(int *arr, size_t len);
int main()
{
	size_t i = 0;

	int arr[13] = {0,1,2,1,0,1,2,2,0,1,2,0,1};
	
	SortArr(arr, 13);
	
	for(i = 0; i < 13; ++i)
	{
		printf("%d",arr[i]);
	}
	puts("");
	
	return 0;
}

int *SortArr(int *arr, size_t len)
{
	size_t i = 0, j = 0;
	int *count = calloc(sizeof(int) , 3);
	
	for(i = 0; i < len; ++i)
	{
		count[arr[i]] += 1;
	}
	
	for(i = 0; i < 3; ++i)
	{
		while(count[i] > 0)
		{
			arr[j] = i;
			count[i] -= 1;
			++j;
		}
	}
	
	free(count);
	return arr;
}
