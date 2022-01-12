#define _POSIX_SOURCE
#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <sys/wait.h> /*wait*/
#include <pthread.h>

void *SendSignals(void *args);
void *CheckSignalRecived(void *args);
void Siguser1Hndler(int signal);
static char **ArgListCreate(int argc, char *argv[],int ratio, time_t sig_freq, unsigned int num_of_retries);


typedef struct args args_t;
struct sigaction siguser2;

struct args
{
    int argc;
    char **argv; /* needs to get a ready to exec argv from MMI */
    int ratio;
    time_t sig_freq;
    unsigned int num_of_retries;
};

sig_atomic_t signal_2_recived;

void Siguser2Hndler(int signal) 
{
    signal_2_recived = (signal == SIGUSR2);
}

pid_t child_pid;
int MMI(int argc, char *argv[], int ratio, time_t sig_freq, unsigned int num_of_retries)
{
    char *dog = "./dog.out";
    pthread_t thread_sending_signals, thread_reciving_signals;
    int i = 0;
    int status = 0;
    args_t *args;
    char **argv_to_exec;

    argv_to_exec = ArgListCreate(argc, argv, ratio, sig_freq, num_of_retries);

    memset(&siguser2, 0, sizeof(siguser2));
    siguser2.sa_handler = &Siguser2Hndler;
    sigaction(SIGUSR2, &siguser2, NULL);

/*
    argv_to_exec = calloc((size_t)(argc + 4), sizeof(char *));
    for(i = 0; i < argc; ++i)
    {
        argv_to_exec[i] = argv[i]; 
    }

    argv_to_exec[argc] = &c_ratio;
    argv_to_exec[argc + 1] = &c_sig_freq;
    argv_to_exec[argc + 2] = &c_num_of_retries;
    argv_to_exec[argc + 3] = NULL;

    printf("c: sig_Freq = %c, num_of_retries = %c, ratio = %c\n", c_sig_freq, c_num_of_retries, c_ratio);
    for(i = 0; i < argc + 4; ++i)
    {
        printf("%d: %s\n",i,argv_to_exec[i]);
    }
*/
    child_pid = fork();
    if(child_pid != 0) /* this is the watcdog pid */
    {
        args = malloc(sizeof(args_t)); /* TODO: free() */
        if(!args)
        {
            args->argv = argv_to_exec;
            args->argc = argc;
            args->ratio = ratio;
            args->sig_freq = sig_freq;
            args->num_of_retries = num_of_retries;
        }
        puts("thread creation");
        pthread_create(&thread_sending_signals, NULL, SendSignals, (void*)args); /* send signals to dog every freq */
        pthread_create(&thread_reciving_signals, NULL, CheckSignalRecived, (void*)args); /* check if signal recived from dog */
    }
    else /* this will be the watchdog */
    {
        puts("dog creation");
        execvp(dog, argv_to_exec);
        puts("exec failed!");
        abort();
    }
    return status;
}

void *SendSignals(void *args) /* needs freq, pid it known */
{
    args_t *pt_args = args;
    long i = 0;
    while(1)
    {
        for(i = 0; i < pt_args->sig_freq; ++i)
        {
            sleep(1);
        }
        kill(child_pid, SIGUSR1);
    }
    puts("send signal in watchdog returns");
    return NULL;
}

void *CheckSignalRecived(void *args) /* needs: num_of_retries, freq, ratio */
{
    args_t *pt_args = args;
    size_t interval = pt_args->ratio * pt_args->sig_freq; /* TODO: get info from struct arg */  
    size_t num_of_retries = pt_args->num_of_retries;
    size_t i = 0;
    pid_t pid_temp;

    while(1)
    {
        while(i < interval)
        {
            sleep(1);
            ++i;
        }
        if(!signal_2_recived)
        {  
            --num_of_retries;
            if(!num_of_retries)
            {
                puts("not reciving signals from dog");
                pid_temp = fork();
                if(pid_temp != 0)
                {
                    kill(child_pid, SIGKILL);
                    child_pid = pid_temp;
                }
                else
                {
                    execvp("dog.out", pt_args->argv);
                    puts("exec failed!");
                    abort();
                }
            }
        }
        i = 0;
    }
    return NULL; /* TODO: not sure about it */
}

static char **ArgListCreate(int argc, char *argv[],int ratio, time_t sig_freq, unsigned int num_of_retries)
{
# define NUM_OF_ARG 4
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
