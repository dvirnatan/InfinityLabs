#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h> 
#include <errno.h>
#include <time.h>

#define NUM_OF_WORDS_IN_DICT 102775
#define MULTIPLY 1
#define THREADS_NUM 100

int Sort(char **array, size_t size, size_t threads_num);
int StrCmp (const void *s1, const void *s2);
void *Shuffel(char **array);
int ShuffelFunc (const void *s1, const void *s2);
void *ThreadBubbleSort(void *args);
static int MergeStr(char **array, size_t left, size_t mid, size_t right);
void *QSort(void *args);

typedef struct args
{
    char **start;
    size_t len;
}args_t;

int main()
{
    struct timespec start, end;
    double elapsed;
    long seconds;
    long nanoseconds;
    char **array_of_pointers = NULL;
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
    fseek(dict, 0, SEEK_SET);
    buffer = malloc(length);
    if(!buffer)
    {
        return errno;
    }
    fread(buffer, 1, length, dict);
    fclose(dict);

    array_of_pointers = malloc(sizeof(char*) * (NUM_OF_WORDS_IN_DICT + 1) * MULTIPLY);

    array_of_pointers[0] = strtok(buffer, "\n");
    for(i = 1; i < NUM_OF_WORDS_IN_DICT; ++i)
    {
        array_of_pointers[i] = strtok(NULL, "\n");
    }

    for(i = 1; i < MULTIPLY; ++i)
    {
        memmove((array_of_pointers + i * NUM_OF_WORDS_IN_DICT) , array_of_pointers, NUM_OF_WORDS_IN_DICT * sizeof(char*));
    }

    Shuffel(array_of_pointers);
    puts("***********************");
    for(i = 0; i < 100; ++i)
    {
        printf("%s\n",array_of_pointers[i]);
    }


    clock_gettime(CLOCK_REALTIME, &start);
    Sort(array_of_pointers, NUM_OF_WORDS_IN_DICT * MULTIPLY - 1, THREADS_NUM);   
    clock_gettime(CLOCK_REALTIME, &end);

    puts("***********************");
    for(i = 0; i < 100; ++i)
    {
        printf("%s\n",array_of_pointers[i]);
    }

    free(array_of_pointers);
    free(buffer);

    seconds = end.tv_sec - start.tv_sec;
    nanoseconds = end.tv_nsec - start.tv_nsec;
    elapsed = seconds + nanoseconds*1e-9;
    printf("time: %.3f\n", elapsed);

    return 0;
}


int Sort(char **array, size_t size, size_t threads_num)
{
    args_t **array_of_args = NULL;
    size_t *count_arr = NULL;
    size_t i = 0;
    pthread_t *threads_id;
    args_t *args = NULL;
    char **copy_of_array = array;
    
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
    
    pthread_create(&threads_id[0], NULL, &QSort, (void*)array_of_args[0]);
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
            return errno;
        }

        array_of_args[i]->start = copy_of_array;
        array_of_args[i]->len = size/threads_num;
        copy_of_array += size/threads_num; /* this is for the next thread */

        pthread_create(&threads_id[i], NULL, &ThreadBubbleSort, (void*)array_of_args[i]);
    }

    pthread_join(threads_id[0], NULL);
    for(i = 1; i < threads_num; ++i)
    {
        pthread_join(threads_id[i], NULL);

        MergeStr(array, 0, array_of_args[i]->len * (i - 1) + array_of_args[0]->len - 1, array_of_args[i]->len * (i + 1) - 1);
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

void *Shuffel(char **array)
{
    srand(time(0));
    qsort(array, NUM_OF_WORDS_IN_DICT * MULTIPLY, sizeof(char*), ShuffelFunc);

    return NULL;
}

void *QSort(void *args)
{
    char **array = ((args_t*)args)->start;
    size_t len = ((args_t*)args)->len;
    qsort(array, len, sizeof(char*), StrCmp);
    return NULL;
}

int ShuffelFunc (const void *s1, const void *s2)
{   
    (void)s1;
    (void)s2;
    return (rand() % 2) * -2 + 1;
}

int StrCmp (const void *s1, const void *s2)
{
    return strcmp(*(const char **)s1, *(const char **)s2);
}

void *ThreadBubbleSort(void *args) 
{
    char **array = ((args_t*)args)->start;
    size_t len = ((args_t*)args)->len;
    size_t i = 0, swapped = 1;
    char *temp = NULL;
    while(swapped > 0)
    {
        swapped = 0;

        for(i = 0; i < len ; ++i)
        {
            if(strcmp(array[i], array[i + 1]) > 0)
            {
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;

                swapped = 1;
            }
        }
    }
    return NULL;
}

static int MergeStr2(char **array, size_t left, size_t mid, size_t right)
{
    size_t index_left, index_right, i;
    size_t n_left = mid - left + 1;
    size_t n_right = right - mid;
    char **sub_arr_left, **sub_arr_right;

    if(mid == left)
    {
        return 0;
    }

    sub_arr_left = malloc(sizeof(char*) * n_left);
    sub_arr_right = malloc(sizeof(char*) * n_right);
    if(NULL == sub_arr_right || NULL == sub_arr_left)
    {
        free(sub_arr_left);
        free(sub_arr_right);
        return errno;
    }

    for(index_left = 0; index_left < n_left; ++index_left)
    {
        sub_arr_left[index_left] = array[left + index_left];
    }

    for(index_right = 0; index_right < n_right; ++index_right)
    {
        sub_arr_right[index_right] = array[mid + index_right + 1];
    }

    index_left = 0;
    index_right = 0;
    i = left;

    while(index_left < n_left && index_right < n_right)
    {
        if(strcmp(sub_arr_left[index_left], sub_arr_right[index_right]) >=0)
        {
            array[i] = sub_arr_left[index_left];
            ++index_left;
        }
        else
        {
            array[i] = sub_arr_right[index_right];
            ++index_right;
        }
        ++i;
    }


    while(index_left < n_left)
    {
        array[i] = sub_arr_left[index_left];
        ++index_left;
        ++i;
    }


    while(index_right < n_right)
    {
        array[i] = sub_arr_right[index_right];
        ++index_right;
        ++i;
    }

    free(sub_arr_left);
    free(sub_arr_right);

    return 0;
}

static int MergeStr(char **list, size_t left, size_t mid, size_t right)
{
    size_t idx_left, idx_right, i;
    size_t idx_main = 0;
    size_t n_left = mid - left + 1;
    size_t n_right = right - mid;
    char **sub_arr_left, **sub_arr_right;

    if(left == mid)
    {
        puts("left == mid");
        return 0;
    }

    sub_arr_left = malloc(sizeof(char *) * n_left);
    sub_arr_right = malloc(sizeof(char *) * n_right);
    if(NULL == sub_arr_left || NULL == sub_arr_right)
    {
        free(sub_arr_left);
        free(sub_arr_right);
        return 1;
    }

    for(idx_left = 0; idx_left < n_left; ++idx_left)
    {
        sub_arr_left[idx_left] = list[left + idx_left];
    }

    for(idx_right = 0; idx_right < n_right; ++idx_right)
    {
        sub_arr_right[idx_right] = list[mid + 1 + idx_right];
    }

    idx_left = 0;
    idx_right = 0;
    idx_main = left;

    /* now we can merge the sub arrays... !!! */
    while(idx_left < n_left && idx_right < n_right)
    {
        if(0 >= strcmp(sub_arr_left[idx_left], sub_arr_right[idx_right]))
        {
            list[idx_main] = sub_arr_left[idx_left];
            ++idx_left;
        }
        else
        {
            list[idx_main] = sub_arr_right[idx_right];
            ++idx_right;
        }
        ++idx_main;
    }

    while(idx_left < n_left)
    {
        list[idx_main] = sub_arr_left[idx_left];
        ++idx_main;
        ++idx_left;
    }

    while(idx_right < n_right)
    {
        list[idx_main] = sub_arr_right[idx_right];
        ++idx_main;
        ++idx_right;
    }

    free(sub_arr_right);
    free(sub_arr_left);

    return 0;
}