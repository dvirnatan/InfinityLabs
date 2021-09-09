/*********************************************************
*	Aoutor: Dvir Natan
*
*
**********************************************************/

#include <stddef.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

int tolower(int);

size_t  StrLen (const char *str)
{
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
	while (*str1 && *str1 == *str2)
	{
		++str1;
		++str2;
	}

	return (*str1 - *str2);
}

char *StrnCpy(char *dest, const char *src, size_t n)
{	
	size_t i = 0;
	while (i <= n && *(src + i) != '\0')
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
	while (*str1 && *str1 != *str2 && n > 0)
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
	while (*str != '\0' && *str != c)
		++str;
	
	return (char *) str;		
}

char *StrDup(const char *s)
{
	char *new; 
	size_t i = 0;
	new = (char*)malloc (StrLen(s) * sizeof(char));
	for (i = 0; *(s + i) != '\0'; ++i)
	{	
		*(new + i) = *(s + i); 
	}	

	return new;
}

char *StrCat(char *dest, const char *src)
{
	size_t dest_len = StrLen(dest);
	size_t i = 0;

	for (i = 0; src[i] != '\0' ; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}


char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t dest_len = StrLen(dest);
	size_t i;

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}

char *StrStr(const char *haystack, const char *needle)
{
	char *hay = (char *)haystack;
	char *nee = (char *)needle;	
	
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
			nee = (char *)needle;
		}
	}
	if ('\0' == *nee)	
		return hay -= (nee-needle);
	else 
		return NULL;
}







