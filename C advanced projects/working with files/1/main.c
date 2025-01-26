#include <stdio.h>
#include "stringInFile.h"
#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

int main(int argc,char* argv[])
{
   int i;
   FILE * fpRead;
   FILE * fpWrite;
   unsigned int numOfStrings;
   char ** myStrings = NULL;
   char *newName = NULL;

   sscanf(argv[2],"%d",&numOfStrings);

   // opening the relevant files
   fpRead = fopen(argv[1],"r");
   CheckAllocation(fpRead)
   newName = getFileName(argv[1], strlen(argv[1]));
   fpWrite = fopen(newName,"w");
   CheckAllocation(fpWrite)

   // getting the strings from the user and sorting them
   myStrings = getStringFromFile(fpRead,numOfStrings);
   sortStrings(myStrings,numOfStrings);

   // copying the strings for the new file
   for(i = 0;i<numOfStrings;i++)
   {
       fputs(myStrings[i], fpWrite);
       fputc('\n',fpWrite);
   }
    fclose(fpRead);
    fclose(fpWrite);
    return 0;
}
