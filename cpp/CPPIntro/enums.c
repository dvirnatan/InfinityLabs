#include <stdio.h>

int main()
{   
    enum E{AA, BB, CC, DD};
    enum E2{TT, KK};
    enum E e = (E)2; 
    enum E2 e2 = TT; 
    int i = e;
    /*(int)e = 3;*/
    printf("%d\n", e2);
    printf("%d\n", i); 
    return 0;
}