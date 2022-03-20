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
Dispatcher<int> *dispach;

class ChangeNum
{
public:
    void UpdateNum(int num) {dispach->Notify(num);}
};

class Animal 
{
public:
    virtual ~Animal() {}
    virtual void MakeSound() =0;
    virtual void UpdateNum(int num) =0;
};


class Dog : public Animal
{
public:
    ~Dog() {}
    Dog(): 
    m_subs([this](int num){this->UpdateNum(num);},[this](){this->MakeSound();}, *dispach)
    {

    }
    virtual void MakeSound() {cout << " Its time to Bark: HAV-HAV!\n";}
    virtual void UpdateNum(int num) {m_num = num; cout << "num updated to:" << m_num << endl;};
private:
    int m_num = 0;
    Subscriber<int> m_subs;
};

class Cat : public Animal
{
public:
    ~Cat() {}
    Cat(): 
    m_subs([this](int num){this->UpdateNum(num);},[this](){this->MakeSound();}, *dispach)
    {

    }
    void MakeSound() {cout << " Its time to Miao: MIAO-MIAO!\n";}
    void UpdateNum(int num) {m_num = num; cout << "num updated to:" << m_num << endl;};
private:
    int m_num = 0;
    Subscriber<int> m_subs;
};

int main()
{
    dispach = new  Dispatcher<int>;

    ChangeNum number;

    Dog *Rex = new Dog;
    Cat *Mitzi = new Cat;
    
    number.UpdateNum(6);

    

    delete Mitzi;
    delete Rex;
    
    delete dispach;
    return 0;
}
