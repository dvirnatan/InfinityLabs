/*
gd user_prog.c watchdog.c ../ds/src/scheduler.c ../ds/src/pqueue.c ../ds/src/sllist.c ../ds/src/task.c ../ds/src/uid.c ../ds/src/sorted_list.c ../ds/src/dllist.c -o user_prog -I ../ds/include -pthread
*/
#define _POSIX_SOURCE
# define NUM_OF_ARG 4
#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <sys/wait.h> /*wait*/
#include <pthread.h>

#include "scheduler.h"

enum 
{
	SUCCESS = 0, 
	FORK_FAILED = -1, 
	EXEC_FAILED = -2,
	PTHREAD_CREATE_FAILED = -3,
    MALLOC_FAILED = -4
};

int SendSignals(void *args);
void *Dogwalker(void *args);
void Siguser1Handler(int signal);
void *DogSitter(void *args);
int WatchTheDog(void *args);
int DoDNR(void *sched);
int RestartDogProgram(void *args);
static char **ArgListCreate(int argc, char *argv[],int ratio, time_t sig_freq, unsigned int num_of_retries);

/**************** GLOBAL VAR *********************/
sig_atomic_t siguser1_recived;
sig_atomic_t DNR_flag = 1;
pid_t child_pid;
char *dog = "./dog.out";
pthread_t dog_sitter_thread;

int MMI(int argc, char *argv[], int ratio, time_t sig_freq, unsigned int num_of_retries)
{
    struct sigaction siguser1;
    char **argv_to_exec;

    argv_to_exec = ArgListCreate(argc, argv, ratio, sig_freq, num_of_retries);

    child_pid = fork();
    if(child_pid > 0) /* this is the watcdog pid */
    {
        memset(&siguser1, 0, sizeof(siguser1));
        siguser1.sa_handler = &Siguser1Handler;
        sigaction(SIGUSR1, &siguser1, NULL);
        pause();
        if(pthread_create(&dog_sitter_thread, NULL, &DogSitter, argv_to_exec))
        {
            return PTHREAD_CREATE_FAILED;
        }
    }
    else 
    {
        if(child_pid == -1)
        {
            return FORK_FAILED;
        }

        execvp(dog, argv_to_exec);
        puts("exec failed!");
        return EXEC_FAILED;
    }
    return SUCCESS;
}

int DNR()
{
    DNR_flag = 0;
    kill(child_pid, SIGUSR2);
    pthread_join(dog_sitter_thread, NULL);
    return 0;
}

void *DogSitter(void *args) 
{
    size_t i = 0;
    char **cast_args = args;
    int ratio = (int)strtol(cast_args[1], NULL, 10);
    time_t sig_freq = strtol(cast_args[2], NULL, 10);
    sched_t *dog_sched = SchedCreate();

    SchedAddTask(dog_sched, 0, sig_freq, SendSignals, NULL);
    SchedAddTask(dog_sched, 1, (sig_freq / 2), DoDNR, dog_sched);
    SchedAddTask(dog_sched, 2, (sig_freq * ratio), WatchTheDog, args);
    SchedRun(dog_sched);

    SchedDestroy(dog_sched);
    for(i = 0; i < NUM_OF_ARG; ++i)
    {
        free(cast_args[i]);
    }
    free(args);
    return NULL;
}

void Siguser1Handler(int signal) 
{
    siguser1_recived = (signal == SIGUSR1);
}

int SendSignals(void *args) 
{
    (void)args;
    kill(child_pid, SIGUSR1);
    return 0;
}

int WatchTheDog(void *args)
{
    if(siguser1_recived)
    {  
        siguser1_recived = 0;
        return 0;
    }
    puts("The Dog Is Dead, RestartDogProgram");
    return RestartDogProgram(args);   
}

int RestartDogProgram(void *args)
{
    pid_t temp_pid;

    temp_pid = fork();
    if(temp_pid > 0)
    {
        kill(child_pid, SIGKILL);
        child_pid = temp_pid;
    }
    else if(!temp_pid)
    {
        execvp(dog, (char**)args);
        puts("exec failed in WatchDog!");
        return EXEC_FAILED;
    }
    return SUCCESS;
}

int DoDNR(void *sched)
{
    if(!DNR_flag)
    {
        SchedStop((sched_t*)sched);
    }
    return 0;
}

static char **ArgListCreate(int argc, char *argv[],int ratio, time_t sig_freq, unsigned int num_of_retries)
{
    char **arg_list = malloc(sizeof(char *) * (argc + NUM_OF_ARG));

    char *str_ratio = malloc(12);
    char *str_sig_freq = malloc(12);
    char *str_num_of_retries = malloc(12);

    sprintf(str_ratio, "%d", ratio);
    sprintf(str_sig_freq, "%ld", sig_freq);
    sprintf(str_num_of_retries, "%d", num_of_retries);

    arg_list[0] = str_ratio;
    arg_list[1] = str_sig_freq;
    arg_list[2] = str_num_of_retries;
    arg_list[3] = argv[0];

    memcpy(arg_list + NUM_OF_ARG, argv + 1, (sizeof(char *) * (argc - 1)));
    arg_list[argc + NUM_OF_ARG - 1] = NULL;

    return arg_list;
}
