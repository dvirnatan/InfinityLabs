#include <stdio.h>
#include <stdlib.h>


void printArray(int arr[], int size);


int main() 
{
  int arr[] = {5,4,3,2,1,0 ,9, 34, -5 ,-7};
  int size = sizeof(arr) / sizeof(arr[0]);

  MergeSort(arr, size);

  printf("Sorted array: \n");
  printArray(arr, size);
}

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

    return merge(arr, start, middle, end);
  }
  return 0;
}

void printArray(int arr[], int size) 
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
