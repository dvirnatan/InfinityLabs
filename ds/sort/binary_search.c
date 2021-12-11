#include <stdio.h>
#include <stdlib.h>

int BinarySearchIterativ(int *arr, size_t len, int num);
int BinarySearchRecursive(int *arr, size_t len, int num);
static int BinarySearchAux(int *arr, size_t left, size_t right, int num);


int main()
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9, 10 ,11 ,12 };
    size_t index = 0;
    size_t len = sizeof(arr)/sizeof(int);
    index = BinarySearchRecursive(arr, len, 12);
    
    if(index != -1)
    {
        printf("number is: %d\n", arr[index]);
    }
}

int BinarySearchIterativ(int *arr, size_t len, int num)
{
    size_t left, right, middle;
    left = 0;
    right = len - 1;
    
    while(left <= right)
    {
        middle = (left + right) / 2;
        if(arr[middle] > num)
        {
            right = middle - 1;
        }
        else if(arr[middle] < num)
        {
            left = middle + 1;
        }
        else
        {
            return (int)middle;
        }
    }
    return -1;
}

static int BinarySearchAux(int *arr, size_t left, size_t right, int num)
{
    size_t middle = (left + right) / 2;

    if(arr[middle] == num)
    {
        return middle;
    }

    if(left == right)
    {
        return -1;
    }

    if(arr[middle] > num)
    {
        return BinarySearchAux(arr,left, middle - 1, num);
    }

    if(arr[middle] < num)
    {
        return BinarySearchAux(arr, middle + 1, right, num);
    }
    
}

int BinarySearchRecursive(int *arr, size_t len, int num)
{
  return BinarySearchAux(arr, 0, len - 1, num);
}