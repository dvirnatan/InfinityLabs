/********************************************
	Author: Dvir Natan
	Reviewer: Or Shoham
	Status: send
	Date: 11/10/21
********************************************/

#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */
#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert */
#include "bit_array.h"

#define ARR_LEN (CHAR_BIT * sizeof(bit_arr_t))

bit_arr_t SetBitOn(bit_arr_t arr, size_t index)
{
	bit_arr_t mask = 1;
	
	assert(ARR_LEN > index);
	
	mask <<= index;
	arr |= mask;
	
	return arr;
}

bit_arr_t SetBitOff(bit_arr_t arr, size_t index)
{	
	bit_arr_t mask = 1;
	
	assert( ARR_LEN > index );
	
	mask <<= index;
	mask = ~mask;
	arr &= mask;
	
	return arr;
}
	
bit_arr_t SetBit(bit_arr_t arr, size_t index, size_t val)
{
	
	assert( ARR_LEN > index );

	val = !!val;
	
	if (val == 0)
	{
		arr = SetBitOff(arr, index);
	}
	else
	{
		arr = SetBitOn(arr, index);
	}
	
	return arr;
}

bit_arr_t SetAllOn(bit_arr_t arr)
{
	(void)arr;
	return (~0);
}

bit_arr_t SetAllOff(bit_arr_t arr)
{
	(void)arr;
	return 0;
}

int GetBit(bit_arr_t arr, size_t index)
{
	bit_arr_t mask = 1;
	
	assert( ARR_LEN > index );
	
	mask <<= index;
	
	return ((arr & mask) > 0);
}

bit_arr_t FlipBit(bit_arr_t arr, size_t index)
{	
	bit_arr_t mask = 1;
	
	assert( ARR_LEN > index );
	
	mask <<= index;
	
	return (arr ^ mask);
}

size_t CountOn(bit_arr_t arr)
{
	size_t count = 0;
	
	while (arr)
	{
		arr = arr & (arr - 1);  
		++count;
	}
	 return count;  
}
	
size_t CountOff(bit_arr_t arr)
{
	size_t count = 0;
	
	arr = ~arr;
	
	while (arr)
	    {
		arr = arr & (arr - 1);  
		++count;
	    }
 
    	return count;
}

char *ToString(bit_arr_t arr, char* buffer)
{
	
	size_t base = 2;
	size_t i = 0;
	size_t j = 0;
	char temp;
	
	assert (NULL != buffer);
	
	while ( arr != 0 )
	{
		buffer[i] = (arr % base) + '0';
		arr /= base;
		++i;
	}

	while ( i < ARR_LEN  )
	{
		buffer[i] = '0';
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

bit_arr_t MirrorBitArr(bit_arr_t arr)
{
  arr = ((arr << 32) & 0xFFFFFFFF00000000) | ((arr >> 32) & 0x00000000FFFFFFFF);
  arr = ((arr << 16) & 0xFFFF0000FFFF0000) | ((arr >> 16) & 0x0000FFFF0000FFFF);
  arr = ((arr << 8)  & 0xFF00FF00FF00FF00) | ((arr >> 8)  & 0x00FF00FF00FF00FF);
  arr = ((arr << 4)  & 0xF0F0F0F0F0F0F0F0) | ((arr >> 4)  & 0x0F0F0F0F0F0F0F0F);
  arr = ((arr << 2)  & 0xCCCCCCCCCCCCCCCC) | ((arr >> 2)  & 0x3333333333333333);
  arr = ((arr << 1)  & 0xAAAAAAAAAAAAAAAA) | ((arr >> 1)  & 0x5555555555555555);

  return arr;
}

bit_arr_t RotateRight(bit_arr_t arr, size_t n)
{
	bit_arr_t mask = 1;
	
	for (mask = 1; n > 0; --n)
	{
		mask = 1;
		
		mask &= arr;
		arr >>= 1;
		mask <<= ARR_LEN - 1 ;
		
		arr |= mask;
	}
	return arr;
}

bit_arr_t RotateLeft(bit_arr_t arr, size_t n)
{
	bit_arr_t mask = 1;
	
	for (mask = 1; n > 0; --n)
	{
		mask = 1;
		
		mask <<= ARR_LEN - 1;
		mask &= arr;
		arr <<= 1;
		mask >>= ARR_LEN - 1;
		
		arr |= mask;
	}
	return arr;
}


