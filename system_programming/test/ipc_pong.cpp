#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

/* We must define union semun ourselves. */
union semun 
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

static const key_t key_ping = 13;

/* Obtain a binary semaphore's ID, allocating if necessary. */
int binary_semaphore_allocation (key_t key, int sem_flags)
{
	return semget (key, 1, sem_flags);
}

/* Initialize a binary semaphore with a value of 1. */
int binary_semaphore_initialize (int semid)
{
	union semun argument;
	unsigned short values[1];
	values[0] = 1;
	argument.array = values;
	return semctl (semid, 0, SETALL, argument);
}

/* Deallocate a binary semaphore. All users must have finished their
use. Returns -1 on failure. */
int binary_semaphore_deallocate (int semid)
{
	union semun ignored_argument;
	return semctl (semid, 1, IPC_RMID, ignored_argument);
}

/* Wait on a binary semaphore. Block until the semaphore value is positive,
then decrement it by 1. */
int binary_semaphore_wait (int semid)
{
	struct sembuf operations[1];

	/* Use the first (and only) semaphore. */
	operations[0].sem_num = 0;

	/* Decrement by 1. */
	operations[0].sem_op = -1;

	/* Permit undo'ing. */
	operations[0].sem_flg = SEM_UNDO;

	return semop (semid, operations, 1);
}

/* Post to a binary semaphore: increment its value by 1.
This returns immediately. */
int binary_semaphore_post (int semid)
{
	struct sembuf operations[1];

	/* Use the first (and only) semaphore. */
	operations[0].sem_num = 0;

	/* Increment by 1. */
	operations[0].sem_op = 1;

	/* Permit undo'ing. */
	operations[0].sem_flg = SEM_UNDO;

	return semop (semid, operations, 1);
}

int main()
{
	int semid_ping = binary_semaphore_allocation(key_ping, IPC_CREAT | 0666);
	int semid_pong = binary_semaphore_allocation(key_ping + 1, IPC_CREAT | 0666);

	if (semid_ping == -1 || semid_pong == -1)
	{
		perror("allocation failed\n");
		return -1;
	}

	while(1)
	{
		int wait = binary_semaphore_wait(semid_pong);
		std::cout << "pong" << std::endl;
		int post = binary_semaphore_post(semid_ping);

		if(wait != 0 || post != 0)
		{
			perror("wait or post failed\n");
			return 0;
		}


		sleep(1);
	}

	return 0;
}