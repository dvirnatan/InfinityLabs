/*****************************
*****Calculator (Data Structures)
*****Author: Lior Ben Harosh
*****Date: 19/11/2021 
******************************/

#include <stdlib.h> /* malloc() */
#include <stdio.h> /* printf() */

#include "calculator.h" /* state machine func */

/***********************Function declarations *********************************/
static void TestToCalculateStageOne (void);
static void TestToCalculateStageTwo (void);
static void TestToCalculateStageThree (void);
static void TestToCalculateStageFour (void);
static void TestToCalculateStageFive (void);

/************************************Macros *********************************/
#define DEFAULT     "\033[0m"
#define RED         "\033[31m"             /* Red */
#define TEST_NUM(name, real, expected) \
    do { \
        ((real) == (expected)) ? \
        (1) : \
        printf(RED "%s, Failed on line %d, Real: %f, Expected: %f\n" DEFAULT, name, __LINE__, (double) (real), (double) (expected)); \
    } while (0)


/************************************Main *********************************/
int main() 
{
	
	printf("addition & substraction operations:\n");
	TestToCalculateStageOne();
	printf("If there are no failures - you passed\n");
	
	printf("division & multiplication operations:\n");
	TestToCalculateStageTwo();
	printf("If there are no failures - you passed\n");
	
	printf("power operation:\n");
	TestToCalculateStageThree();
	printf("If there are no failures - you passed\n");
	
	printf("combination of different operators:\n");
	TestToCalculateStageFour();
	printf("If there are no failures - you passed\n");
	
	printf("parenthesis usage & math errors:\n");
	TestToCalculateStageFive();
	printf("If there are no failures - you passed\n");
	
	return 0;
}

/***********************************************************************/
static void TestToCalculateStageOne (void)
{
	double *result = (double *)malloc(sizeof(double));
	
	TEST_NUM("Calculate", Calculate("1+1", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2);
	
	TEST_NUM("Calculate", Calculate("5-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 3);
	
	TEST_NUM("Calculate", Calculate("5+3+6", result), SUCCESS);
	TEST_NUM("Calculate", *result, 14);
	
	TEST_NUM("Calculate", Calculate("-5+3", result), SUCCESS);
	TEST_NUM("Calculate", *result, -2);
	
	TEST_NUM("Calculate", Calculate("+5+3+30", result), SUCCESS);
	TEST_NUM("Calculate", *result, 38);
	
	TEST_NUM("Calculate", Calculate("5+3+6+", result), SYNTAX_ERROR);
	
	TEST_NUM("Calculate", Calculate("+5-3", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2);
	
	TEST_NUM("Calculate", Calculate("5-3", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2);
	
	TEST_NUM("Calculate", Calculate("5+5+2-5+1-3-", result), SYNTAX_ERROR);
	
	TEST_NUM("Calculate", Calculate("5+5+2-5+1-3", result), SUCCESS);
	TEST_NUM("Calculate", *result, 5);
	
	TEST_NUM("Calculate", Calculate("5-2+3-5+1-3", result), SUCCESS);
	TEST_NUM("Calculate", *result, 5-2+3-5+1-3);
	
	free(result); result = NULL;
}

/***********************************************************************/
static void TestToCalculateStageTwo (void)
{
	double *result = (double *)malloc(sizeof(double));
	
	TEST_NUM("Calculate", Calculate("5/2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2.5);
	
	TEST_NUM("Calculate", Calculate("-5*3*10", result), SUCCESS);
	TEST_NUM("Calculate", *result, -150);
	
	TEST_NUM("Calculate", Calculate("5*3/10", result), SUCCESS);
	TEST_NUM("Calculate", *result, 1.5);
	
	TEST_NUM("Calculate", Calculate("+2*10*5/10/4", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2.5);
	
	TEST_NUM("Calculate", Calculate("+2*10*5/10/4/", result), SYNTAX_ERROR);
	
	TEST_NUM("Calculate", Calculate("-20*5/4*", result), SYNTAX_ERROR);
	
	free(result); result = NULL;
}

/***********************************************************************/
static void TestToCalculateStageThree (void)
{
	double *result = (double *)malloc(sizeof(double));
	
	TEST_NUM("Calculate", Calculate("5^2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 25);
	
	TEST_NUM("Calculate", Calculate("5^-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 0.04);
	
	TEST_NUM("Calculate", Calculate("20^2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 400);
	
	TEST_NUM("Calculate", Calculate("2^3^2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 512);
	
	TEST_NUM("Calculate", Calculate("2^2^2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 16);
	
	TEST_NUM("Calculate", Calculate("2^2^2^", result), SYNTAX_ERROR);

	free(result); result = NULL;
}

/***********************************************************************/
static void TestToCalculateStageFour (void)
{
	double *result = (double *)malloc(sizeof(double));
	
	TEST_NUM("Calculate", Calculate("5+2*3-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 9);
	
	TEST_NUM("Calculate", Calculate("5+2*3^2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 23);
	
	TEST_NUM("Calculate", Calculate("5^2*3-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 73);

	TEST_NUM("Calculate", Calculate("6/3*4+1*5-1", result), SUCCESS);
	TEST_NUM("Calculate", *result, 12);
	
	TEST_NUM("Calculate", Calculate("5+2*3-2-", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+2*3-2+", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+2*3-2*", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+2*3-2/", result), SYNTAX_ERROR);

	
	TEST_NUM("Calculate", Calculate("-5+2*6+4+10*2*2-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 49);
	
	TEST_NUM("Calculate", Calculate("4+2*6+4+2/4*6+10*2*2-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 61);
	
	TEST_NUM("Calculate", Calculate("5+2^2*3/3+4-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 11);
	
	TEST_NUM("Calculate", Calculate("-3+2^2*3/3+4-2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 3);
	
	TEST_NUM("Calculate", Calculate("-3+2^2*3/3+4-2+", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("-3+2^2*3/3+4*2-", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("-3+2^2*3/3+4*2*", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("-3+2^2*3/3+4^2/", result), SYNTAX_ERROR);
	
	free(result); result = NULL;
}

/***********************************************************************/
static void TestToCalculateStageFive (void)
{
	double *result = (double *)malloc(sizeof(double));
	
	
	TEST_NUM("Calculate", Calculate("(5+2)", result), SUCCESS);
	TEST_NUM("Calculate", *result, 7);
	
	
	TEST_NUM("Calculate", Calculate("(5+2)*(3-2)", result), SUCCESS);
	TEST_NUM("Calculate", *result, 7);
	
	TEST_NUM("Calculate", Calculate("(((5+2)*(3-2)", result), SUCCESS);
	TEST_NUM("Calculate", *result, 7);
	
	TEST_NUM("Calculate", Calculate("(5+2)^2-19+(20+4)*2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 78);
	
	TEST_NUM("Calculate", Calculate("((25+5)/2-10)/2", result), SUCCESS);
	TEST_NUM("Calculate", *result, 2.5);
	
	TEST_NUM("Calculate", Calculate("5+(2*3)-2-)", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+(2*3)-2-)+", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+(2*3)-2-)-", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+(2*3)-2-)^", result), SYNTAX_ERROR);
	TEST_NUM("Calculate", Calculate("5+(2*3)-2-)*", result), SYNTAX_ERROR);
	
	TEST_NUM("Calculate", Calculate("2/0", result), MATH_ERROR);
	TEST_NUM("Calculate", Calculate("0^0", result), MATH_ERROR);
	
	free(result); result = NULL;
}
