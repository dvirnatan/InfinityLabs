#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Write COUNT copies of MESSAGE to STREAM, pausing for a second between each. */
void writer (const char* message, int count, FILE* stream)
{
	for (; count > 0; --count) 
	{
		/* Write the message to the stream, and send it off immediately. */
		fprintf (stream, "%s\n", message);
		fflush (stream);

		/* Snooze a while. */
		sleep (1);
	}
}

/* Read random strings from the stream as long as possible. */
int reader (FILE* stream)
{
	char buffer[1024];
	/* Read until we hit the end of the stream. fgets reads until
	either a newline or the end-of-file. */

	while (!feof (stream)
	&& !ferror (stream)
	&& fgets (buffer, sizeof (buffer), stream) != NULL)
	if (strcmp(buffer, "ping.\n") == 0)
	{
		fputs (buffer, stdout);
		fputs("pong.\n", stdout);
		memset(buffer, 0, sizeof(buffer));
	}
	else if (strcmp(buffer, "quit\n") == 0)
	{
		fputs("done\n", stdout);
		return 1;
	} 

	return 0;
}
int main ()
{
	int fds[2];
	pid_t pid;

	/* Create a pipe. File descriptors for the two ends of the pipe are placed in fds. */
	pipe (fds);

	/* Fork a child process. */
	pid = fork ();
	int status = 0;
	if (pid == (pid_t) 0) 
	{
	 	/* This is the child process. Close our copy of the write end of the file descriptor. */
		close (fds[1]); 

		/* Convert the read file descriptor to a FILE object, and read from it. */
		FILE* stream = fdopen (fds[0], "r");
		if (reader (stream) == 1)
		{
			close (fds[0]);
			close (fds[1]);
			fclose(stream);
		}
		return 0;
	}
	else 
	{
		/* This is the parent process. */
	
		/* Close our copy of the read end of the file descriptor. */
		close (fds[0]);

		/* Convert the write file descriptor to a FILE object, and write to it. */
		FILE* stream = fdopen (fds[1], "w");
		writer ("ping.\n", 5, stream);
		writer ("quit\n", 1, stream);
		close (fds[1]);
		fclose(stream);
		wait(&status);
	}

	return status;
}