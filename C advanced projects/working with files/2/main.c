#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "myFile.h"

int main()
{
    char fname[20] = "myFile.txt";
    char fnameCopy[20] = "myFileCopy.txt";

    createTextFile(fname);

    printTextFileToScreen(fname);

    copyTextFile(fnameCopy, fname);

    doubleSpaceTextFile(fname);

    printTextFileToScreen(fname);
    return 0;
}