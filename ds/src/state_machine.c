/************************
	State Machine
	
***********************/
#include <stdio.h>

typedef enum STATE {ACCEPTED, MAYBE, DECLINE, START} state_t;

static const int LUT[4][2] = { {ACCEPTED, MAYBE},
							   {ACCEPTED, MAYBE},
							   {DECLINE, DECLINE}, 
							   {MAYBE, DECLINE}    };

int IsAccepted(char* str)
{
	state_t state = START;
	
	while(*str != '\0')
	{
		state = LUT[state][*str - '0'];
		printf("%d\t", state);
		++str;
	}
	
	return (state == ACCEPTED);
}

int main ()
{
	char *str = "0010010";
	
	printf("\n\n%d\n",IsAccepted(str));
	
	return 0;
}
