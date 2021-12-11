/***********
* VSA API * 
************/

#ifndef __VSA_H__OL111__
#define __VSA_H__OL111__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;
/* typedef struct vsa_header vsa_header_t; (for .c file) */


/* pool size should be atleast 16 bytes, for meta-data and the first header.
** - pool_start should be aligned otherwise it will aligned to word size.
** - Returns pointer to the pool (ready for allocation). */
vsa_t *VSAInit(void *pool_start, size_t pool_size);

/* - Returns pointer to allocated block with the asked size.
** - If there is no free block, returns NULL
** - time complexity of o(n)
** - May include defragmentaion */
void *VSAAlloc(vsa_t *pool, size_t size);

/* Free the allocated block 
** - time complexity of o(1) */
void VSAFree(void *block);

/* Return the largest availble block
** - May include defragmentaion
** - time complexity of o(n) */
size_t VSALargestBlockAvailble(vsa_t *pool);

#endif /*__VSA_H_HOL111__*/
