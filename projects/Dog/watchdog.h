#ifndef __WATCHDOG_H__OL111
#define __WATCHDOG_H__OL111

#include <time.h> /*time_t*/

/*
Params: argc, argv - same as user's program 'main' arguments. If main didn't recieve
arguments, pass 0 and NULL.
ratio - The ratio between number of times the main process will alert the watchdog
 that it's alive and each check (1 check) from the watchdog itself.
sig_freq - The amount of times a confirmation is sent to the watchdog that the main
process still exists.
num_of_retries - An integer value of 0 or more that represents the number of times
the watchdog will allow for an error (i.e didn't recieve proof of existence from
the user process) without re-running the user process.
Return value - Boolean integer: 0 if the watchdog was successfuly initialized,
Non-zero value for error. 
*/
int MMI(int argc, char *argv[], int ratio, time_t sig_freq, unsigned int num_of_retries);
/*
DNR will terminate the watchdog process.
Return value - 0 for success. Non-zero value for error. 
*/
int DNR(void);

#endif /*__WATCHDOG_H__OL111*/