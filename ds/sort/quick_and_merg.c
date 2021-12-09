
/*************************************************
*	  Quick & Merge
*		Author: Dvir Natan
*		Reviewer: Eli
*		Date: 9/12/21
*		Status: Send
**************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Compare(const void *one,const void *other);

void Qsort(void *base, size_t nmemb, size_t size,
                  int (*Compar)(const void *, const void *));

static void QsortAux(void *base, int start, int end, size_t size,
                                      int (*Compar)(const void *, const void *));
                
static void Swap(char *cpy1, char* cpy2, size_t size);

int MergeSort(int *arr_to_sort, size_t num_elements);

int Merge(int *arr, int start, int split, int end);

int MergeSortAux(int arr[], int start, int end);

static void PrintArr(int *arr, size_t size);


/*****************MAIN**************************/

#define Arrsize 10000
int main ()
{
	size_t i = 0;
	clock_t start_t ,end_t;
	int ret = 0;
	int *array1 = malloc (Arrsize * sizeof(int));
 	int *array2 = malloc (Arrsize * sizeof(int));   
    int *array3 = malloc (Arrsize * sizeof(int));
	
	srand(time(0));
	
	while(i < Arrsize)
	{
		array1[i] = rand() % 100;
        array2[i] = rand() % 100;
        array3[i] = rand() % 100;
		++i;
	}

	start_t = clock();	
    Qsort(array1, Arrsize, sizeof(int), Compare);
	end_t = clock();
	printf("Qsort : ret = %d time = %f\n",ret,(double)(end_t - start_t) / CLOCKS_PER_SEC);
	
    start_t = clock();	
    qsort(array2, Arrsize, sizeof(int), Compare);
	end_t = clock();
	printf("qsort : ret = %d time = %f\n",ret,(double)(end_t - start_t) / CLOCKS_PER_SEC);

    start_t = clock();	
    MergeSort(array3, Arrsize);
	end_t = clock();
	printf("Merge : ret = %d time = %f\n",ret,(double)(end_t - start_t) / CLOCKS_PER_SEC);

	free(array1);
  free(array2);
  free(array3);
	
	return 0;
}

static void Swap(char *cpy1, char* cpy2, size_t size)
{
    size_t i = 0;
    char temp = 0;

    for(i = 0; i < size; ++i)
    {
        temp = *cpy1;
        *cpy1 = *cpy2;
        *cpy2 = temp;
        ++cpy1;
        ++cpy2;
    }
}

 static void QsortAux(void *base, int start, int end, size_t size,
                                      int (*Compar)(const void *, const void *))
 {
    int first_big = start;
    int runner = start;
    char temp;
    char *cpy1;
    char *cpy2;

    int pivot = end;
    size_t i = 0;

    if((end - start) < 1)
    {
        return;
    }

    while(runner < end)
    {
      if(0 > Compar((char *)base  + runner * size, (char *)base  + pivot * size))
       {
            cpy1 = (char *)base  + runner * size;
            cpy2 = (char *)base  + first_big * size;
            Swap(cpy1, cpy2, size);

           ++first_big;
       }
        ++runner;
    }

    cpy1 = (char *)base  + runner * size;
    cpy2 = (char *)base  + first_big * size;
    Swap(cpy1, cpy2, size);

    pivot = first_big ;
    QsortAux(base,pivot + 1,end,size,Compar);
    QsortAux(base,start,pivot - 1,size,Compar);
 }

   
void Qsort(void *base, size_t nmemb, size_t size,
                  int (*Compar)(const void *, const void *))
{
    QsortAux(base ,0 , nmemb - 1, size,Compar);
}

/**********************MERGE*****************************/

int MergeSort(int *arr_to_sort, size_t num_elements)
{
  return MergeSortAux(arr_to_sort, 0 ,num_elements - 1);
}

int Merge(int *arr, int start, int split, int end) 
{
  int n1 = split - start + 1;
  int n2 = end - split;
  size_t i = 0, j = 0, k = 0;

  int *arr1 = malloc(sizeof(int)* n1);
  int *arr2 = malloc(sizeof(int)* n2);

  if(arr1 == NULL || arr2 == NULL)
  {
    free(arr1);
    free(arr2);
    return -1;
  }

  for (i = 0; i < n1; i++)
  {
    arr1[i] = arr[start + i];
  }
  for (j = 0; j < n2; j++)
  {
    arr2[j] = arr[split + 1 + j];
  }

  i = 0;
  j = 0;
  k = start;

  while (i < n1 && j < n2) 
  {
    if (arr1[i] <= arr2[j]) 
    {
      arr[k] = arr1[i];
      i++;
    } 
    else 
    {
      arr[k] = arr2[j];
      j++;
    }

    k++;
  }

  while (i < n1) 
  {
    arr[k] = arr1[i];
    i++;
    k++;
  }

  while (j < n2) 
  {
    arr[k] = arr2[j];
    j++;
    k++;
  }

  free(arr1);
  free(arr2);

  return 0;
}

int MergeSortAux(int arr[], int start, int end) 
{
  int status = 0;
  if(status == -1)
  {
    return -1;
  }

  if (start < end) 
  {    
    int middle = start + (end - start) / 2;

    status = MergeSortAux(arr, start, middle);
    status = MergeSortAux(arr, middle + 1, end);

    return Merge(arr, start, middle, end);
  }
  return 0;
}

/******************PRINT AND COMPARE******************/

static void PrintArr(int *arr, size_t size)
{
	size_t i = 0;
	
	for(i = 0; i < size; ++i)
	{
		printf("%d ",arr[i]);
	}
	puts("\n");
}

int Compare(const void *one,const void *other)
{
    return *(int*)one - *(int*)other;
}

/*______________________EOF______________________*/
