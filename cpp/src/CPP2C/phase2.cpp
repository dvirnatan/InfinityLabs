#include <stdio.h>
#include <iostream>
	
	class B 
	{
	public:
		const int one;
		int two;
	};

	class U 
	{
		char c;
		int i;
		double d;
		void print() {std::cout << d << "\n";}
	};



int main()
{
	B b1 = {1, 2};
	B b2 = b1;
	
	// printf("sizeof A = %ld, sizeof B = %ld\n", sizeof(a), sizeof(b));
	// printf("%d, %d\n", b.one, b.two);

	return 0;
}