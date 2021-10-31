/******************************************
	_______Scheduler_______
	Author: Dvir Natan
	Date: 31.10.21
	Reviewer: Eli
	Status: Approved
******************************************/
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#include "task.h"
#include "pqueue.h"
#include "scheduler.h"

enum ret {OK, malloc_failed, stoped};


struct scheduler
{
    pqueue_t *pqueue;
    int is_runing;
};


int priority_func(const void *task1, const void *task2)
{
	int diff = 0;
	const task_t *one = task1;
	const task_t *other = task2;
	
	diff = TaskGetTimeToExec(other) - TaskGetTimeToExec(one);
	
	return diff;
}


sched_t *SchedCreate(void)
{
	sched_t *scheduler;
	
	scheduler = malloc(sizeof(sched_t));
	
	if(NULL != scheduler)
	{
		scheduler->pqueue = PQCreate(priority_func);
		scheduler->is_runing = 0;
		
		if(NULL == scheduler->pqueue)
		{
			free(scheduler); scheduler = NULL;
		}
	}	
	
	return scheduler;
}

void SchedDestroy(sched_t *sched)
{
	assert(NULL != sched);
	
	SchedFlush(sched->pqueue);
	PQDestroy(sched->pqueue);
	free(sched); sched = NULL;
}

ilrd_uid_t SchedAddTask(sched_t *sched, time_t exec_time, time_t freq, 
                                 int (*func_to_ex)(void *param), void *param)
{
	task_t *task = TaskCreate(exec_time, freq, func_to_ex, param);
	
	assert(NULL != sched);
	
	if(NULL != task)
	{
		if(0 == PQEnqueue(sched->pqueue,task))
		{
			return TaskGetUID(task);
		}
	}
	
	return TaskGetUID(NULL);
}

static int TaskIsSameUID(const void *task1, const void *uid)
{
	return UIDIsSame(*(ilrd_uid_t*)uid, TaskGetUID(task1));
}

void SchedRemoveTask(sched_t *sched, ilrd_uid_t task_uid)
{
	task_t *tmp;	
	
	assert(NULL != sched);
	
	tmp = PQErase(sched->pqueue, &task_uid, TaskIsSameUID);
	if(NULL != tmp)
	{	
		TaskDestroy(tmp);
	}
}

size_t SchedSize(const sched_t *sched)
{
	assert(NULL != sched);
	
	return PQSize(sched->pqueue);
}

int SchedIsEmpty(const sched_t *sched)
{
	assert(NULL != sched);
	
	return 	PQIsEmpty(sched->pqueue);
}

int SchedRun(sched_t *sched)
{
	int sleep_for;
	time_t start_time = time(0);
    task_t *tmp;
    time_t freq = 0;
    int status = 0;
    sched->is_runing = 1;
   
    while(!SchedIsEmpty(sched) && 1 == sched->is_runing)
    {
        tmp = PQPeek(sched->pqueue);
        PQDequeue(sched->pqueue);
        
        sleep_for = start_time - time(0) + TaskGetTimeToExec(tmp);
        
		while(sleep_for > 0)
		{
			sleep(1);
			--sleep_for;
		}
		
        status = TaskRun(tmp);
        
        if(sched->is_runing == 0)
        {
        	TaskDestroy(tmp);
        	return stoped;
        }
        
        if(0 != status)
        {
        	return status;
        }
     	
     	freq = TaskGetFreq(tmp);
        if(freq  > 0)
        {
        	TaskSetTime(tmp, freq + TaskGetTimeToExec(tmp));
        	status = PQEnqueue(sched->pqueue, tmp);
        	
        	if(status != 0)
        	{
        		
        		return malloc_failed;
        	}
        }
        else
        {
		    TaskDestroy(tmp);
        }
    }
    sched->is_runing = 0;
    return OK;
}


void SchedStop(sched_t *sched)
{
	assert(NULL != sched);
	
	sched->is_runing = 0;
}

void SchedFlush(sched_t *sched)
{
	assert(NULL != sched);
	
	while (!PQIsEmpty(sched->pqueue))
	{
		TaskDestroy(PQPeek(sched->pqueue));
		PQDequeue(sched->pqueue);
	}
}

