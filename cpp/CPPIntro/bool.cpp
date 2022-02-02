#include <stdio.h>

int main()
{
    bool b1;
    bool b2;
    int i = 5;
    b2 = i;
    printf("b1 = %d\t size = %ld\n",b1, sizeof(b1));
    printf("b2 = %d\t size = %ld\n",b2, sizeof(b2));

    return 0;
}