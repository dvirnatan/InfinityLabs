#include <iostream>

namespace useless
{
	unsigned int g_wastefull[400];
	void Foo() {std::cout << "Foo() in useless" << std::endl; };
	
	namespace stam
	{
		void Foo () {std::cout << "Foo() in isless::stam" << std::endl;};
	}
}

namespace stupid
{
	void Foo() {std::cout << "Foo() in stupid" << std::endl;};
	void Bar() {std::cout << "Bar() in stupid" << std::endl;};
	void DoNothing(unsigned int) {std::cout << "Donothing(unsigned int) in stupid" << std::endl;};
}

namespace useless
{
	#define X 5
	int x = ;
	void DoNothing(int) {std::cout << "Donothing(int) in useless x = " << X << std::endl;}
} // namespace useless

//using namespace useless;

void DoStuff()
{
	stupid::Bar();
	//Foo();
	using stupid::Foo;
	Foo();
	using namespace stupid;
	Bar();
}

void Foo() {std::cout << "nothing\n";};

//using namespace stupid; // forbidden!

namespace comeon = useless::stam;

void DoMoreStuff()
{
	comeon::Foo();
	stupid::Foo();
	useless::Foo();
	Foo();
	stupid::Bar(); //why no error?

}

int main()
{
	std::cout << "x = " << X << std::endl;
	// useless::DoNothing(5);
	// std::cout << "x = " << useless::x << std::endl;
	//DoStuff();
	//DoMoreStuff();
	return 0;
}