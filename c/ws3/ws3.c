/*********************************************************
*	Author: Dvir Natan
*	Status: Sent
*	Reviwer:Lior Ben Harosh
*	Status: 
**********************************************************/


#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /*strdup */
#include <ctype.h> /* tolower */

char * strdup( const char *str1 ); /* or macro */
void Envp (char **envp);
void Print(char ** buffer);
void Tolower (char ** buffer);
void Free(char ** buffer);
void Copy(char **envp, char **buffer);
size_t Josephus (size_t n);
void TurnZero (char *arr, size_t n, size_t i);


void TurnZero (char *arr, size_t n, size_t i)
{
	for (; i < n - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}
	arr[i] = 0;
}
	
size_t Josephus (size_t n)
{
	char *arr = malloc (n * sizeof(size_t));
	size_t i = 0;
	size_t res = 0;
	int kill = 0;

	assert (arr != NULL);
	for (i = 0; i < n; ++i) 
	{
		arr[i] = i + 1;
	}
	
	while (arr[1] != 0)
	{
		for(i = 0; i < n && arr[i] != 0; kill = !kill)
		{
			if (kill == 0)
			{
				++i;
			}
			else
			{
				TurnZero (arr, n, i);
			}
		}
	}
	res = arr[0];
	free (arr);	arr = NULL;	
	return res;	
}


void Envp (char **envp)
{
	size_t i = 0;
	char **buffer = NULL;
	
	for (i = 0; envp[i] != NULL; ++i) 	/* count number of pointers to creat */
	;
	
	buffer = (char **)malloc (sizeof(char *) * (i + 1));
	assert (buffer != NULL);
	
	buffer[i] = NULL;
	
	Copy(envp, buffer);
	
	Tolower(buffer);

	Print(buffer);
			
	Free (buffer);
}

void Print(char **buffer)	
{
	size_t i = 0;
	
	for (i = 0; *(buffer + i) != NULL; ++i)	
	{
		printf("%s\n", *(buffer + i));
	}
}

void Free(char ** buffer) 	
{
	size_t i = 0;	
	for (i = 0; *(i + buffer) != NULL ; ++i)
	{
		free(*(i + buffer));
	}
	free (buffer);
	buffer = NULL;
}

void Tolower (char **buffer)		
{
	size_t i, j = 0;
	
	for (i = 0; *(i + buffer) != NULL ; ++i) 	
		for (j = 0; *(j + *(buffer + i)) != '\0'; ++j)
			*(j + *(buffer + i)) = tolower(*(j + *(buffer + i)));
}


void Copy(char **envp, char **buffer)
{
	size_t i = 0;
	for (i = 0; envp[i] != NULL; ++i) 	
	{
		buffer[i] = strdup (envp[i]);
		assert (buffer[i] != NULL);
	}
}


