#include <iostream>
#include "singelton.hpp"

using ilrd::Singleton;
using std::cout;
using std::endl;


int main()
{
    int &x = Singleton<int>::getInstance();

    x = 5;
  

    int &y = Singleton<int>::getInstance();
    
    cout << y << endl;

    return 0;
}
