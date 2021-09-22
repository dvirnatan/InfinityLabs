#ifndef WS_5
#define WS_5

#define MAX_STR 256

#include <stdio.h> /*FILE*/
#include <string.h>
#include <stdlib.h> /*exit*/
#include <assert.h>

void Logger ();


static const char RemoveN[] = "-remove\n";
static const char CountN[] = "-count\n";
static const char ExitN[] = "-exit\n";
static const char PrependN[] = "<";
enum op_status {Success = 0, Failed = 1};

#endif
