#include <iostream>
#include "Ex11.h"

extern "C" void Foo() { std::cout << "foo(void)" << std::endl; };
//void Foo(int i) { std::cout << "second foo" << std::endl; };
//void Foo(char c) {std::cout << "third foo" << std::endl; };