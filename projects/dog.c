/*gd -pthread dog.c -o dog.out*/
#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/
#include <pthread.h>

void Siguser1Hndler(int signal);
void *Watch(void *args);
void *SendSignals(void *args);
int RestartUserProgram(void *args);

enum{EXEC_FAILED = -2, FORK_FAILED = -1};

typedef struct args args_t;

struct args
{
    int argc;
    char **argv; /* needs to get a ready to exec argv from MMI */
    int ratio;
    time_t sig_freq;
    unsigned int num_of_retries;
};

sig_atomic_t signal_1_recived;
void Siguser1Hndler(int signal) 
{
    signal_1_recived = (signal == SIGUSR1);
}

int main(int argc, char *argv[]) /* arguments were recived from exec (MMI) */
                                /* argc is the number of arg for user_prog + 3 arg for MMI */
{
    struct sigaction siguser1;
    pthread_t thread_watch, thread_send;
    args_t *args = malloc(sizeof(args_t)); /* TODO: free() */
    puts("dog was created");
    if(args)
    {
        args->argv = argv;
        args->argc = argc;
        args->ratio = *argv[argc + 1];
        args->sig_freq = *argv[argc + 2];
        args->num_of_retries = *argv[argc + 3];
    }
    else
    {
        puts("malloc failed in dog");
        abort();
    }

    memset(&siguser1, 0, sizeof(siguser1));
    siguser1.sa_handler = &Siguser1Hndler;
    sigaction(SIGUSR1, &siguser1, NULL);

    pthread_create(&thread_watch, NULL, &Watch, (void*)args); 
    pthread_create(&thread_send, NULL, &SendSignals, (void*)args); 

    pthread_join(thread_watch, NULL); 
    pthread_join(thread_send, NULL);  
    
    puts("HO HO you are not supposed to be here");
    return 0;
}

void *Watch(void *args)
{
    args_t *pt_args = args;
    size_t interval = pt_args->ratio * pt_args->sig_freq; 
    size_t num_of_retries = pt_args->num_of_retries;
    size_t i = 0;

    printf("interval = %d, num_of_retries = %ld, ratio = %d/n", interval, num_of_retries, pt_args->ratio);

    puts("Watch started");
    while(1)
    {
        while(i < 2)
        {
            sleep(1);
            ++i;
        }
        if(signal_1_recived == 0)
        {  
            puts("signal not recived");
            printf("%ld\n", num_of_retries);
            --num_of_retries;
            if(!num_of_retries)
            {
                RestartUserProgram(args);
            }
        }
        else
        {
            signal_1_recived = 0;
            num_of_retries = pt_args->num_of_retries;
        }
        i = 0;
    }
    puts("returned from thread Watch");
    return NULL; /* TODO: not sure about it */
}

void *SendSignals(void *args) /* needs freq, pid it known */
{
    pid_t ppid;
    args_t *pt_args = args;
    long i = 0;
    ppid = getppid();
    while(1)
    {
        for(i = 0; i < pt_args->sig_freq; ++i)
        {
            sleep(1);
        }
        kill(ppid, SIGUSR2);
    }
    return NULL;
}


int RestartUserProgram(void *args) 
{
    args_t *pt_args = args;
    execvp("./user_prog.out", pt_args->argv);
    puts("exec by dog failed");
    return EXEC_FAILED;
}
