#include <iostream>

void foo(int, int = 3, float = 4);

int main()
{
	foo(1 );
	return 0; // this is so mush betther my god
}
// TODO: NOTHING.
void foo(int a, int b, float f)
{
	std::cout << "a=" << a << "\nb=" << b << "\nf=" << f << std::endl;
}
