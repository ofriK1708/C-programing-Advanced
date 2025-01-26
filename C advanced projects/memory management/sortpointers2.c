#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

void pointerSort(int *arr, unsigned int size, int ascend_flag, int ***pointers);
void mergeSort(int **arr, unsigned int size, int ascend_flag);
void merge(int **arr1, unsigned int a1, int **arr2, unsigned int a2, int **tempArr, int ascend_flag);
void cpyArr(int **dest, int **src, unsigned int size);
void printPointers(int **pointers, unsigned int size);

int main()

{

  unsigned int size, i;

  int arr[SIZE];

  int **pointers;

  int ascend_flag;

  printf("Please enter the number of items:\n");

  scanf("%u", &size);

  for (i = 0; i < size; i++)

    scanf("%d", &arr[i]);

  scanf("%d", &ascend_flag);

  pointerSort(arr, size, ascend_flag, &pointers);

  printf("The sorted array:\n"); // Print the sorted array

  printPointers(pointers, size);

  free(pointers);

  return 0;
}
void pointerSort(int *arr, unsigned int size, int ascend_flag, int ***pointers)

{
  int **pointersArr = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) // filling the pointers array with the addresses of the array of numbers we got from the user
  {
    pointersArr[i] = &(arr[i]);
  }
  mergeSort(pointersArr, size, ascend_flag); // sorting the addresses by their value inside and the ascend key
  *(pointers) = pointersArr;                 // modifing the value of pointers to the right address
}

void mergeSort(int **arr, unsigned int size, int ascend_flag) // this function take an array of int pointers and sort then by their value using the merge-sort
{
  if (size <= 1)
  {
    return;
  }
  int **tempArr = NULL;
  mergeSort(arr, size / 2, ascend_flag);
  mergeSort(arr + size / 2, size - size / 2, ascend_flag);
  tempArr = (int **)malloc(size * sizeof(int *));
  if (tempArr) // memory allocation succeeded (NONE == false)
  {
    merge(arr, size / 2, arr + size / 2, size - size / 2, tempArr, ascend_flag);
    cpyArr(arr, tempArr, size);
    free(tempArr);
  }
  else
  {
    printf("Memory allocation failed!!!");
    exit(1);
  }
}

// the function receives two sorted arrays of pointers, their sizes and another array, it merges the two array to the third array according to the ascend flag
void merge(int **arr1, unsigned int a1, int **arr2, unsigned int a2, int **tempArr, int ascend_flag)
{
  int i1, i2, iTemp;
  i1 = i2 = iTemp = 0;
  while (i1 < a1 && i2 < a2)
  {
    if ((*(arr1[i1])) >= (*(arr2[i2])))
    {
      if (ascend_flag) // if ascend_flag == 1 (true) the direction is low to high
      {
        tempArr[iTemp] = arr2[i2];
        i2++;
        iTemp++;
      }
      else // if ascend == 0 (false) the direction is high to low
      {
        tempArr[iTemp] = arr1[i1];
        i1++;
        iTemp++;
      }
    }
    else
    {
      if (ascend_flag)
      {
        tempArr[iTemp] = arr1[i1];
        i1++;
        iTemp++;
      }
      else
      {
        tempArr[iTemp] = arr2[i2];
        i2++;
        iTemp++;
      }
    }
  }
  // if we aren't finished with one array then we fill the rest of whats left automatically to the third array
  while (i1 < a1)
  {
    tempArr[iTemp] = arr1[i1];
    i1++;
    iTemp++;
  }
  while (i2 < a2)
  {
    tempArr[iTemp] = arr2[i2];
    i2++;
    iTemp++;
  }
}
void cpyArr(int **dest, int **src, unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    dest[i] = src[i];
  }
}
void printPointers(int **pointers, unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%d ", *(pointers[i]));
  }
}