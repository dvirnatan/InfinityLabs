#ifndef __WS9_5_H__
#define __WS9_5_H__


long int AtoiBase10(const char *nptr);
long int Atoi(const char *nptr, int base);
char *ItoaBase10(int n, char *buffer);
char *Itoa(long int n, char *buffer, int base);

void AppearOnlyInTwoFirst(char *a, size_t len_a, char *b, size_t len_b,
char *c, size_t len_c);
												 
/*if the system is Little Endian return 1 else 0*/	
int IsLittleEndian();

int IsLittleEndian2();
#endif
