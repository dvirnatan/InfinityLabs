#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */

#include "vsa.h"

int main()
{
    
    vsa_t *pool = malloc(1000);
    double *darr;
    int *arr;
    int *iarr;
    VSAInit(pool, 1000);
    
    arr = VSAAlloc(pool, 100);
    iarr = VSAAlloc(pool, 600);
    darr = VSAAlloc(pool, 200);
    
 
    VSAFree(arr); 
 	
 	VSAFree(iarr);
    
    VSAFree(darr);
   

 
    iarr[5] = 12;
    darr[3] = 3.5;
    arr[1] = 7;
    printf("iarr[5] = %d\n", iarr[5]);
    printf("darr[3] = %f\n", darr[3]);
    
   printf("VSALargestBlockAvailble = %lu\n", VSALargestBlockAvailble(pool));
    free(pool);
    
    return 0;
}
