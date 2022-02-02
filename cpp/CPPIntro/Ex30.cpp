#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

struct BadDog : public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog") : runtime_error(s_) {}
};

void Fifi()
{
    throw BadDog("bad pup\n"); cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar after Foo" << endl;
}

int main()
{
    try
    {
        Bar();
		cout << "getting here?" << endl; // nop.
    }
    catch(bad_alloc&)
    {
        std::cerr << "Out of memory! exiting."; exit(2);
    }
    catch(BadDog& b)
    {
        std::cerr << "Bad dog exception: " << b.what(); exit(3);
    }
    catch(exception& r)
    {
        cerr << "unknown exception: " << r.what();
        exit(4);
    }

    return 0;
}