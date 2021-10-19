/*****************************************************************************/
/*                                                                           */
/*                            Bit Array API                                  */
/*                                                                           */
/*****************************************************************************/

#ifndef BIT_ARRAY_H_OL111
#define BIT_ARRAY_H_OL111

#include <stddef.h> /* size_t */

typedef size_t bit_arr_t;

/************************** Utility ******************************/

/* Set given index bit to on, Gets bit_array_t and return it after change */


/*SetBitOn: 
error: index should be larger than or equal to 0 & less then 64
Time Complexity: O(1)
return type: bit_arr_t 
*/
bit_arr_t SetBitOn(bit_arr_t arr, size_t index);

/*SetBitOff: 
error: index should be larger than or equal to 0 & less then 64
Time Complexity: O(1)
return type: bit_arr_t
*/
bit_arr_t SetBitOff(bit_arr_t arr, size_t index);

/*SetBit: 
error: index should be larger than or equal to 0 & less then 64, val is 0 or 1.
Time Complexity: O(1)
return type: bit_arr_t
*/
bit_arr_t SetBit(bit_arr_t arr, size_t index, size_t val);

/*SetAllOn: 
Time Complexity: O(1)
return type: bit_arr_t
*/
bit_arr_t SetAllOn(bit_arr_t arr);

/*SetBitOff: 
Time Complexity: O(1)
return type: bit_arr_t
*/
bit_arr_t SetAllOff(bit_arr_t arr);

/*GetBit: 
error: index should be larger than or equal to 0 & less then 64 
Time Complexity: O(1)
return type: int
*/
int GetBit(bit_arr_t arr, size_t index);

/*FlipBit: 
error: index should be larger than or equal to 0 & less then 64 
Time Complexity: O(1)
return type: bit_arr_t
*/
bit_arr_t FlipBit(bit_arr_t arr, size_t index);


/********************** Information *********************************/

/*CountOn: 
Time Complexity: O(1)
return type: bit_arr_t
*/
size_t CountOn(bit_arr_t arr);

/*CountOff: 
Time Complexity: O(1)
return type: bit_arr_t
*/
size_t CountOff(bit_arr_t arr);


/************************ Special ***********************************/

/*ToString: 
error: buffer should be as big as sizeof(size_t) + 1 for null terminator.
Time Complexity: O(1)
return type: char *
NOTE: The bit order is RTL. buffer[63] is bit at index 0.
*/
char *ToString(bit_arr_t arr, char* buffer);

/*MirrorBitArr: 
Time Complexity: O(log N)
return type: bit_arr_t
*/
bit_arr_t MirrorBitArr(bit_arr_t arr);

/*RotateRight: 
error: n should be larger than or equal to 0 & less then 64
Time Complexity: O(N)
return type: bit_arr_t
*/
bit_arr_t RotateRight(bit_arr_t arr, size_t n);

/*RotateLeft: 
error: n should be larger than or equal to 0 & less then 64
Time Complexity: O(N)
return type: bit_arr_t
*/
bit_arr_t RotateLeft(bit_arr_t arr, size_t n);


#endif /* BIT_ARRAY_H_OL111 */

