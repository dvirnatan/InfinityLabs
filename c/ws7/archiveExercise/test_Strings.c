/* test for ws2 */

#include <stdio.h>
#include <stdlib.h> /* free() */
#include <string.h> /* for testing */
#include <strings.h>  /* strcasecmp() */
#include "String.h"
#define _POSIX_C_SOURCE 200809L /* strdup */

/* Strlen */
void TestForStrLen(const char *str)
{
    if(strlen(str) != StrLen(str))
        printf("Error in StrLen\n");
}

/* StrCpy */
void TestForStrCpy(char *dest, const char *src)
{
    if(StrCmp(StrCpy(dest, src), src) != 0)
        printf("Error in StrCpy\n");
}

/* StrnCpy */
void TestForStrnCpy(char *dest, const char *src, size_t n)
{
    if(StrnCmp(StrnCpy(dest, src, n), src, n) != 0)
        printf("Error in StrnCpy\n");
}

/* StrCmp */
void TestForStrCmp(const char *str1, const char *str2)
{
    if(StrCmp(str1, str2) != strcmp(str1, str2))
        printf("Error in StrCmp\n");
}

/* StrnCmp */
void TestForStrnCmp(const char *str1, const char *str2, size_t n)
{
    if(strncmp(str1, str2, n) != StrnCmp(str1, str2, n))
        printf("Error in StrnCmp\n");
}

/* StrCaseCmp */
void TestForStrCaseCmp(const char *str1, const char *str2)
{
    if(StrCaseCmp(str1, str2) != strcasecmp(str1, str2))
        printf("Error in StrCaseCmp\n");
}

/* StrChr */
void TestForStrChr(const char *str, int c)
{
    if(strchr(str, c) != StrChr(str, c))
        printf("Error in StrChr\n");
}

/* StrDup */
void TestForStrDup(const char *str)
{
    if(StrCmp(StrDup(str), str) != 0)
        printf("Error in StrDup\n");
}

/* StrCat */
void TestForStrCat(char *dest, const char *src)
{
    if(StrCmp(StrCat(dest, src), strcat(dest, src)) != 0)
        printf("Error in StrCat\n");
}

/* StrnCat */
void TestForStrnCat(char *dest, const char *src, size_t n)
{
    if(StrCmp(StrnCat(dest, src, n), strncat(dest, src, n)) != 0)
        printf("Error in StrnCat\n");
}

/* StrStr */
void TestForStrStr(const char *str1, const char *str2)
{
    if(StrCmp(StrStr(str1, str2), strstr(str1, str2)) != 0)
        printf("Error in StrStr\n");
}

/* StrSpn */
void TestForStrSpn(const char *str1, const char *str2)
{
    if(StrSpn(str1, str2) != strspn(str1, str2))
        printf("Error in StrSpn\n");
}

int main()
{
    const char str1[] = "Hello World!";
    const char str2[] = "ehly";
    const char str3[] = "poin and point";
    const char str4[] = "point";
    const char str5[] = "Yael.Ben.Meshulam";
    char str6[20];
    char str7[30] = "hey ";

/*Strlen*/
    TestForStrLen(str1);

/*StrCpy*/
    TestForStrCpy(str6, str1);

/*StrnCpy*/
    TestForStrnCpy(str6, str1, 5);

/*Strcmp*/
    TestForStrCmp(str1, str2);

/*Strncmp*/
    TestForStrnCmp(str1, str2, 5);

/*StrCaseCmp*/
    TestForStrCaseCmp(str3, str4);

/*StrChr*/
    TestForStrChr(str5, '.');

/*StrDup*/
    TestForStrDup(str1);

/*StrCat*/
    TestForStrCat(str7, str1);

/*StrnCat*/
    TestForStrnCat(str7, str1, 2);

/*StrStr*/
    TestForStrStr(str3, str4);

/*StrSpn*/
    TestForStrSpn(str1, str2);

    return 0;
}



