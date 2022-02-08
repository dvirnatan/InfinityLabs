#include <iostream>
#include <typeinfo>
#include <exception>
#include <new>
#include <ios>

using namespace std;


class X
{
public:
	X();
	~X();
	int m_a;

};

int Foo(int) throw(bad_alloc)
{
	//X x1;
	cout << " I am Foo()"  << endl;// << x1.m_a << endl;
	throw bad_cast();
	return 6; //x1.m_a;
}

void Bar() throw(bad_cast)
{
	cout << " I am Bar()" << endl;
	// int x = 5;
	// int *i = &x;
	// char *pt = (char*)i;
	throw bad_cast();
	cout << "Bar after throw" << endl;
}

X::~X()
{
    cerr << Foo(m_a) << endl;
}

X::X() : m_a(5)
{
	// empty
}

void Fishi()
{
    X x1;

    Bar();
}

int main()
{
	// Fishi();
	try
	{
		Fishi();
		// Foo(5);
		/* code */
	}
	catch(const std::exception& bad_cast)
	{
		std::cerr << bad_cast.what() << '\n';
		cout << "cougt somthing" << endl;
	}
	
}