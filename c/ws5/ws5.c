#include "ws5.h"

#define MAX_STR 256

#include <stdio.h> /*FILE*/
#include <string.h>
#include <stdlib.h> /*exit*/
#include <assert.h>

static size_t exit_flag = 0;
static size_t found_flag = 0;


void Print(int a)
{
	printf("%d\n", a);
}

void PrintMe()
{
	typedef void (*ptr_fu)(int);
	typedef struct print_me
	{
		int a;
		ptr_fu PrintPtr;
	} print_me;
	
	print_me arr[10];
	size_t i;
	
	for ( i = 0; i < 10; ++i)
	{
		arr[i].a = i*2;
		arr[i].PrintPtr = &Print;
	}
	
	for ( i = 0; i < 10; ++i )
	{
		arr[i].PrintPtr(arr[i].a);
	}
	
}


int CmpFuncRemove (const char *string_u, const char *cmd_name) 
{
	return (strcmp (string_u, cmd_name));
}

int CmpFuncCount (const char *string_u, const char *cmd_name) 
{
	return (strcmp (string_u, cmd_name));
}
	
int CmpFuncExit (const char *string_u, const char *cmd_name) 
{
	return (strcmp (string_u, cmd_name));
}

int CmpFuncPrepend (const char *string_u, const char *cmd_name) 
{
	return (strncmp (string_u, cmd_name, 1));
}

int CmpFuncDef (const char *string_u, const char *cmd_name) 
{
	(void)string_u;
	(void)cmd_name;
	return Success;
}

int RemoveFunc(char *string_u)
{
	(void)string_u;
	remove("Logger.txt");
	return Success;
}

int CountFunc(char *string_u)
{
	
	FILE *fp = fopen("Logger.txt", "r");
	int ch ;
	int lines = 0;
	(void) string_u;
	
	if (fp == NULL)
	{
		printf("Unable to access file\n");
		found_flag = 0;
	}
	
	if (found_flag)
	{
		while ((ch = fgetc(fp)) != EOF)
		{

			if (ch == '\n')
			{
				++lines;
			}
		}

		fclose(fp);
		
		printf("The total number of lines in the file are: %d\n", lines);
	}
	return Success;
}


int ExitFunc(char *string_u)
{
	(void)string_u;
	exit_flag = 1;
	return Success;
}


int Prepend(char *string_u)
{
	int c;
	FILE *fp = fopen("Logger.txt", "r+");
	FILE *tmp_f = fopen("tmp.txt", "a+");
	fputs(++string_u ,tmp_f); 
	c = fgetc(fp);
	while (c != EOF)
	{
		fputc(c, tmp_f);
		c = fgetc(fp);
	}
	
	fseek(fp, 0, SEEK_SET);
	fseek(tmp_f, 0, SEEK_SET);
	
	
	while ((c = fgetc(tmp_f)) != EOF)
	{
		fputc(c, fp);
	}
	
	remove("tmp.txt");
	fclose(fp);
	fclose(tmp_f);
	return Success;
}


int DefFunc (char *string_u)
{
        FILE *fp = fopen("Logger.txt", "a+");
	if (NULL == fp)
	{
		return Failed;
	}
	
	fputs(string_u ,fp); 
	fclose(fp);
	return Success;
}
	
	
void Logger ()
{
	size_t i = 0;
	char string_u[MAX_STR] = {'\0'};
	
	typedef int(*cmp_ptr)(const char *s1, const char *s2);
	typedef int(*op_ptr)( char *string_u);
	
	typedef struct chain 
	{
		const char *cmd_name;
		cmp_ptr cmp_func;
		op_ptr op_func;
	} chain_t;
	
	chain_t chain_arr[5];
	
	chain_arr[0].op_func = &RemoveFunc;
	chain_arr[0].cmd_name = RemoveN;
	chain_arr[0].cmp_func = &CmpFuncRemove;
	
	chain_arr[1].op_func = &CountFunc;
	chain_arr[1].cmd_name = CountN;
	chain_arr[1].cmp_func = &CmpFuncCount;
	
	chain_arr[2].op_func = &ExitFunc;
	chain_arr[2].cmd_name = ExitN;
	chain_arr[2].cmp_func = &CmpFuncExit;
	
	chain_arr[3].op_func = &Prepend;
	chain_arr[3].cmd_name = PrependN;
	chain_arr[3].cmp_func = &CmpFuncPrepend;
	
	chain_arr[4].op_func = &DefFunc;
	chain_arr[4].cmd_name = NULL;
	chain_arr[4].cmp_func = &CmpFuncDef;

	  
	while(!exit_flag) 
	{	
		
		fgets(string_u, MAX_STR, stdin);
		found_flag = 1;	
		for (i = 0; i < 5 && (found_flag); ++i)
		{		
			if(0 == (chain_arr[i].cmp_func(string_u, chain_arr[i].cmd_name)))
			{
				found_flag = chain_arr[i].op_func(string_u);
			}
		}
	}
}



