#include "myBits.h"
Short_client * createShortClientArr(int size)
{
    Client * bigClients = getBigClients(size);
    int j;
    Short_client * smallClients = (Short_client*) calloc(size,sizeof(Short_client));
    int bigClientIndex;
    for(int i = 0; i < size;i++)
    {
      bigClientIndex = 0;
      for(j = 0; j < 4;j++)
      {
          smallClients[i].short_id[j] += bigClients[i].id[bigClientIndex] - '0';
          smallClients[i].short_id[j] += (bigClients[i].id[bigClientIndex + 1] - '0') << 4;
          bigClientIndex += 2;
      }
      bigClientIndex = 0;
      for(j = 0; j < 5;j++)
      {
          if(bigClientIndex == 2) // dont copy '-'
          {
              smallClients[i].short_phone[j] += bigClients[i].phone[bigClientIndex] - '0';
              smallClients[i].short_phone[j] += (bigClients[i].phone[bigClientIndex + 2] - '0') << 4;
              bigClientIndex += 3;
          }
          else
          {
              smallClients[i].short_phone[j] += bigClients[i].phone[bigClientIndex] - '0';
              smallClients[i].short_phone[j] += (bigClients[i].phone[bigClientIndex + 1] - '0') << 4;
              bigClientIndex += 2;
          }
      }
    }
    free(bigClients);
    return smallClients;

}
Client * getBigClients(int n)
{
    Client * bigClients = (Client*) malloc(n * sizeof (Client));
    if (bigClients == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for bigClients\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i < n;i++)
    {
        printf("Please enter client ID: ");
        scanf("%s",bigClients[i].id);
        printf("Please enter client phone number in the form xxx-xxxxxxx: ");
        scanf("%s",bigClients[i].phone);
    }
    return bigClients;

}
char * searchClientByID(Short_client * arr,int size,char Id[])
{
    unsigned char * smallId = compressID(Id);
    char * bigTelephone = (char*) malloc(12*sizeof(char));
    for(int i = 0; i< size;i++)
    {
        if(checkIdTheSame(arr[i].short_id,smallId))
        {
            decompressPhone(bigTelephone,arr[i].short_phone);
            free(smallId);
            return bigTelephone;
        }
    }
    free(bigTelephone);
    free(smallId);
    return NULL;
}
unsigned char * compressID(char * Id)
{
    unsigned char * small_ID = (unsigned char*) malloc(4*sizeof(unsigned char));
    CheckAllocation(small_ID)
    for (int i = 0; i < 4; i++)
    {
        small_ID[i] = (Id[i * 2] - '0') + ((Id[i * 2 + 1] - '0') << 4);
    }
    return small_ID;
}
bool checkIdTheSame(unsigned char* Id1,unsigned char * Id2)
{
    for(int i = 0; i < 4;i++)
    {
        if(Id1[i] != Id2[i])
        {
            return false;
        }
    }
    return true;
}
void decompressPhone(char phone[],unsigned char smallPhone[])
{
    phone[0] = (smallPhone[0] & 0x0F) + '0';
    phone[1] = ((smallPhone[0] >> 4) & 0x0F) + '0';
    phone[2] = (smallPhone[1] & 0x0F) + '0';
    phone[3] = '-';
    phone[4] = ((smallPhone[1] >> 4) & 0x0F) + '0';

    for(int i = 2; i < 5;i++)
    {

            phone[i * 2 + 1] = (smallPhone[i] & 0x0F) + '0';
            phone[i * 2 + 2] = ((smallPhone[i] >> 4) & 0x0F) + '0';
    }
    phone[11] = '\0';
}