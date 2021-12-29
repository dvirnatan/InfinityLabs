#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 199309L
#define _ISOC99_SOURCE

#include <signal.h>
#include <unistd.h> /*fork*/
#include <sys/types.h>/*pid_t*/
#include <string.h> /*memset*/
#include <stdio.h>/*puts*/

sig_atomic_t sig2_recived;

void Pong(char *pid);
 
void Siguse1Hndler(int signal)
{
    sig2_recived = (signal == SIGUSR1);
}
void Pong(char *argv)
{
    pid_t pid = atoi(argv);
    struct sigaction pong;
    memset(&pong,0 ,sizeof(pong));
    pong.sa_handler = &Siguse1Hndler;
    sigaction(SIGUSR1, &pong, NULL);
    kill(pid, SIGUSR2);
    while(1)
    {
        if(sig2_recived == 1)
        {
                sig2_recived = 0;
                puts("pong");
                kill(pid, SIGUSR2);
        }
    }
}

int main(int argc, char *argv[])
{
    puts("(:");
    if(argc < 2)
    {
        puts("Enter pid");
        return 0;
    }

    Pong(argv[1]);
    return 0;
}