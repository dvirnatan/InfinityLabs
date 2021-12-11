#include<string.h>
#include <stdio.h>


void foo1(char *a, char *b)
{
    printf("%d\n", strcmp(a,b));
}

int main()
{
    char *str1 = "aaa ";
    char *str2 = "z";

    int x = strcmp("aaa ", "aaq");
    printf("%d\n", x);
    foo1(str1, str2);

    return 0;
}