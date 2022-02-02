#include <iostream>
#include "complex.hpp"

using namespace ilrd;

static void Test(const Complex& c, double e_real, double e_imaginary, int line);

int main()
{
	Complex c1(1, 0.5), c2(2, 1.5), c3;

	Test(c1, 1, 0.5, __LINE__);

	Test(c2, 2, 1.5, __LINE__);

	c3 = c2 + c1;

	Test(c3, 1+2, 0.5+1.5, __LINE__);
	
	c3 -= c2;
	if(!(c3 == c1))
	{
		std::cout << __LINE__ << ": failed" << std::endl;
	}
	c3 += c3;
	Test(c3, 2, 1, __LINE__);

	// std::cin >> c1;
	// std::cout << c1 << std::endl;

	c1 = Complex(1, 2);
	c2 = Complex(2, 4);
	c3 = c1 * c2;
	Test(c3, -6, 8, __LINE__);
	c3 = c3 / c2;
	Test(c3, 1, 2, __LINE__);

	std::cout << "BenchMade:" << std::endl;

	for(int i = 0; i < 100000; ++i)
	{
		c1 += c1;
	}

	return 0;
}

static void Test(const Complex& c, double e_real, double e_imaginary, int line)
{
	if(! (c.GetReal() == e_real && c.GetImaginary() == e_imaginary))
	{
		std::cout << line << ": Test fail on object: " << c  << std::endl;
	}
}

