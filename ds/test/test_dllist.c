/*****************************
*****Doubly Linked List (Data Structures)
*****Author: Lior Ben Harosh
*****Date: 21/10/2021 
******************************/

#include <stdio.h> /* printf() , size_t */
#include <string.h> /* strcmp() , strlen() */
#include "dllist.h" /* dllist_node_t, dllist_t, dllist_iter_t */

/* Function declarations */
static void TestToDLListInitials (void);
static void TestToDLListBasicFuncs (void);
static void TestToDLListSpecialFuncs (void);

static int CompareInts (const void *x, const void *y);
static int ZeroFunc (void *x, void *y);


/* Macros */ 
#define DEFAULT     "\033[0m"
#define RED         "\033[31m"             /* Red */
#define POINTERS_IS_MATCH(name, real, expected) \
    do { \
        ((void *)(real) == (void *)(expected)) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p Expected Value: %p \n" DEFAULT, name, __LINE__, (void *)(real), (void *)(expected)); \
    } while (0)

#define POINTERS_IS_NOT_MATCH(name, real, expected) \
    do { \
        ((void *)(real) != (void *)(expected)) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p Expected Value: %p \n" DEFAULT, name, __LINE__, (void *)(real), (void *)(expected)); \
    } while (0)

#define TEST_NOT_NULL_POINTER(name, real) \
    do { \
        ((void *)(real) != NULL) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p \n" DEFAULT, name, __LINE__, (void *)(real)); \
    } while (0)

#define TEST_IS_NULL_POINTER(name, real) \
    do { \
        ((void *)(real) == NULL) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Pointer Value: %p \n" DEFAULT, name, __LINE__, (void *)(real)); \
    } while (0)
    
#define TEST_NUM(name, real, expected) \
    do { \
        ((real) == (expected)) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Real: %ld, Expected: %ld\n" DEFAULT, name, __LINE__, (long) (real), (long) (expected)); \
    } while (0)

#define TEST_IS_MATCH_STRINGS(name, real, expected) \
    do { \
        (strcmp((real), (expected))) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Real: %s, Expected: %s\n" DEFAULT, name, __LINE__, (char *) (real), (char *) (expected)); \
    } while (0)

/* Main */
int main() 
{
	TestToDLListInitials();
	TestToDLListBasicFuncs();
 	TestToDLListSpecialFuncs ();
 	
	puts("Test completed");
	return 0;
}

static void TestToDLListInitials (void)
{
	dllist_t *test_dllist = DLListCreate();
	dllist_t *test_dllist2 = DLListCreate();
	

	TEST_NOT_NULL_POINTER("DLListCreate", test_dllist);
	TEST_NOT_NULL_POINTER("DLListCreate", test_dllist2);
	
	TEST_NOT_NULL_POINTER("DLListBegin", DLListBegin(test_dllist));
	TEST_NOT_NULL_POINTER("DLListBegin", DLListBegin(test_dllist2));
	
	TEST_NOT_NULL_POINTER("DLListEnd", DLListEnd(test_dllist));
	TEST_NOT_NULL_POINTER("DLListEnd", DLListEnd(test_dllist2));	
	
	POINTERS_IS_MATCH("DLListBegin & DLListEnd", DLListBegin(test_dllist), DLListEnd(test_dllist));
	POINTERS_IS_MATCH("DLListBegin & DLListEnd", DLListBegin(test_dllist2), DLListEnd(test_dllist2));
	POINTERS_IS_NOT_MATCH("DLListBegin & DLListEnd", DLListBegin(test_dllist2), DLListEnd(test_dllist));
	POINTERS_IS_NOT_MATCH("DLListBegin & DLListEnd", DLListBegin(test_dllist), DLListEnd(test_dllist2));
	
	POINTERS_IS_NOT_MATCH("DLListPrev", DLListPrev(DLListEnd(test_dllist)), DLListEnd(test_dllist));
	POINTERS_IS_NOT_MATCH("DLListPrev", DLListPrev(DLListEnd(test_dllist2)), DLListEnd(test_dllist2));
	POINTERS_IS_NOT_MATCH("DLListPrev", DLListPrev(DLListEnd(test_dllist)), DLListEnd(test_dllist2));
	
	POINTERS_IS_MATCH("DLListNext", DLListNext(DLListPrev(DLListEnd(test_dllist))), DLListEnd(test_dllist));
	POINTERS_IS_MATCH("DLListNext", DLListNext(DLListPrev(DLListEnd(test_dllist2))), DLListEnd(test_dllist2));
	POINTERS_IS_NOT_MATCH("DLListNext", DLListNext(DLListPrev(DLListEnd(test_dllist))), DLListEnd(test_dllist2));
	POINTERS_IS_NOT_MATCH("DLListNext", DLListNext(DLListPrev(DLListEnd(test_dllist2))), DLListEnd(test_dllist));
	
	TEST_IS_NULL_POINTER("DLListCreate or DLListEnd",DLListNext(DLListEnd(test_dllist)));
	TEST_IS_NULL_POINTER("DLListCreate or DLListBegin",DLListPrev(DLListPrev(DLListBegin(test_dllist))));
	
	TEST_NUM("DLListIsSameIter", DLListIsSameIter(DLListEnd(test_dllist), DLListEnd(test_dllist)), 1);
	TEST_NUM("DLListIsSameIter", DLListIsSameIter(DLListEnd(test_dllist2), DLListEnd(test_dllist)), 0);

	
	DLListDestroy(test_dllist); test_dllist = NULL;
	DLListDestroy(test_dllist2); test_dllist2 = NULL;
}

static void TestToDLListBasicFuncs (void)
{
	dllist_t *test_dllist = DLListCreate();
	dllist_iter_t test_iter = NULL;
	dllist_iter_t test_iter2 = NULL;
	int i = 0;
	int arr_front[4] = {4, 3, 2, 1};
	int arr_back[4] = {8, 7, 6, 5};
	
	TEST_NOT_NULL_POINTER("DLListCreate", test_dllist);
	
	TEST_NUM("DLListSize", DLListSize(test_dllist), 0);
	TEST_NUM("DLListIsEmpty", DLListIsEmpty(test_dllist), 1);
	
	TEST_NUM("DLListInsertBefore", DLListInsertBefore(DLListEnd(test_dllist), &i), 0); 
	++i;
	TEST_NUM("DLListInsertBefore", DLListInsertBefore(DLListEnd(test_dllist), &i), 0); 
	
	test_iter = DLListPrev(DLListEnd(test_dllist));
	
	TEST_NUM("DLListInsertBefore", 	DLListIsSameIter(DLListEnd(test_dllist), test_iter), 0);
	TEST_NUM("DLListInsertBefore", 	DLListIsSameIter(DLListBegin(test_dllist), test_iter), 0);
	
	test_iter = DLListPrev(test_iter);
	
	TEST_NUM("DLListInsertBefore", 	DLListIsSameIter(DLListEnd(test_dllist), test_iter), 0);
	TEST_NUM("DLListInsertBefore", 	DLListIsSameIter(DLListBegin(test_dllist), test_iter), 1);
	
	TEST_NUM("DLListSize", DLListSize(test_dllist), 2);
	TEST_NUM("DLListIsEmpty", DLListIsEmpty(test_dllist), 0);
	
	test_iter = DLListNext(test_iter);
	
	DLListRemove(DLListBegin(test_dllist));
	
	TEST_NUM("DLListRemove", DLListSize(test_dllist), 1);
	TEST_NUM("DLListRemove", DLListIsSameIter(DLListBegin(test_dllist), test_iter), 1);
	TEST_NUM("DLListRemove", DLListIsEmpty(test_dllist), 0);
	
	TEST_NUM("DLListGetData", *(int *)DLListGetData(test_iter), 1);
	
	i = 1337;
	DLListSetData(test_iter, &i);

	TEST_NUM("DLListSetData", *(int *)DLListGetData(test_iter), 1337);
	

	DLListSetData(test_iter, &i);
	
	test_iter2 = test_iter;
	
	for (i = 0; i < 4; ++i)
	{
		TEST_NUM("DLListPushFront", DLListPushFront(test_dllist, &arr_front[i]), 0);
		test_iter = DLListPrev(test_iter);
		TEST_NUM("DLListPushFront", *(int *)DLListGetData(test_iter), arr_front[i]);
		
		TEST_NUM("DLListPushBack", DLListPushBack(test_dllist, &arr_back[i]), 0);
		test_iter2 = DLListNext(test_iter2);
		TEST_NUM("DLListPushBack", *(int *)DLListGetData(test_iter2), arr_back[i]);
	}
	
	TEST_NUM("DLListPushBack/DLListPushFront", DLListSize(test_dllist), 9);
	
	for (i = 0; i < 4; ++i)
	{
		test_iter = DLListNext(test_iter);
		DLListPopFront(test_dllist);
		TEST_IS_NULL_POINTER("DLListPopFront",DLListPrev(DLListPrev(test_iter)));

		test_iter2 = DLListPrev(test_iter2);
		DLListPopBack(test_dllist);
		TEST_IS_NULL_POINTER("DLListPopBack",DLListNext(DLListNext(test_iter2)));
	}
	
	TEST_NUM("DLListPushBack/DLListPushFront", DLListSize(test_dllist), 1);
 
	DLListDestroy(test_dllist);
	test_iter = NULL; test_iter2 = NULL; test_dllist = NULL;
}



static void TestToDLListSpecialFuncs (void)
{
	dllist_t *test_dllist = DLListCreate();
	dllist_t *test_dllist2 = DLListCreate();
	dllist_iter_t test_iter = NULL;
	dllist_iter_t test_iter2 = NULL;
	dllist_iter_t test_iter3 = NULL;
	int arr_num[100], arr_num2[100];
	int i = 0, j = 0, k = 75, z = 21, h = 17, p = 19, l = -20, m = -40, n = 0;
	
	TEST_NOT_NULL_POINTER("DLListCreate", test_dllist);
	TEST_NOT_NULL_POINTER("DLListCreate", test_dllist2);
	
	arr_num[i] = i;
	arr_num2[i] = j;	
	TEST_NUM("DLListPushBack", DLListPushBack(test_dllist, &arr_num[i]), 0);
	TEST_NUM("DLListPushFront", DLListPushFront(test_dllist2, &arr_num2[i]), 0);
	test_iter = DLListBegin(test_dllist);
	test_iter2 = DLListBegin(test_dllist2);
	++i;
	--j;
	
	for (; i < 100; ++i, --j)
	{
		arr_num[i] = i;
		arr_num2[i] = j;
		
		TEST_NUM("DLListPushBack", DLListPushBack(test_dllist, &arr_num[i]), 0);
		test_iter = DLListNext(test_iter);
		TEST_NUM("DLListPushBack", *(int *)DLListGetData(test_iter), arr_num[i]);
		
		TEST_NUM("DLListPushFront", DLListPushFront(test_dllist2, &arr_num2[i]), 0);
		test_iter2 = DLListPrev(test_iter2);
		TEST_NUM("DLListPushFront", *(int *)DLListGetData(test_iter2), arr_num2[i]);
	}
	
	test_iter = DLListBegin(test_dllist);
	TEST_NUM("DLListPushBack", *(int *)DLListGetData(test_iter), 0);
	for (i = 1; i <= 20; ++i, test_iter = DLListNext(test_iter));
	TEST_NUM("DLListNext or DLListBegin", *(int *)DLListGetData(test_iter), 20);
	
	/* k = 75, z = 21, h = 17 , p = 19*/ 

	test_iter3 = DLListFind(&k, DLListBegin(test_dllist), test_iter, &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter3), *(int *)DLListGetData(test_iter));
	test_iter2 = DLListFind(&h, DLListBegin(test_dllist), test_iter, &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter2), h);
	test_iter3 = DLListFind(&z, DLListBegin(test_dllist), test_iter, &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter3), *(int *)DLListGetData(test_iter));
	test_iter3 = DLListFind(&p, DLListBegin(test_dllist), test_iter, &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter3), p);
	test_iter3 = DLListFind(&k, test_iter2, DLListEnd(test_dllist), &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter3), k);

	test_iter2 = DLListForEach(DLListNext(DLListBegin(test_dllist)), test_iter3, 
											&ZeroFunc, NULL); /* 75 0's */

	TEST_NUM("DLListForEach", *(int *)DLListGetData(test_iter2), k);
	TEST_NUM("DLListForEach", *(int *)DLListGetData(DLListNext(test_iter2)), 76);
	test_iter = DLListBegin(test_dllist);
	TEST_NUM("DLListForEach", *(int *)DLListGetData(test_iter), 0);
	for (i = 1; i <= 75; ++i, test_iter = DLListNext(test_iter)) 
	/* 75 sits at node 76 (first node is 0) */
	{
		TEST_NUM("DLListForEach", *(int *)DLListGetData(test_iter), 0);
	}
	
	
	test_iter = test_iter2; /* test iter at node 75 */

	/* m = -40 , l = -20 */
	
	test_iter2 = DLListFind(&m, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter2), m);
	test_iter3 = DLListFind(&l, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListFind", *(int *)DLListGetData(test_iter3), l);
	
/* iter2 = from_src , iter3 = to_src (NOT INCLUDED IN SPLICE) , test_iter = dest */
	DLListSplice(test_iter2, test_iter3, test_iter);
	
	TEST_NUM("DLListSplice", DLListSize(test_dllist), 120);
	TEST_NUM("DLListSplice", DLListSize(test_dllist2), 80);
	
	TEST_NUM("DLListSplice", *(int *)DLListGetData(test_iter), 75);
	TEST_NUM("DLListSplice", *(int *)DLListGetData(DLListPrev(test_iter)), -21);
	TEST_NUM("DLListSplice", *(int *)DLListGetData(DLListPrev(test_iter2)), 0);
	TEST_NUM("DLListSplice", *(int *)DLListGetData(DLListPrev(test_iter3)), -41);
	
	test_iter3 = DLListFind(&m, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListSplice", DLListIsSameIter(test_iter3, DLListEnd(test_dllist2)), 1);
	
	test_iter3 = DLListFind(&l, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListSplice", DLListIsSameIter(test_iter3, DLListEnd(test_dllist2)), 0);
	
	test_iter3 = DLListFind(&l, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListSplice", *(int *)DLListGetData(test_iter3), -20);

	test_iter3 = DLListFind(&m, DLListBegin(test_dllist), DLListEnd(test_dllist), &CompareInts);
	TEST_NUM("DLListSplice", *(int *)DLListGetData(test_iter3), -40);
	
	TEST_NUM("DLListSplice", *(int *)DLListGetData(DLListPrev(test_iter3)), 0);
	for (i = -40; i <= -21 ; ++i, test_iter3 = DLListNext(test_iter3)) 
	{
		TEST_NUM("DLListSplice", *(int *)DLListGetData(test_iter3), i);
	}
	for (i = 75; i < 100 ; ++i, test_iter3 = DLListNext(test_iter3)) 
	{
		TEST_NUM("DLListSplice", *(int *)DLListGetData(test_iter3), i);
	}
	
	test_iter3 = DLListFind(&l, DLListBegin(test_dllist), DLListEnd(test_dllist), &CompareInts);
	TEST_NUM("DLListSplice", DLListIsSameIter(test_iter3, DLListEnd(test_dllist)), 1);
	test_iter3 = DLListFind(&m, DLListBegin(test_dllist2), DLListEnd(test_dllist2), &CompareInts);
	TEST_NUM("DLListSplice", DLListIsSameIter(test_iter3, DLListEnd(test_dllist2)), 1);
	puts("************");
	
	test_iter3 = DLListFind(&m, DLListBegin(test_dllist), DLListEnd(test_dllist), &CompareInts);
	
	TEST_NUM("DLListMultiFind", DLListMultiFind(&n, test_dllist2, 
            			test_iter3, DLListEnd(test_dllist), &CompareInts), 0);
	
		
	TEST_NUM("DLListMultiFind", DLListMultiFind(&n, test_dllist2, 
            			DLListBegin(test_dllist), test_iter3, &CompareInts), 75);
	
	TEST_NUM("DLListMultiFind", DLListSize(test_dllist), 120);
	TEST_NUM("DLListMultiFind", DLListSize(test_dllist2), 155);

    
	test_iter3 = DLListBegin(test_dllist2);
	for (i = -99; i <= -41 ; ++i, test_iter3 = DLListNext(test_iter3)) 
	{
		TEST_NUM("DLListMultiFind", *(int *)DLListGetData(test_iter3), i);
	}
	
	for (i = -20; i <= -1 ; ++i, test_iter3 = DLListNext(test_iter3)) 
	{
		TEST_NUM("DLListMultiFind", *(int *)DLListGetData(test_iter3), i);
	}
	
	for (i = 1; i <= 75 ; ++i, test_iter3 = DLListNext(test_iter3)) 
	{
		TEST_NUM("DLListMultiFind", *(int *)DLListGetData(test_iter3), 0);
	}
	
	DLListDestroy(test_dllist); test_dllist = NULL;
	DLListDestroy(test_dllist2); test_dllist2 = NULL;
	test_iter = NULL; test_iter2 = NULL;
}


/***********************************************************************/

static int CompareInts (const void *x, const void *y)
{
	return (*((int *)x) == *((int *)y));
}

static int ZeroFunc (void *x, void *y)
{
	(void)y;	
	*(int *)x = 0; 

	return 0;
}

