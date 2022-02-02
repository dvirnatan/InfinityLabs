#include <iostream>

struct Ex23
{
	Ex23(int a_, int b_);

	void Inc();
	void Dec();

	int m_a;
	int m_b;
};

struct Ex23_b
{
	Ex23_b(int a_, int b_) : m_a(a_), m_b(b_) {}

	int m_a;
	int m_b;
};

Ex23::Ex23(int a_, int b_) : m_a(a_) , m_b(b_)
{}



void Ex23::Inc()
{
	std::cout << "this Inc " << this << std::endl;
	++m_a;
	++m_b;
	std::cout << "&m_a: " << &m_a << " &m_b " << &m_b << std::endl;

}

void Ex23::Dec()
{
	void* &&ref = this;
	std::cout << "this Dec " << this << std::endl;
	std::cout << "ref Dec " << &ref << std::endl;
	--m_a;
	--m_b;
	std::cout << "&m_a: " << &m_a << " &m_b " << &m_b << std::endl;
}

void Inc(Ex23& x)
{
	//std::cout << this << std::endl;
	++x.m_a;
	++x.m_b;
}


int main()
{

	Ex23 x1(3, 5);
	//Inc(x1);
	Ex23 x2(x1);
	Ex23_b y1 (5, 6);
	// std::cout << "m_a = " << x1.m_a << "m_b = " << x1.m_b
	// << std::endl;
	// x1.Inc();
	x2.Dec();
	// std::cout << "m_a = " << x1.m_a << "m_b = " << x1.m_b
	// << std::endl;
	// std::cout << "m_a = " << x2.m_a << "m_b = " << x2.m_b
	// << std::endl;
	std::cout << "sizeof(x1) " << sizeof(x1) << std::endl;
	std::cout << "sizeof(y1) " << sizeof(y1) << std::endl;
	return 0;
}

