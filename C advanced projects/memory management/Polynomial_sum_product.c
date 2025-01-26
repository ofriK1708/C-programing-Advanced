#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITSIZE 1
#define INITCHAR 'a'
typedef struct monom
{
  int coefficient; // המקדם
  int power;       // החזקה
} Monom;

Monom *getPolynom(unsigned int *size);
void MonomMergeSort(Monom *arr, unsigned int size);
void merge(Monom *arr1, unsigned int a1, Monom *arr2, unsigned int a2, Monom *tempArr);
void cpyArr(Monom *dest, Monom *src, unsigned int size);
Monom *MonomFusion(Monom *monoArr, int *size);
void allocMemoryCheck(Monom *test);
void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);
void printPoly(Monom *polynom, int size);
void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);

int main()
{
  Monom *polynom1, *polynom2;              // The input polynoms
  unsigned int polynom1Size, polynom2Size; // The size of each polynom

  printf("Please enter the first polynom:\n");
  polynom1 = getPolynom(&polynom1Size); // get polynom 1

  printf("Please enter the second polynom:\n");
  polynom2 = getPolynom(&polynom2Size); // get polynom 2

  printf("The multiplication of the polynoms is:\n"); // print the multiplication
  printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
  printf("\n");

  printf("The sum of the polynoms is:\n"); // print the sum
  printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
  printf("\n");

  free(polynom1); // releasing all memory allocations
  free(polynom2);

  return 0;
}

// this function is in charge of taking the polynom from the user and save it
Monom *getPolynom(unsigned int *size)
{
  Monom *polynoms;
  int numOfMonom = 0;
  int phyiscalSize = INITSIZE;
  char ch = INITCHAR;
  polynoms = (Monom *)malloc(INITSIZE * sizeof(Monom));
  allocMemoryCheck(polynoms);
  while (ch != '\n') // as long as the user didn't enter the Enter keyword
  {
    if (numOfMonom == phyiscalSize)
    {
      phyiscalSize *= 2;
      polynoms = (Monom *)realloc(polynoms, phyiscalSize * sizeof(Monom));
      allocMemoryCheck(polynoms);
    }
    // this scanf takes the first and second number it sees and then the immediate char after the second number, if we aren't done it will be ' ' but we are and since there is no space after the last number, it will be '\n' and end the loop
    scanf("%d%d%c", &polynoms[numOfMonom].coefficient, &polynoms[numOfMonom].power, &ch);
    numOfMonom++;
  }
  polynoms = (Monom *)realloc(polynoms, numOfMonom * sizeof(Monom)); // update the needed size
  MonomMergeSort(polynoms, numOfMonom);                              // sort the polynom from high to low
  polynoms = MonomFusion(polynoms, &numOfMonom);                     // merge together same power monoms and clear the monoms with coefficient 0
  *size = numOfMonom;
  return polynoms;
}

// this function handel the multiplication of the polynoms
void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size)
{
  int sizeOfProduct = polynom1Size * polynom2Size;
  if (sizeOfProduct > 0) // check if one of the polynoms is 0
  {
    Monom *polyPower = (Monom *)malloc(sizeOfProduct * sizeof(Monom));
    allocMemoryCheck(polyPower);
    int iPoly1 = 0, iPoly2 = 0, iPolyProduct = 0;
    for (; iPoly1 < polynom1Size; iPoly1++)
    {
      for (iPoly2 = 0; iPoly2 < polynom2Size; iPoly2++)
      {
        polyPower[iPolyProduct].power = polynom1[iPoly1].power + polynom2[iPoly2].power;
        polyPower[iPolyProduct].coefficient = polynom1[iPoly1].coefficient * polynom2[iPoly2].coefficient;
        iPolyProduct++;
      }
    }
    MonomMergeSort(polyPower, sizeOfProduct);           // sort from high to low
    polyPower = MonomFusion(polyPower, &sizeOfProduct); // get rid of 0 coefficient and combine same power coefficient
    printPoly(polyPower, sizeOfProduct);
  }
  else // if one the polynoms is 0 then the multiplication should be 0
  {
    printf("0");
  }
}

// function to handel the sum of the polynoms
void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size)
{
  int sizeOfSum = polynom1Size + polynom2Size;
  if (sizeOfSum > 0)
  {
    Monom *sumPoly = (Monom *)malloc(sizeOfSum * sizeof(Monom));
    allocMemoryCheck(sumPoly);

    // no need to sort because the polynoms are already sorted we only need to merge the polynoms correctly
    merge(polynom1, polynom1Size, polynom2, polynom2Size, sumPoly);
    sumPoly = MonomFusion(sumPoly, &sizeOfSum);
    printPoly(sumPoly, sizeOfSum);
  }
  else
  {
    printf("0");
  }
}

// this function uses the merge-sort and sorts the two monoms arrays
void MonomMergeSort(Monom *arr, unsigned int size)
{
  if (size <= 1)
  {
    return;
  }
  Monom *tempArr = NULL;
  MonomMergeSort(arr, size / 2);
  MonomMergeSort(arr + size / 2, size - size / 2);
  tempArr = (Monom *)malloc(size * sizeof(Monom));

  allocMemoryCheck(tempArr); // if we failed to malloc we will exit the whole program

  merge(arr, size / 2, arr + size / 2, size - size / 2, tempArr);
  cpyArr(arr, tempArr, size);
  free(tempArr);
}

// this function takes two sorted array and merge them into one sorted array from high to low
void merge(Monom *arr1, unsigned int a1, Monom *arr2, unsigned int a2, Monom *tempArr)
{
  int i1, i2, iTemp;
  i1 = i2 = iTemp = 0;
  while (i1 < a1 && i2 < a2)
  {
    if (arr1[i1].power >= arr2[i2].power)
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
void cpyArr(Monom *dest, Monom *src, unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
    dest[i] = src[i];
  }
}

// this function merge together same power monoms and also clear of all the monoms with coefficient 0
Monom *MonomFusion(Monom *monoArr, int *size)
{
  Monom *newMonoArr;
  Monom tempMonom;
  int newSize, oldSize;
  newSize = oldSize = *size;
  int currentPower, IndexNewMono = 0;
  bool newPower = false;
  newMonoArr = (Monom *)malloc(oldSize * sizeof(Monom));
  allocMemoryCheck(newMonoArr);
  int i = 0, j = 0;
  while (i < oldSize) // while we aren't done with the whole polynom
  {
    if (monoArr[i].coefficient == 0) // if the coefficient is 0 we don't need it and move to the next one
    {
      newSize--;
      i++;
    }
    else
    {
      newPower = false;
      tempMonom = monoArr[i]; // temp monom to check if after we summed same power monoms we didn't reach 0
      currentPower = monoArr[i].power;
      j = i + 1;
      while (j < oldSize && !newPower)
      {
        if (monoArr[j].power == currentPower)
        {
          tempMonom.coefficient += monoArr[j].coefficient;
          newSize--;
          j++;
        }
        else
        {
          newPower = true;
        }
      }
      if (tempMonom.coefficient != 0) // if we didn't reduced the monom completely
      {
        newMonoArr[IndexNewMono] = tempMonom; // save it to the new array
        IndexNewMono++;
      }
      else // if we did we dont need to copy it to the new array
      {
        newSize--;
      }
      i = j;
    }
  }
  // after we are done merging we return the new polynoms and update it's size
  newMonoArr = (Monom *)realloc(newMonoArr, newSize * sizeof(Monom));
  allocMemoryCheck(newMonoArr);
  free(monoArr);     // get rid of the previous polynom, we don't need it anymore
  *size = newSize;   // update the size
  return newMonoArr; // return the new polynom
}

void printPoly(Monom *polynom, int size)
{
  int currentCoefficient, currentPower;

  for (int i = 0; i < size; i++)
  {
    currentPower = polynom[i].power;
    currentCoefficient = polynom[i].coefficient;
    switch (currentPower)
    {
    case 0:       // power is 0 (a)
      if (i == 0) // first number of polynom
      {
        printf("%d ", currentCoefficient);
      }
      else if (currentCoefficient > 0) // not the fist number
      {
        printf("+ %d", currentCoefficient);
      }
      else
      {
        printf("- %d", currentCoefficient * -1);
      }
      break;
    case 1: // power is 1 (ax)
      switch (currentCoefficient)
      {
      case 1:       // power and coefficient is 1 (x)
        if (i != 0) // we aren't at the first number
        {
          printf("+ x ");
        }
        else // first number of polynom
        {
          printf("x ");
        }
        break;
      case -1:      // power is 1 and coefficient is -1 (-x)
        if (i != 0) // not first number
        {
          printf("- x ");
        }
        else // first number
        {
          printf("-x ");
        }
        break;
      default:      // power is 1 and coefficient is not 1/-1
        if (i != 0) // not first number
        {
          if (currentCoefficient > 0)
          {
            printf("+ %dx ", currentCoefficient);
          }
          else
          {
            printf("- %dx", currentCoefficient * -1);
          }
        }
        else // first number
        {
          printf("%dx ", currentCoefficient);
        }
        break;
      }
      break;
    default: // the power is > 1 (ax^n)
      switch (currentCoefficient)
      {
      case 1:       // power is > 1 and coefficient is 1 (x^n)
        if (i != 0) // not first number
        {
          printf("+ x^%d ", currentPower);
        }
        else // first numer
        {
          printf("x^%d ", currentPower);
        }
        break;

      case -1:      // power is > 1 and coefficient is -1 (-x^n)
        if (i != 0) // not first number
        {
          printf("- x^%d ", currentPower);
        }
        else // first number
        {
          printf("-x^%d ", currentPower);
        }
        break;

      default:      // power is > 1 and coefficient is not 1/-1
        if (i != 0) // not first number
        {
          if (currentCoefficient > 0)
          {
            printf("+ %dx^%d ", currentCoefficient, currentPower);
          }
          else
          {
            printf("- %dx^%d", currentCoefficient * -1, currentPower);
          }
        }
        else // first number
        {
          printf("%dx^%d ", currentCoefficient, currentPower);
        }
        break;
      }
      break;
    }
  }
}

// checks if memory allocation/reallocation succeeded
void allocMemoryCheck(Monom *test)
{
  if (test == NULL)
  {
    printf("Memory allocation failed!!!\n");
    exit(1);
  }
}