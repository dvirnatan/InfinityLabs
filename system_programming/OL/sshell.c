/*****************************
 * Author: Dvir Natan        *
 * Reviewer: Lior Ben Harosh *
 * Status: Sent              *
 * Date: 25.12.21            *
 *****************************/
#include <sys/types.h> /*pid_t*/
#include <unistd.h> /*fork*/
#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/
#include <stdlib.h> /*system*/
#include <sys/wait.h> /*wait*/

#define MAX_LINE 80
#define NUM_OF_WORDS 20

int SimpleShell(char *input)
{
    char command[MAX_LINE];
    size_t i = 0;
    int status = 0;
    pid_t child_pid;
    char *argv[NUM_OF_WORDS]; 
    char *runner;

    if(!strcmp(input, "system"))
    {
        puts("Will use system");
        while(strcmp(command, "exit\n"))
        {
            printf(">");
            fgets(command, MAX_LINE, stdin);
            system(command);
        }
    }
    else
    {
        puts("Will use fork");
        while(1)
        {
            printf(">");
            fgets(command, MAX_LINE, stdin);
            if(!strcmp(command, "exit\n"))
            {
                break;
            }
            child_pid = fork();
            if(child_pid != 0)
            {
                if(child_pid == -1)
                {
                    puts("fork failed");
                    return -1;
                }
                wait(&status);
            }
            else
            { 
                argv[i] = strtok(command, " ");
                while(argv[i] != NULL)
                {
                    ++i;
                    argv[i] = strtok(NULL, " ");
                }
                runner = argv[i - 1];
                while(*runner != '\n')
                {
                    ++runner;
                }
                *runner = '\0';
                argv[i] = NULL;

                execvp(argv[0], argv);
                puts("exec failed");
                exit(status);
            }
        }
    }
    return status;
}

int main(int argc ,char **argv)
{
    int status = 0;
    if(argc < 2)
    {
        puts("Enter fork or system inline command.");
        return 1;
    }
    status =  SimpleShell(argv[1]);
    printf("returned status is: %d\n", status);

    return 0;
}