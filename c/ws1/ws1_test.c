#include "ws1.h"

int main ()
{
	int x = 1, y = 2;
	
	hello();
	
	printf ("1^10 = %d, 2^10 = %d, 5^10 = %d\n",npow(1), npow(2), npow(5));
	
	printf ("flip: a = 123 - %d ,flip: b = 658 - %d \n", flip(123), flip(658)); 
	
	
	printf("x = %d, y = %d\n",x,y);
	swap (&x,&y);
	printf("after swap: \nx = %d, y = %d\n",x,y);
	
	return 0;
}

