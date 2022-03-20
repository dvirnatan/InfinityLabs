#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L


#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/

sig_atomic_t sig2_recived;
pid_t sender_pid;
void Ping();

void Siguse2Hndler(int signal, siginfo_t *info, void *context)
{
    (void)context;
    sender_pid = info->si_pid;
    sig2_recived = (signal == SIGUSR2);
}


void Ping()
{
    struct sigaction ping;
    memset(&ping,0 ,sizeof(ping));
    ping.sa_sigaction = &Siguse2Hndler;
    ping.sa_flags |= SA_SIGINFO;
    sigaction(SIGUSR2, &ping, NULL);
    
    while(1)
    {
        if(sig2_recived == 1)
        {
                sig2_recived = 0;
                puts("ping");
                kill(sender_pid, SIGUSR1);
        }
    }
}

int main()
{
    Ping();
    return 0;
}