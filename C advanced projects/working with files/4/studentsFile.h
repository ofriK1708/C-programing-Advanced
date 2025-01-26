#ifndef Q3_STUDENTSFILE_H
#define Q3_STUDENTSFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

typedef struct myStudent
{
    int offset;
    int average;
}MyStudent;



MyStudent **getSortedStudentsOffset(FILE *studentsData,int *size);
void mergeSortStudents(MyStudent **arr, int size);
void merge(MyStudent **arr1, unsigned int a1, MyStudent **arr2, unsigned int a2, MyStudent **tempArr);
void cpyArr(MyStudent **dest, MyStudent **src, unsigned int size);
void makeIndexFile(char fileName[],MyStudent **studData,int numOfStud);
void freeStudents(MyStudent** students,int size);
char ** findAverageGrade(char* database, int avgGrade, int * resSize);
#endif //Q3_STUDENTSFILE_H
