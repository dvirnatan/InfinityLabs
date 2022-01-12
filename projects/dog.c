/*gd dog.c ../ds/src/scheduler.c ../ds/src/pqueue.c ../ds/src/sllist.c ../ds/src/task.c ../ds/src/uid.c ../ds/src/sorted_list.c ../ds/src/dllist.c -o dog.out -I ../ds/include -pthread
*/
#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <pthread.h>

#include "scheduler.h"

void Siguser1Handler(int signal);
void Siguser2Handler(int signal);
int Watch(void *args);
int SendSignals(void *args);
int DoDNR(void *sched);
int RestartUserProgram(void *args);

enum 
{
	SUCCESS = 0, 
	FORK_FAILED = -1, 
	EXEC_FAILED = -2,
	PTHREAD_CREATE_FAILED = -3,
    MALLOC_FAILED = -4
};


sig_atomic_t siguser1_recived;
sig_atomic_t DNR_flag = 1;
unsigned int num_of_retries;


int main(int argc, char *argv[])                             
{
    struct sigaction siguser1, siguser2;
    sched_t *sched = NULL;
    int ratio = 0;
    time_t sig_freq = 0;
    (void)argc;

    ratio = strtol(argv[1], NULL, 10);
    sig_freq = strtol(argv[2], NULL, 10);
    num_of_retries = strtol(argv[3], NULL, 10);

    memset(&siguser1, 0, sizeof(siguser1));
    siguser1.sa_handler = &Siguser1Handler;
    sigaction(SIGUSR1, &siguser1, NULL);

    memset(&siguser2, 0, sizeof(siguser2));
    siguser2.sa_handler = &Siguser2Handler;
    sigaction(SIGUSR2, &siguser2, NULL);

    sched = SchedCreate();
    SchedAddTask(sched, 0, sig_freq, SendSignals, argv);
    SchedAddTask(sched, 1, sig_freq/2, DoDNR, sched);
    SchedAddTask(sched, ratio, sig_freq * ratio, Watch, argv);
    SchedRun(sched);
    SchedDestroy(sched);

    return 0;
}

int Watch(void *args)
{
    if(siguser1_recived)
    {  
        siguser1_recived = 0;
        return 0;
    }
    puts("signal not recived RestartUserProgram");
    return RestartUserProgram(args);
}

void Siguser1Handler(int signal) 
{
    siguser1_recived = (signal == SIGUSR1);
}

void Siguser2Handler(int signal)
{
    DNR_flag = !(signal == SIGUSR2);
}

int SendSignals(void *args) 
{
    (void)args;
    kill(getppid(), SIGUSR1);
    return 0;
}

int DoDNR(void *sched)
{
    if(!DNR_flag)
    {
        SchedStop((sched_t*)sched);
    }
    return 0;
}

int RestartUserProgram(void *args) 
{
    char **cast_args = ((char**)args + 3);
    execvp(cast_args[0], cast_args);
    puts("exec by dog failed");
    return EXEC_FAILED;
}
