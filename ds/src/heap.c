/********************************************
	Author: Dvir Natan
	Reviewer: Yael
	Status: Send
	Date: 13/12/2021
********************************************/

#include <stdio.h>/* print func */
#include <assert.h>
#include <stdlib.h> /* malloc */

#include "heap.h"

#define RIGHT(x) (x << 1) | 1
#define LEFT(x) x << 1
#define PARENT(x) x >> 1 

struct heap
{
    dvector_t *vector;
    int (*cmp_func)(const void *one, const void *other);
};

static size_t Find(heap_t *heap, void *data, int(* is_match_func)(const void *one, const void *other));
static void Swap(heap_t *heap, size_t parent, size_t side);
static void HeapifyUp(heap_t *heap);
static void HeapifyDown(heap_t *heap, size_t i);
static void Remove(heap_t *heap, size_t i);
void print2DTree(heap_t* heap);

heap_t *HeapCreate(int(*cmp_func)(const void *one, const void *other))
{
    #define INIT_CAPACITY 5
    heap_t *heap;
    void *DEADBEEF = (void*)0XDEADBEEF;
    assert(cmp_func);

    heap = malloc(sizeof(heap_t));

    if(heap == NULL)
    {
        return NULL;
    }

    heap->vector = DVectorCreate(INIT_CAPACITY);

    if(heap->vector == NULL)
    {
        free(heap);
        return NULL;
    }

    heap->cmp_func = cmp_func;
    heap->vector =  DVectorPushBack(heap->vector, DEADBEEF);

    return heap;
}

void HeapDestroy(heap_t *heap)
{
    assert(heap);

    DVectorDestroy(heap->vector);
    heap->vector  = NULL;
    free(heap); heap = NULL;
}

int HeapInsert(heap_t *heap, void *data)
{
    dvector_t *tmp;
    assert(heap);
    tmp = DVectorPushBack(heap->vector, data);
    if(tmp == NULL)
    {
        return -1;
    }
    heap->vector = tmp;
    HeapifyUp(heap);
    return 0;
}

void *HeapRemove(heap_t *heap, void *data, int(* is_match_func)(const void *one, const void *other))
{
    size_t i;
    void *ret = NULL;
    assert(heap);
    assert(is_match_func);
    
    i = Find(heap, data, is_match_func);
    if(i == 0)
    {
        return NULL;
    }
    ret = DVectorGetElement(heap->vector, i);
    Remove(heap, i);
    return ret;
}

void HeapPop(heap_t *heap)
{
    dvector_t *tmp;
    void *new_root;
    assert(NULL != heap);
    
    new_root = DVectorGetElement(heap->vector, DVectorSize(heap->vector) - 1);

    DVectorSetElement(heap->vector, new_root, 1);
    tmp = DVectorPopBack(heap->vector);

    if(tmp != NULL)
    {
        heap->vector = tmp;
    }

    HeapifyDown(heap, 1);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return DVectorGetElement(heap->vector, 1);
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return DVectorSize(heap->vector) - 1;
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);

    return (!HeapSize(heap));
}

/*_______________ STATIC FUNCTIONS __________________*/

/* return the found index or 0 if not found */
static size_t Find(heap_t *heap, void *data, int(* is_match_func)(const void *one, const void *other))
{
    size_t i = DVectorSize(heap->vector) - 1;
    while(i > 0 && 1 != is_match_func(DVectorGetElement(heap->vector, i), data))
    {
        --i;
    }

    return i;
}

static void Swap(heap_t *heap, size_t parent, size_t side)
{
    void *tmp = DVectorGetElement(heap->vector, side);
    DVectorSetElement(heap->vector, DVectorGetElement(heap->vector, parent),side);
    DVectorSetElement(heap->vector, tmp, parent);
}

static void HeapifyUp(heap_t *heap)
{
    int status = 0;
    int i = DVectorSize(heap->vector) - 1;

    while(i > 1)
    {
       status =  heap->cmp_func(DVectorGetElement(heap->vector, i), 
       DVectorGetElement(heap->vector, PARENT(i)));
       if(status > 0)
       {
            Swap(heap, PARENT(i), i);
            i = PARENT(i);
       }
       else
       {
           return;
       }
    }
}

static void HeapifyDown(heap_t *heap, size_t i)
{
    size_t largest;
    if(i >= DVectorSize(heap->vector) / 2)
    {
        return;
    }
 
    largest = (i << 1) | (0 > heap->cmp_func(DVectorGetElement(heap->vector, LEFT(i)), 
                            DVectorGetElement(heap->vector, RIGHT(i))));
   
    if(0 > heap->cmp_func(DVectorGetElement(heap->vector ,i),
                          DVectorGetElement(heap->vector, largest)))
    {
        Swap(heap, i, largest);
        HeapifyDown(heap, largest);
        HeapifyUp(heap);
    }
    return;
}

static void Remove(heap_t *heap, size_t i)
{
    dvector_t *tmp;
    void *to_remove = NULL;
    to_remove = DVectorGetElement(heap->vector, DVectorSize(heap->vector) - 1);
    DVectorSetElement(heap->vector, to_remove, i);
    tmp = DVectorPopBack(heap->vector);
    if(tmp != NULL)
    {
        heap->vector = tmp;
    }

    HeapifyDown(heap, i);
}


/***********PRINT***************/
#define PRINT_COUNT 10
static void print2D(heap_t* heap, size_t inode, int space)
{
    int i;
    if (inode > HeapSize(heap))
        return;
        
    space += PRINT_COUNT;
    print2D(heap, inode * 2 + 1, space);

    printf("\n");
    for (i = PRINT_COUNT; i < space; ++i)
        printf(" ");
    printf("i=%lu,d=%d\n", inode, *(int*)DVectorGetElement(heap->vector, inode));

    print2D(heap, inode * 2, space);
}

void print2DTree(heap_t* heap)
{
    print2D(heap, 1, 0);
}
/*************************************/

