#include "ws1_5.h"

int main ()
{
	char *X = "dvir";
    	char *Y = "natan";
  	int ret = StrCmp(X, Y);
	size_t x = 1, y = 2;	
	size_t *px = &x;
	size_t *py = &y;
        	
	int arr1[] = {1,2,3,4,5};
	int *new;
	
	
	printf("len of arr1 = %d\narr1: ",5);
	print_array (arr1, 5);
	
	new = copy_array(arr1, 5);
	
	
	printf ("new:  ");
	print_array (new,5);
	
	
	q();
	
	printf("x = %ld, y = %ld\n",x,y);
	swap (&x,&y);
	printf("after swap: \nx = %ld, y = %ld\n",x,y);
	
	printf("x = %ld, y = %ld\n",*px,*py);
	swap (&x,&y);
	printf("after swap: \nx = %ld, y = %ld\n",*px,*py);
	
	
 
  	 
    printf("%ld %ld\n", StrLen(X) , StrLen(Y));
    if (ret > 0) {
       		 printf("%s", "X is greater than Y");
   		 }
    else if (ret < 0) {
        printf("%s", "X is less than Y");
    }
    else {
        printf("%s", "X is equal to Y");
    }
 
	

	return 0;
}
