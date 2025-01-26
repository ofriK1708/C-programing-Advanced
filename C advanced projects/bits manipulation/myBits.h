
#ifndef __MY_BITS_H
#define __MY_BITS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

typedef struct client
{
    char id[9];     // “12345678\0”
    char phone[12]; // “054-1234567\0”
} Client;

typedef struct _short_client
{
    unsigned char short_id[4];
    unsigned char short_phone[5];
} Short_client;


Short_client * createShortClientArr(int size);
Client * getBigClients(int n);
unsigned char * compressID(char Id[]);
bool checkIdTheSame(unsigned char* Id1,unsigned char * Id2);
void decompressPhone(char phone[],unsigned char smallPhone[]);
char * searchClientByID(Short_client * arr,int size,char Id[]);
#endif //__MY_BITS_H
