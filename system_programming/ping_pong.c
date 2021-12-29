#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/

sig_atomic_t sig1_recived, sig2_recived;
void PingPong();
void Siguse1Hndler(int signal);
void Siguse2Hndler(int signal);

int main()
{
    PingPong(); 
    return 0;
}

void PingPong()
{
    pid_t pid = 0;
    struct sigaction parent;
    struct sigaction child;
    memset(&child,0 ,sizeof(child));
    memset(&parent,0 ,sizeof(parent));
    parent.sa_handler = &Siguse2Hndler;
    child.sa_handler = &Siguse1Hndler;
    sigaction(SIGUSR2, &parent, NULL);
    sigaction(SIGUSR1, &child, NULL);

    pid = fork();

    if(pid != 0)
    {
        if(pid == -1)
        {
            return;
        }
        kill(pid, SIGUSR1);
        while(1)
        {
            if(sig2_recived == 1)
            {
                sig2_recived = 0;
                puts("pong\n");
                kill(pid, SIGUSR1);
            }
        }
    }
    else
    {
        while(1)
        {
            if (sig1_recived == 1)
            {
                sig1_recived = 0;
                puts("ping");
                kill(getppid(),SIGUSR2);
            }
        }

    }
}

void Siguse1Hndler(int signal)
{
    sig1_recived = (signal == SIGUSR1);
}

void Siguse2Hndler(int signal)
{
    sig2_recived = (signal == SIGUSR2);
}