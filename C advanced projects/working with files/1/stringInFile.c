#include "stringInFile.h"
char **getStringFromFile(FILE * fp,unsigned int numOfString)
{
    char chCheck;
    unsigned int goodCharIndex;
    unsigned int stringIndex = 0,charIndex = 0,sizeString,finalSize;
    char ** myStrings = (char**) malloc(numOfString*sizeof(char*));
    CheckAllocation(myStrings)
    for(int i = 0; i < numOfString;i++)
    {
        sizeString = fgetc(fp) - '0';
        finalSize = sizeString;
        myStrings[stringIndex] = (char*) malloc(sizeString*sizeof(char));
        CheckAllocation(myStrings[stringIndex])
        goodCharIndex = 0;
        for(charIndex = 0;charIndex < sizeString;charIndex++)
        {
            chCheck = (char)fgetc(fp);
            if(islower(chCheck) != 0)
            {
                myStrings[stringIndex][goodCharIndex] = chCheck;
                goodCharIndex++;
            }
            else
            {
                finalSize--;
            }
        }
        myStrings[stringIndex][finalSize] = '\0';
        if(finalSize != sizeString)
        {
            myStrings[stringIndex] = (char*)realloc(myStrings[stringIndex],finalSize + 1);
            CheckAllocation(myStrings[stringIndex])
        }
        stringIndex++;
    }
    return myStrings;

}
void freeStrings(char ** strings,unsigned int numOfStrings)
{
    for (int i = 0; i < numOfStrings; i++)
    {
        free(strings[i]);
    }
    free(strings);
}
void sortStrings(char **myStrings, unsigned int size)
{
    for (int i = 1; i < size; ++i)
    {
        char *current = myStrings[i];
        int j = i - 1;

        // Move elements greater than current to one position ahead
        while (j >= 0 && strcmp(myStrings[j], current) > 0)
        {
            myStrings[j + 1] = myStrings[j];
            j--;
        }
        // Insert current at its correct position
        myStrings[j + 1] = current;
    }
}
char * getFileName(char str[],unsigned int size)
{
    char fileEnd[] = {".srt.txt"};
    int i = 0;
    char * newFileName = strtok(str,".");
    strcat(newFileName, fileEnd);
    return newFileName;
}