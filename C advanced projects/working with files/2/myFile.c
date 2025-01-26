#include "myFile.h"
void checkFileOpen(FILE * fl)
{
    if(fl == NULL)
    {
        printf("Opening File failed! exiting!");
        exit(1);
    }
}

void createTextFile(char * fileName)
{
    FILE * fl;
    fl = fopen(fileName,"w");
    checkFileOpen(fl);
    int ch;
    printf("Enter text, if you have windows press Ctrl+Z to end, for mac press Ctrl+D to end: \n");
    ch = getchar();
    while (ch != EOF) {
        fputc(ch, fl);
        ch = getchar();
    }
    fclose(fl);
}
void printTextFileToScreen(char * fileName)
{
    FILE * fl;
    fl = fopen(fileName,"r");
    checkFileOpen(fl);
    int ch;
    ch = fgetc(fl);

    while(ch != EOF)
    {
        putchar(ch);
        ch = fgetc(fl);
    }
    fclose(fl);
}
void copyTextFile(char * destFileName, char * srcFileName)
{
    FILE * fpRead;
    FILE *fpWrite;
    fpRead = fopen(srcFileName,"r");
    fpWrite = fopen(destFileName,"w");
    int ch;
    ch = fgetc(fpRead);
    while(!feof(fpRead))
    {
        fputc(ch,fpWrite);
        ch = fgetc(fpRead);
    }
    fclose(fpRead);
    fclose(fpWrite);
}
void doubleSpaceTextFile(char * fileName)
{
    FILE * fp = fopen(fileName,"r");
    checkFileOpen(fp);
    FILE * fpTemp;
    int ch;
    char * tempFileName = "tempFp.temp";
    fpTemp = fopen(tempFileName,"w");
    checkFileOpen(fpTemp);
    ch = fgetc(fp);
    while(!feof(fp))
    {
        if(ch == '\n')
        {
            fputc(ch, fpTemp);
            fputc('\n',fpTemp);
        }
        else
        {
            fputc(ch,fpTemp);
        }
        ch = getc(fp);
    }
    fclose(fp);
    fclose(fpTemp);
    copyTextFile(fileName,tempFileName);
    remove(tempFileName);
}