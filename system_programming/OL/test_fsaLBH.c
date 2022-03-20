/*****************************
*****Fixed Size Allocator (System Programming)
*****Author: Lior Ben Harosh
*****Date: 05/11/2021 
******************************/

/* Note: this test is not so good, because it tests specific implementation
stuff , but it's good enough for testing everything works as expected in this
specific implementation */

#include <stdio.h> /* printf() , size_t */
#include <stdlib.h> /* malloc(), free() */

#include "fsa.h" /* fsa_t, fsa operations */

/* Function declarations */
void TestToFSASanityCheck (void);
void TestToFSACheck2 (void);

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

/* Main */
int main() 
{
	TestToFSASanityCheck();
	printf("No failures - Passed sanity check\n");
	TestToFSACheck2 ();
	printf("No failures - Passed, Enjoy the shabbat\n");
	return 0;
}

/***********************************************************************/
void TestToFSASanityCheck (void)
{
	void *test_1 = NULL, *test_2_init = NULL;
	char *test_2 = NULL;
	fsa_t *fsa_test = NULL, *fsa_test2 = NULL;
	void *addrs[10] = {NULL}, *addrs2[10] = {NULL};
	size_t pool_size = 0, block_size = 15, num_blocks = 10;
	size_t i = 0;
	size_t block_size_test = block_size + (WORD_SIZE - block_size % WORD_SIZE);
	
	pool_size = block_size_test * num_blocks + WORD_SIZE;
	/*line 62 - explanation below the tests */
	test_1 = (void *)malloc(sizeof(void *) * pool_size);
	test_2_init = (void *)malloc(sizeof(void *) * pool_size);

	TEST_NUM("FSASuggestSize", FSASuggestSize(num_blocks, block_size), pool_size);
	
	pool_size = FSASuggestSize(num_blocks, block_size);

	fsa_test = FSAInit(test_1, pool_size, block_size);
	TEST_NUM("FSAInit and/or FSACountFree", FSACountFree(fsa_test), num_blocks);
	
	for (i = 0; i < 10 ;++i)
	{
		addrs[i] = FSAAlloc(fsa_test);
		--num_blocks;
		TEST_NUM("FSAAlloc", FSACountFree(fsa_test), num_blocks);
		TEST_NUM("FSAAlloc and/or FSAInit", addrs[i], 
									(((char *)addrs[0]) + i * block_size_test));
		if (9 != i)
		{
		TEST_NUM("FSAAlloc and/or FSAInit", *(void **)addrs[i], 
							(((char *)addrs[0]) + (i + 1) * block_size_test));
		}
		else
		{
			TEST_NUM("FSAAlloc and/or FSAInit", *(void **)addrs[i], NULL);
		}
	}
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test));
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test));
	
	for (i = 0; i < 10 ;++i)
	{
		FSAFree(fsa_test, addrs[i]);
		if (0 == i)
		{
			TEST_NUM("FSAFree", *(void **)addrs[i], NULL);
		}
		else
		{
			TEST_NUM("FSAFree", *(void **)addrs[i], 
										((char *)addrs[i] - block_size_test));
		}
		++num_blocks;
		TEST_NUM("FSAFree", FSACountFree(fsa_test), num_blocks);
	}
	
	for (i = 0; i < 10 ;++i)
	{
		addrs[i] = FSAAlloc(fsa_test);
		--num_blocks;
	}
	
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test));
	
	FSAFree(fsa_test, addrs[3]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs[3], NULL);
	FSAFree(fsa_test, addrs[7]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs[7], addrs[3]);
	FSAFree(fsa_test, addrs[9]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs[9], addrs[7]);
	
	addrs[7] = FSAAlloc(fsa_test);
	addrs[9] = FSAAlloc(fsa_test);
	addrs[3] = FSAAlloc(fsa_test);
	num_blocks -= 3;
	TEST_NUM("FSAAlloc", FSACountFree(fsa_test), num_blocks);
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test));
	
	/************************/
	/**Unaligned pool test**/
	/************************/
	block_size = 15;
	num_blocks = 10; 
	pool_size = FSASuggestSize(num_blocks, block_size);
	--num_blocks;
	test_2 = (char *)test_2_init + 1;
	fsa_test2 = FSAInit(test_2, pool_size, block_size);
	TEST_NUM("FSAInit", FSACountFree(fsa_test2), num_blocks);
	
	for (i = 0; i < 9 ;++i)
	{
		addrs2[i] = FSAAlloc(fsa_test2);
		--num_blocks;
		TEST_NUM("FSAAlloc", FSACountFree(fsa_test2), num_blocks);
		TEST_NUM("FSAAlloc and/or FSAInit", addrs2[i],
								(((char *)addrs2[0]) + i * block_size_test));
		if (8 != i)
		{
		TEST_NUM("FSAAlloc and/or FSAInit", *(void **)addrs2[i], 
							(((char *)addrs2[0]) + (i + 1) * block_size_test));
		}
		else
		{
			TEST_NUM("FSAAlloc and/or FSAInit", *(void **)addrs2[i], NULL);
		}
	}
	TEST_NUM("FSAAlloc", FSACountFree(fsa_test2), 0);
	
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test2));
	
	for (i = 0; i < 9 ;++i)
	{
		FSAFree(fsa_test2, addrs2[i]);
		if (0 == i)
		{
			TEST_NUM("FSAFree", *(void **)addrs2[i], NULL);
		}
		else
		{
			TEST_NUM("FSAFree", *(void **)addrs2[i], 
										((char *)addrs2[i] - block_size_test));
		}
		++num_blocks;
		TEST_NUM("FSAFree", FSACountFree(fsa_test2), num_blocks);
	}
	
	for (i = 0; i < 9 ;++i)
	{
		addrs2[i] = FSAAlloc(fsa_test2);
		--num_blocks;
	}
	
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test2));
	
	FSAFree(fsa_test2, addrs2[3]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test2), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs2[3], NULL);
	FSAFree(fsa_test2, addrs2[7]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test2), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs2[7], addrs2[3]);
	FSAFree(fsa_test2, addrs2[8]);
	++num_blocks;
	TEST_NUM("FSAFree", FSACountFree(fsa_test2), num_blocks);
	TEST_NUM("FSAFree", *(void **)addrs2[8], addrs2[7]);
	
	addrs2[7] = FSAAlloc(fsa_test2);
	addrs2[8] = FSAAlloc(fsa_test2);
	addrs2[3] = FSAAlloc(fsa_test2);
	num_blocks -= 3;
	TEST_NUM("FSAAlloc", FSACountFree(fsa_test2), num_blocks);
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test2));
	
	free(test_2_init); test_2_init = NULL;
	free(test_1); test_1 = NULL;
}

/***********************************************************************/
void TestToFSACheck2 (void)
{
	void *test_1 = NULL, *test_2_init = NULL;
	char *test_2 = NULL;
	fsa_t *fsa_test = NULL, *fsa_test2 = NULL;
	size_t block_size = 8, num_blocks = 10, pool_size = block_size * num_blocks;
	size_t i = 0;
	
	test_1 = (void *)malloc(sizeof(void *) * pool_size);
	test_2_init = (void *)malloc(sizeof(void *) * pool_size);
	test_2 = (char *)test_2_init + 1;
	
	fsa_test = FSAInit(test_1, pool_size, block_size);
	fsa_test2 = FSAInit(test_2, pool_size, block_size);
	TEST_NUM("FSAInit and/or FSACountFree", FSACountFree(fsa_test), 9);
	TEST_NUM("FSAInit and/or FSACountFree", FSACountFree(fsa_test2), 8);
	for (i = 0; i < 8 ;++i)
	{
		FSAAlloc(fsa_test);
		FSAAlloc(fsa_test2);
	}
	TEST_NOT_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test));
	TEST_IS_NULL_POINTER("FSAAlloc", FSAAlloc(fsa_test2));
	
	free(test_2_init); test_2_init = NULL;
	free(test_1); test_1 = NULL;
}


	/*line 62 - explanation: */
	/* you have unaligned address and you want a blocks size 15 and 10 blocks,
	first you will make the blocks 16 so they will be multiples of word size,
	than you add another 8 for the metadata structure 
	AND you need to consider the possibility that  the start address might 
	be word unaligned - so we have to add another 8 in case alignment 
	correction will be needed */
