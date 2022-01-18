#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h> /* memset */
#include <errno.h>

#define MULTIPLE 100
#define NUM_OF_THREADS 4

int CountingSort(char *array, size_t size, size_t threads_num);
void *thread_count(void *args);

pthread_mutex_t count_arr_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct args
{
    char *start;
    size_t *count_arr;
    size_t len;
}args_t;

int main ()
{
    struct timespec start, end;
    double elapsed;
    long seconds;
    long nanoseconds;
    size_t i = 0;
    char *buffer = NULL;
    long length;
    FILE *dict = fopen("/usr/share/dict/words", "r");
    if(!dict)
    {
        puts("dict didn't open");
        return errno;
    }
    fseek(dict, 0, SEEK_END);
    length = ftell(dict);
    printf("%ld\n", length * MULTIPLE);
    fseek(dict, 0, SEEK_SET);
    buffer = malloc(length * MULTIPLE);
    if(!buffer)
    {
        return errno;
    }
    fread(buffer, 1, length, dict);
    fclose(dict);
    for(i = 1; i < MULTIPLE; ++i)
    {
        memmove((buffer + length * i), buffer, length);
    }
    clock_gettime(CLOCK_REALTIME, &start);
    CountingSort(buffer, length * MULTIPLE, NUM_OF_THREADS);
    clock_gettime(CLOCK_REALTIME, &end);
    free(buffer);

    seconds = end.tv_sec - start.tv_sec;
    nanoseconds = end.tv_nsec - start.tv_nsec;
    elapsed = seconds + nanoseconds*1e-9;
    printf("time: %.3f\n", elapsed);
    return 0;
}

int CountingSort(char *array, size_t size, size_t threads_num)
{
    args_t **array_of_args = NULL;
    size_t *count_arr = NULL;
    size_t i = 0;
    pthread_t *threads_id;
    args_t *args = NULL;
    char *copy_of_array = array;
    
    array_of_args = calloc(threads_num, sizeof(args_t*));
    threads_id = malloc(threads_num * sizeof(pthread_t));
    args = malloc(sizeof(args_t));
    count_arr = calloc(CHAR_MAX + 1, sizeof(size_t));

    array_of_args[0] = malloc(sizeof(args_t));
    if(NULL == count_arr || NULL == args || NULL == threads_id || NULL == array_of_args || NULL == array_of_args[0])
    {
        free(array_of_args[0]);
        free(array_of_args);
        free(threads_id);
        free(args);
        free(count_arr);
        return errno;
    }
    /*  initilaising the firts strcut and creating first thread */
    array_of_args[0]->start = copy_of_array;
    array_of_args[0]->len = (size/threads_num) + (size % threads_num);
    array_of_args[0]->count_arr = count_arr;
    pthread_create(&threads_id[0], NULL, &thread_count, (void*)array_of_args[0]);
    copy_of_array += (size/threads_num) + (size % threads_num);

    for(i = 1; i < threads_num; ++i)
    {
        array_of_args[i] = malloc(sizeof(args_t));

        if(!array_of_args[i])
        {
            while(i > 0)
            {
                free(array_of_args[i]);
            }
            free(array_of_args);
            free(threads_id);
            free(args);
            free(count_arr);
            return 12;
        }

        array_of_args[i]->start = copy_of_array;
        array_of_args[i]->len = size/threads_num;
        array_of_args[i]->count_arr = count_arr;
        copy_of_array += size/threads_num; /* this is for the next thread */

        pthread_create(&threads_id[i], NULL, &thread_count, (void*)array_of_args[i]);
    }

    for(i = 0; i < threads_num; ++i)
    {
        pthread_join(threads_id[i], NULL);
    }   

    for(i = 0; i <= CHAR_MAX; ++i)
    {
        memset(array, i, count_arr[i]);
        array += count_arr[i];
    }
    /* free() */
    for(i = 0; i < threads_num; ++i)
    {
        free(array_of_args[i]);
    }
    free(array_of_args);
    free(threads_id);
    free(args);
    free(count_arr);

    return 0;
} 

void *thread_count(void *args)
{
    size_t loacl_counting_arr[CHAR_MAX + 1] = {0};
    size_t i = 0;
    size_t len = ((args_t*)args)->len;
    char *array = ((args_t*)args)->start;
    size_t *count_arr = ((args_t*)args)->count_arr;

    for(i = 0; i < len; ++i)
    {
        ++loacl_counting_arr[(size_t)array[i]];
    }

    pthread_mutex_lock(&count_arr_lock);
    for(i = 0; i <= CHAR_MAX; ++i)
    {
        count_arr[i] += loacl_counting_arr[i]; 
    }
    pthread_mutex_unlock(&count_arr_lock);

    return 0;
}

