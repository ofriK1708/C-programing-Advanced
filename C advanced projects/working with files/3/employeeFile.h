#ifndef Q2_EMPLOYEEFILE_H
#define Q2_EMPLOYEEFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}
#define INIT_EMPLOYEES_SIZE 1

typedef struct employee
{
    int name_length;
    char *name;
    float salary;
} Employee;

Employee **getEmployeesData(FILE *employeesData, FILE *employeesBonus, int *size);

void mergeSortEmployees(Employee **arr, int size);

void merge(Employee **arr1, unsigned int a1, Employee **arr2, unsigned int a2, Employee **tempArr);

void cpyArr(Employee **dest, Employee **src, unsigned int size);

void freeEmployees(Employee **employeesData, int numOfEmployees);

void writeEmployeesDataToFile(FILE *updatedData, Employee **employeesArrP, int numOfEmployees);

#endif //Q2_EMPLOYEEFILE_H
