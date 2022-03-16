#include <iostream>
#include <string>
#include "factory.hpp"


using ilrd::Factory;
using std::cout;
using std::endl;

class Animal
{
public:
    virtual ~Animal() =0;

    virtual void print() {};
};

Animal::~Animal() {}

class Dog : public Animal
{
public:
    ~Dog() {}
    static Animal *create(int a = 0) { return new Dog; }
    void print() { cout << "HAV-HAV\n"; }

};

class Cat : public Animal
{
public:
    ~Cat() {}
    static Animal *create(int a = 1) { return new Cat; }
    void print() { cout << "MIAO-MIAO\n"; }

};


class Duck : public Animal
{
public:

    ~Duck() {}
    static Animal *create(int a = 2) { return new Duck; }
    void print() { cout << "QUACK_QUACK\n"; }

};


//template <class BASE, typename KEY, typename PARAM>
int main()
{
	using namespace ilrd;


    Factory<Animal, int, int>& f =  Singleton <Factory<Animal, int, int> > ::getInstance();

    f.Add(0, Dog::create);
    Animal *dog = f.Create(0,0);

    f.Add(1, Cat::create);
    Animal *cat = f.Create(1, 0);

    f.Add(2, Duck::create);
    Animal *duck = f.Create(2, 0);


    dog->print();
    cat->print();
    duck->print();


    delete dog;
    delete cat;
    delete duck;

	return 0;
}