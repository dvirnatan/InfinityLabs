#ifndef WS_6
#define WS_6

#include <stdio.h> /* printf in tester */
#include <stddef.h>
#include <stdlib.h>

unsigned int AddOne (unsigned int n);
long Pow2(unsigned int x, unsigned int y);
size_t IfPow2Loop (unsigned int n);
size_t IfPow2 (unsigned int n);
void ThreeBitsOn (unsigned int *arr, unsigned int len);
unsigned char TwoAndSixAreOn (unsigned char c);
unsigned char TwoOrSixAreOn (unsigned char c) ;
unsigned char SwapThreeAndFive (unsigned char c);
unsigned char MirrorLoop (unsigned char v);
unsigned char Mirror (unsigned char v);
unsigned int SixTeen (unsigned int v);
void Swap (unsigned int *a, unsigned int *b);
unsigned int CountSetBitsLoop(unsigned int v);
size_t CountSetBitsNoLoop(unsigned int i);
void PrintFloat(float num);

#endif /* WS6_H */
