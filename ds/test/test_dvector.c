#include <stdio.h>
#include "dvector.h"

int main ()
{
	int int_elem1 = 1;
	size_t i = 0;
	size_t n = 40;
	dvector_t *dvector;
	
	dvector = DVectorCreate(0);
	
	while (n > 0)
	{
		dvector = DVectorPushBack(dvector, &int_elem1);
		printf("Capacity  =  %ld\t \t Size = %ld\t(%ld)\n", DVectorCapacity(dvector),DVectorSize(dvector) ,i);
		++i;
		--n;
	}
	
	puts("________PopBack_________");
	n = 50;
		while (n > 0 )
	{
		dvector = DVectorPopBack(dvector);
		printf("Capacity  =  %ld\t \t Size = %ld\t(%ld)\n", DVectorCapacity(dvector),DVectorSize(dvector) ,i);
		--i;
		--n;
	}

	
	
	return 0;
}
