/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~
 ~ Author        EsJay L Blau                                  *
 * Description   shared_ptr test file                          ~
 ~ Group         R&D 111                                       *
 * Company       ILRD Ramat Gan                                ~
 ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <iostream>
using std::cout;
using std::endl;
#include "SharedPtr.hpp"   // this.API
using namespace ilrd;

#define S_MSG(func) "SUCCESS: " #func " works as expected!\n"
static const char *_N_ = "\033[0m";
static const char *_BLD_ = "\033[1m";
static const char *_U_ = "\033[4m";
static const char *_R_ = "\033[31m";
static const char *_G_ = "\033[32m";
static const char *_Y_ = "\033[33m";
static const char *_P_ = "\033[35m";
static const char *_B_ = "\033[36m";

class Base
{
private:
    int m_i;
public:
    Base(int i = 0);
    virtual ~Base();
};

Base::Base(int i): m_i(i)
{
    // empty
}

Base::~Base()
{
    // empty
}

class Derived: public Base
{
private:
    char m_c;
public:
    Derived(char c = 0);
    virtual ~Derived();
};

Derived::Derived(char c): m_c(c)
{
    // empty
}

Derived::~Derived()
{
    // empty
}

void shared_ptrTest()
{
    SharedPtr<Base> baseSP(new Base(3));
    SharedPtr<Base> emptySP;
    SharedPtr<Derived> derSP(new Derived(4));
    // derSP = baseSP; should not compile
    baseSP = derSP;

    
}

int main()
{
    cout <<_B_<<_BLD_<<"\t\t~"<<_U_<< "SJ Shared Pointer"<<_N_<<_B_<<_BLD_
         <<"~\n"<<_N_;

    shared_ptrTest();

    cout <<_B_<< "Please check " <<_P_<<_BLD_<< "Valgrind " <<_N_<<_B_<<
        "to ensure memory integrity.\n\t\t~Have a lovely day!~" <<_N_<< endl;

    return 0;
    (void)_Y_;
    (void)_R_;
    (void)_G_;
}