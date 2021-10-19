#include <stdio.h>

#include "queue.h"

#define TEST(x, y) if ((x) != (y)) printf("Error in %d.\n", __LINE__)

void TestQueue();
void TestAddToQueue();
void TestQueueAppend();

int main()
{
	TestQueue();
	TestAddToQueue();
	TestQueueAppend();
	
	printf("test queue done\n");
	
	return 0;
}

void TestQueue()
{
	queue_t *queue = QCreate();
	TEST(1, QIsEmpty(queue));
	TEST(0, QSize(queue));
	QDestroy(queue);
}

void TestAddToQueue()
{
	queue_t *queue = QCreate();
	size_t i = 0;
	
	for (i = 0; i < 10; ++i)
	{
		TEST(i, QSize(queue));
		QEnqueue(queue, (void *)i);
	}
	
	for (i = 0; 0 != QIsEmpty(queue); ++i)
	{
		TEST((void *)i, QPeek(queue));
		QDequeue(queue);
	}
	
	QDestroy(queue);
}
void TestQueueAppend()
{
	queue_t *queue1 = QCreate();
	queue_t *queue2 = QCreate();
	size_t i = 0;

	for (i = 0; i < 10; ++i)
	{
		QEnqueue(queue1, (void *)i);
	}	
	for (i = 10; i < 20; ++i)
	{
		QEnqueue(queue2, (void *)i);
	}
	
	TEST(10, QSize(queue1));
	TEST(10, QSize(queue2));
	
	QAppend(queue1, queue2);
	
	TEST(20, QSize(queue1));
	TEST(0, QSize(queue2));
	
	for (i = 0; 0 != QIsEmpty(queue1); ++i)
	{
		TEST((void *)i, QPeek(queue1));
		QDequeue(queue1);
	}
	
	QDestroy(queue1);
		
	for (i = 0; i < 10; ++i)
	{
		TEST(i, QSize(queue2));
		QEnqueue(queue2, (void *)i);
	}
	
	for (i = 0; 0 != QIsEmpty(queue2); ++i)
	{
		TEST((void *)i, QPeek(queue2));
		QDequeue(queue2);
	}
	
	QDestroy(queue2);
}
