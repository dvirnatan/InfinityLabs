#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main ()
{
	// static const char *shm_name = "ping_pong";
	// static const int shm_id = 3;

	// key_t key = ftok(shm_name, shm_id);

	static const key_t key = 54321;

	int shemid = shmget(key, __getpagesize(), 0666 | IPC_CREAT);
	char *shared_page = (char *)shmat(shemid, NULL, 0);

	if (*(size_t *)shared_page > 0)
	{
		--(*(size_t *)shared_page);
		printf("%s \n", shared_page + sizeof(size_t));
	}
	else
	{
		shmctl(shemid, IPC_RMID, 0);
	}
	
	shmdt(shared_page);

	return 0;
}