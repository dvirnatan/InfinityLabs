/********************************************
	Author: Dvir Natan
	Reviewer: Maor Bergel
	Status: Sent
	Date: 26/9/21
********************************************/

#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */

long Pow2(unsigned int x, unsigned int y)
{
	return (x << y);
}


size_t IfPow2Loop (unsigned int n)
{
	unsigned c = 0;
	
	for (c = 0; n; ++c)
	{
		n &= n - 1;
	}
	if (c == 1)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

size_t IfPow2 (unsigned int n)
{
	unsigned c = (n - 1);
	
	if (n & c)
		return 0;
		
	return 1;
}

unsigned int AddOne (unsigned int n)
{
	unsigned c, res, temp;
	c = 0;
	res = temp = 1;
	
	if ((n & temp) == 0) /* n - even */
	{
		n = n | temp;
	}
	else
	{
		while (res > 0)
		{
			res = n & temp;
			++c;
			temp = temp << 1;
		}
		temp = temp >> 1;
		--c;
		n = n | temp;
		temp = -1 ;
		temp = temp << c;
		n = n & temp;
	}
	
	return n;
}

void ThreeBitsOn (unsigned int *arr, unsigned int len)
{
	unsigned int i, c, v;
	i = c = v = 0;
	
	for (i = 0; i < len; ++i)
	{
		v = arr[i];
		for (c = 0; v; ++c)
		{
			v &= v - 1;
		}
		if (c == 3)
		{
			printf("%u\n", arr[i]);
		}
	}
}	

unsigned char TwoAndSixAreOn (unsigned char c) 
{
	unsigned char v1 = 4;
	unsigned char v2 = 64;
	
	v1 &= c;
	v2 &= c;
	c = (v1 && v2);
	
	return c;
}

unsigned char TwoOrSixAreOn (unsigned char c) 
{
	unsigned char v1 = 4;
	unsigned char v2 = 64;
	
	v1 &= c;
	v2 &= c;
	c = (v1 || v2);
	
	return c;
}

unsigned char SwapThreeAndFive (unsigned char c) 
{
	unsigned char v1 = 8;
	unsigned char v2 = 32;
	
	v1 &= c;
	v2 &= c;
	v1 <<= 2;
	v2 >>= 2;
	v1 |= v2;
	v2 = 40;
	v2 = ~v2;
	c &= v2;
	c |= v1;
	
	return c;
}

unsigned char MirrorLoop (unsigned char v)
{
	size_t i = 0;
	unsigned char res = 0;
	
	for(i = 0; i < 8; ++i)
     		res |= ((v >> i) & 1) << (7 - i);
     		
     	return res;
}

unsigned char Mirror(unsigned char num)
{
	unsigned char half = 15; /*00001111*/
	unsigned char quarter = 51; /*00110011*/
	unsigned char eighth = 85; /*01010101*/
	
	num = ((num << 4) & half << 4) | ((num >> 4) & half);
	num = ((num << 2) & quarter << 2) | ((num >> 2) & quarter);
	num = ((num << 1) & eighth << 1) | ((num >> 1) & eighth);
	
	return num;	
}

unsigned int SixTeen (unsigned char v)
{
	unsigned int m = ~15;
	
	v &= m;
	return v;
}

void Swap (unsigned int *a, unsigned int *b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

unsigned int CountSetBitsLoop(unsigned int v)
{
	unsigned int count = 0;
	
	while (v) 
	{
		v = v & (v - 1);
		++count;
	}
	
	return count;
}

size_t CountSetBitsNoLoop (unsigned int i) 
{
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}

void PrintFloat(float num)
{
	int i = 8 * sizeof(float)-1;
  	int *ptr = (int *)(&num);
	int x;
	
	for(; i >= 0; --i)
	{
		x = ((*ptr >> i) & 1);
		printf("%d",x);
		
	}
	printf("\n");
}


	

