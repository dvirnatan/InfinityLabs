#include <stdio.h>

//int j = 3;
int main()
{
	const int NUM_OF_THREADS = 10;
	const int i = 3;
	int *ip = (int*)&i;
	*ip = 5;
	int arr[i];
	int *j = (int*)&i;
	
	printf("i = %d *ip = %d j = %d\n", i, *ip, *j);

	return 0;
}
