#include <stdio.h>
#include "studentsFile.h"
void printNames(char **records,int size);

int main(int argc, char** argv)
{
    char **records;
    int resSize = 0;

    records = findAverageGrade(argv[1], 85, &resSize);
    printNames(records,resSize);

    return 0;

}

void printNames(char **records,int size)
{
    int i;
    printf("The students names are:\n");
    for (i=0 ; i<size ;i++ ){
        printf("%s\n" , records[i]);
    }
}