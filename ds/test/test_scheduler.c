#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

#define TEST(x, y) if ((x) != (y)) printf("Error in %d.\n", __LINE__);

static time_t start_time;
static size_t counter;

int InitializeTime(void *null)
{
	if (NULL == null)
	{
		start_time = time(NULL);
		counter = 0;
	}
	
	return 0;
}

int RecordTime(void *times)
{
	++counter;
	((time_t *)times)[counter] = time(NULL);
	
	return 0;
}

int UpdateTimer(void *times)
{
	*(time_t *)times += 2;
	
	return 0;
}

int StopScheduler(void *sched)
{
	SchedStop((sched_t *)sched);
	
	return 0;
}

int TestTimes(void *times)
{
	TEST(*(time_t *)times, ((time_t *)times)[counter] - start_time);
	
	return 0;
}

static int FlashScheduler(void *sched)
{
	SchedFlush(sched);
	
	return 0;
}

static int CleanStopScheduler(void *sched)
{
	SchedFlush(sched);
	SchedAddTask(sched, -1, 0, FlashScheduler, sched);
	
	return 0;
}

int RunSchedOneTime(void *sched)
{
	sched_t *sched2 = SchedCreate();
	time_t times[1000] = {-2};
	
	SchedAddTask(sched2, 30, 1, CleanStopScheduler, sched2);
	SchedAddTask(sched2, 1, 2, TestTimes, times);
	SchedAddTask(sched2, 0, 2, UpdateTimer, times);
	SchedAddTask(sched2, 0, 2, RecordTime, times);
	SchedAddTask(sched2, 0, 0, InitializeTime, NULL);
	
	TEST(5, SchedSize(sched2));
	
	TEST(0, SchedRun(sched2));
	TEST(0, SchedSize(sched2));
	SchedFlush(sched2);
	TEST(0, SchedSize(sched2));
	
	SchedDestroy(sched2);
	
	SchedAddTask(sched, -1, 1, CleanStopScheduler, sched);
	
	return 0;
}
/******************************************************************************/

void TestSched1();
void TestSched2();
void TestSched3();

int main()
{
	TestSched1();
	TestSched2();
	TestSched3();

	printf("test scheduler done\n");
	
	return 0;
}

void TestSched1()
{
	sched_t *sched = SchedCreate();
	TEST(0, SchedSize(sched));
	TEST(1, SchedIsEmpty(sched));
	SchedDestroy(sched);
}

void TestSched2()
{
	sched_t *sched = SchedCreate();
	time_t times[1000] = {-2};
	
	TEST(0, SchedSize(sched));
	TEST(1, SchedIsEmpty(sched));
	
	SchedAddTask(sched, 30, 0, StopScheduler, sched);
	SchedAddTask(sched, 1, 2, TestTimes, times);
	SchedAddTask(sched, 0, 2, UpdateTimer, times);
	SchedAddTask(sched, 0, 2, RecordTime, times);
	SchedAddTask(sched, 0, 0, InitializeTime, NULL);
	
	TEST(5, SchedSize(sched));
	
	TEST(2, SchedRun(sched));
	TEST(3, SchedSize(sched));
	SchedFlush(sched);
	TEST(0, SchedSize(sched));
	
	SchedDestroy(sched);
}


void TestSched3()
{
	sched_t *sched = SchedCreate();
	
	SchedAddTask(sched, 3, 3, RunSchedOneTime, sched);
	TEST(0, SchedRun(sched));
	TEST(0, SchedSize(sched));
	
	SchedDestroy(sched);
}
















