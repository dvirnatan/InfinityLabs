/***************** Scheduler moudule - Header File *******************/

#ifndef	__SCHEDULER_H__OL111__ 
#define	__SCHEDULER_H__OL111__

#include <stddef.h> /*size_t*/

#include "uid.h"

typedef struct scheduler sched_t;

/*
 *	Create new scheduler and return pointer to Sched handle
 *	Error: failed malloc returns NULL pointer
 */
sched_t *SchedCreate(void);

/*	Free all the dynamic allocated memory	*/
void SchedDestroy(sched_t *sched); 

/*
 *	Add new task to the scheduler, in case of failure
 *	returns badUID
 *  Negative time is valid(smaller task will be first).
 */
ilrd_uid_t SchedAddTask(sched_t *sched, time_t exec_time, time_t freq, 
                                 int (*func_to_ex)(void *param), void *param);

/*	Removes task from the scheduler	*/
void SchedRemoveTask(sched_t *sched, ilrd_uid_t task_uid);

/*	Returns scheduler number of pending tasks*/
size_t SchedSize(const sched_t *sched);

/*	Return 1 - if empty otherwise 0*/
int SchedIsEmpty(const sched_t *sched);

/*
 *	Run the scheduler tasks by priority
 *	Return 0 after all tasks were executed successfully
 *	Return 1 if malloc faile
 *	Return 2 if the stop fuction was excuted
 *	Any other number will represent error according to task functions return val
 *      Freq should be non-negative.
 *	If freq is 0 - the task will run only once.
 *	Task reschedule shoud be relative to task excution time.
 * If task failed it will be rescdule anyway, but the SchedRun will stop.
 */
int SchedRun(sched_t *sched);

/*
 *	SchedStop will stop scheduler running, should be called by an inner task
 *	return number that represent error according to inner functions return val
 */
void SchedStop(sched_t *sched);

/*
 * remove all scheduler's tasks
 */
void SchedFlush(sched_t *sched);

#endif /*__SCHEDULER_H__OL111__*/

