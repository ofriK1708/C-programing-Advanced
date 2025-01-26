#ifndef ASSIGNMENT6_STRINGINFILE_H
#define ASSIGNMENT6_STRINGINFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

void freeStrings(char ** strings,unsigned int numOfStrings);
char **getStringFromFile(FILE * fp,unsigned int numOfString);
void sortStrings(char **myStrings, unsigned int size);
char * getFileName(char str[],unsigned int size);
#endif //ASSIGNMENT6_STRINGINFILE_H
