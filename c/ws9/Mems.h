#ifndef __MEMS_H__
#define __MEMS_H__

#include <stddef.h>



void *MemSet(void *s, int c, size_t n);
void *MemCpy(void *dest, const void *src, size_t n);
void *MemMove(void *dest, const void *src, size_t n);

#endif
