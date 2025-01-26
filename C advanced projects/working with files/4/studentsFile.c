#include "studentsFile.h"

// this function gets a file of students and store all the offsets and grades of the students, then it sorts them using merge sort
MyStudent **getSortedStudentsOffset(FILE *studentsData,int *size)
{
    short int nameLen, i,numOfStudents;
    fread(&numOfStudents,sizeof(short int),1,studentsData);
    MyStudent **studData = (MyStudent **) malloc(numOfStudents * sizeof(MyStudent *));
    CheckAllocation(studData)
    for (i = 0; i < numOfStudents; i++)
    {
        studData[i] = (MyStudent *) malloc(sizeof(MyStudent));
        CheckAllocation(studData[i])
        studData[i]->offset = (int) ftell(studentsData);
        fread(&nameLen, sizeof(short int), 1, studentsData);
        fseek(studentsData,nameLen,SEEK_CUR); // we don't need the name so we skip it
        fread(&(studData[i]->average), sizeof(int), 1, studentsData);
    }
    mergeSortStudents(studData,numOfStudents);
    *size = numOfStudents;
    return studData;
}

// this function take an array of employees pointers and sort then by their salary using the merge-sort
void mergeSortStudents(MyStudent **arr, int size)
{
    if (size <= 1)
    {
        return;
    }
    MyStudent **tempArr = NULL;
    mergeSortStudents(arr, size / 2);
    mergeSortStudents(arr + size / 2, size - size / 2);
    tempArr = (MyStudent **) malloc(size * sizeof(MyStudent *));
    if (tempArr) // memory allocation succeeded (NULL == false)
    {
        merge(arr, size / 2, arr + size / 2, size - size / 2, tempArr);
        cpyArr(arr, tempArr, size);
        free(tempArr);
    } else {
        printf("Memory allocation failed!!!");
        exit(1);
    }
}

// the function receives two sorted arrays of pointers, their sizes and another array, it merges the two array to the third array from high to low
void merge(MyStudent **arr1, unsigned int a1, MyStudent **arr2, unsigned int a2, MyStudent **tempArr)
{
    int i1, i2, iTemp;
    i1 = i2 = iTemp = 0;
    while (i1 < a1 && i2 < a2) {
        if ((arr1[i1]->average) <= (arr2[i2]->average)) {
            tempArr[iTemp] = arr1[i1];
            i1++;
            iTemp++;
        } else {
            tempArr[iTemp] = arr2[i2];
            i2++;
            iTemp++;
        }
    }

    while (i1 < a1) {
        tempArr[iTemp] = arr1[i1];
        i1++;
        iTemp++;
    }
    while (i2 < a2) {
        tempArr[iTemp] = arr2[i2];
        i2++;
        iTemp++;
    }
}

void cpyArr(MyStudent **dest, MyStudent **src, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}
void makeIndexFile(char fileName[],MyStudent **studData,int numOfStud)
{
    char newFileEnd[] = ".ind";
    char * newFileName = strdup(fileName);
    strcat(newFileName, newFileEnd);
    FILE *indexFile = fopen(newFileName, "w");
    CheckAllocation(indexFile)
    for(int i = 0;i < numOfStud;i++)
    {
        fwrite(&(studData[i]->offset),sizeof(int),1,indexFile);
    }
    free(newFileName);
    fclose(indexFile);
}
void freeStudents(MyStudent** students,int size)
{
    for (int i = 0; i < size; i++)
    {
        free(students[i]);
    }
    free(students);
}

char ** findAverageGrade(char* database, int avgGrade, int * resSize)
{
    FILE * studentsData = fopen(database,"r");
    char ** avgGradeStudents;
    char *tempName;
    int currentGrade = 0;
    int studentOffset,nameLen,studentsIndex = 0;
    CheckAllocation(studentsData)
    int numOfStudents;
    fread(&numOfStudents, sizeof(short int), 1, studentsData);
    avgGradeStudents = (char**) malloc(numOfStudents * sizeof(char *));
    char indexEnd[] = ".ind";
    strcat(database,indexEnd);
    FILE *indexFile = fopen(database, "r");
    if (indexFile == NULL)
    {
        printf("Error opening index file!");
        exit(1);
    }
    while (currentGrade <= avgGrade)
    {
        fread(&studentOffset,sizeof(int),1,indexFile);
        fseek(studentsData,studentOffset,SEEK_SET);
        fread(&nameLen,sizeof(short int),1,studentsData);
        tempName = (char*) malloc((nameLen + 1) * sizeof(char));
        fread(tempName, sizeof(char), nameLen, studentsData);
        tempName[nameLen] = '\0';
        fread(&currentGrade,sizeof (int),1,studentsData);
        if(currentGrade == avgGrade)
        {
            avgGradeStudents[studentsIndex] = strdup(tempName);
            studentsIndex++;
        }
        free(tempName);
    }
    if((studentsIndex+1) != numOfStudents)
    {
        if(studentsIndex == 0)
        {
            free(avgGradeStudents);
            *resSize = 0;
            return NULL;
        }
        else
        {
            avgGradeStudents = (char**) realloc(avgGradeStudents,(studentsIndex) * sizeof(char*));
        }
    }
    *resSize = studentsIndex;
    return avgGradeStudents;
}