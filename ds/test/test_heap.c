#include <stdio.h>
#include "/home/dvir/git/ds/include/heap.h"

void print2DTree(heap_t* heap);

int IsMatch(const void *one, const void *other)
{
    return (*(int*)one == *(int*)other);
}

int cmp_func (const void* one, const void *other)
{
	return (*(int*)one) - (*(int*)other);
}

int main()
{
    heap_t *heap = NULL;
    size_t len = 0;
    size_t i = 0;
    int *num = NULL;
    int arr[] = {1,2,3,5,6,7,8,9};
    len = (sizeof(arr)/sizeof(int));

    heap = HeapCreate(cmp_func);

    while(i < len)
    {
        HeapInsert(heap, &arr[i]);
        ++i;
    }
    
    print2DTree(heap);
    puts("-------------------------------");

    while(!HeapIsEmpty(heap))
    {
        num = HeapPeek(heap);
        printf("%d ", *num);
        HeapPop(heap);
    }

    puts("\n-------------------------------");
/*
    HeapRemove(heap, &arr[8], IsMatch);

    puts("-------------------------------");
    print2DTree(heap);

    HeapRemove(heap, &arr[2], IsMatch);
    HeapRemove(heap, &arr[3], IsMatch);
    HeapRemove(heap, &arr[2], IsMatch);
    HeapRemove(heap, &arr[3], IsMatch);

    puts("\n-------------------------------");
    print2DTree(heap);
*/
    HeapDestroy(heap);
    return 0;
}
/*
gd src/heap.c src/dvector.c test/test_heap.c -I include
*/