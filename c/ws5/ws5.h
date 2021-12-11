#ifndef WS_5
#define WS_5

#define UNUSED(x) (void)x
#define MAX_STR 256

#include <stdio.h> /*FILE*/
#include <string.h> /*strcmp */
#include <stdlib.h> /*exit*/
#include <assert.h>/*assert*/

void Logger (int argc, char *file_name);
void Print(int a);


static const char RemoveN[] = "-remove\n";
static const char CountN[] = "-count\n";
static const char ExitN[] = "-exit\n";
static const char PrependN[] = "<";
enum op_status {Success = 0, Failed = 1};

#endif
