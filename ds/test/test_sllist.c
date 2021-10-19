#include <stdio.h>

#include "sllist.h"

#define TEST(x, y) if ((x) != (y)) printf("Error in %d.\n", __LINE__);

#define NUM 17

void TestSLList();
void TestAddToSLList();
void TestSLListFind();
void TestSLListForEach();
void TestSLListAppend();

int main()
{
	TestSLList();
	TestAddToSLList();
	TestSLListFind();
	TestSLListForEach();
	TestSLListAppend();

	printf("test sllist done\n");
	
	return 0;
}

void TestSLList()
{
	sllist_t *list = SLListCreate();
	TEST(1, SLListIsSameIter(SLListBegin(list), SLListEnd(list)));
	TEST(1, SLListIsEmpty(list));
	TEST(0, SLListCount(list));
	SLListDestroy(list);
}


void TestAddToSLList()
{
	sllist_t *list = SLListCreate();
	
	SLListInsertBefore(list, SLListBegin(list), (void *)0xf);
	TEST((void *)0xf, SLListGetData(SLListBegin(list)));
	
	TEST(0, SLListIsEmpty(list));
	TEST(1, SLListCount(list));
	
	SLListInsertBefore(list, SLListEnd(list), (void *)0xff);
	TEST((void *)0xff, SLListGetData(SLListNext(SLListBegin(list))));
	
	SLListInsertBefore(list, SLListEnd(list), (void *)573);
	TEST((void *)573, SLListGetData(SLListNext(SLListNext(SLListBegin(list)))));
	
	SLListSetData(SLListNext(SLListBegin(list)), (void *)0x55555);
	TEST((void *)0x55555, SLListGetData(SLListNext(SLListBegin(list))));
	
	TEST(0, SLListIsEmpty(list));
	TEST(3, SLListCount(list));
	
	SLListRemove(list, SLListNext(SLListNext(SLListBegin(list))));
	TEST(2, SLListCount(list));
	TEST(1, SLListIsSameIter(SLListNext(SLListNext(SLListBegin(list))), SLListEnd(list)));
	
	SLListRemove(list, SLListBegin(list));
	TEST(1, SLListCount(list));
	TEST((void *)0x55555, SLListGetData(SLListBegin(list)));
	
	SLListDestroy(list);
}

int IsSameInteger(const void *x, const void *y)
{
	return (size_t)x == (size_t)y;
}


void TestSLListFind()
{
	size_t i = 0;
	sllist_t *list = SLListCreate();
	
	for (i = 0; i < 100; ++i)
	{
		SLListInsertBefore(list, SLListEnd(list), (void *)i);
	}
	TEST(0, SLListIsSameIter(SLListEnd(list), SLListFind((void *)99, SLListBegin(list), SLListEnd(list), IsSameInteger)));
	TEST(1, SLListIsSameIter(SLListEnd(list), SLListFind((void *)100, SLListBegin(list), SLListEnd(list), IsSameInteger)));
	TEST(0, SLListIsSameIter(SLListEnd(list), SLListFind((void *)49, SLListBegin(list), SLListEnd(list), IsSameInteger)));
	TEST(1, SLListIsSameIter(SLListEnd(list), SLListFind((void *)200, SLListBegin(list), SLListEnd(list), IsSameInteger)));
	
	SLListDestroy(list);
}

int SPrint(void *data, void *buffer)
{
	static size_t i;
	if (data == NULL)
	{
		i = 0;
	}
	((char *)buffer)[i] = (char)(size_t)data;
	++i;
	return 0;
}

void TestSLListForEach()
{
	size_t i = 0;
	sllist_t *list = SLListCreate();
	char buffer[100];
	
	for (i = 0; i < 100; ++i)
	{
		SLListInsertBefore(list, SLListEnd(list), (void *)i);	
	}
	SLListForEach(SLListBegin(list), SLListEnd(list), SPrint, buffer);
	for (i = 0; i < 100; ++i)
	{
		TEST((char)i, buffer[i]);
	}
	
	SLListDestroy(list);
}

void TestSLListAppend()
{
	sllist_t *list1 = SLListCreate();
	sllist_t *list2 = SLListCreate();
	size_t i = 0;
	char buffer[20];
	
	for (i = 0; i < 10; ++i)
	{
		SLListInsertBefore(list1, SLListEnd(list1), (void *)i);
	}
	for (i = 10; i < 20; ++i)
	{
		SLListInsertBefore(list2, SLListEnd(list2), (void *)i);
	}
	TEST(10, SLListCount(list1));
	TEST(10, SLListCount(list2));
	
	SLListAppend(list1, list2);
	
	TEST(20, SLListCount(list1));
	TEST(0, SLListCount(list2));
	
	SLListForEach(SLListBegin(list1), SLListEnd(list1), SPrint, buffer);
	for (i = 0; i < 20; ++i)
	{
		TEST((char)i, buffer[i]);
	}
	
	SLListDestroy(list1);
	
	SLListInsertBefore(list2, SLListBegin(list2), (void *)0xf);
	TEST((void *)0xf, SLListGetData(SLListBegin(list2)));
	
	TEST(0, SLListIsEmpty(list2));
	TEST(1, SLListCount(list2));
	
	SLListInsertBefore(list2, SLListEnd(list2), (void *)0xff);
	TEST((void *)0xff, SLListGetData(SLListNext(SLListBegin(list2))));
	
	SLListInsertBefore(list2, SLListEnd(list2), (void *)573);
	TEST((void *)573, SLListGetData(SLListNext(SLListNext(SLListBegin(list2)))));
	
	SLListSetData(SLListNext(SLListBegin(list2)), (void *)0x55555);
	TEST((void *)0x55555, SLListGetData(SLListNext(SLListBegin(list2))));
	
	TEST(0, SLListIsEmpty(list2));
	TEST(3, SLListCount(list2));
	
	SLListRemove(list2, SLListNext(SLListNext(SLListBegin(list2))));
	TEST(2, SLListCount(list2));
	TEST(1, SLListIsSameIter(SLListNext(SLListNext(SLListBegin(list2))), SLListEnd(list2)));
	
	SLListRemove(list2, SLListBegin(list2));
	TEST(1, SLListCount(list2));
	TEST((void *)0x55555, SLListGetData(SLListBegin(list2)));
	
	SLListDestroy(list2);
}




















