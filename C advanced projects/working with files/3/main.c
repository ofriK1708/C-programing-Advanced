#include <stdio.h>
#include "employeeFile.h"

int main(int argc, char *argv[]) {
    int numOfEmployees;
    FILE *employeesData = fopen(argv[1], "rb+");
    FILE *employeesBonus = fopen(argv[2], "rb");
    Employee **employeesUpdatedData;
    if (employeesData == NULL || employeesBonus == NULL) {
        printf("Error opening files\n");
        exit(1);
    }
    employeesUpdatedData = getEmployeesData(employeesData, employeesBonus, &numOfEmployees);
    mergeSortEmployees(employeesUpdatedData, numOfEmployees);
    fseek(employeesData, 0, SEEK_SET); // move the caret back to the start of the file in order to update it
    writeEmployeesDataToFile(employeesData, employeesUpdatedData, numOfEmployees);
    freeEmployees(employeesUpdatedData, numOfEmployees);
    fclose(employeesData);
    fclose(employeesBonus);
}
