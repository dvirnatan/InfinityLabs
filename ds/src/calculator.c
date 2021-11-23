/******************************************************************************
	 Calculator
	 Author: Dvir Natan
	 Date: 23/11/2021
	 Reviewer: Yael
	 Status: Approved
******************************************************************************/

#include <stdlib.h> /* strtod() */
#include <assert.h> /* assert() */
#include <math.h> /* pow() */

#include "stack.h" /* stack_t, stack op_handlers */
#include "calculator.h" /* calculator op_handlers singatures and data types */

/******************************* Data type defintions *******************************/
typedef enum
{
	Cal_WFN_S, /* Waiting For Number state */
	Cal_WFO_S, /* Waiting For Operator state */
	Cal_SYN_ERR_S, /* Syntax error state */
	Cal_MATH_ERR_S, /*  error state */
	Cal_Alloc_ERR_S
} cal_state_t;

typedef enum
{
	left_to_right, 
	right_to_left 
} associativity_t;

typedef status_t (*cal_return_func_t)(double *, stack_t *, stack_t *);

typedef struct
{
	cal_state_t next_state;
	char * (*cal_handler)(char *str, stack_t *stack_op, stack_t *stack_num, cal_state_t *);
} cal_t;

typedef struct
{
    int precedence; 
    associativity_t associativity;
    double (*op_handler)(double second_num, double first_num, cal_state_t *state);
} cal_op_t;


/*************************** Function declarations *****************************/
status_t Calculate(char* str,double* res); 

char * HandleNum (char *str, stack_t *stack_op, stack_t *stack_num, cal_state_t *state); /* HandleNum */
char * HandleOp(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state); /* HandleOp */
char * HandleOpenBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state);/* ( Func */
char * HandleCloseBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state);  /* ) Func */
char * HandleErrCloseBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state);

static status_t HandleEnd(double *res, stack_t *stack_op, stack_t *stack_num); /* End */
static status_t HandleErr(double *res, stack_t *stack_op, stack_t *stack_num); /* Syntax Err */
static status_t HandleMathErr(double *res, stack_t *stack_op, stack_t *stack_num); /* Math Err */
static status_t HandleAllocErr(double *res, stack_t *stack_op, stack_t *stack_num); /* Alloc Err */

static void CalInit(stack_t **stack_op, stack_t **stack_num, cal_state_t *state); /* Initializer */
static void CalDestroy(stack_t *stack_op, stack_t *stack_num);
static void ComputingHandler(stack_t *stack_op, stack_t *stack_num, cal_state_t *state);

static double HandleAdd(double num2, double num1, cal_state_t *state); /* + */
static double HandleSubstract(double num2, double num1, cal_state_t *state); /* - */
static double HandleMultiply(double num2, double num1, cal_state_t *state); /* * */
static double HandleDivision(double num2, double num1, cal_state_t *state); /* / */
static double HandlePower(double num2 ,double num1, cal_state_t *state); /* ^ */

/************************ Global static variables *******************************/
static cal_op_t lut_operator[256]; /* defines handlers of +,-,/,^,* operations, 
their precedence and associativity */
static cal_t fsm_calculator[3][256]; 

static cal_return_func_t status_state_table[5];

/****************************************************************************/
status_t Calculate(char *str, double *res)
{
	stack_t *stack_op = NULL, *stack_num = NULL;
	cal_state_t current_state = Cal_WFN_S, old_state = current_state;
	status_t current_status;
	
	assert (str);
	
	CalInit(&stack_op, &stack_num, &old_state);
	
	while ((*str != '\0') && (current_state != Cal_SYN_ERR_S) && 
				(old_state != Cal_MATH_ERR_S)  && (old_state != Cal_Alloc_ERR_S))
	{
		old_state = current_state;
		current_state = fsm_calculator[old_state][(size_t)*str].next_state;
		
		str = fsm_calculator[old_state][(size_t)*str].cal_handler
									(str, stack_op, stack_num, &old_state);
	}
	current_status = status_state_table[old_state](res, stack_op, stack_num);

	CalDestroy(stack_op, stack_num);
	
	return current_status;
}

/****************************************************************************/
static void CalInit(stack_t **stack_op, stack_t **stack_num, cal_state_t *state)
{
	size_t i, j;
	
	/* Stack Creation */
	#define MAX_SIZE_STACK 256
	*stack_num = StackCreate(MAX_SIZE_STACK);
	*stack_op = StackCreate(MAX_SIZE_STACK);
	if ((!*stack_num)||(!*stack_op))
	{
		*state = Cal_Alloc_ERR_S;
		return;
	}
	(void)stack_num;
	(void)stack_op;
	
	/* Initialize status-state table */
	status_state_table[Cal_WFN_S] = HandleEnd; /* not ERR state (WFN) */
	status_state_table[Cal_WFO_S] = HandleErr; /* not supposed to reach here */
	status_state_table[Cal_SYN_ERR_S] = HandleErr; /* ERR SYN state */
	status_state_table[Cal_MATH_ERR_S] = HandleMathErr; /* ERR MATH state */
	status_state_table[Cal_Alloc_ERR_S] = HandleAllocErr; /* ERR Alloc state */
	
	/* Initialize LUT finite state machine calculator */
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 256; ++j)
		{
			fsm_calculator[i][j].next_state = Cal_SYN_ERR_S;
			fsm_calculator[i][j].cal_handler = NULL;
		}
	}
	
	i = 0; /* Cal_WFN_S STATE */
	fsm_calculator[i]['\0'].next_state = Cal_WFN_S; /* looping in itself \0 */
	fsm_calculator[i]['\0'].cal_handler = NULL; /* \0 */
	
	fsm_calculator[i]['+'].next_state = Cal_WFO_S; /* + */
	fsm_calculator[i]['+'].cal_handler = HandleNum; /* + */
	
	fsm_calculator[i]['-'].next_state = Cal_WFO_S; /* - */
	fsm_calculator[i]['-'].cal_handler = HandleNum; /* - */
	
	fsm_calculator[i]['('].next_state = Cal_WFN_S; /* looping in itself ( */
	fsm_calculator[i]['('].cal_handler = HandleOpenBrace; /* ( */
	
	fsm_calculator[i][')'].next_state = Cal_SYN_ERR_S; /* looping in itself ( */
	fsm_calculator[i][')'].cal_handler = HandleErrCloseBrace; /* ( */
	
	for (j = '0'; j <= '9'; ++j)
	{
		fsm_calculator[i][j].next_state = Cal_WFO_S;
		fsm_calculator[i][j].cal_handler = HandleNum;
	}
	
	i = 1; /* Cal_WFO_S STATE */
	fsm_calculator[i]['\0'].next_state = Cal_SYN_ERR_S; /* ( */
	fsm_calculator[i]['\0'].cal_handler = NULL; /* ( */
	
	fsm_calculator[i]['('].next_state = Cal_SYN_ERR_S; /* ( */
	fsm_calculator[i]['('].cal_handler = HandleOp; /* ( */
	
	fsm_calculator[i]['+'].next_state = Cal_WFN_S; /* + */
	fsm_calculator[i]['+'].cal_handler = HandleOp; /* + */
	
	fsm_calculator[i]['-'].next_state = Cal_WFN_S; /* - */
	fsm_calculator[i]['-'].cal_handler = HandleOp; /* - */
	
	fsm_calculator[i]['*'].next_state = Cal_WFN_S; /* * */
	fsm_calculator[i]['*'].cal_handler = HandleOp; /* * */
	
	fsm_calculator[i]['/'].next_state = Cal_WFN_S; /* / */
	fsm_calculator[i]['/'].cal_handler = HandleOp; /* / */
	
	fsm_calculator[i]['^'].next_state = Cal_WFN_S; /* ^ */
	fsm_calculator[i]['^'].cal_handler = HandleOp; /* ^ */
	
	fsm_calculator[i][')'].next_state = Cal_WFO_S; /* ) */
	fsm_calculator[i][')'].cal_handler = HandleCloseBrace; /* ) */
	
	/* Initialize LUT operator */
	for (j = 0; j < 256; ++j)
	{
		lut_operator[j].precedence = -1;
		lut_operator[j].associativity = left_to_right;
		lut_operator[j].op_handler = NULL;
	}
	
	lut_operator['('].precedence = 1000; /* + */
	lut_operator['('].associativity = left_to_right;
	
	lut_operator['+'].precedence = 0; /* + */
	lut_operator['+'].associativity = left_to_right;
	lut_operator['+'].op_handler = HandleAdd; /* + */
	
	lut_operator['-'].precedence = 0; /* - */
	lut_operator['-'].associativity = left_to_right;
	lut_operator['-'].op_handler = HandleSubstract; /* - */
	
	lut_operator['*'].precedence = 1; /* * */
	lut_operator['*'].associativity = left_to_right;
	lut_operator['*'].op_handler = HandleMultiply; /* * */
	
	lut_operator['/'].precedence = 1; /* / */
	lut_operator['/'].associativity = left_to_right;
	lut_operator['/'].op_handler = HandleDivision; /* / */
	
	lut_operator['^'].precedence = 2; /* ^ */
	lut_operator['^'].associativity = right_to_left;
	lut_operator['^'].op_handler = HandlePower; /* ^ */
	
	lut_operator[')'].precedence = -1000; /*  */
	lut_operator[')'].associativity = left_to_right;
}

/****************************************************************************/
char * HandleErrCloseBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state)
{
	(void)stack_op;
	(void)stack_num;
	*state = Cal_SYN_ERR_S;
	return op+1;
}

/****************************************************************************/
char *HandleNum (char *str, stack_t *stack_op, stack_t *stack_num, cal_state_t *state)
{
	char *str_next = NULL;
	double temp;
	(void)stack_op;
	(void)state;
	temp = strtod(str, &str_next);

	StackPush(stack_num, *(void **)&temp); 
	
	return str_next;
}

/****************************************************************************/
char *HandleOp(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state) 
{
	int current_operator = lut_operator[(size_t)*op].precedence;
	int operator_associativity = lut_operator[(size_t)*op].associativity; 
	char temp_op = '\0';
	int last_operator = -1;
	
	if (!IsStackEmpty(stack_op))
	{
		temp_op = *(char *)StackPeek(stack_op);
		last_operator = lut_operator[(size_t)temp_op].precedence;
	}
	
	if ((temp_op != '(') && (current_operator < last_operator)) /* operate */
	{
		while  ((temp_op != '(') && (!IsStackEmpty(stack_op)) && (StackSize(stack_num) > 1))
		{
			ComputingHandler(stack_op, stack_num, state);
		}
	}
	
	
	if ((current_operator == last_operator) && (operator_associativity == left_to_right)) /* operate */
	{
		ComputingHandler(stack_op, stack_num, state);
	}
	
	StackPush(stack_op, op);
	
	return (op + 1);
}

/****************************************************************************/
static status_t HandleEnd(double *res, stack_t *stack_op, stack_t *stack_num) /* End */
{
	status_t status = SUCCESS;
	cal_state_t state = Cal_WFN_S;
	void *tmp = NULL;
	assert(stack_op);
	assert(stack_num);
	
	while((!IsStackEmpty(stack_op)) && (StackSize(stack_num) > 1))
	{
		ComputingHandler(stack_op, stack_num, &state);
	}
	tmp = StackPeek(stack_num);
	*res = *(double *)&tmp;
	StackPop(stack_num);
	(void)res;
	if(state == Cal_MATH_ERR_S)
	{
		status = MATH_ERROR;
	}
	return status;
}

/****************************************************************************/
char * HandleOpenBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state)  /* ( Func */
{
	(void)stack_num;
	(void)state;
	StackPush(stack_op, op);
	
	return (op + 1);
}

/****************************************************************************/
char * HandleCloseBrace(char *op, stack_t *stack_op, stack_t *stack_num, cal_state_t *state)
{
	(void)op;
	assert(stack_op);
	assert(stack_num);
	
	while((!IsStackEmpty(stack_op)) && (StackSize(stack_num) > 1) && (*(char *)StackPeek(stack_op) != '('))
	{
		ComputingHandler(stack_op, stack_num, state);
	}
	
	if ((!IsStackEmpty(stack_op)) && ('(' == *(char *)StackPeek(stack_op)))
	{
		StackPop(stack_op);
	}
	else
	{
		*state = Cal_SYN_ERR_S;
	}
	if (*(op + 1) == '\0')
	{
		*state = Cal_WFN_S;
	}

	return (op + 1);
}

/****************************************************************************/
static status_t HandleAllocErr(double *res, stack_t *stack_op, stack_t *stack_num)
{
	(void)stack_op; (void)stack_num; (void)res;
	
	return (ALLOCATION_ERROR);
}

/****************************************************************************/
static status_t HandleMathErr(double *res, stack_t *stack_op, stack_t *stack_num)
{
	(void)stack_op; (void)stack_num; (void)res;
	
	return (MATH_ERROR);
}

/****************************************************************************/
static status_t HandleErr(double *res, stack_t *stack_op, stack_t *stack_num) 
{
	(void)stack_op; (void)stack_num; (void)res;
	
	return (SYNTAX_ERROR);
}

/****************************************************************************/
static void CalDestroy(stack_t *stack_op, stack_t *stack_num) 
{
	if (stack_op)
	{
		while(!IsStackEmpty(stack_op))
		{
			StackPop(stack_op);
		}
		StackDestroy(stack_op);
	}
	
	if (stack_num)
	{
		while(!IsStackEmpty(stack_num))
		{
			StackPop(stack_num);
		}
		StackDestroy(stack_num);
	}
}

/****************************************************************************/
static double HandleAdd(double num2, double num1, cal_state_t *state) 
{
	(void)state;
	return (num2 + num1);
}

/****************************************************************************/
static double HandleSubstract(double num2, double num1, cal_state_t *state) 
{
	(void)state;
	return (num2 - num1);
}

/****************************************************************************/
static double HandleMultiply(double num2, double num1, cal_state_t *state) 
{
	(void)state;
	return (num2 * num1);
}

/****************************************************************************/
static double HandleDivision(double num2, double num1, cal_state_t *state)
{
	if(num1 == 0)
	{
		*state = Cal_MATH_ERR_S;
		return 0;
	}
	
	return (num2 / num1);
}

/****************************************************************************/
static double HandlePower(double num ,double power, cal_state_t *state)
{
	if ((num == 0) && (power == 0))
	{
		*state = Cal_MATH_ERR_S;
		return 0;
	}
	
	return pow(num,power);
}

/****************************************************************************/
static void ComputingHandler(stack_t *stack_op, stack_t *stack_num, cal_state_t *state)
{
	double first_num, second_num, new_num;
	char op;
	void *tmp = NULL;
	
	/* calculation stage */
	tmp = StackPeek(stack_num);
	first_num = *(double *)&tmp;
	StackPop(stack_num);
	
	tmp = StackPeek(stack_num);
	second_num = *(double *)&tmp;
	StackPop(stack_num);
	
	op = *(char *)StackPeek(stack_op);
	StackPop(stack_op);
	
	new_num = lut_operator[(size_t)op].op_handler(second_num , first_num, state);
	
	StackPush(stack_num, *(void **)&new_num); /* inserting new num to stack */
}

/*__________________EOF______________________*/
