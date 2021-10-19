#ifndef __DVector_H__OL111__
#define __DVector_H__OL111__

#include <stddef.h> /*size_t*/
typedef struct dvector dvector_t;

/*
Create new dvector 
Error: malloc failed
Time Complexity: O(1)
Return type: dvector_t *
*/
dvector_t *DVectorCreate(size_t initial_capacity);

/*
Free all spaces taken by dvector 
Error: dvector isn't valid. 
Time Complexity: O(1)
Return type: void
*/
void DVectorDestroy(dvector_t *dvector);

/*
Set an existing dvector index to element pointer. 
Error: malloc failed. dvector isn't valid. index isn't valid.
Time Complexity: O(1)
Return type: void
*/
void DVectorSetElement(dvector_t *dvector, void *element, size_t index);

/*
Returns pointer to element in a giver index 
Error: dvector isn't valid. index isn't valid.
Time Complexity: O(1)
Return type: void *
*/
void *DVectorGetElement(const dvector_t *dvector, size_t index);

/*
Push element pointer to end of dvector. Enlarge dvector If needed.
If realloc failed, NULL is returned and element is not pushed.
Error: dvector isn't valid. element doesn't exist.
Time Complexity: O(n)/ O(1) amortized.
Return type: using realloc might return a new pointer.
*/
dvector_t *DVectorPushBack(dvector_t *dvector, void *element);

/*
Remove element from end of the dvector.
Element is popped out, regardless of realloc return value.
Error: dvector isn't valid. 
Time Complexity: O(n)/ O(1) amortized.
Return type: using realloc might return a new pointer.
*/
dvector_t *DVectorPopBack(dvector_t *dvector);

/*
Returns current used size of dvector
Error: dvector isn't valid. 
Time Complexity: O(1)
Return type: size_t
*/
size_t DVectorSize(const dvector_t *dvector);

/*
Returns current dvector capacity.
Error: dvector isn't valid. 
Time Complexity: O(1)
Return type: size_t
*/
size_t DVectorCapacity(const dvector_t *dvector);

/*
Resize the dvector.'size' should be bigger than return value of DVctorSize()
DVectorSize(dvector) <= size <= DVectorCapacity(dvector)
Error: dvector isn't valid. reallocation failed.
Time Complexity: O(n)/ O(1) amortized.
Return type: using realloc might return a new pointer.
*/
dvector_t *DVectorResize(dvector_t *dvector, size_t size);

/*
Shrink the capacity to match current used size of the dvector.
Error: dvector isn't valid. reallocation failed.
Time Complexity: O(n)/ O(1) amortized.
Return type: using realloc might return a new pointer.
*/
dvector_t *ShrinkToFit(dvector_t *dvector);

#endif /*__DVector_HOL111__*/
