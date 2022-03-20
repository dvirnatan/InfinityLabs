#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define _N_  "\033[0m"
#define _BLD_  "\033[1m"
#define _U_  "\033[4m" 
#define _R_  "\033[31m"
#define _G_  "\033[32m"
#define _Y_  "\033[33m"
#define _P_  "\033[35m"
#define _B_  "\033[36m"

static int Random(int a, int b);
int RandomEx(int min, int max);

int main ()
{
	srand(time(0));
	
	// int counter = 0;
	// for(int j = 0; j > -100; --j)
	// {
	// 	for (int i = 1; i < 100; ++i)
	// 	{
	// 		++counter;
	// 		int res = Random(j, i);
	// 		if(res > i || res < j)
	// 		{
	// 			printf("error, res is: %d", res);
	// 		}
	// 	}
	// }
	// printf("counter: %d\n", counter);

	for(int i = 0; i < 6; ++i)
	{
		// int max = 6;
		// int min = 0;
		int ret = RandomEx(0 , 6);
		printf("%d ", ret);
	}
	printf("\n");

	return 0;
}


int RandomEx(int min, int max)
{
	static int index = -2;
	static int *arr = NULL;

	if(index == -2)
	{
		arr = malloc(max - min);
		index = max - min - 1;
		for(int i = 0; i <= index; ++i)
		{
			arr[i] = min++;
		}
	}
	
	if(index == -1)
	{
		free(arr);
		--index;
	}

	if(index > 0)
	{
		int Iret  = Random(0, index + 1);
		int Vret = arr[Iret];
		arr[Iret] = arr[index];
		index--;

		return Vret;
	}

	printf("index out of rang: %d\n", index);
	return -1;
}

static int Random(int a, int b)
{
	if(b == 0)
	{
		printf("b == 0\n");
		return -1;
	}
	
	return (((rand()% b) + a));
}