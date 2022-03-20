#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_OF_THREADS 4
#define NUMBER 1234567899
#define RANGE (NUMBER/NUM_OF_THREADS)
#define START(x) (RANGE * (x) + 1)
#define END(x) (START(x) + RANGE)


void *SumOfDivisors (void *range)
{
    size_t sum_of_divisors = 0, i = 0;
    for(i = START((size_t)range); i <  END((size_t)range); ++i)
    {
        if(0 == NUMBER % i)
        {
            sum_of_divisors += i;
        }
    }
    /*printf("%ld\t%ld\n",pthread_self(), sum_of_divisors);*/
    return (void*)sum_of_divisors;
}

void EX4()
{
    pthread_t array_of_thread_ids[NUM_OF_THREADS] = {0};
    size_t sum = 0, i = 0, sum_from_thread = 0;

    for(i = 1; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&array_of_thread_ids[i], NULL, &SumOfDivisors, (void*)i);
    }

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(array_of_thread_ids[i], (void**)&sum_from_thread);
        sum += sum_from_thread;
    }
    printf("%ld\n", sum);
}

void EX5(size_t number)
{
    int sum_of_devisor_single_thread = 0;
    size_t i = 0;
    
    #pragma omp parallel for
    for(i = 1; i < number; ++i)
    {
        if(0 == number % i)
        {
            sum_of_devisor_single_thread += i;
        }
    }
    printf("%d\n",sum_of_devisor_single_thread);
}

int main()
{
    time_t start, end;
    start = time(0);
    EX4();
    end = time(0);
    printf("time is: %ld\n", end - start);
    start = time(0);
    EX5(NUMBER);
    end = time(0);
    printf("time is: %ld\n", end - start);

    return 0;
}