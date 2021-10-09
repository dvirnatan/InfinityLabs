#include <stdio.h>
#include <stdlib.h> /* atio */
#include <ctype.h>/* isspace() */
#include <math.h> /* pow() */
#include <assert.h>
#include "ws9_5.h"


#define IS_BIG_ENDIAN (*(uint16_t *)"\0\xff" < 0x0100)


/*----------------------------------------------------------------------------*/

long int AtoiBase10(const char *nptr)
{
	long res = 0;
	const char *ptr = nptr;
	int sign_flag = 1;
	
	for( ; isspace(*ptr) && *ptr != '\0' ; ++ptr )
		;
	if ( *ptr == 45 )
	{
		++ptr;
		sign_flag = -1;
	}
	while ( *ptr != '\0' && *ptr > 47 && *ptr < 58)
	{
		res += *ptr - 48;	/* '0' = 48 */
		++ptr;
		res *= 10;
	}
	res /= (10 * sign_flag);
	
	return res;
}

/*-----------------------STRING TO INT ---------------------------------------*/

long int Atoi(const char *nptr, int base)
{
	long res = 0;
	const char *ptr = nptr;
	unsigned int n = 0;
	int sign = 1;
	int *arr;
	int i = 0;
	char temp;

	assert ( NULL != nptr );	
	
	arr = malloc(sizeof(int) * 100);  
	assert ( NULL != arr );
	
	for( ; isspace(*ptr) && *ptr != '\0' ; ++ptr )
		;
		
	if ( *ptr == 45 )	/* '-' = 45 */
	{
		++ptr;
		sign = -1;
	}
	while ( *ptr != '\0' && ( isdigit(ptr[i]) || isalpha(ptr[i]) ))
	{
		if (isdigit(ptr[i]))
		{
			if( ptr[i] - 48 >= base )
			{
				break;
			}
			arr[i] = ptr[i] - 48;	/* '0' = 48 */
			++i;	
			
		}
		else if ( isalpha(ptr[i]) )
		{
			temp = tolower( ptr[i] );
			if ( temp - 87 >= base )
			{
				break;
			}
			arr[i] = temp - 87;	/* 'a' = 97 */
			++i;
		}
	}
/*---------- Convert Base ----------*/
		
	
	for(--i ; i >= 0 && arr[i] <= base ; --i , ++n )
	{		
		res += arr[i] * pow(base,n); 	
	}
	return res * sign;
}

/*----------------------------------------------------------------------------*/

char *ItoaBase10(int n, char *buffer)
{
	int base = 10;
	int i = 0;
	int j = 0;
	char temp;
	while ( n > 0 )
	{
		buffer[i] = (n % base) + 48; /* '0' = 48 */
		n /= base;
		++i;
	}
	buffer[i] = '\0';
	
	for (--i ; j <= i; --i, ++j )
	{
		temp = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = temp;
	}
	
	return buffer;
}

/*-----------------------INT TO STRING----------------------------------------*/

char *Itoa(long int n, char *buffer, int base)
{
	char *buffer_r;
	size_t *carie;
	size_t res = n;
	int counter = 0;

	carie =(size_t*)malloc(sizeof(int) * 10000); 
	buffer =(char*)malloc(sizeof(char) * 10000); 
	buffer_r = buffer;
/*---------- Convert Base ----------*/
		
		while ( res > 0 )
		{
			
			*carie = res % base;
			res /= base;
			++carie;
			++counter;
		}
		--carie;
/*---------- Convert To String ----------*/
		while ( counter > 0 )
		{
			if( *carie < 10 )
			{
				*buffer_r = *carie + 48;
			}
			else 
			{
				*buffer_r = *carie + 87;
			} 
			--carie;
			++buffer_r;
			--counter;
		}
		*buffer_r = '\0'; 
		
		return buffer;
}
/*---------------------------------------------------------------------------*/	
	
void AppearOnlyInTwoFirst(char *a, size_t len_a, char *b, size_t len_b,
char *c, size_t len_c)
{
	char *abc; 
	size_t i = 0;
	
	abc = (char*)calloc(127, sizeof(char));
	
	for( i = 0; i < len_a; ++i)
	{
		abc[(int)a[i]] = 1;
	}
	for( i = 0; i < len_b; ++i)
	{
		abc[(int)b[i]] *= 2;
	}
	for( i = 0; i < len_c; ++i)
	{
		abc[(int)c[i]] *= 0;
	}
	for( i = 0; i < 128; ++i)
	{
		if ( abc[i] > 1 )
		{
			printf("%c ", (char)i);
		}
	}
	printf("\n");
}

/*---------------------------------------------------------------------------*/

int IsLittleEndian()
{
	unsigned int e = 1;
	char *c = (char*)&e;
	return (*c);	
}	

/*---------------------------------------------------------------------------*/


