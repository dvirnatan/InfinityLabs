/******************************************
	Author: Dvir Natan
	Date: 31.10.21
	Reviewer: Eli
	Status: Approved
******************************************/


#include "uid.h"
#include <pthread.h>

pthread_mutex_t mutex_to_protect_counter = PTHREAD_MUTEX_INITIALIZER;

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t uid;
	static size_t counter = 0;
	pthread_mutex_lock(&mutex_to_protect_counter);
	++counter;
	pthread_mutex_unlock(&mutex_to_protect_counter);
	uid.time_stamp = time(0);
	uid.pid = getpid();
	uid.counter = counter;
	
	return uid;
}

int UIDIsSame(ilrd_uid_t one, ilrd_uid_t other)
{
	return (one.time_stamp == other.time_stamp)&&(one.pid == other.pid)&&(one.counter == other.counter);
}

ilrd_uid_t UIDGetBadUID(void)
{
	ilrd_uid_t uid;
	
	uid.time_stamp = 0;
	uid.pid = 0;
	uid.counter = 0;
	
	return uid;
}
