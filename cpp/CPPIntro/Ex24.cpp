#include <iostream>
struct Ex24
{
	explicit Ex24(int);
	~Ex24();
	void Foo();
	void Bar() const;

	int m_a;
	int *m_p;
};

Ex24::Ex24(int a_) : m_a(a_), m_p(new int(a_)) {}

Ex24::~Ex24() { delete m_p; m_a = 0;}

void Ex24::Foo() { --m_a; ++(*m_p);}

void Ex24::Bar() const 
{
	std::cout << "Inside Bar Func" << std::endl;
	std::cout << "m_a: " << m_a << std::endl;
	std::cout << "&m_a: " << &m_a << std::endl;
	std::cout << "*m_p: " << *m_p << std::endl;
	std::cout << "m_p: " << m_p << std::endl;
	std::cout << "&m_p: " << &m_p << std::endl;

	// m_a = 0;
	// m_p = 0;
	// *m_p = 0;
	// Foo();
}

void Fifi(const Ex24& ex24_)
{
	ex24_.Bar();
}

int main()
{
	Ex24 x1(2);

	x1.Foo();
	// Fifi(x1);
	x1.Bar();

	return 0;
}