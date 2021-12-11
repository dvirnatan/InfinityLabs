#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcat */
#include <assert.h> /* assert */
/*	MACROS	 */

#define max(a,b) (a > b) ? a : b   /* max(a,b)  */
#define maxx(a,b,c) (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c) /* max(a, b, c) */
#define SIZEOF_TYPE(type) \ ((unsigned int)(-1) - (0)) / ((type *)(unsigned int)(-1) - (type *)(0))
#define SIZEOF(object) (char *)(&object+1) - (char *)(&object)

/*************** Element ******************/
#define ELEMENTS_NUM 3

	typedef void*(*ptrf_add_t)(void*, int n);
	typedef void(*ptrf_print_t)(void*);
	typedef void *ptr_void_t;
	
	typedef struct element 
	{
		ptrf_add_t add_pt;
		ptrf_print_t print_pt;
		ptrf_print_t clean_pt;
		ptr_void_t value;
	} element_t;
	
	element_t *elements;

static void AddToAll(int n)
{
	size_t i = 0;
	for (i = 0; i < ELEMENTS_NUM; ++i)
	{
		elements[i].value = elements[i].add_pt(elements[i].value ,n);
	}
}
static void PrintElem()
{
	size_t i = 0;
	for (i = 0; i < ELEMENTS_NUM; ++i)
	{
		elements[i].print_pt(elements[i].value);
	}
}

static void CleanAll()
{
	size_t i = 0;
	for (i = 0; i < ELEMENTS_NUM; ++i)
	{
		elements[i].clean_pt(elements[i].value);
	}
}

/*	PRINT FUNCTIONS		*/
static void print_int(void *value)
{
	int *val;
	assert (NULL != value);
	val = (int*)value;
	printf("int - %d\n", (*val));
}
static void print_float(void *value)
{
	float *val;
	assert (NULL != value);
	val = (float*)value;
	printf("float - %f\n", (*val));
}
static void print_string(void *value)
{
	char *val;
	assert (NULL != value);
	val = (char*)value;
	printf("string - %s\n", val);
}
/*	ADD FUNCTIONS		*/
static void *add_int (void *val, int n)
{
	int *ptr;
	assert (NULL != val);
	ptr = (int*)val;
	*ptr += n;
	return val;
}
static void *add_float (void *val, int n)
{
	float *ptr;
	assert (NULL != val);
	ptr = (float*)val;
	*ptr += n;
	return val;
}
static void *add_string (void *val, int n)
{
	char *ptr;
	char *str_temp;
	assert(val != NULL);

	str_temp = (char *) malloc(10);
	if (NULL == str_temp)
	{
		free(str_temp);
		puts("malloc failed");
		return val;
	}
	
	sprintf(str_temp, "%d", n);
	ptr = (char *)realloc(val, strlen(val) + strlen(str_temp) + 1);
		if (NULL == ptr)
	{
		free(ptr);
		puts("malloc failed");
		return val;
	}
	
	strcat( ptr, str_temp );
	free(str_temp);
	str_temp = NULL;
	val = ptr;
	ptr = NULL;
	return val;
}

static void Clean (void *val)
{
	assert (NULL != val);
	*(char *)val = *(char *)val;
	free(val);
	val = NULL;
}
static void NoClean(void *val)
{
	(void)val;
}

void Init()
{
	static int x = 8;
	static float y = 12.2;
	static char str1[] = "test";
	char *str2 = (char *)malloc( sizeof(str1) + 1);
	strcpy(str2, str1);

	elements[0].print_pt = &print_int;
	elements[1].print_pt = &print_float;
	elements[2].print_pt = &print_string;
	
	elements[0].add_pt = &add_int;
	elements[1].add_pt = &add_float;
	elements[2].add_pt = &add_string;
	
	elements[0].value = &x;
	elements[1].value = &y;
	elements[2].value = str2;	
	
	elements[0].clean_pt = &NoClean;
	elements[1].clean_pt = &NoClean;
	elements[2].clean_pt = &Clean;
}

int main ()
{
	int a ,b ,c;
	float f = 0.5;
	a = 1; b = 2; c = 3;
	
	printf("int - %ld\n", SIZEOF(a));
	printf("float - %ld\n", SIZEOF(f));
	
	printf("%d\n",max(a, b));
	printf("%d\n",maxx(a, b, c));

	elements = malloc(sizeof(element_t) * ELEMENTS_NUM);

	Init();

	PrintElem();
	AddToAll(12);
	PrintElem();
	AddToAll(1);
	PrintElem();	
	
	CleanAll();
	
	free(elements);
	return 0;
}

		
