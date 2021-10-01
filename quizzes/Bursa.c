#include <stdio.h>
#include <stddef.h>


struct result
{
	size_t i_min;
	size_t i_max;
	size_t profit;
};

struct result Bursa (int *arr, size_t len);	

int main()
{
	int arr[10] = {2, 3, 2, 4, 10, 8, 5, 7, 4, 4};
	struct result res;
	res = Bursa (arr, 10);
	printf("i_min = %ld, i_max = %ld, profit = %ld\n", res.i_min,
		res.i_max, res.profit);
	
	return 0;
}


struct result Bursa (int *arr, size_t len)
{

	size_t i = 0;
	size_t i_min = 0;
	size_t i_max = 0;
	int profit = 0;
	int min = arr[0];
	int max = arr[0];
	struct result ret;

	for( i = 0; i < len - 1; ++i )
	{
		if( arr[i] < min )
		{
			min = arr[i];
			max = arr[i];
			i_min = i;
		}
		else if( arr[i] > max )
		{
			max = arr[i];
			i_max = i;
		}
		if( profit < (max - min))
		{
			profit = max - min;
			ret.i_min = i_min;
			ret.i_max = i_max;
			ret.profit = profit;
		}
	}
	return ret;		
}
