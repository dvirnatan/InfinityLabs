#include <stdio.h>
#include <stdlib.h>
void print_array (int * , int);


/* prosume that the variable len is known outside the function */
/* the funcions recive an array and copy it to a diffrent memory location */

int *copy_array (int *original, int len)
{
	int *new; 
	int i = 0;
	new = (int*)malloc (len * sizeof(int));
	for (i = 0; i < len ; ++i)
	{	
		*(new + i) = *(original + i);
	}	

	return new;
}

/* print an array */

void print_array (int *arr, int len)
{
	int i;
	for (i = 0; i < len ; ++i)
	{
		printf("%d ", *(arr + i));
	}
	printf("\n");
}

void q()
{

	static int s_i = 7;
	int *ptr2 = (int *)malloc(sizeof(int));
	int i = 7;
	int *ptr = &i;
	printf("&s_i: %p\n", (void *)&s_i);
	printf("&ptr: %p\n", (void *)&ptr);
	printf("&ptr2 %p\n", (void *)&ptr2);
	if(ptr)
	{
		int **ptr3 = &ptr;
		printf("&ptr3 %p\n", (void *)&ptr3);
	}
}


void swap (size_t *px, size_t *py)
{
	size_t temp = *px;
	*px = *py;
	*py = temp;	
}


size_t  StrLen (char *str)
{
	size_t res = 0;	
	while (*str != '\0')
	{
		++res;
		++str;
	}
	return res;
}


int StrCmp (const char *str1, const char *str2)
{
	while (*str1)
	{
		if (*str1 != *str2)
			break;
		++str1;
		++str2;
	}

	return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}





























