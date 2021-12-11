#ifndef __CALCULATOR_H__OL111
#define __CALCULATOR_H__OL111

/******************************* Data type defintions *******************************/
typedef enum 
{
	SUCCESS,
	MATH_ERROR,
	SYNTAX_ERROR,
	ALLOCATION_ERROR
} status_t;

/****************************** Function declarations *******************************/
status_t Calculate(char* str,double* res);


#endif /* __CALCULATOR_H__OL111 */
