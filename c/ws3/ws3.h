#ifndef WS3_H 
#define WS3_H


#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */
#include <string.h> /*strdup */
#include <ctype.h> /* tolower */

char * strdup( const char *str1 );
void Envp (char **envp);
void Print(char ** buffer);
void Tolower (char ** buffer);
void Free(char ** buffer);
void Copy(char **envp, char **buffer);
size_t Josephus (size_t n);
void TurnZero (char *arr, size_t n, size_t i);

#endif
