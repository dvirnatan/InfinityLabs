#include <iostream>
#include <typeinfo>

class X
{
public:
    X() { std::cout << "X Ctor: " << this << std::endl; }
   virtual ~X() { std::cout << "X Dtor: " << this << std::endl; }
private:
    double m_a;
};

class Y : public X
{
public:
    Y() { std::cout << "Y Ctor: " << this << std::endl; }
    ~Y() { std::cout << "Y Dtor: " << this << std::endl; }
    std::string GetStr() { return "Y\n"; }
private:
    int m_b;
};

void Foo(X x)
{
    //std::type_info t = typeid(x);
    std::cout << typeid(x).name() << std::endl;
    //x.GetStr();
}

int main()
{
    // X *xp = new Y[2];
    // delete[] static_cast<Y*>(xp);
	// std::cout << sizeof(X) << std::endl;

    // X *xp = new Y;
    Y y;
    Foo(y);
    // delete xp;


    return 0;
}