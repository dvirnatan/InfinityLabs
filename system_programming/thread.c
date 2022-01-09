#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE (15)
#define NUM (1000000000)
#define RANGE (NUM/SIZE)

# define START(x) ((RANGE * (x)) + 1)
# define END(x) ((START(x)) + (RANGE))


static size_t j = 0;
    size_t cnt = 0;

static void *AddToArr(void *arr)
{
    *(((int*)arr) + j) = j;
    ++j;
    return arr;

}


static void *SumNumber(void *num)
{
    size_t sum = 0;
    size_t k = 0;
    for (k = START((size_t)num); k < END((size_t)num); ++k)
    {
        if(0 == NUM % k)
        {
            sum += k;
            ++cnt;
        }
    }

    return (void *)sum;
}


void Ex1()
{
    pthread_t thread;
    int arr[SIZE];

    for(j = 0; j < SIZE;)
    {
        pthread_create(&thread, NULL, AddToArr, arr);
    }

}

void Ex2()
{
    pthread_t thread;
    int arr[SIZE];
    size_t j = 0;
    int status = -1;

    for(j = 0; j < SIZE; ++j)
    {
        while(status != 0)
        {
            status = pthread_create(&thread, NULL, AddToArr, arr);
        }
        printf("status : %d , i = %lu\n", status , j);
        status = -1;
        
    }
    pthread_exit(NULL);
}

void Ex3()
{
    pthread_t thread;
    int arr[SIZE];
    int status = -1;
    size_t cnt = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for(j = 0; j < SIZE;)
    {
        status = pthread_create(&thread, &attr, AddToArr, arr);
    }

    for(j = 0; j < SIZE; ++j)
    {
        if(arr[j] != (int)j )
        {
            ++cnt;
        }
    }
    printf("counter = %ld\n", cnt);
}


void Ex4()
{
    pthread_t thread[SIZE];
    size_t i = 0;
    size_t sum = 0;
    size_t sum_from_thread = 0;
    
    for(i = 0; i < SIZE; ++i)
    {
        pthread_create(&thread[i], NULL, SumNumber, (void *)i);
    }

    for(i = 0; i < SIZE; ++i)
    {
        pthread_join(thread[i], (void **)&sum_from_thread);
        sum += sum_from_thread;
    }

    printf("%ld\n",sum);
}

int Ex5(size_t number)
{
    int sum_of_devisor_single_thread = 0;
    size_t i = 0;

    for(i = 1; i < number; ++i)
    {
        if(0 == number % i)
        {
            sum_of_devisor_single_thread += i;
        }
    }
    return sum_of_devisor_single_thread;
}

int main()
{
    /*time_t start = time(NULL);
    time_t stop ;
    
    /* Ex3(); 
    printf("\n %d \n", Ex5(NUM));
    stop = time(NULL);

    printf("\n Time of FUNC is : %ld \n", stop - start);
    
    start = time(NULL);*/
    Ex4();
    printf("    %ld\n",cnt);
/*    stop = time(NULL);
    printf("\n Time of Ex4 is : %ld \n", stop - start); */
    return 0;
}
