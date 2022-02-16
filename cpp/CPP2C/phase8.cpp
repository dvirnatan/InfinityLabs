#include <iostream>
static int counter = 0;
class B
{
public:
	B() {std::cout << "Ctor num:" << ++counter << std::endl;}
	~B() {std::cout << "Dtor num:" << ++counter << std::endl;}
	int x;
	int y;
};


int main()
{
	B array1[5];

	counter = 0;

	B *array2 = new B[5];
	counter = 0;
	delete[] array2;

	return 0;
}