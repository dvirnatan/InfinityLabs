#include <iostream>

class X 
{
public:
	void Foo(int num) {m_x = num;}
	int Get(){return m_x;}
	int m_x;
};

class Y : public X 
{
public:
	void Foo(int x_num, int y_num){m_y = y_num; m_x = x_num;}
	int Get() {return m_y;}
	int m_y;
};

int main()
{
	X *xp = new X;
	Y *yp = new Y;

	xp->Foo(5);
	yp->Foo(10, 20);
	
	std::cout << xp->Get() << std::endl;
	std::cout << yp->Get() << std::endl;
}

