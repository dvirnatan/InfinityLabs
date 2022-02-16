#include <iostream>
using std::cout;
using std::endl;

class A
{
private:
	int a;
public:
	A();
	~A();
};

A::A()
{
	cout << "A Ctor" << endl;
}

A::~A()
{
	cout << "A Dtor" << endl;
}


class B : A
{
private:
	int b;
public:
	B();
	~B();
};

B::B()
{
	cout << "B Ctor" << endl;
}

B::~B()
{
	cout << "B Dtor" << endl;
}

class C : B
{
private:
	int c;
public:
	C();
	~C();
};

C::C()
{
	cout << "C Ctor" << endl;
}

C::~C()
{
	cout << "C Dtor" << endl;
}

int main()
{
	C c1;

	return 0;
}