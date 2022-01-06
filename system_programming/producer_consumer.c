#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>


#define MAX_LEN 80
#define SIZE 50

int flag_ex1;
int counter;
int execution_counter;
struct node
{
    struct node *next;
    int data;
};
struct node *head = NULL;
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t node_counter;
pthread_mutex_t fsq_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fsq_mutex2 = PTHREAD_MUTEX_INITIALIZER;

sem_t sem_cons_ex4, sem_prod_ex4;
size_t not_full;


void *reader_func (void *buffer)
{
    while(1)
    {
        if(flag_ex1)
        {
            printf("%s", (char*)buffer);
            flag_ex1 = 0;
        }
    }

    return NULL;
}
void *writer_func(void *buffer)
{
    while(1)
    {
        if(!flag_ex1)
        {
            printf(">");
            fgets((char*)buffer, MAX_LEN, stdin);
            flag_ex1 = 1;
        }
    }
    return NULL;
}

void *add_node_ex2(void *unused)
{
    struct node *new;
    (void)unused;
    pthread_mutex_lock(&list_mutex); 

    new = malloc(sizeof(struct node));
    new->data = ++counter;
    execution_counter++;

    new->next = head;
    head = new;

    printf("add: %d\n", head->data);
    pthread_mutex_unlock(&list_mutex);

    return NULL;
}
void *remove_node_ex2(void *unused)
{
    struct node *temp = NULL;
    (void)unused;
    pthread_mutex_lock(&list_mutex);  
    while(head == NULL)
    {
        pthread_mutex_unlock(&list_mutex);
        pthread_mutex_lock(&list_mutex);  
    }

    temp = head;
    printf("remove: %d\n", head->data);
    head = head->next;
    free(temp);
    --counter; 
    execution_counter++;
    
    pthread_mutex_unlock(&list_mutex);
    return NULL;
}

void *add_node_ex3(void *unused)
{
    struct node *new;
    (void)unused;
    pthread_mutex_lock(&list_mutex); 
    sem_post(&node_counter);

    new = malloc(sizeof(struct node));
    new->data = ++counter;
    new->next = head;
    head = new;
    execution_counter++;

    printf("add: %d\n", head->data);
    pthread_mutex_unlock(&list_mutex);

    return NULL;
}
void *remove_node_ex3(void *unused)
{
    struct node *temp = NULL;
    (void)unused;
    sem_wait(&node_counter);
    pthread_mutex_lock(&list_mutex);  
   
    temp = head;
    printf("remove: %d\n", head->data);
    head = head->next;
    free(temp);
    --counter; 
    execution_counter++;

    pthread_mutex_unlock(&list_mutex);
    return NULL;
}

void *produce_ex4(void *queue)
{
    int *pt_queue = queue;
    sem_wait(&sem_prod_ex4);
    pthread_mutex_lock(&fsq_mutex);
    ++counter;

    pt_queue[not_full] = not_full;
    printf("write: %d\n", pt_queue[not_full]);
    ++not_full;

    sem_post(&sem_cons_ex4);
    pthread_mutex_unlock(&fsq_mutex);

    return NULL;
}
void *comsume_ex4(void *queue)
{
    int *pt_queue = queue;
    sem_wait(&sem_cons_ex4);
    pthread_mutex_lock(&fsq_mutex);
    ++counter;

    --not_full;
    printf("read: %d\n", pt_queue[not_full]);

    sem_post(&sem_prod_ex4);
    pthread_mutex_unlock(&fsq_mutex);

    return NULL;
}

void *produce_ex5(void *queue)
{
    int *pt_queue = queue;
    sem_wait(&sem_prod_ex4);
    pthread_mutex_lock(&fsq_mutex);
    ++counter;

    pt_queue[not_full] = not_full;
    printf("write: %d\n", pt_queue[not_full]);
    ++not_full;

    sem_post(&sem_cons_ex4);
    pthread_mutex_unlock(&fsq_mutex);

    return NULL;
}

void *comsume_ex5(void *queue)
{
    int *pt_queue = queue;
    sem_wait(&sem_cons_ex4);
    pthread_mutex_lock(&fsq_mutex2);
    ++counter;

    --not_full;
    printf("read: %d\n", pt_queue[not_full]);

    sem_post(&sem_prod_ex4);
    pthread_mutex_unlock(&fsq_mutex2);

    return NULL;
}


void EX1()
{
    pthread_t writer, reader;
    char *buffer = NULL;

    buffer = malloc(MAX_LEN);
    pthread_create(&writer, NULL, &writer_func, (void*)buffer);
    pthread_create(&reader, NULL, &reader_func, (void*)buffer);
    pthread_join(writer, NULL);
}

void EX2()
{
    pthread_t thread_add[SIZE] = {0};
    pthread_t thread_remove[SIZE] = {0};
    size_t i = 0;


    for (i = 0; i < SIZE; i++)
    {
        pthread_create(&thread_add[i], NULL, &add_node_ex2, (void*)head);
        pthread_create(&thread_remove[i], NULL, &remove_node_ex2, (void*)head);
    }
    for (i = 0; i < SIZE; i++)
    {
        pthread_join(thread_add[i], NULL);
        pthread_join(thread_remove[i], NULL);
    }    
    printf("SIZE sould be %d\n", execution_counter/2);
}

void EX3()
{
    pthread_t thread_add[SIZE] = {0};
    pthread_t thread_remove[SIZE] = {0};
    size_t i = 0;

    sem_init(&node_counter, 0, 0);
    for (i = 0; i < SIZE; i++)
    {
        pthread_create(&thread_add[i], NULL, &add_node_ex3, (void*)head);
        pthread_create(&thread_remove[i], NULL, &remove_node_ex3, (void*)head);
    }
    for (i = 0; i < SIZE; i++)
    {
        pthread_join(thread_add[i], NULL);
        pthread_join(thread_remove[i], NULL);
    }    
    printf("SIZE sould be %d\n", execution_counter/2);
}

void EX4()
{
    #define NUM_OF_THREADS 10
    #define SIZE_QUEUE 32

    int *queue = NULL;
    size_t i = 0;
    pthread_t consumer[NUM_OF_THREADS];
    pthread_t producer[NUM_OF_THREADS];
    sem_init(&sem_prod_ex4, 0, SIZE_QUEUE);
    sem_init(&sem_cons_ex4, 0, 0);
    queue = malloc(sizeof(int) * SIZE_QUEUE);
    
    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&consumer[i],NULL, &produce_ex4, (void*)queue);
        pthread_create(&producer[i],NULL, &comsume_ex4, (void*)queue);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        pthread_join(consumer[i], NULL);
        pthread_join(producer[i], NULL);
    }
    printf("num of thread is: %d\n", counter/2);
}

void EX5()
{
    #define NUM_OF_THREADS_EX5 50
    #define SIZE_QUEUE 32

    int *queue = NULL;
    size_t i = 0;
    pthread_t consumer[NUM_OF_THREADS_EX5];
    pthread_t producer[NUM_OF_THREADS_EX5];
    sem_init(&sem_prod_ex4, 0, SIZE_QUEUE);
    sem_init(&sem_cons_ex4, 0, 0);
    queue = malloc(sizeof(int) * SIZE_QUEUE);
    
    for(i = 0; i < NUM_OF_THREADS_EX5; ++i)
    {
        pthread_create(&consumer[i],NULL, &produce_ex4, (void*)queue);
        pthread_create(&producer[i],NULL, &comsume_ex4, (void*)queue);
    }

    for (i = 0; i < NUM_OF_THREADS_EX5; ++i)
    {
        pthread_join(consumer[i], NULL);
        pthread_join(producer[i], NULL);
    }
    printf("num of thread is: %d\n", counter/2);
}

int main()
{
    /*EX1();*/
   /* EX2(); */
    /*EX3();*/
   /* EX4(); */
    EX5(); 

    return 0;
}