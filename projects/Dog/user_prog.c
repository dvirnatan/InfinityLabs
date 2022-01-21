/* +++++++++++++++++++++++++ */

#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "watchdog.h"

#define LINE_LEN 8 /* needs to be power of 2 */
#define MASK (LINE_LEN - 1)

int main(int argc, char *argv[])
{   
    int i = 0;
    int stop = 0;
    const struct timespec sleep_time = {0, 500000000L};
   
    MMI(argc, argv, 2, 1, 3);
    puts("STARTING");
    while(1)
    {
        printf("*");
        fflush(stdout);
        nanosleep(&sleep_time, NULL);
        ++i;
        if(!(i &= MASK))
        {
            printf("\n");
        }

        if(stop++ == 5)
        {
            puts("EXITING PROGREM");
            break;
        }
    }
    DNR();

    return 0;
}