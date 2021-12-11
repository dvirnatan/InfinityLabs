#include <stdio.h>
#define subtruct(a,b) (a - b) /* using macro */


int num ()
{
	int a = 5; int b = 4;
	printf("Subtruct is: %d\n", subtruct(a,b));
	return 0;
}
