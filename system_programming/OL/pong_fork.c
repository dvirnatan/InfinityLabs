#define _POSIX_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/

sig_atomic_t sig2_recived;
void PongFork();
void Siguse2Hndler(int signal);

void Siguse2Hndler(int signal)
{
    sig2_recived = (signal == SIGUSR2);
}

void PongFork()
{
    struct sigaction pong;
    memset(&pong,0 ,sizeof(pong));
    pong.sa_handler = &Siguse2Hndler;
    sigaction(SIGUSR2, &pong, NULL);
    
    while(1)
    {
        if(sig2_recived == 1)
        {
                sig2_recived = 0;
                puts("ping!");
                kill(getppid(), SIGUSR1);
        }
    }
}

int main()
{
    PongFork();
    return 0;
}