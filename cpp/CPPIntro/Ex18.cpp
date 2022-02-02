#include <iostream>

void foo(const int& num)
{
	std::cout << "const duoble = " << num << "\n";
	std::cout << "adress of const num " << &num <<"\n";
	std::cout << "sizeof(const num) = " << sizeof(num) << std::endl;
}

void bar(int& num)
{
	num = INT32_MIN;
	std::cout << "non-const duoble = " << num << "\n";
	std::cout << "adress of non-const num " << &num <<"\n";
	std::cout << "sizeof(num) = " << sizeof(num) << std::endl;
}

int main()
{
	double x = 10;
	//double& y = reinterpret_cast<double&>(x);
	foo(x);
	std::cout << "__________BAR_____________\n";
	bar(reinterpret_cast<int&>(x));
	x = 99999999999;
	int &y = reinterpret_cast<int&>(x);
	std::cout << "___________y____________\n";
	std::cout << "int y = " << y << "\n";
	std::cout << "adress of y " << &y <<"\n";
	std::cout << "sizeof(y) = " << sizeof(y) << std::endl;
	std::cout << "___________MAIN____________\n";
	std::cout << "int x = " << x << "\n";
	std::cout << "adress of x " << &x <<"\n";
	std::cout << "sizeof(x) = " << sizeof(x) << std::endl;

	return 0;
}