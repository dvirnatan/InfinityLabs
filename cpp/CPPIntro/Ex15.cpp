#include <iostream>
#include "Ex15.h"

int main()
{
	char a = 'a';
	char b = 'b';
	char *p = &a;
	char *p2 = &b;
	std::cout << Max<char*>(p, p2) << std::endl;
	//int arr[12];
	// std::cout << Max<int>(3,5) << " " << Max<double>(3.7, 12.9) << " \n";
	// std::cout << Max(arr, arr+ 8) << std::endl;
	// unsigned char c = 5;
	// std::cout << Max(99, 100) << std::endl;
	
	MaxCalling();

	return 0;
}