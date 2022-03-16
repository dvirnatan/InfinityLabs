#include <iostream>

class X
{
private:
    /* data */
public:
    X();
    X(int a_);
    X(int a_, int b_);
	int m_b;
    operator char()const;
    void Print() const;
private:
    int m_a;
};

X::X() : m_a(0) {}

X::X(int a_) : m_a(a_) {}

X::X(int a_, int b_) : m_a(a_ + b_) {}

X::operator char()const
{
    return m_a;
}

void X::Print() const
{
    std::cout << "X::print(): " << m_a << std::endl;
}

void Fifi(X x_)
{
	x_.m_b = 5;
    std::cout << "Fifi(): " << x_ << std::endl;
    x_.Print();
}

int main()
{
    X x1(97);

    Fifi(x1);
	
	//Fifi(static_cast<X>(7));
	// Fifi ((X)7);
    // Fifi((X)9);

	//std::cout << x1 << std::endl;

    return x1 * 3;
}