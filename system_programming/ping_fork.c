#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/
#include <stdlib.h> /*abort*/

sig_atomic_t sig1_recived;
void PingFork();
void Siguse1Hndler(int signal);

void Siguse1Hndler(int signal)
{
    sig1_recived = (signal == SIGUSR1);
}

void PingFork()
{
    pid_t pid = fork();
    struct sigaction ping;
    memset(&ping,0 ,sizeof(ping));
    ping.sa_handler = &Siguse1Hndler;
    sigaction(SIGUSR1, &ping, NULL);

    if(pid == -1)
    {
        puts("fork failed");
        return;
    }
    if(pid != 0)
    {
        sleep(1);
        kill(pid, SIGUSR2);
        while(1)
        {
            if(sig1_recived == 1)
            {
                sig1_recived = 0;
                puts("pong!\n");
                kill(pid, SIGUSR2);
            }
        }
    }
    else
    {
        execl("/home/dvir/git/system_programming/pong.out", "pong.out", NULL);
        puts("execl failed");
        abort();
    }
}

int main()
{
    PingFork();
    return 0;
}