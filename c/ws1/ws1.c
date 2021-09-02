#include <stdio.h>
#define power 10

void hello()
{
	char str[] = {0x48, 0x65, 0x6c, 0x6c,0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64};
	printf ("\"%s\"!\n",str);
}

int npow (int n)
{
	int i = power;
	int res = 1;
	
	for ( ; i > 0; i--)
	{
		res *= n;
	}
	return res;
}

int flip (int a)
{
	int b = 0;
	
	while (a > 0)
	{
		b += a % 10;
		b *= 10;
		a /= 10;
	}
	b /= 10;
	return b;
}

void swap (int *px, int *py)
{
	int temp = *px;
	*px = *py;
	*py = temp;	
}

