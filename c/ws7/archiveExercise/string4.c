#include "String.h"

char *StrStr(const char *str1, const char *str2)
{
	const char *hay = str1;
	const char *nee = str2;	

	assert (str1 != NULL);
	assert (str2 != NULL);
	
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
	size_t res = 0;	

	assert (str1 != NULL);
	assert (str2 != NULL);
	
	while (*str1 && StrChr(str2, *str1))
	{
		++str1;
		++res;
	}
	return res;
}				

size_t Palin (char *str)
{
	size_t i, j;

	assert (str != NULL);
	
	for (i = 0, j = StrLen(str) - 1; i != j && str[i] == str[j]; ++i, --j);
	if (i == j)
		return 1;
	else
		return 0;
}


