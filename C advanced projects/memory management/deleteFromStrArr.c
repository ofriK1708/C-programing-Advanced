#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITSIZE 1
#define DELETE_FLAG -1

char **getStrArrayInput(unsigned int *str_array_size);
void printArray(char **strArr, int size);
unsigned int RemoveFromStrArray(char ***pstrArr, unsigned int str_array_size, char **ptr_to_chars_array);
void allocMemoryCheck(char *test);
void freeArray(char **str_array, int size);

char **setPtrToCharsArray(char **str_array)

{

  char **res;

  int size, i;

  int str_array_row, str_array_col;

  scanf("%d", &size); // Get number of ptrs

  res = (char **)malloc(sizeof(char *) * (size + 1)); // Add 1 for NULL at the end

  if (res == NULL)
  {

    exit(1);
  }

  for (i = 0; i < size; i++)

  {

    scanf("%d", &str_array_row);

    scanf("%d", &str_array_col);

    res[i] = str_array[str_array_row] + str_array_col;
  }

  res[size] = NULL; // Set the last one to NULL

  return res;
}

int main()

{

  char **str_array;

  unsigned int str_array_size;

  char **ptr_to_chars_array;

  unsigned int res;

  str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)

  ptr_to_chars_array = setPtrToCharsArray(str_array);

  res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);

  printArray(str_array, str_array_size - res);

  // Free memory

  freeArray(str_array, str_array_size - res);

  free(ptr_to_chars_array);
}

char **getStrArrayInput(unsigned int *str_array_size)
{
  int size, i, j, logicSize, phyiscalSize;
  char ch;
  char **strArr;
  scanf("%d\n", &size);
  strArr = (char **)malloc(size * sizeof(char *));
  if (strArr == NULL)
  {
    printf("Memory allocation failed!!!");
    exit(1);
  }
  for (i = 0; i < size; i++)
  {
    j = 0;
    strArr[i] = (char *)malloc(INITSIZE * sizeof(char));
    allocMemoryCheck(strArr[i]);
    logicSize = 0;
    phyiscalSize = INITSIZE;
    scanf("%c", &ch);
    while (ch != '\n') // we stop receiving chars from the user when the enters the Enter key
    {
      if (phyiscalSize == logicSize) // checking to see if we have enough space for a new char
      {
        phyiscalSize *= 2;
        strArr[i] = (char *)realloc(strArr[i], phyiscalSize);
        allocMemoryCheck(strArr[i]);
      }
      strArr[i][j] = ch;
      scanf("%c", &ch);
      j++;
      logicSize++;
    }
    strArr[i][j] = '\0';                               // marking the end of the string
    strArr[i] = (char *)realloc(strArr[i], logicSize); // updating to the needed size
    allocMemoryCheck(strArr[i]);
  }
  *str_array_size = size;
  return strArr;
}

unsigned int RemoveFromStrArray(char ***pstrArr, unsigned int str_array_size, char **ptr_to_chars_array)
{
  int currStrLen, i = 0;
  int numOfDelete = 0;
  char **strArr = *pstrArr;
  char *tempStr = NULL;
  int tempStrIndex;

  while (ptr_to_chars_array[i] != NULL) // loop for marking the chars we want to delete
  {
    *(ptr_to_chars_array[i]) = DELETE_FLAG;
    i++;
  }

  for (int i = 0; i < str_array_size; i++)
  {
    currStrLen = strlen(strArr[i]);
    tempStr = (char *)malloc(currStrLen * sizeof(char)); // using a temporary string
    allocMemoryCheck(tempStr);
    tempStrIndex = 0;
    for (int j = 0; j < currStrLen; j++) // copying the string to the temp string without the flagged chars
    {
      if (strArr[i][j] != DELETE_FLAG)
      {
        tempStr[tempStrIndex] = strArr[i][j];
        tempStrIndex++;
      }
    }
    tempStr[tempStrIndex] = '\0'; // mark the end of the tempStr
    strcpy(strArr[i], tempStr);
    strArr[i] = (char *)realloc(strArr[i], (tempStrIndex + 1) * sizeof(char)); // updating the needed size
    free(tempStr);                                                             // releasing the temporary string, we don't need it any more
  }
  for (int i = 0; i < str_array_size; i++)
  {
    if (strArr[i][0] == '\0') // if we deleted the string completely
    {
      free(strArr[i]); // first we release the string from the memory
      for (int j = i; j < str_array_size - numOfDelete - 1; j++)
      {
        strArr[j] = strArr[j + 1]; // moving all the other string up the array
      }
      numOfDelete++;
    }
  }

  strArr = (char **)realloc(strArr, (str_array_size - numOfDelete) * sizeof(char *)); // update the size
  if (strArr == NULL)
  {
    printf("Memory allocation failed!!!");
    exit(1);
  }
  return numOfDelete;
}

void printArray(char **strArr, int size)
{
  for (int i = 0; i < size; i++)
  {
    printf("%s\n", strArr[i]);
  }
}
// checks if memory allocation/reallocation succeeded
void allocMemoryCheck(char *test)
{
  if (test == NULL)
  {
    printf("Memory allocation failed!!!\n");
    exit(1);
  }
}

void freeArray(char **str_array, int size)
{
  for (int i = 0; i < size; i++)
  {
    free(str_array[i]); // release each string individually
  }
  free(str_array); // releasing the whole array
}