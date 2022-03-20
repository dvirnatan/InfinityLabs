#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#define FILE_LENGTH 0x100

int main (int argc, char* const argv[])
{
int fd;
void* file_memory;
int integer;

/* Open the file. */
if(argc < 2)
{
	fd = open (argv[1], O_RDWR, S_IRUSR | S_IWUSR);
	if (fd != 0)
	{
		puts("open failed");
	}
	printf("argv[1] = %s\n", argv[1]);
}
else
{
	puts("arge");
}

/* Create the memory mapping. */
file_memory = mmap (0, FILE_LENGTH, PROT_READ | PROT_WRITE,
MAP_SHARED, fd, 0);
close (fd);

/* Read the integer, print it out, and double it. */
scanf (file_memory, "%d", &integer);
printf ("value: %d\n", integer);
sprintf ((char*) file_memory, "%d\n", 2 * integer);


/* Release the memory (unnecessary because the program exits). */
munmap (file_memory, FILE_LENGTH);

return 0;
}