#ifndef STRINGS_H
#define STRINGS_H
#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t  StrLen (const char *str);
char *StrCpy(char *dest, const char *src);
char *StrnCpy(char *dest, const char *src, size_t n);
int StrnCmp(const char *str1, const char *str2, size_t n);
int StrCaseCmp(const char *s1, const char *s2);
char *StrChr(const char *str, int c);
char *StrDup(const char *s);
char *StrCat(char *dest, const char *src);
char *StrnCat(char *dest, const char *src, size_t n);
char *StrStr(const char *str1, const char *str2);
size_t StrSpn(const char *str1, const char *str2);
char *StrTok(char *str1, const char *str2);  /* advanced */
size_t Palin (char *str);



int StrCmp (const char *str1, const char *str2);

#endif /* STRINGS_H */
