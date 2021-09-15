#include "ws3.h"

int main (__attribute__((unused)) int argc, __attribute__((unused)) char **argv,__attribute__((unused)) char **envp)
{
	
	
	Envp(envp);
	
	printf("%ld\n", Josephus (41));
	
	return 0;
}																	
