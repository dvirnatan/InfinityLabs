/*****************************
*****Sorted Linked List (Data Structures)
*****Author: Lior Ben Harosh
*****Date: 17/11/2021
******************************/

#include <stdio.h> /* printf() , size_t */

#include "btree.h" /* btree functions */

/* Function declarations */
static void TestToBTreeInitials (void);
static void TestToBTreeBasics (void);

static int Doubler (void *data, void *params);
static int CmpInts (const void *x, const void *y, void *params);

/* Macros */ 
#define DEFAULT     "\033[0m"
#define RED         "\033[31m"             /* Red */

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



/* Main */
int main() 
{
	TestToBTreeInitials();
	printf("No failures - Passed Initials Test (Destroy, Create)\n");
	TestToBTreeBasics();
	printf("No failures - Passed Test \n");
	
	return 0;
}
/*
void BTreeRemove(btree_iter_t iter);
 
*/

static void TestToBTreeInitials (void)
{
	btree_t *test_tree1 = BTreeCreate(&CmpInts, NULL);
	btree_t *test_tree2 = BTreeCreate(&CmpInts, NULL);
	
	TEST_NOT_NULL_POINTER("BTreeCreate", test_tree1);
	TEST_NOT_NULL_POINTER("BTreeCreate", test_tree2);
	
	BTreeDestroy(test_tree1);
	BTreeDestroy(test_tree2);
}

static void TestToBTreeBasics (void)
{
	size_t i = 0;
	long int j = 0;
	int arr1[13] = {7, 4, 5, 2, 3, 1, 20, 14, 10, 17, 31, 27, 42};
	int arr1_ordered_index[13] = {5, 3, 4, 1, 2, 0, 8, 7, 9, 6, 11, 10, 12};
	int test_arr1[13] = {1, 2, 3, 4, 5, 7, 10, 14, 17, 20, 27, 31, 42};
	int test_arr1twice[13] = {0}; /* gonna be twice the size of test_arr1 */
	int arr2[7] = {5, 3, 9, 2, 4, 7, 12};
	int arr2_ordered_index[7] = {3, 1, 4, 0, 5, 2, 6};
	int test_arr2[7] = {2, 3, 4, 5, 7, 9, 12};
	int nums[2] = {51 , 37};
	int x = 24;
	btree_iter_t iter1[13];
	btree_iter_t iter2[7];
	btree_iter_t iter_end[2], iter_begin[2], iter_testorder[2];
	
	btree_t *test_tree1 = BTreeCreate(&CmpInts, NULL);
	btree_t *test_tree2 = BTreeCreate(&CmpInts, NULL);
	
	TEST_NOT_NULL_POINTER("BTreeCreate", test_tree1);
	TEST_NOT_NULL_POINTER("BTreeCreate", test_tree2);
	
	iter_end[0] = BTreeEnd(test_tree1);
	iter_end[1] = BTreeEnd(test_tree2);
	
	TEST_NUM("BTreeIsSameIter / BTreeEnd", BTreeIsSameIter(iter_end[0], iter_end[1]), 0);
	
	iter_begin[0] = BTreeBegin(test_tree1);
	iter_begin[1] = BTreeBegin(test_tree2);
	
	TEST_NUM("BTreeBegin", BTreeIsSameIter(iter_begin[0], iter_begin[1]), 0);
	TEST_NUM("BTreeBegin", BTreeIsSameIter(iter_begin[0], iter_end[0]), 1);
	TEST_NUM("BTreeBegin", BTreeIsSameIter(iter_begin[1], iter_end[1]), 1);
	
	TEST_NUM("BTreeIsEmpty", BTreeIsEmpty(test_tree1), 1);
	TEST_NUM("BTreeSize", BTreeSize(test_tree1), 0);
	TEST_NUM("BTreeIsEmpty", BTreeIsEmpty(test_tree2), 1);
	TEST_NUM("BTreeSize", BTreeSize(test_tree2), 0);
	
	
	for (i = 0; i < (sizeof(arr1)/sizeof(int)); ++i)
	{
		iter1[i] = BTreeInsert(test_tree1, &arr1[i]);
		TEST_NUM("BTreeGetData/BTreeInsert", *(int *)BTreeGetData (iter1[i]), arr1[i]);
		;
	}
	for (i = 0; i < (sizeof(arr2)/sizeof(int)); ++i)
	{
		iter2[i] = BTreeInsert(test_tree2, &arr2[i]);
		TEST_NUM("BTreeGetData/BTreeInsert", *(int *)BTreeGetData (iter2[i]), arr2[i]);
	}
	
	TEST_NUM("BTreeIsEmpty", BTreeIsEmpty (test_tree1), 0);
	TEST_NUM("BTreeIsEmpty", BTreeIsEmpty (test_tree2), 0);
	TEST_NUM("BTreeInsert", BTreeSize(test_tree1), 13);
	TEST_NUM("BTreeInsert", BTreeSize(test_tree2), 7);
	
	iter_testorder[0] = BTreeBegin(test_tree1); 
	TEST_NUM("BTreeBegin", BTreeIsSameIter(iter_testorder[0], 
											iter1[arr1_ordered_index[0]]), 1);
	TEST_NUM("BTreeBegin", *(int *)BTreeGetData (iter_testorder[0]), 1);
	
	for (i = 0; i < (sizeof(arr1)/sizeof(int)); ++i)
	{
		TEST_NUM("BTreeNext", BTreeIsSameIter(iter_testorder[0], 
											iter1[arr1_ordered_index[i]]), 1);
		TEST_NUM("BTreeNext", *(int *)BTreeGetData (iter_testorder[0]),  
											test_arr1[i]);
		iter_testorder[0] = BTreeNext(iter_testorder[0]);
	}
	
	iter_testorder[1] = BTreeEnd(test_tree2);
	
	for (j = (long int)(sizeof(arr2)/sizeof(int)) - 1; j >= 0;  --j)
	{
		iter_testorder[1] = BTreePrev(iter_testorder[1]);
		TEST_NUM("BTreePrev", BTreeIsSameIter(iter_testorder[1], 
											iter2[arr2_ordered_index[j]]), 1);
		TEST_NUM("BTreePrev", *(int *)BTreeGetData (iter_testorder[1]),
											test_arr2[j]);
	}

	iter_testorder[0] = BTreeFind(test_tree1, &arr1[6]);
	iter_testorder[1] = BTreeFind(test_tree2, &arr2[0]);
	TEST_NUM("BTreeFind", *(int *)BTreeGetData (iter_testorder[0]), arr1[6]);
	TEST_NUM("BTreeFind", *(int *)BTreeGetData (iter_testorder[1]), arr2[0]);
	iter_testorder[0] = BTreeFind(test_tree1, &nums[0]);
	iter_testorder[1] = BTreeFind(test_tree2, &nums[1]);
	TEST_NUM("BTreeFind", BTreeIsSameIter(iter_testorder[0], BTreeEnd(test_tree1)), 1);
	TEST_NUM("BTreeFind", BTreeIsSameIter(iter_testorder[1], BTreeEnd(test_tree2)), 1);
	
	for (i = 0; i < (sizeof(arr1)/sizeof(int)); ++i)
	{
		test_arr1twice[i] = 2 * test_arr1[i];
	}
	
	iter_testorder[0] = BTreeBegin(test_tree1);
	iter_testorder[1] = BTreeEnd(test_tree1);
	/**/
	
	TEST_NUM("BTreeForEach", BTreeIsSameIter(iter_testorder[1], 
		BTreeForEach(BTreeBegin(test_tree1), BTreeEnd(test_tree1), &Doubler, NULL)), 1);
	
	for (i = 0; i < (sizeof(arr1)/sizeof(int)); ++i)
	{
		TEST_NUM("BTreeNext", BTreeIsSameIter(iter_testorder[0], 
											iter1[arr1_ordered_index[i]]), 1);
		TEST_NUM("BTreeNext", *(int *)BTreeGetData (iter_testorder[0]),  
											test_arr1twice[i]);
		iter_testorder[0] = BTreeNext(iter_testorder[0]);
	}
	
	iter_testorder[0] = BTreeFind(test_tree1, &test_arr1twice[5]);
	TEST_NUM("BTreeGetData", *(int *)BTreeGetData (iter_testorder[0]), test_arr1twice[5]);
	
	iter_testorder[1] = BTreeInsert(test_tree1, &x);
	
	
	BTreeRemove(iter_testorder[1]);
	iter_testorder[1] = BTreeFind(test_tree1, &x);
	TEST_NUM("BTreeRemove", BTreeIsSameIter(iter_testorder[1], BTreeEnd(test_tree1)), 1);
	
	
	BTreeRemove(iter_testorder[0]);
	iter_testorder[0] = BTreeFind(test_tree1, &test_arr1twice[5]);
	TEST_NUM("BTreeRemove", BTreeIsSameIter(iter_testorder[0], BTreeEnd(test_tree1)), 1);
	
	
	BTreeDestroy(test_tree1);
	BTreeDestroy(test_tree2);

}

static int Doubler (void *data, void *params)
{
	(void)params;
	*((int *)data) *= 2;
	
	return 0;
}

static int CmpInts (const void *x, const void *y, void *params)
{
	(void)params;
	return (*((int *)x) - *((int *)y));
}
