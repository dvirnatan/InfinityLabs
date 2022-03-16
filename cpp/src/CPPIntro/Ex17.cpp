#include <iostream>
#include <stdio.h>

void addone(int &one);

int main()
{
	int i = 8;
	int &ip = i;
	ip = 9;
	std::cout << "i = " << i << std::endl;
	int *pt = &ip;
	int *&pt2 = pt;
	//&pt2 = pt;
	
	std::cout << *pt2 << "\n";
	std::cout << "adress of (i) = " << &i << "\n";

	char a = 'a';
	char &A = a;
	char *cpt = &a;
	A = 'b';
	std::cout << "(a) = " << reinterpret_cast<void*>(&a) << "\n";
	std::cout << "(A) = " << reinterpret_cast<void*>(&A) << "\n";
	std::cout << "sizeof(A) = " << sizeof(A) << "\n";
	std::cout << "adress of (a) = " << &a << "\n";
	cpt = &A;
	std::cout << "adress of (A) = " << &A << "\n";
	printf("%p\n", &A);
	printf("%p\n", &a);
	std::cout << "------------------------\n";
	std::cout << "i = " << i << "\n";
	addone(i);
	std::cout << "i = " << i << "\n";


	return 0;
}

void addone(int &one)
{
	++one;
}