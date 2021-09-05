#include <stdio.h>

#define len(x)  (sizeof((x))/sizeof((x)[0]))


int * copy_array (int *pt, int len);
void print_array (int * , int);
void q();
void swap (size_t *px, size_t *py);
int StrCmp (const char *str1, const char *str2);
size_t  StrLen (const char *str);
