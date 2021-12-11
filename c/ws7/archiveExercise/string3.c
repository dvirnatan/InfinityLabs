#include "String.h"

char *StrDup(const char *s)
{
	char *new;
	
	assert (s != NULL);
	 
	new = (char*)malloc (StrLen(s) * sizeof(char));
	assert (new != NULL);
	
	StrCpy (new, s);	

	return new;
}

char *StrCat(char *dest, const char *src)
{
	size_t dest_len = StrLen(dest);
	size_t i = 0;

	assert (dest != NULL);
	assert (src != NULL);

	for (i = 0; src[i] != '\0' ; ++i)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}


char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t dest_len = StrLen(dest);
	size_t i;

	assert (dest != NULL);
	assert (src != NULL);

	for (i = 0 ; i < n && src[i] != '\0' ; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return dest;
}
