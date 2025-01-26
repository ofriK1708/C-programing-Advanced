#ifndef EXERICE_8_FILE_H
#define EXERICE_8_FILE_H
#include <stdio.h>
#include <stdlib.h>
void createTextFile(char * fileName);
void checkFileOpen(FILE * fl);
void printTextFileToScreen(char * fileName);
void copyTextFile(char * destFileName, char * srcFileName);
void doubleSpaceTextFile(char * fileName);
#endif //EXERICE_8_FILE_H
