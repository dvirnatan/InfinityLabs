/*******************UID module - Header_File********************/
#ifndef	__UID_H__OL111__ 
#define	__UID_H__OL111__

#include <sys/types.h> /* pid_t */ 
#include <time.h> /* time_t */
#include <unistd.h>/*getpid()*/

struct ilrd_uid
{
    time_t time_stamp;
    pid_t pid;
    size_t counter;
};

typedef struct ilrd_uid ilrd_uid_t;

/* Create a Unique identifier */
ilrd_uid_t UIDCreate(void);

/* Error: invalid uid */
int UIDIsSame(ilrd_uid_t one, ilrd_uid_t other);

/* Returns badUID */
ilrd_uid_t UIDGetBadUID(void);

#endif /*__UID_H__OL111__*/
