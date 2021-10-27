#include <stdio.h>
#include "sorted_list.h"

#define TEST_EQ(x, y) if ((x) != (y)) printf("Error in %d.\n", __LINE__);
#define TEST_GR(x, y) if ((x) > (y)) printf("Error in %d.\n", __LINE__);

void TestSortedList();
void TestAddToSortedList();
void TestSortedListFind();
void TestSortedListMarge();

int main()
{
	TestSortedList();
	TestAddToSortedList();
	TestSortedListMarge();
	TestSortedListFind();

	printf("test sorted_list done\n");
	
	return 0;
}

int IntegerCmp(const void *n1, const void *n2)
{
	return ((size_t)n1 > (size_t)n2) - ((size_t)n1 < (size_t)n2);
	/*return (size_t)n1 - (size_t)n2;*/
}

int Divisible3Cmp(const void *n1, const void *n2)
{
	return (size_t)n1 % 3 - (size_t)n2 % 3;
}

void TestSortedList()
{
	sorted_list_t *list = SortedListCreate(IntegerCmp);
	TEST_EQ(0, SortedListSize(list));
	TEST_EQ(1, SortedListIsEmpty(list));
	SortedListDestroy(list);
}

void TestAddToSortedList()
{
	sorted_list_t *list = SortedListCreate(IntegerCmp);
	size_t i = 0;
	sorted_list_iter_t runner;
	size_t arr2[] = {0, 3, 6, 9, 12, 15, 1, 4, 7, 10, 13, 16, 2, 5, 8, 11, 14};
	
	for (i = 0; i < 20; ++i)
	{
		TEST_EQ(i, SortedListSize(list));
		SortedListInsert(list, (void *)i);
	}
	for (i = 1, runner = SortedListNext(SortedListBegin(list));
		 !SortedListIsSameIter(runner, SortedListEnd(list));
		 ++i, runner = SortedListNext(runner))
	{
		TEST_GR(SortedListGetData(SortedListPrev(runner)), SortedListGetData(runner));
		TEST_EQ(i, (size_t)SortedListGetData(runner));
	}
	while (!SortedListIsEmpty(list))
	{
		TEST_EQ((size_t)SoretdListPopBack(list), SortedListSize(list));
	}
	
	SortedListDestroy(list);
	
	
	
	list = SortedListCreate(Divisible3Cmp);
	
	for (i = 0; i < 17; ++i)
	{
		TEST_EQ(i, SortedListSize(list));
		SortedListInsert(list, (void *)i);
	}
	for (i = 0; i < 17; ++i)
	{
		SortedListInsert(list, (void *)arr2[i]);
	}
	SortedListDestroy(list);
}

void TestSortedListFind()
{
	sorted_list_t *list = SortedListCreate(IntegerCmp);
	size_t i = 0;
	sorted_list_iter_t runner;
	
	for (i = 0; i < 20; ++i)
	{
		TEST_EQ(i, SortedListSize(list));
		SortedListInsert(list, (void *)i);
	}
	for (i = 0, runner = SortedListBegin(list);
		 i < 20 && !SortedListIsSameIter(runner, SortedListEnd(list));
		 ++i, runner = SortedListNext(runner))
	{
		TEST_EQ(i, (size_t)SortedListGetData(SortedListFind(list, 
					SortedListBegin(list), SortedListNext(runner), (void *)i)));
	}
	for (i = 0, runner = SortedListBegin(list);
		 i < 20 && !SortedListIsSameIter(runner, SortedListEnd(list));
		 ++i, runner = SortedListNext(runner))
	{
		TEST_EQ(0, (size_t)SortedListGetData(SortedListFind(list, 
					SortedListNext(runner), SortedListEnd(list), (void *)i)));
	}
	
	SortedListDestroy(list);
}

void TestSortedListMarge()
{
	sorted_list_t *list1 = SortedListCreate(IntegerCmp);
	sorted_list_t *list2 = SortedListCreate(IntegerCmp);
	sorted_list_iter_t runner;
	size_t i = 0;
	size_t arr[20] = {0, 3, 6, 9, 12, 15, 18, 1, 4, 7, 10, 13, 16, 19, 2, 5, 8, 11, 14, 17};
	
	for (i = 0; i < 10; ++i)
	{
		SortedListInsert(list1, (void *)i);
	}
	for (i = 10; i < 20; ++i)
	{
		SortedListInsert(list2, (void *)i);
	}
	SortedListMerge(list1, list2);
	TEST_EQ(20, SortedListSize(list1));
	TEST_EQ(0, SortedListIsEmpty(list1));
	TEST_EQ(0, SortedListSize(list2));
	TEST_EQ(1, SortedListIsEmpty(list2));
	for (i = 1, runner = SortedListNext(SortedListBegin(list1));
		 i < 20 && !SortedListIsSameIter(runner, SortedListEnd(list1));
		 ++i, runner = SortedListNext(runner))
	{
		TEST_GR((size_t)SortedListGetData(SortedListPrev(runner)), (size_t)SortedListGetData(runner));
		TEST_EQ(i, (size_t)SortedListGetData(runner));
	}
	
	SortedListDestroy(list1);
	SortedListDestroy(list2);
	
	
	
	
	list1 = SortedListCreate(Divisible3Cmp);
	list2 = SortedListCreate(Divisible3Cmp);
	
	for (i = 0; i < 10; ++i)
	{
		SortedListInsert(list1, (void *)i);
	}
	for (i = 10; i < 20; ++i)
	{
		SortedListInsert(list2, (void *)i);
	}
	SortedListMerge(list1, list2);
	TEST_EQ(20, SortedListSize(list1));
	TEST_EQ(0, SortedListIsEmpty(list1));
	TEST_EQ(0, SortedListSize(list2));
	TEST_EQ(1, SortedListIsEmpty(list2));
	for (i = 0, runner = SortedListBegin(list1);
		 i < 20 && !SortedListIsSameIter(runner, SortedListEnd(list1));
		 ++i, runner = SortedListNext(runner))
	{
		TEST_EQ(arr[i], (size_t)SortedListGetData(runner));
	}
	
	SortedListDestroy(list1);
	SortedListDestroy(list2);
}
