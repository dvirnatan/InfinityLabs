#include "ws3.h"

int main (int argc, char **argv,__attribute__((unused)) char **envp)
{
	
	size_t n = 0;
	Envp(envp);
	n = 100;
	
	if (argc == 2)
	{
		n = atoi(argv[2]);
		printf("%ld\n", n);
	}
	printf("%ld\n", Josephus (n));
	
	return 0;
}																	
