#include <stdio.h>

int main()
{
    int i, j, counter = 0;
    int arr[5][10] = {0};

    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 10; ++j)
        {
            arr[i][j] = counter++;
        }
    }

    for(i = 0; i < 5; ++i)
    {
        for(j = 0; j < 10; ++j)
        {
            printf("%d ", *(*(arr+i) + j));
        }
        puts("");
    }
    return 0;
}