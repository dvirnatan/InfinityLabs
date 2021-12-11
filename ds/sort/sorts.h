
#ifndef __SORTS_H__
#define __SORTS_H__

#include <stddef.h>

/* Comparison sorts */
void BubbleSort(int *array,size_t size);
void SelectionSort(int *array, size_t size);
void InsetionSort(int *array, size_t size);


/* Linear sorts */
int CountingSort(int *array, size_t size);
int RadixSort(int *array, size_t size);

#endif /* __SORTS_H__ */

