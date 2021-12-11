/*****************************
*****Memory Mapping Part 1 (System Programming)
*****Author: Lior Ben Harosh
*****Date: 04/11/2021 
******************************/

#include <stdio.h> /* printf() */

/***********************************************************************/
void extern_fun (void)
{
	int y;
	printf("&y (extra fun) = %p\n", (void *)&y);
}

