#include <iostream>
#include <exception>
#include <string>
#include <cstdlib>

using namespace std;

class I
{
public:
	I() : local_var (555) {cout << "Ctor for I\n";}
	~I() {cout << "Dtor for I\n";}
	int local_var;
};

struct BadCat : public runtime_error
{
	BadCat(const string& s_ = "This is a bad CAT") : runtime_error (s_) {cout <<"BadCat is found\n";}
};
struct BadDog : public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog\n") : runtime_error(s_) {}
};

void BadCatFunc() throw(BadDog)
{
	throw BadCat();
}
void Fifi() //throw(BadDog)
{
	// throw BadDog(); // Used to throw an exception.
    throw BadDog("somthing else\n"); cerr << "Fifi() after throw" << endl;
}

void Foo()
{
	I i1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar after Foo" << endl;
}
void MyUnexpected()
{
    cout << "Unexpected throw\n";
    //abort();
}
void MyTerminate()
{
    cout << "MyTeminate had been called\n";
    abort();
}
int main()
{
    // set_unexpected(MyUnexpected);
    // set_terminate(MyTerminate);

    try // a block of code that can throw an exception.
    {
		BadCatFunc();
        Bar();
		cout << "getting here?" << endl; // nop.
    }

	catch(BadCat &c)
	{
		cout << "BadCat is catched!\n" << c.what();
	}
    catch(bad_alloc&) //block of code that is executed when a particular exception is thrown.
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