#include <stdio.h>
#include <stdlib.h>


void ifelse()
{
	char c = 0;

	system ("stty -icanon -echo");

	while ((c = getchar()) != 27)
	{
		if (c == 'A')
		{
			printf("A-pressed\n");
		}
		if (c == 'T')
		{
			printf("T-pressed\n");
		}
	}
	system ("stty icanon echo");
}

void Case()
{
	char c = 0;

	system ("stty -icanon -echo");

	while ((c = getchar()) != 27)
	{
		switch (c)
		{
			case 't':  
			case 'T':
				printf("T-pressed\n");
				break;
							
			case 'A': 
				printf("A-pressed\n");
				break;
			case 'a':
				printf("A-pressed\n");
				break;
			default: 
				break;
		}			 
	}
	system ("stty icanon echo");
}

void null()
{
}

void presT()
{
	printf("T-preesed\n");
}
void presA()
{	
	printf("A-preesed\n");
}

void lut()
{

	typedef void (*ptr_fun)();

	static ptr_fun const ptr_presT = presT;
	static ptr_fun const ptr_presA = presA;
	static ptr_fun const pn = null;
	
	static const ptr_fun arr_ptr_fun[128] = 
	     { pn, pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, ptr_presA,
		    	               pn ,pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, ptr_presT,
		    		   pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn, pn, pn, pn,
		   pn, pn, pn, pn, pn, pn, pn               };
	   	
	char c = 0;
	
	system ("stty -icanon -echo");
	
	while ((c= getchar()) != 27)
	{
		(*(arr_ptr_fun + (unsigned)c))();
	}
	
	system ("stty icanon echo");
}







