#include "Mems.h"
#include <stdio.h>
#include <string.h>

int main ()
{
	char str1[100] ;
	char str2[100] ;

	char str3[] = "abcdefghijklmnopqrst1234567890";
	char str4[100];
	
/*-------- Test MemSet ---------*/

	/*MemCpy(str4, str3 ,31);
	printf("str1 before = %s\n",str1);
	MemSet( str1, '1' , 20);
	printf("str1 after = %s\n",str1);
	printf("str2 before = %s\n",str2);
	memset( str2, '1' , 20);
	printf("str2 after = %s\n",str2);
	*/
/*-------- Test MemCpy ---------*/	
	


	printf("str3 = %ld bytes\n", sizeof(str3));
	
	printf("%s\n",str3);
	printf("%s\n",str4);
	


	MemMove(str4, str3 ,10);

	printf("%s\n",str3);
	printf("%s\n",str4);
	
	return 0;
}
