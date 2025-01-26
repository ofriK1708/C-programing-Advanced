#include <stdlib.h>
#include <stdio.h>
#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}
int main()
{
    int * testp = (int*) malloc(-1);
    CheckAllocation(testp);
    free(testp);
}