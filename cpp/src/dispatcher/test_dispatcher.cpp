#include <iostream>
#include "dispatcher.hpp"

using std::cout;
using std::endl;
using namespace ilrd;

static size_t failed_tests = 0;

static inline void Test(bool expr, size_t test_num)
{
    if (!expr)
    {
        cout << "test: " << test_num << " failed" << endl;
        ++failed_tests;
    }
}

class Animal 
{
public:
    virtual void MakeSound() =0;
    virtual void UpdateNum() =0;
};

class Dog : public Animal
{
public:
    void MakeSound() {cout << " Its time to Bark: HAV-HAV!\n";}
    void UpdateNum() {++m_num;};
private:
    int m_num = 0;
    Subscriber<Animal> sub;
};

class Cat : public Animal
{
public:
    void MakeSound() {cout << " Its time to Miao: MIAO-MIAO!\n";}
    void UpdateNum() {++m_num;};
private:
    int m_num = 0;
    Subscriber<Animal> sub;
};

int main()
{

    // Dispatcher<Animal>dispacher_obj;
    // Subscriber Subscriber_obj;
    
    return 0;
}
