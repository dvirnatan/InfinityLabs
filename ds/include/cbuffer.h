/************************
 ****** CBuffer API******
 * **********************/

#ifndef __CBUFFER_H__OL111__
#define __CBUFFER_H__OL111__

#include <stddef.h> /* size_t */
#include <unistd.h> /*ssize_t*/
/* either size or write should be used, not both*/
/*
struct cbuffer
{
    size_t capacity;
    size_t size;  choose this
    size_t write;  or this
    size_t read;
    char buffer[1];
};
*/

typedef struct cbuffer cbuff_t;

/*Error:failed malloc return NULL pointer*/
cbuff_t *CBuffCreate(size_t initial_capacity);

/*cbuff should be valid
O(n) */
void CBuffDestroy(cbuff_t *cbuffer);

/*The function returns the number of bytes actually written
cbuff should be valid. 
O(n) */
ssize_t CBuffWrite(cbuff_t *cbuffer, const void *src, size_t nbytes);   

/* The function returns the number of bytes actually read
cbuff should be valid. */
ssize_t CBuffRead(cbuff_t *cbuffer, void *dest, size_t nbytes);

/* return the number of written bytes
cbuff should be valid*/
size_t CBuffSize(const cbuff_t *cbuffer);

/*return 1 if true, 0 if false
cbuff should be valid*/
size_t CBuffIsEmpty(const cbuff_t *cbuffer);

/* return the number of bytes avilable to write
cbuff should be valid*/
size_t CBuffFreeSpace(const cbuff_t *cbuffer);

#endif /*__CBUFFER_H__OL111__*/
