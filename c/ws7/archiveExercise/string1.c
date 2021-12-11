
#include "String.h"

size_t StrLen (const char *str)
{
	size_t res = 0;
		
	assert (str != NULL);
	
	while (*str != '\0')
	{
		++res;
		++str;
	}
	return res;
}


char *StrCpy (char *dest, const char *src)
{ 
	size_t i = 0;
	
	assert (dest != NULL);
	assert (src != NULL);
	
	while ('\0' !=  *(src + i))
	{
		*(dest + i) = *(src + i); 
		++i;
	}
	*(dest + i) = '\0';
	return dest;
}

int StrCmp (const char *str1, const char *str2)
{
	assert (str1 != NULL);
	assert (str2 != NULL);
	
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}

