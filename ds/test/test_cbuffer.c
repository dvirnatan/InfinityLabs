#include <stdio.h>/*printf*/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*rand*/

#include "cbuffer.h"

#define TEST(x, y) if(x != y) printf("Error in %d.\n", __LINE__)

void TestStage1();
void TestStage2();

int main()
{
	TestStage1();
	TestStage2();
	
	return 0;
}

void TestStage1()
{
	size_t capacity = 10;
	char arr1[50] = "123456789abcdefghi";
	char arr2[50];
	
	cbuff_t *cbuff = CBuffCreate(capacity);
	
	TEST(0, CBuffSize(cbuff));
	TEST(1, CBuffIsEmpty(cbuff));
	TEST(capacity, CBuffFreeSpace(cbuff));
	
	TEST(10, CBuffWrite(cbuff, arr1, (size_t)15));
	
	TEST(10, CBuffSize(cbuff));
	
	TEST(5, CBuffRead(cbuff, arr2, (size_t)5));
	TEST(5, CBuffSize(cbuff));
	TEST(5, CBuffFreeSpace(cbuff));
	
	TEST(5, CBuffWrite(cbuff, arr1, (size_t)15));
	TEST(10, CBuffSize(cbuff));
	
	TEST(10, CBuffRead(cbuff, arr2, (size_t)15));
	TEST(0, CBuffSize(cbuff));
	TEST(10, CBuffFreeSpace(cbuff));
	
	
	CBuffDestroy(cbuff);
}

void TestStage2()
{
	size_t capacity = 100;
	char arr1[100] = "123456789abcdefghi";
	char arr2[100];
	size_t n = 0;
	ssize_t size = 0;
	size_t size_cmp = 0;
	size_t i = 0;

	
	cbuff_t *cbuff = CBuffCreate(capacity);
	
	for(i = 0; i < 100000; ++i)
	{
		if(rand() % 2)
		{
			n = rand() % 100;
			size += CBuffWrite(cbuff, arr1, n);
			
			while(n > 0 && size_cmp < capacity)
			{
				++size_cmp;
				--n;
			}
			
			TEST(size_cmp, CBuffSize(cbuff));
		}
		else
		{
			n = rand() % 100;
			size -= CBuffRead(cbuff, arr2, n);
			
			while(n > 0 && size_cmp > 0)
			{
				--size_cmp;
				--n;
			}
			
			TEST(size_cmp, CBuffSize(cbuff));
		}
	 }
	
	CBuffDestroy(cbuff);

	
}


