#include <iostream>
#include <typeinfo>

template<>
void foo(int t)
{
	std::cout << t << " Specialized foo (int)\n";
}

template<typename T>
void foo(T t)
{ 	
	std::cout << t << " Generic foo for " <<  typeid(t).name()  <<   std::endl;
}


int main()
{
	int *pt = NULL;
	foo(pt);
	foo(4);
	foo<int>(5);

	return 0;
}