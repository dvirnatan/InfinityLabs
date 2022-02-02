#include <iostream>

class X
{
public:
	friend void Locate(const X&);
    X() : m_id(++s_cntr) {}
    int GetId() { std::cout << m_id << std::endl; return m_id; }
    int GetCntr() {std::cout << s_cntr << std::endl; return s_cntr;}
private:
    int m_id;
    static int s_cntr;
};

int X::s_cntr = 0;

void Locate(X x_)
{
	std::cout << "&s_cntr: " << &x_->s_cntr << std::endl;
	std::cout << "&m_id: " << &x_->m_id << std::endl;
}

int main()
{
    X x1;
    X x2;
	X x3;

    x1.GetId();
    x2.GetId();
	x3.GetId();
    x1.GetCntr();

	Locate(x1);
	Locate(x2);
	Locate(x3);

    return 0;
}