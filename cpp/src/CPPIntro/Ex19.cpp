#include <iostream>

struct X
{
	explicit X(); // Initialization finction without parameters is named. //Default constructor (often abbreviated as:Ctor)
	explicit X(int a, int b_ = 8);// Regular (non default) Ctor.
	~X();// Deinitialization function is called destructor (Dtor).
	X(const X& other_);// Copy initialization function is called copy constructor or CCtor.
	//X& operator=(const X& other_);// Assigment operator.

	int m_a;
	const int m_b;
};

struct Y
{
	X m_x;
	int m_i;
};

X::X(): m_a(), m_b() // Implementation of the default Ctor. Why the X::X? the cose after the colon is called as initializtion list.
{
	// m_a = 3;
	// m_b = 4;
	std::cout << "this: " << this << " X default Ctor. m_a: "
	<< m_a << " m_b: " << m_b << std::endl;
}

X::X(int a_, int b_): m_a(a_), m_b(b_) //Implementation of the second Ctor.
{
	std::cout << "this: " << this << " X int Ctor. m_a " << m_a 
	<< " m_b: " << m_b << std::endl; 
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) //Imlementation of the copy Ctor.
{
	std::cout << "this: " << this << " X copy Ctor. m_a: " << m_a 
	<< " m_b: " << m_b << std::endl;
}

// X& X::operator=(const X& other_)
// {
// 	m_a= other_.m_a;
// 	//m_b= other_m.b;
// 	std::cout << "this: " << this << " X assigment perator. m_a " << m_a 
// 	<< " does not change m_b: " << m_b << std::endl;
// 	return *this;
// }

X::~X()
{
	std::cout << "this: " << this << " X Dtor. m_a " << m_a
	<< " m_b: " << m_b << std::endl;
}

int main()
{
	X x1;
	// //std::cout << sizeof(x1) << std::endl;
	// X x2(7);
	// X *px = new X(x2);
	// X x3(9,10);
	// X x4(x1);
	// x1 = x3;
	// delete px; px = 0;

	// X* xp = new X[10];
	// delete[] xp;
	//X x1{1,2};
	// X x2{10};
	//x1 == x2;

	Y y1{x1, 0};
	// //y1.m_x.m_a = 250;
	// //y1.m_x.m_b = 750;
	// // Y y2(y1);
	Y y2{x1, 10};
	// Y y3{y1.m_x.m_a, y1.m_i};
	
	y2.m_x.m_a = y1.m_x.m_a;
	y2.m_i = y1.m_i;
	

	return 0;
}