#ifndef __Heap_HOL111__
#define __Heap_HOL111__

#include <stddef.h> /* size_t */
#include "/home/dvir/git/ds/include/dvector.h"

typedef struct heap heap_t;

heap_t *HeapCreate(int(* cmp_func)(const void *one, const void *other));
void HeapDestroy(heap_t *heap);
int HeapInsert(heap_t *heap, void *data);
void *HeapRemove(heap_t *heap, void *data, int(* is_match_func)(const void *one, const void *other));
void HeapPop(heap_t *heap);
void *HeapPeek(const heap_t *heap);
size_t HeapSize(const heap_t *heap);
int HeapIsEmpty(const heap_t *heap);

#endif /*__Heap_HOL111__*/
