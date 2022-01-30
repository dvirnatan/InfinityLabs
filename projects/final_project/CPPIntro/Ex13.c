#include <stdio.h>

const int i = 3;
int main()
{
	int *ip = (int*)&i;
	int arr[i];
	*ip = 5;

	printf("i = %d *ip = %d\n", i, *ip);
	return 0;
}