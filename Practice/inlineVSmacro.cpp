#include<stdio.h>

#define max(a,b) ((a > b) ? (a) : (b))
#define n_square(a) (a * a)
#define square(a) ((a) * (a))

static int counter = 0;
int foo(){ ++counter; return 5;}
int bar(){ ++counter; return 5;}

inline int max_inline(int x, int y) {return (x > y ? x : y);}
inline int square_inline(int a) {return a * a;}
int main()
{
	int a, b;
	a = 10;
	b = 15;
	int *pt_a = &a;
	int *pt_b = &b;
	
	// pt_a = max(pt_a,pt_b);

	// pt_a = max_inline(pt_a,pt_b);

	// printf("macro: %d\n", *pt_a);
	// printf("inline: %d\n", *pt_a);

	// printf("n_sqare of 2+3 is: %d\n", n_square(2+3)); // 2 + 3 * 2 + 3
	// printf("sqare of 2+3 is: %d\n", square(2+3)); // (2 + 3) * (2 + 3)

	/****************************/

	// a = 2;
	// printf("sqare of 3 is: %d\n", square(++a));
	// a = 2;
	// printf("sqare_inline of 3 is: %d\n", square_inline(++a));
	
	counter = 0; square(foo());
	printf("foo called %d times\n", counter);
	counter = 0; square_inline(bar());
	printf("bar called %d times\n", counter);

	return 0;
}

