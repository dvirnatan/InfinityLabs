#include <stdio.h>
#include "ws9_5.h"
#include <stdlib.h>
#include <time.h>   /* for time() */
#include <limits.h>

int main ()
{
	char *str1;
	unsigned int base = 0;
	int random_num = 0;
	int n = 1000000;
	
	str1 = malloc(50);
	
	srand( time(0) );
	
		
	while ( n > 0 )
	{
		random_num = rand();
		base = random_num % 35;
		if( base == 0 )
		{
			base++;
		}
		sprintf( str1, "%d" , random_num );
		if ( strtol(str1, NULL, base) != Atoi( str1, base) )
		{
			puts("Atoi");
			printf("random_num = %d\nbase = %d\n",random_num, base);
			printf("str1 = %s\n", str1);
			break;
		}
		
		--n;
	}			
	
	
	
	
	
	
	return 0;
}

