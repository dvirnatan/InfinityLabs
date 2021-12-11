/***********
* FSA API * 
************/

#ifndef __FSA_H__OL111__
#define __FSA_H__OL111__

#include <stddef.h> /*size_t*/



typedef struct fsa fsa_t;

/* Returns suggested size of memory pool including meta-data */
size_t FSASuggestSize(size_t block_number, size_t block_size);

/* - Returns pointer to the pool (ready for allocation).
** - If pool_size is not a result of FSASuggestSize(), number of blocks might
**   be smaller than intended. */
fsa_t *FSAInit(void *pool_start, size_t pool_size, size_t block_size);

/* - Returns pointer to allocated block 
** - If there is no free block, returns NULL */
void *FSAAlloc(fsa_t *pool);

/* Frees a block */
void FSAFree(fsa_t *pool, void *block);

/* Returns number of free blocks. */
size_t FSACountFree(const fsa_t *pool);

#endif /*__FSA_H_HOL111__*/
