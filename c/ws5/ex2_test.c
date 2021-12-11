/*****************************
*****Worksheet 5 (Files)
*****Author: Lior Ben Harosh
******************************/

#include <stdio.h> /* printf(), fputs(), fgets(), fopen(), fclose() */
#include <stdlib.h> /* system(), malloc(), free() */
#include <string.h> /* strcmp() */

#include "ws5.h"

/* Ex2 */
#define STRMAXSIZE 300

#define SHELLSCRIPT2 "\
#/bin/bash \n\
find LBHTest.txt 1>/dev/null 2>&1 \n\
"

void TestExTwo(void (*LoggerEx_ptr)(const char *));


int main() 
{
	/* pointer to the address of your function */
/* Please change the name of the function if it's different */
/* Assumption your logger function is of this type:  void function (const char *)  */
	void (*LoggerEx_ptr)(const char *) = &Logger; 

	TestExTwo(LoggerEx_ptr);

	return 0;
}


void TestExTwo(void (*LoggerEx_ptr)(const char *))
{ 
	char file_name[] = "LBHTest.txt";
	char test[] = "You Passed\nThe test\n";
	char *test_two[] = {"Amazing\n","You Passed\n","The test\n","Again\n"};
	char **buf_buf = (char **) malloc(4 * sizeof(char *));
	int flag = 0;
	size_t i = 0;
	FILE *fptr = fopen(file_name, "w+");
	
	printf("Set the mode in fopen at your program to a+ before the test (at file creation)\n");
	printf("First: do -count (you're suppose to get 2)\n");
	printf("Second: add a string \"Again\", third: add a string \"<Amazing\"\n");
	printf("Last: write \"-exit\" \n");
	
	fputs(test,fptr);
	fclose(fptr);
	
	if (0 != system (SHELLSCRIPT2)) /* Checks if the file has been created */
	{
		printf("Your logger doesn't create the file requested.\n");
		printf("BAD LOGGER! BAD!!\n");
	}
	else
	{
		LoggerEx_ptr(file_name); /* Your logger program is invoked */
		fptr = fopen(file_name, "r");
		for (i = 0; i < 4; ++i) /* Checks if the words in your file are correct and in the correct order */
		{
			buf_buf[i] = (char *) malloc(STRMAXSIZE	 * sizeof(char));
			fgets(buf_buf[i], STRMAXSIZE, fptr);
			flag = strcmp(buf_buf[i],test_two[i]);
			free(buf_buf[i]);
			if (0 != flag)
			{
				printf("You didn't pass the test, something is wrong with one of your string addition operations\n");
				break;
			}
		}
		free(buf_buf);
		fclose(fptr);
	}
	if (0 == flag)
	{
		printf("\n\nEnter the program again and type \"-remove\"\n");
		LoggerEx_ptr(file_name); /* Your logger program is invoked again */
		if (0 != system(SHELLSCRIPT2)) /* Checks if the file has been removed */
		{
			printf("\nCongratulations, you passed all the tests!\n");
		}		
	}
}

