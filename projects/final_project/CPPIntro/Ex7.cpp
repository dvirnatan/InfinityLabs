#include <stdio.h>
#include <iostream>

int main()
{
    float *f = new float(0.1);
    printf("%f\n", *f);
    delete f;
    int *null = NULL;
    delete (null);

    f = new float[15];
    f[1] = 12.5;
    std::cout << f[1] << std::endl;
    delete []f;

    int *one = new int(5);
    //one = new int(7);
    std::cout << "one is: " << *one << std::endl;
    delete one;
    delete one;
    return 0;
}