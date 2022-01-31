#include "string.hpp"
#include <iostream>
#include <cstddef>


int main()
{
	ilrd::String s1("hello");

	printf("%s\n", s1.ilrd::String::Cstr());
	ilrd::String s2(s1);
	std::cout << s2.ilrd::String::Cstr() << std::endl;

	ilrd::String s3("ok");
	std::cout << s3.ilrd::String::Cstr() << std::endl;	
	s2 = s3;
	std::cout << s2.ilrd::String::Cstr() << std::endl;
	std::cout << (s1 == s3) << std::endl;	
	
	return 0;
}