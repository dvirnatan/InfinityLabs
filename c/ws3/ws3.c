#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /*strdup */
#include <ctype.h> /* tolower */

char * strdup( const char *str1 );
void Envp (char **envp);
void Print(char ** buffer);
void Tolower (char ** buffer);
void Free(char ** buffer);
void Copy(char **envp, char **buffer);

void Envp (char **envp)
{
	size_t i = 0;
	char **buffer = NULL;
	
	for (i = 0; envp[i] != NULL; ++i) 	/* count number of pointers to creat */
	;
	
	buffer = (char **)malloc (sizeof(char *) * i);
	assert( buffer != NULL);
	buffer[i] = NULL;
	
	Copy(envp, buffer);
	
	Tolower(buffer);

	Print(buffer);
			
	Free (buffer);
}

void Print(char ** buffer)	/* prints the buffer */
{
	size_t i = 0;
	
	for (i = 0; *(buffer + i) != NULL; ++i)	
		printf("%s\n", *(buffer + i));
}

void Free(char ** buffer) 	/*	FREE		*/	
{
	size_t i = 0;	
	for (i = 0; *(i + buffer) != NULL ; ++i)
		free(*(i + buffer));
	free (buffer);
}

void Tolower (char ** buffer)		/* turns all charecter tolower case */
{
	size_t i, j = 0;
	
	for (i = 0; *(i + buffer) != NULL ; ++i) 	
		for (j = 0; *(j + *(buffer + i)) != '\0'; ++j)
			*(j + *(buffer + i)) = tolower(*(j + *(buffer + i)));
}


void Copy(char **envp, char **buffer)
{
	size_t i = 0;
	for (i = 0; envp[i] != NULL; ++i) 	/* copy string to the buffer */
	{
		buffer[i] = strdup (envp[i]);
		assert (buffer[i] != NULL);
	}
}
