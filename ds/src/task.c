/******************************************
	_______TASK_______
	Author: Dvir Natan
	Date: 31.10.21
	Reviewer: Eli
	Status: Approved
******************************************/
#include <stdlib.h>
#include <assert.h>

#include "task.h"

struct task
{
    time_t time_to_exec;
    time_t frequency;
    ilrd_uid_t uid;
    int (*func_to_excute)(void *params);
    void *params;
};

task_t *TaskCreate(time_t exec_time, time_t freq, 
                    int (*excute_func_t)(void *params), void *params)
{
	task_t *task = malloc(sizeof(task_t));
	
	if(NULL != task)
	{
		task->time_to_exec = exec_time;
		task->frequency = freq;
		task->uid = UIDCreate();
		task->func_to_excute = excute_func_t;
		task->params = params;  
	}
	
	return task;    	
}

void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	
	free(task); task = NULL;
}

int TaskRun(task_t *task)
{
	assert(NULL != task->func_to_excute);
	
	return task->func_to_excute(task->params);
}

void TaskSetFreq(task_t *task, time_t freq)
{
	assert(NULL != task);

	task->frequency = freq;
}

time_t TaskGetFreq(const task_t *task)
{
	assert(NULL != task);	
	
	return task->frequency;
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
	if(NULL == task)
	{
		return UIDGetBadUID();
	}		
	
	return task->uid;
}

time_t TaskGetTimeToExec(const task_t *task)
{
	assert(NULL != task);
	
	return task->time_to_exec;
}

void TaskSetTime(task_t *task, time_t exec_time)
{
	assert(NULL != task);
	
	task->time_to_exec = exec_time;
}

