/*********************************************************
*	Author: Dvir Natan
*	Status: Sent
*	Reviwer:Or Shoham
*	Status: Approved
**********************************************************/

#include <stddef.h>
#include <assert.h>
#include <ctype.h> /*tolower*/
#include <stdlib.h>/*malloc*/


size_t  StrLen (const char *str)
{
	assert (str != NULL);
	size_t res = 0;	
	
	while (*str != '\0')
	{
		++res;
		++str;
	}
	return res;
}


char *StrCpy (char *dest, const char *src)
{ 
	assert (dest != NULL);
	assert (src != NULL);
	
	size_t i = 0;
	
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

char *StrnCpy(char *dest, const char *src, size_t n)
{	
	assert (dest != NULL);
	assert (src != NULL);
	
	size_t i = 0;
	
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

char *StrDup(const char *s)
{
	assert (s != NULL);
	char *new; 
	size_t i = 0;
	new = (char*)malloc (StrLen(s) * sizeof(char));
	assert (new != NULL);
	
	StrCpy (new, s);	

	return new;
}

char *StrCat(char *dest, const char *src)
{
	assert (dest != NULL);
	assert (src != NULL);
	size_t dest_len = StrLen(dest);
	size_t i = 0;

	for (i = 0; src[i] != '\0' ; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}


char *StrnCat(char *dest, const char *src, size_t n)
{
	assert (dest != NULL);
	assert (src != NULL);
	size_t dest_len = StrLen(dest);
	size_t i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}

char *StrStr(const char *str1, const char *str2)
{
	assert (str1 != NULL);
	assert (str2 != NULL);
	const char *hay = str1;
	const char *nee = str2;	
	
	while ( '\0' != *hay && '\0' != *nee)
	{
			if (*hay == *nee)
		{
			++hay;
			++nee;
		}
		else
		{
			++hay;
			nee = str2;
		}
	}
	if ('\0' == *nee)
	{	
		hay -= nee-str2;
		return (char *) hay;
	}
	else 
		return NULL;
}

size_t StrSpn(const char *str1, const char *str2)
{
	assert (str1 != NULL);
	assert (str2 != NULL);
	size_t res = 0;	
	
	while (*str1 && StrChr(str2, *str1))
	{
		++str1;
		++res;
	}
	return res;
}				

size_t Palin (char *str)
{
	assert (str != NULL);
	size_t i, j;
	
	for (i = 0, j = StrLen(str) - 1; i != j && str[i] == str[j]; ++i, --j);
	if (i == j)
		return 1;
	else
		return 0;
}


	
