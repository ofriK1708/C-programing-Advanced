#include "employeeFile.h"


Employee **getEmployeesData(FILE *employeesData, FILE *employeesBonus, int *size)
{
    int nameLen, logicalSize = 0, physicalSize = INIT_EMPLOYEES_SIZE;
    bool reachedEndOfFile = false;
    float bonus;
    Employee **employeesArrP = (Employee **) malloc(
            physicalSize * sizeof(Employee *)); // allocating the memory needed from the employees structs pointers
    CheckAllocation(employeesArrP)
    fread(&nameLen, sizeof(int), 1, employeesData);
    while (reachedEndOfFile == false)
    {
        if (logicalSize == physicalSize)
        {
            physicalSize *= 2;
            employeesArrP = (Employee **) realloc(employeesArrP, physicalSize * sizeof(Employee *));
            CheckAllocation(employeesArrP)
        }
        // allocating the memory needed
        employeesArrP[logicalSize] = (Employee *) malloc(
                sizeof(Employee));// allocating the memory needed for the employee struct
        CheckAllocation(employeesArrP[logicalSize])
        employeesArrP[logicalSize]->name = (char *) malloc(
                (nameLen + 1) * sizeof(char)); // allocating the memory needed for the employee name
        CheckAllocation(employeesArrP[logicalSize]->name)

        // filling the employee data
        employeesArrP[logicalSize]->name_length = nameLen;
        fread(employeesArrP[logicalSize]->name, sizeof(char), nameLen, employeesData);
        employeesArrP[logicalSize]->name[nameLen] = '\0';
        fread(&(employeesArrP[logicalSize]->salary), sizeof(float), 1, employeesData);
        fread(&bonus, sizeof(float), 1, employeesBonus);
        employeesArrP[logicalSize]->salary += bonus;
        logicalSize++;

        // get the next name (it exist) length
        if (fread(&nameLen, sizeof(int), 1, employeesData) == 0)
        {
            reachedEndOfFile = true;
        }
    }
    // reallocating the needed memory only
    if (physicalSize != logicalSize)
    {
        employeesArrP = (Employee **) realloc(employeesArrP, logicalSize * sizeof(Employee *));
    }
    *size = logicalSize;
    return employeesArrP;
}

// this function take an array of employees pointers and sort then by their salary using the merge-sort
void mergeSortEmployees(Employee **arr, int size)
{
    if (size <= 1)
    {
        return;
    }
    Employee **tempArr = NULL;
    mergeSortEmployees(arr, size / 2);
    mergeSortEmployees(arr + size / 2, size - size / 2);
    tempArr = (Employee **) malloc(size * sizeof(Employee *));
    if (tempArr) // memory allocation succeeded (NULL == false)
    {
        merge(arr, size / 2, arr + size / 2, size - size / 2, tempArr);
        cpyArr(arr, tempArr, size);
        free(tempArr);
    } else
    {
        printf("Memory allocation failed!!!");
        exit(1);
    }
}

// TODO fix the merge function
// the function receives two sorted arrays of pointers, their sizes and another array, it merges the two array to the third array from high to low
void merge(Employee **arr1, unsigned int a1, Employee **arr2, unsigned int a2, Employee **tempArr)
{
    int i1, i2, iTemp;
    i1 = i2 = iTemp = 0;
    while (i1 < a1 && i2 < a2)
    {
        if ((arr1[i1]->salary) >= (arr2[i2]->salary))
        {
            tempArr[iTemp] = arr1[i1];
            i1++;
            iTemp++;
        } else
        {
            tempArr[iTemp] = arr2[i2];
            i2++;
            iTemp++;
        }
    }

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

void cpyArr(Employee **dest, Employee **src, unsigned int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

void freeEmployees(Employee **employeesData, int numOfEmployees)
{
    for (int i = 0; i < numOfEmployees; i++)
    {
        free(employeesData[i]->name);
        free(employeesData[i]);
    }
    free(employeesData);
}

void writeEmployeesDataToFile(FILE *updatedData, Employee **employeesArrP, int numOfEmployees)
{
    int nameLen, i;
    for (i = 0; i < numOfEmployees; i++)
    {
        nameLen = employeesArrP[i]->name_length;
        fwrite(&(employeesArrP[i]->name_length), sizeof(int), 1, updatedData);
        fwrite(employeesArrP[i]->name, sizeof(char), nameLen, updatedData);
        fwrite((&employeesArrP[i]->salary), sizeof(float), 1, updatedData);
    }
}