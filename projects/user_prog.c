/* gd -pthread user_prog.c watchdog.c -o user_prog.out */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "watchdog.h"

#define LINE_LEN 16 /* needs to be power of 2 */
#define MASK (LINE_LEN - 1)

int main(int argc, char *argv[])
{
    /*
    struct timespec 
    {
        time_t tv_sec;       
        long   tv_nsec;       
    }sleep_duration;

    sleep_duration.tv_sec = 0;
    sleep_duration.tv_nsec = 20000000;
    const struct timespec *pt_sleep_duration = &sleep_duration;
    */
    int i = 0;
    int stop = 0;

    MMI(argc, argv, 2, 1, 3);

    puts("STARTING");
    while(1)
    {
        printf("*");
        sleep(1);
        ++i;
        if(!(i &= MASK))
        {
            printf("\n");
        }

    DNR();
        if(stop++ == 5)
        {
            puts("EXITING PROGREM");
            return 1;
        }
    }
    return 0;
}