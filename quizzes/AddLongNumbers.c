#include <stdio.h>
#include <string.h>
void AddLongNumbers(const char *num1, const char *num2, char *output);

int main ()
{
	char num1[] = "999";
	char num2[] = "1";
	char output[80] = {'\0'};

	AddLongNumbers(num1, num2, output);	
	printf("%s\n", output);
	
	return 0;
}

void AddLongNumbers(const char *num1, const char *num2, char *output)
{
	int i, j, t;
	unsigned int carie = 0;
	i = j  = t = 0;
	
	i = strlen(num1) - 1;
	j = strlen(num2) - 1;
	t = (i > j) ? i : j;	/* t = max(i, j) */
	++t;
	while( i >= 0 && j >= 0 )
	{
		output[t] = (((carie + num1[i] + num2[j]) - 2 * '0') % 10) + '0';
		carie = ((carie + num1[i] + num2[j]) - 2 * '0') / 10;
		--i; --j; --t;
	}
	
	if (i >= 0)
	{
		for( ; i >= 0; --i, --t)
		{
			output[t] = (((carie + num1[i]) - '0') % 10) + '0';
			carie = (int)((carie + num1[i]) - '0') / 10;
		}
	}
	
	else if (j >= 0)
	{
		for( ; j >= 0; --j, --t)
		{
			output[t] = (((carie + num2[j]) - '0') % 10) + '0';
			carie = (int)((carie + num2[j]) - '0') / 10;
		}
	}
	
	output[0] = carie + '0';
	
	if( 0 == carie )
	{
		for( t = 0; '\0' != output[t]; ++t )
		{	
			output[t] = output[t + 1];
		}
	}
}
