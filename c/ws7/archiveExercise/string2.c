#include "String.h"

char *StrnCpy(char *dest, const char *src, size_t n)
{	
	size_t i = 0;
	
	assert (dest != NULL);
	assert (src != NULL);
	
	while (i < n && *(src + i) != '\0')
	{
		*(dest + i) = *(src + i); 
		++i;
	}
	if (*(src + i) == '\0')
		*(dest + i) = '\0';
	return dest;
}

int StrnCmp (const char *str1, const char *str2, size_t n)
{
	assert (str1 != NULL);
	assert (str2 != NULL);
	
	while (*str1 && *str1 == *str2 && n > 0)
	{
		++str1;
		++str2;
		--n;
	}

	return (*str1 - *str2);
}

int StrCaseCmp(const char *s1, const char *s2)
{
	while (*s1 && tolower(*s1) == tolower(*s2))
	{
		++s1;
		++s2;
	}

	return (tolower(*s1) - tolower(*s2));
}

char *StrChr(const char *str, int c)
{
	assert (str != NULL);	
	
	while (*str != '\0' && *str != c)
		++str;
	if ('\0' == *str)
		return NULL;
	return (char *) str;		
}
