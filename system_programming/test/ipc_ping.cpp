#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
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
int binary_semaphore_initialize (int semid, int value)
{
	union semun argument;
	unsigned short values[1];
	values[0] = value;
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

	int sem_init_ping = binary_semaphore_initialize(semid_ping ,1); // initialized to 1;
	int sem_init_pong = binary_semaphore_initialize(semid_pong ,0); // initialized to 0;

	if (sem_init_ping != 0 || sem_init_pong != 0)
	{
		perror("sem init failed\n");
	}

	int num_of_ping = 20;

	while(num_of_ping > 0)
	{
		int wait = binary_semaphore_wait(semid_ping);
		std::cout << "ping" << std::endl;
		int post = binary_semaphore_post(semid_pong);

		if(wait != 0 || post != 0)
		{
			perror("wait or post failed\n");
		}
		--num_of_ping;
		sleep(1);
	}

	int dealloc_ping = binary_semaphore_deallocate(semid_ping);
	int dealloc_pong = binary_semaphore_deallocate(semid_pong);
	
	if (dealloc_ping == -1 || dealloc_pong == -1)
	{
		perror("dealloc failed");
	}

	return 0;
}