#include <iostream>
using namespace std;

struct Base
{
    Base(int a=0)   { cout << "Base ctor" << endl; }
    virtual ~Base() { cout << "Base dtor" << endl; }
    Base(const Base&) { cout << "Base cctor" << endl; }
    virtual void operator=(const Base&)  { cout << "Base =" << endl; }
    virtual void print() const { cout << "Base print" << endl; } 
};

struct Derived : public Base
{
    Derived()   { cout << "Derived ctor" << endl; }
    ~Derived() { cout << "Derived dtor" << endl; }
    Derived(const Derived&) : Base(*this)  { cout << "Derived cctor" << endl; }
    void operator=(const Derived&)  { cout << "Derived =" << endl; }
    void print() const{ cout << "Derived print" << endl; } 
};

void Print(const Base& p) {     p.print(); }

int main()
{
Base b;

std::cout << "\n";

Base *pb = new Derived;

std::cout << "\n";
Derived drv(*static_cast<Derived*>(pb));

std::cout << "\n";
Print(b);
std::cout << "\n";
    Print(*pb);
	std::cout << "\n";
    pb->print();
	std::cout << "\n";
    
    delete pb;
    return 0;
}




/* 
	Base ctor  // b

	Base ctor	// pb
	Derived ctor

	Base ctor	// dvr
	Derived cctor

	Base cctor	// 
	Base print
	Base Dtor
 
	Base cctor	// 
	Base print
	Base Dtor

	Derived print

	Base dtor

	Derived Dtor
	Base Dtor

	Base Dtor









 */