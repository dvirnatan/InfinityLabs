/******************* Task moudule - Header File ********************/
#ifndef	__TASK_H__OL111__ 
#define	__TASK_H__OL111__

#include "uid.h"

/*
struct task
{
    time_t time_to_exec;
    time_t frequency;
    ilrd_uid_t uid;
    int (*func_to_excute)(void *params);
    void *params;
}
*/

typedef struct task task_t;

/*	
 *	Create new task and return pointer to this task
 *	Error:failed malloc return NULL pointer
 */
task_t *TaskCreate(time_t exec_time, time_t freq, 
                    int (*excute_func_t)(void *params), void *params);

/*	Free all the dynamic allocated memory	*/
void TaskDestroy(task_t *task);

/*	Run the task
 *	return value: the return value of excute func
 */
int TaskRun(task_t *task);

/*	Changes task's frequency	*/
void TaskSetFreq(task_t *task, time_t freq);

/*	Returns task's frequency	*/
time_t TaskGetFreq(const task_t *task);

/*	returns task's UID	*/
ilrd_uid_t TaskGetUID(const task_t *task);

/*	returns task's time to execute	*/
time_t TaskGetTimeToExec(const task_t *task);

/*	Change task's time to execute	*/
void TaskSetTime(task_t *task, time_t exec_time);

#endif /*__TASK_H__OL111__*/
