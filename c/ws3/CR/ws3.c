/**************************************************
*	Writer: Or Shoham
*	Reviewer: Dvir Natan
*	Date: 17/09
*
**************************************************/

#include <stdlib.h> /*malloc()*/
#include <string.h> /*strlen()*/
#include <ctype.h> /*tolower()*/
#include <assert.h> /*assert()*/
#include <stdio.h> /*printf()*/


size_t CheckEnvSize(char *envp[])
{
	size_t i = 0;
	
	assert(NULL != envp);
	
	while (NULL != envp[i])
	{
		++i;
	}
	
	return i;
}

void PrintEnv(char *arr[], size_t size)
{
	size_t i = 0;
	
	assert (NULL != arr);
	
	while ( i < size )
	{
		printf("%s\n", *(arr + i) );
		++i;
	}
}

void ConvertToLowerCase( char *str, char *lowercase_str, size_t size)
{
	size_t i = 0;
	
	assert(NULL != str);
	assert(NULL != lowercase_str);
	
	for( i = 0; i < size; ++i)
	{
		*(lowercase_str + i) = tolower( *(str + i) );
	}
	
	*(lowercase_str + i) = '\0';	
}

void CopyAllStrings( char *envp[], char *new_env_array[], size_t env_size)
{
	size_t i = 0;
	size_t current_string_size = 0;

	assert(NULL != envp);
	assert(NULL != new_env_array);
	
	for( i = 0; i < env_size ; ++i)
	{
		current_string_size = strlen( *(envp + i) );		
		*(new_env_array + i) = malloc( current_string_size * sizeof(char) + 1 );
		ConvertToLowerCase( *(envp + i), *(new_env_array + i) , current_string_size);
	}
	
	PrintEnv(new_env_array, env_size);
}

void FreeAllPtrs(char **new_env_array, size_t size)
{
	size_t i = 0;
	
	assert(NULL != new_env_array);

	for (i = 0 ; i < size ; ++i)
	{
		free(*(new_env_array + i));
	}
}

void Envp(char *envp[])
{
	size_t env_size = CheckEnvSize(envp);
	char **new_env_array = (char **) malloc( env_size * sizeof(char *));
	
	CopyAllStrings(envp, new_env_array, env_size);
	FreeAllPtrs(new_env_array, env_size);
	free(new_env_array);
}


/*JOSEPHUS PROBLEM*/
/*Creates a circle of living soldiers. 1 is a living soldier. 0 is a dead one*/
void MakeCircle(int *arr, size_t size)
{
	size_t i = 0;
	
	assert(NULL != arr);
	
	for(i = 0; i < size; ++i)
	{
		*(arr + i) = 1;
	}
}

int *FindAlive(int *ptr,const int *first,const int *last)
{
	assert(NULL != ptr);
	assert(NULL != first);
	assert(NULL != last);

	if(ptr > last)
	{
		ptr = (int *) first;
	}
	
	while(*ptr == 0)
	{
		if(ptr == last)
		{
			ptr = (int *) first;	
		}
		else
		{
			++ptr;
		}
	}
	
	return ptr;
}

int *PlayGame(int *arr, size_t size)
{
	const int *start_address = arr;
	const int *end_address = arr + size - 1;
	int *sword_holder = arr;
	size_t dead_soldiers = 0;
	int *next_soldier_alive;
	
	assert(NULL != arr);

	while( dead_soldiers < size - 1)
	{
		next_soldier_alive = FindAlive( sword_holder + 1, start_address, end_address);
		*next_soldier_alive = 0;  
		++dead_soldiers;
		sword_holder = FindAlive(next_soldier_alive + 1, start_address, end_address);
	}
	
	return sword_holder;
}

void Josephus()
{
	size_t soldier_amount = 100;
	int *winner;
	int *soldiers = calloc(soldier_amount, sizeof(int));
	
	MakeCircle(soldiers, soldier_amount);
	winner = PlayGame(soldiers, soldier_amount);
	printf("The Flavius winner is person number %lu", winner - soldiers + 1);
	free(soldiers);
}




















