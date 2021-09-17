/********************************************************
*	Author: Dvir Natan
*	Status: Sent
*	Reviwer:Lior Ben Harosh
*	Status: Approved
*	Date: 17/09/21
**********************************************************/


#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /*strdup */
#include <ctype.h> /* tolower */

char *strdup(const char *str1); /* or macro */

static void Print(char ** buffer);
static void Tolower(char ** buffer);
static void Free(char ** buffer);
static void Copy(char **envp, char **buffer);
static void TurnZero(size_t *arr, size_t n, size_t i);
void Envp(char **envp);
size_t Josephus(size_t n);

static void TurnZero(size_t *arr, size_t n, size_t i)
{
	for (; i < n - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}
	arr[i] = 0;
}
	
size_t Josephus(size_t n)
{
	size_t *arr = malloc(n * sizeof(size_t));
	size_t i = 0;
	size_t res = 0;
	int kill = 0;

	assert(NULL != arr);
	for (i = 0; i < n; ++i) 
	{
		arr[i] = i + 1;
	}
	
	while (0 != arr[1])
	{
		for (i = 0; i < n && 0 != arr[i]; kill = !kill)
		{
			if (0 == kill)
			{
				++i;
			}
			else
			{
				TurnZero(arr, n, i);
			}
		}
	}
	res = arr[0];
	free(arr);	arr = NULL;	
	return res;	
}

static void Copy(char **envp, char **buffer)
{
	size_t i = 0;
	assert(NULL != envp);
	for (i = 0; NULL != envp[i]; ++i) 	
	{
		buffer[i] = strdup (envp[i]);
		assert (NULL != buffer[i]);
	}
}

static void Tolower(char **buffer)		
{
	size_t i, j = 0;
	
	for (i = 0; NULL != *(i + buffer); ++i)
	{	
		for (j = 0; '\0' != *(j + *(buffer + i)); ++j)
		{
			*(j + *(buffer + i)) = tolower(*(j + *(buffer + i)));
		}
	}
}

static void Print(char **buffer)	
{
	size_t i = 0;
	
	for (i = 0; NULL != *(buffer + i); ++i)	
	{
		printf("%s\n", *(buffer + i));
	}
}

static void Free(char ** buffer) 	
{
	size_t i = 0;	
	for (i = 0; *(i + buffer) != NULL; ++i)
	{
		free(*(i + buffer));
	}
	free (buffer);
	buffer = NULL;
}


void Envp(char **envp)
{
	size_t i = 0;
	char **buffer = NULL;
	
	assert(NULL != envp);
	for (i = 0; NULL != envp[i]; ++i)  
	;
	
	buffer = (char **)malloc (sizeof(char *) * (i + 1));
	assert(buffer != NULL);
	
	buffer[i] = NULL;
	
	Copy(envp, buffer);
	
	Tolower(buffer);

	Print(buffer);
			
	Free (buffer);
}









