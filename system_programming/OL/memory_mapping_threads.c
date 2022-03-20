#include <stdio.h> /*fgets()*/
#include <string.h> /*strcmp()*/
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h> 


int globaL = 0;
pthread_mutex_t lock;
__thread int TLS;

void *DoPing()
{
    int stack = 0;
    char* heap = malloc(sizeof (char *));

    printf("TLS %p\n", &TLS);
    printf("stack %p\n", &stack);
    printf("heap %p\n", heap);
    printf("globaL %p\n", &globaL);
    return NULL;
}


void *DoPong()
{
    int stack = 0;
    int stack_ = 0;
    char* heap = malloc(sizeof (char *));

    printf("TLS2 %p\n", &TLS);
    printf("stack2 %p\n", &stack);
    printf("stack2_ %p\n", &stack_);
    printf("heap2 %p\n", heap);
    return NULL;
}

int main()
{
    int stack = 0;
    char* Mheap = malloc(sizeof (char *));
    pthread_t thread_ping;
    pthread_t thread_pong;

    pthread_create(&thread_ping,NULL,DoPing, NULL);
    pthread_create(&thread_pong,NULL,DoPong, NULL);
    pthread_join(thread_ping, NULL);
    pthread_join(thread_pong, NULL);
    printf("stack_main %p\n", &stack);
    printf("heap_main %p\n", Mheap);

    return 0;
}
