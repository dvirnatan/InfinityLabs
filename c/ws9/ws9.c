/***********************************************
	 Author: Dvir
	 Reviewer: Gal 
	 Status: sent 
	 Status Date:  06/10/21 
***********************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

#include "Mems.h"

#define BYTES_IN_WORD (int)(sizeof(size_t) / sizeof(char))
#define WORD_SIZE (int)(sizeof(size_t))

/*-----------------------------------------------*/

void *MemSet(void *s, int c, size_t n)
{
	char *ptr_s = (char*)s;	
	size_t *ptr_buf = (size_t*)s;
	unsigned char one_byte = c;
	size_t buffer = 0;
	int counter = 0;
	size_t addr = 0;
	size_t offset = 0;
	
	assert( NULL != s);
	
/*-----      fill the buffer   --------------*/
	buffer = one_byte;	
	while ( counter < BYTES_IN_WORD )
	{
		buffer <<= WORD_SIZE;
		buffer |=  one_byte;
		++counter;
	}

	counter = n;
	addr = (size_t)s;
	offset = addr % sizeof(size_t);
	
/*---- (n < WORD_SIZE) => one by one  ------*/	
	
	if( counter < WORD_SIZE )
	{
		while ( counter > 0 )
		{
			*ptr_s = one_byte;
			--counter;
			++ptr_s;
		}
		*ptr_s = '\0';
	}
/*------	fill until aligned	-----*/
	
	else if ( offset > 0 )
	{
		while ( counter > 0 && offset > 0)
		{
			*ptr_s = one_byte;
			--counter;
			--offset;
			++ptr_s;
		}
		*ptr_s = '\0';
	}
/*----		fill by chunks		--------*/
	if ( counter >= WORD_SIZE && offset == 0)
	{

		while ( counter >= WORD_SIZE)
		{
			*ptr_buf = buffer;
			counter -= (WORD_SIZE);
			++ptr_buf;
		}
			ptr_s = (char*)ptr_buf;
			*ptr_s = '\0';
	}
/*----		fill  the remining	-----*/
	while ( counter > 0 )
	{
		*ptr_s = one_byte;
		--counter;
		++ptr_s;
	}
	*ptr_s = '\0';

	return s;
}

/*-----------------------------------------------*/

void *MemCpy(void *dest, const void *src, size_t n)
{
	char *r_dest = dest;
	const char *r_src = src;
	
	size_t *b_dest = dest;
	const size_t *b_src = src;
	
	size_t offset = 0;
	
	size_t addr = (size_t)r_src;
	offset = addr % WORD_SIZE;
	
	assert( NULL != dest); 
	assert( NULL != src);
	
/*----- copy one by one -------------*/
	if ( offset > 0 )
	{
		while ( r_src != NULL && n > 0 && offset > 0 )
		{
			*r_dest = *r_src;
			++r_src;
			++r_dest;
			--n;
			--offset;
		}
		if ( *r_src == '\0' )
		{
			*r_dest = '\0';
		}
	}
/*----- copy by words -------------*/	
	b_dest = (size_t*)r_dest;
	b_src = (size_t*)r_src;
	
	if ( offset == 0 && n >= WORD_SIZE )
	{
		while ((n >= WORD_SIZE) && (b_src != NULL) && (*b_src != '\0'))
		{ 
			*b_dest = *b_src;
			++b_dest;
			++b_src;
			n -= WORD_SIZE;
		}
	}
/*----- copy one by one until n == 0 -------------*/	
	r_dest = (char*)b_dest;
	r_src = (char*)b_src;
	
	while ( r_src != NULL && n > 0 )
	{
		*r_dest = *r_src;
		++r_src;
		++r_dest;
		--n;
	}
	if ( *r_src == '\0' )
	{
		*r_dest = '\0';
	}
	
	return dest;
}

/*-----------------------------------------------*/

void *MemMove(void *dest, const void *src, size_t n)
{
	char *r_dest = (char *)dest;
	const char *r_src = (char *)src;
	size_t addr_src = (size_t)r_src;
	size_t addr_dest = (size_t)r_dest;
	long diff = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	
	diff = (long)addr_dest - (long)addr_src;

	if ((diff > (long)n) || (diff < 0))

	{
		MemCpy(r_dest, r_src, n);
		
		return dest;
	}
	
	r_dest += n - 1;
	r_src += n - 1;
	
	while (0 < n)
	{
		*r_dest = *r_src;
		--r_src;
		--r_dest;
		--n;
	}

	r_dest = NULL;
	r_src = NULL;

	return dest;
}

