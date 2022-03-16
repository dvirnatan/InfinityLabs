#include <iostream>
using namespace std;

class A
{
public:
    A()  { cout<< "ctor A\n"; }
    ~A() { cout<< "dtor A\n"; }
};

class B
{
public:
    B()  { cout<< "ctor B\n"; }
    ~B() { cout<< "dtor B\n"; }
private:
    A a;
    A*a2;
};

class C :public B
{
public:
    C(A &aa) : a1(aa), a2(aa) { cout<< "ctor C\n"; }
    ~C()              { cout<< "dtor C\n"; }
private:
    const A &a1;
    A a2;
};

int main()
{
    A a;
    C c(a);
}