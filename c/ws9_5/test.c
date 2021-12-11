#include <stdio.h>
#include "ws9_5.h"
#include <stdlib.h>
#include <time.h>   /* for time() */
#include <limits.h>
#include <string.h>

int main ()
{
	char *str1;
	char *buffer;
	long strtol_r;
	long Atoi_r;
	int base;
	char a[] = "abcdefghi";
	char b[] = "abdcdefg";
	char c[] = "defghijkl";
	
	
	buffer =(char*)malloc(50);
	
	
	str1 = "-10";
	base = 10;

	
	strtol_r = strtol( str1, NULL ,base);
	Atoi_r = Atoi( str1, base );
			
	printf( "strtol %ld\nAtoi %ld\n", strtol_r, Atoi_r );
	
	Itoa( strtol_r , buffer, base );
	
	printf("itoa  %s\n", buffer);
	
	AppearOnlyInTwoFirst(a, strlen(a) - 1, b, strlen(b), c, strlen(c));
	
	ItoaBase10(+20, buffer);
	printf("itoabase10  %s\n", buffer);
	
	free(buffer);
	return 0;
}

