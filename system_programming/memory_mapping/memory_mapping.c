#include <stdio.h>

int g = 3;
static int sg = 5;
const int cg = 3;
const static int csg = 5;
static void sfoo(void); 
void foo(void); 

int main(int agrc, char *argv[], char* envp[])
{
	char string[] = "hello world";
	sfoo();
	printf("g %p\n", &g);
	printf("sg %p\n", &sg);
	printf("cg %p\n", &cg);
	printf("csg %p\n", &csg);
	printf("sfoo %p\n", &sfoo);
	printf("foo %p\n", &foo);
	printf("argv %p\n", &argv);
	printf("envp %p\n", &envp);

	return 0;
}

static void sfoo(void)
{
	g = 4;
}
void foo(void)
{
	g = 2;
}
