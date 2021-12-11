/*****************************
*****Variable Size Allocator (System Programming)
*****Author: Lior Ben Harosh
*****Date: 08/11/2021 
******************************/

/* Note: this test is not so good, because it tests specific implementation
stuff , but it's good enough for testing everything works as expected in this
specific implementation */

#include <stdio.h> /* printf() , size_t */
#include <stdlib.h> /* malloc(), free() */
#include <sys/types.h>
#include "vsa.h" /* fsa_t, fsa operations */

/* Function declarations */
void TestToVSASanityCheck (void);
static void MemoryMap (size_t *runner , size_t i , size_t j);

/* Macros */
#define DEFAULT     "\033[0m"
#define RED         "\033[31m"

#define TEST_IS_NULL_POINTER(name, real) \
    do { \
        ((void *)(real) == NULL) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p \n" DEFAULT, name, __LINE__, (void *)(real)); \
    } while (0)

#define TEST_NOT_NULL_POINTER(name, real) \
    do { \
        ((void *)(real) != NULL) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p \n" DEFAULT, name, __LINE__, (void *)(real)); \
    } while (0)

#define TEST_NUM(name, real, expected) \
    do { \
        ((real) == (expected)) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define WORD_SIZE sizeof(size_t)
#define ROUND_DOWN(num, rounder) (num - (num % rounder ))
/* Main */
int main() 
{
	TestToVSASanityCheck();
	printf("No failures - Passed sanity check\n");
	return 0;
}

/***********************************************************************/
void TestToVSASanityCheck (void)
{
	void *test_1 = NULL, *test_2 = NULL;
	char *test_2_init = NULL;
	vsa_t *vsa_test1 = NULL, *vsa_test2 = NULL;
	size_t pool_size1 = 160, pool_size2 = 160;
	void *addrs1[8] = {NULL}, *addrs2[8] = {NULL};
	size_t i = 0 , j = 0, k = 0;
	
	
	test_1 = (void *)calloc(1, sizeof(void *) * pool_size1);
	test_2_init = (char *)calloc(1, sizeof(void *) * pool_size2);
	test_2 = (void *)(test_2_init + 1);
	
	vsa_test1 = VSAInit(test_1, pool_size1);
	vsa_test2 = VSAInit(test_2, pool_size2);
	
	TEST_NUM("VSAInit", ((size_t)vsa_test1 - (size_t)test_1), 0);
	TEST_NUM("VSAInit", ((size_t)vsa_test2 - (size_t)test_2), 7);
	
	pool_size1 = ROUND_DOWN((pool_size1 - 2 * WORD_SIZE), WORD_SIZE);
	pool_size2 = ROUND_DOWN((pool_size2 - (2 * WORD_SIZE + 7)), WORD_SIZE);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 
													pool_size1); /* size 144 */
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 
													pool_size2); /* size 136 */

	for (i = 8, j = 0; j < 4; ++j, i += 8)
	{
		addrs1[j] = VSAAlloc(vsa_test1, i);
		pool_size1 -= (i + WORD_SIZE); /* block allocated + next header size */
		TEST_NOT_NULL_POINTER("VSAAlloc", addrs1[j]);
		TEST_NUM("VSAAlloc", VSALargestBlockAvailble(vsa_test1), pool_size1);
		addrs2[j] = VSAAlloc(vsa_test2, i);
		pool_size2 -= (i + WORD_SIZE);
		TEST_NOT_NULL_POINTER("VSAAlloc", addrs2[j]);
		TEST_NUM("VSAAlloc", VSALargestBlockAvailble(vsa_test2), pool_size2);
		k = i;
	}
	
	TEST_NUM("VSAAlloc", VSALargestBlockAvailble(vsa_test1), 32);
	TEST_NUM("VSAAlloc", VSALargestBlockAvailble(vsa_test2), 24);
	
	addrs1[j] = VSAAlloc(vsa_test1, 32); /* j = 4 */
	TEST_NOT_NULL_POINTER("VSAAlloc", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 24); /* j = 4 */
	TEST_NOT_NULL_POINTER("VSAAlloc", addrs2[j]);
	
	k = 1;
	printf("Memory Map #%lu\n",k);
	printf("vsa_test1:\n");
	MemoryMap((size_t *)vsa_test1, 5, 5);
	printf("vsa_test2:\n");
	MemoryMap((size_t *)vsa_test2, 5, 5);
	printf("\n");
	
	++j; /* j = 5 */
	addrs1[j] = VSAAlloc(vsa_test1, 1);
	TEST_IS_NULL_POINTER("VSAAlloc", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 1);
	TEST_IS_NULL_POINTER("VSAAlloc", addrs2[j]);
	
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 0);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 0);
	
	for (j = 1; j <= 2; ++j)
	{
		VSAFree(addrs1[j]);
		addrs1[j] = VSAAlloc(vsa_test1, 8 * (j + 1));
		TEST_NOT_NULL_POINTER("VSAFree", addrs1[j]);
		VSAFree(addrs2[j]);
		addrs2[j] = VSAAlloc(vsa_test2, 8 * (j + 1));
		TEST_NOT_NULL_POINTER("VSAFree", addrs2[j]);
	}
	
	addrs1[j] = VSAAlloc(vsa_test1, 1);
	TEST_IS_NULL_POINTER("VSAFree", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 1);
	TEST_IS_NULL_POINTER("VSAFree", addrs2[j]);
	
	for (j = 1; j <= 2; ++j)
	{
		VSAFree(addrs1[j]);
		VSAFree(addrs2[j]);
	}
	
	/* Explaining the numbers - after VSALargestBlockAvailble defragment of
	closeby unoccupied blocks happen - 40 bytes of both the blocks should be 
	released and another 8 of the extra header (only one header to rule them all)*/
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 
													(2 + 3) * 8 + WORD_SIZE);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 
													(2 + 3) * 8 + WORD_SIZE);
	
	j = 1;
	addrs1[j] = VSAAlloc(vsa_test1, 48);
	TEST_NOT_NULL_POINTER("VSALargestBlockAvailble", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 48);
	TEST_NOT_NULL_POINTER("VSALargestBlockAvailble", addrs2[j]);
	
	j = 2;
	addrs1[j] = VSAAlloc(vsa_test1, 1);
	TEST_IS_NULL_POINTER("VSALargestBlockAvailble", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 1);
	TEST_IS_NULL_POINTER("VSALargestBlockAvailble", addrs2[j]);
	
	VSAFree(addrs1[1]);
	VSAFree(addrs2[1]);
	VSAFree(addrs1[4]);
	VSAFree(addrs2[4]);
	/* 3 is occupied therefore no defragmentation suppose to happen */
	k = 2;
	printf("Memory Map #%lu\n",k);
	printf("vsa_test1:\n");
	MemoryMap((size_t *)vsa_test1, 5, 5);
	printf("vsa_test2:\n");
	MemoryMap((size_t *)vsa_test2, 5, 5);
	printf("\n");
	
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 48);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 48);
	j = 1;
	addrs1[j] = VSAAlloc(vsa_test1, 48);
	addrs2[j] = VSAAlloc(vsa_test2, 48);
	
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 32);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 24);
	
	j = 4;
	addrs1[j] = VSAAlloc(vsa_test1, 14);
	addrs2[j] = VSAAlloc(vsa_test2, 14);

	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 8);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 0);
	
	
	j = 5;
	addrs1[j] = VSAAlloc(vsa_test1, 1);
	TEST_NOT_NULL_POINTER("VSALargestBlockAvailble", addrs1[j]);
	addrs2[j] = VSAAlloc(vsa_test2, 1);
	TEST_IS_NULL_POINTER("VSALargestBlockAvailble", addrs2[j]);
	
	j = 6;
	addrs1[j] = VSAAlloc(vsa_test1, 1);
	TEST_IS_NULL_POINTER("VSALargestBlockAvailble", addrs1[j]);
	
	/* arr_number(size of memory in bytes including header) */
	k = 3;
	printf("Memory Map #%lu\n",k);
	printf("vsa_test1:\n");
	MemoryMap((size_t *)vsa_test1, 5, 5);
	printf("vsa_test2:\n");
	MemoryMap((size_t *)vsa_test2, 5, 5);
	printf("\n");
	
	VSAFree(addrs1[4]);
	VSAFree(addrs1[5]);
	VSAFree(addrs2[4]);
	
	k = 4;
	printf("Memory Map #%lu\n",k);
	printf("vsa_test1:\n");
	MemoryMap((size_t *)vsa_test1, 5, 5);
	printf("vsa_test2:\n");
	MemoryMap((size_t *)vsa_test2, 5, 5);
	printf("\n");
	
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test1), 32);
	TEST_NUM("VSALargestBlockAvailble", VSALargestBlockAvailble(vsa_test2), 24);
	
	free(test_1);
	free(test_2_init);
}

static void MemoryMap (size_t *runner , size_t i , size_t j)
{
	size_t k = 0, t = 0;
	for (k = 0; k < i ;++k)
	{
		for (t = k * i; t < (k + 1) * j; ++t)
		{
		printf("%5ld ",  *((ssize_t*)(runner + t)));
		}
	printf("\n");
	}
	
	
}
