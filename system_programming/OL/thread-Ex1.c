
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ARR_LEN 100000

int *arr = NULL;
int i = 0;

void *PutNum(void *unused)
{    
    (void)unused;
    arr[i] = i;
    ++i;
    return NULL;
}

int main()
{
    size_t counter = 0, thread_counter = 0;
    time_t start, end;
    pthread_t thread_id;
    int ret_from_thread = 0;

    pthread_attr_t attr;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED); 

    arr = malloc(sizeof(int) * ARR_LEN);
    start = time(NULL);
    for(i = 0; i < ARR_LEN && ret_from_thread == 0;)
    {
       ret_from_thread = pthread_create(&thread_id, &attr, &PutNum, NULL);
       ++thread_counter;
    }

    pthread_join(thread_id, NULL);
    end = time(NULL);
    
    for(i = 0; i < ARR_LEN; ++i)
    {
        counter += (arr[i] != i);
    }

    printf("counter = %ld\ntime = %ld\nthread_counter = %ld\n", counter ,(end - start), thread_counter);

    pthread_attr_destroy(&attr);
    free(arr);

    return 0;
}
