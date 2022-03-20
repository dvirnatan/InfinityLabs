#include <semaphore.h>
#include <fcntl.h>
#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 80

void SemManipulation()
{
    char name[MAX_LEN] = {0};
    char *name_runner = name;
    char order[MAX_LEN] = {0};
    char *letter = NULL;
    char *char_number = NULL;
    int int_number = 0;
    char c = 0;
    sem_t *semaphore;
    int value = 0;

    puts("Enter semaphore name");
    *(name_runner) = '/';

    while(0 == isspace(c = getc(stdin)))
    {
        *(++name_runner) = c;
    }
    *(++name_runner) = '\0';
    printf("%s\n", name);

    semaphore = sem_open(name, O_CREAT, 0644, 0);

    printf("Enter D number to decrement by number\nEnter I number to Increment by number\nV to view value\nX to exit\n");
    fgets(order, MAX_LEN, stdin);
    letter = strtok(order, " ");
    char_number = strtok(NULL, "\n");
    
    while(*letter != 'X')
    {
        if(*letter == 'D')
        {
            int_number = strtol(char_number, NULL, 10);
            while(int_number > 0)
            {
                sem_wait(semaphore);
                --int_number;
            }
        }
        if(*letter == 'I')
        {
            int_number = strtol(char_number, NULL, 10);
            while(int_number > 0)
            {
                sem_post(semaphore);
                --int_number;
            }
        }
        if(*letter == 'V')
        {
            sem_getvalue(semaphore, &value);
            printf("value is %d\n", value);
        }
        printf("Enter D number to decrement by number\nEnter I number to Increment by number\nV to view value\nX to exit\n");
        fgets(order, MAX_LEN, stdin);
        letter = strtok(order, " ");
        char_number = strtok(NULL, "\n");
    
    }
    if(char_number != NULL && strcmp(char_number, "[undo]") == 0)
    {
        sem_unlink(name);
        sem_close(semaphore);
    }
    else
    {
        sem_close(semaphore);
    }

    }

int main()
{
    SemManipulation();

    return 0;
}