//-----------------------------------Includes----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//-----------------------------------structs-----------------------------------------------
typedef struct YlistNode
{
    int data;
    struct YlistNode * next;
} YListNode;
typedef struct Ylist
{
    YListNode * headY;
    YListNode * tailY;
} YList;

typedef struct XlistNode
{
    int data;
    YList * yList;
    struct XlistNode * next;
    struct XlistNode * prev;

} XListNode;
typedef struct list
{
    XListNode * headX;
    XListNode * tailX;
} List;

//-----------------------------------Prototypes--------------------------------------------------
void make_X_EmptyList(List *lst);
void make_Y_EmptyList(YList *lst);
void insertDataToEnd_X_List(List *lst, int data);
void insertDataToEnd_Y_List(YList *lst, int data);
XListNode *createNew_X_ListNode(int data, XListNode *next,XListNode * prev);
YListNode *createNew_Y_ListNode(int data, YListNode *next);
void insertNodeToEnd_X_List(List *lst, XListNode *tail);
void insertNodeToEnd_Y_List(YList *lst, YListNode *tail);
bool isEmpty_X_List(List *lst);
bool isEmpty_Y_List(YList *lst);
void printList(List *list);
List getCoordList();
unsigned int getYOccurrences(List coord_list, int y);
void freeList(List * coordList);




int main()

{

    List coordList;

    int y;

    unsigned int res;

    coordList = getCoordList();

// get the (*,y) to look for

    scanf("%d", &y);



    res = getYOccurrences(coordList, y);

    printf("The point (*,%d) appears %u times\n", y, res);

    freeList(&coordList);return 0;
}
void make_X_EmptyList(List *lst)
{
    lst->headX = lst->tailX = NULL;
}
void make_Y_EmptyList(YList *lst)
{
    lst->headY = lst->tailY = NULL;
}

void insertDataToEnd_X_List(List *lst, int data)
{
    XListNode *newTail;
    newTail = createNew_X_ListNode(data, NULL,NULL);
    insertNodeToEnd_X_List(lst, newTail);
}
void insertDataToEnd_Y_List(YList *lst, int data)
{
    YListNode *newTail;
    newTail = createNew_Y_ListNode(data, NULL);
    insertNodeToEnd_Y_List(lst, newTail);
}

XListNode *createNew_X_ListNode(int data, XListNode *next,XListNode * prev)
{
    XListNode *res;
    res = (XListNode *)malloc(sizeof(XListNode));
    if(res == NULL)
    {
        printf("Memory allocation failed!!!");
        exit(1);
    }
    res->yList =(YList *)malloc(sizeof(YList));
    if(res->yList == NULL)
    {
        printf("Memory allocation failed!!!");
        exit(1);
    }
    res->prev = prev;
    res->data = data;
    make_Y_EmptyList(res->yList);
    res->next = next;

    return res;
}
YListNode *createNew_Y_ListNode(int data, YListNode *next)
{
    YListNode *res;
    res = (YListNode *)malloc(sizeof(YListNode));
    if(res == NULL)
    {
        printf("Memory Allocation Failed!!!");
        exit(1);
    }
    res->data = data;
    res->next = next;
    return res;
}

void insertNodeToEnd_X_List(List *lst, XListNode *tail)
{
    if (isEmpty_X_List(lst) == true)
    {
        lst->headX = lst->tailX = tail;
        tail->prev = NULL;
    }
    else
    {
        lst->tailX->next = tail;
        tail->prev = lst->tailX;
        lst->tailX = tail;
    }
    tail->next = NULL;
}
void insertNodeToEnd_Y_List(YList *lst, YListNode *tail)
{
    if (isEmpty_Y_List(lst) == true)
    {
        lst->headY = lst->tailY = tail;
    }
    else
    {
        lst->tailY->next = tail;
        lst->tailY = tail;
    }
    tail->next = NULL;
}

bool isEmpty_X_List(List *lst)
{
    if (lst->headX == NULL)
        return true;
    else
        return false;
}
bool isEmpty_Y_List(YList *lst)
{
    if (lst->headY == NULL)
        return true;
    else
        return false;
}
void printList(List *list)
{
    XListNode *currX;
    YListNode *currY;
    int xPoint;
    currX = list->headX;
    printf("(");
    while (currX != NULL)
    {
        currY = currX->yList->headY;
        xPoint = currX->data;
        while (currY != NULL)
        {
            printf("(%d,%d), ",xPoint,currY->data);
            currY = currY->next;
        }
        currX = currX->next;
    }
    printf("\b\b)\n");
}



List getCoordList()
{
    int pointX,pointY,pointXFlag,numOfPoints,i = 0;
    List Xlist;
    make_X_EmptyList(&Xlist);
    printf("Please enter the number of points: ");
    scanf("%d",&numOfPoints);
    if(numOfPoints > 0)
    {
        printf("Please enter the points:\n");
        scanf("%d", &pointX);
        while (i < numOfPoints) {
            insertDataToEnd_X_List(&Xlist, pointX);
            pointXFlag = pointX;
            while (pointXFlag == pointX && i < numOfPoints) {
                scanf("%d", &pointY);
                insertDataToEnd_Y_List(Xlist.tailX->yList, pointY);
                i++;
                if (i < numOfPoints)
                    scanf("%d", &pointX);
            }
        }
    }
    return Xlist;
}

unsigned int getYOccurrences(List coord_list, int y)
{
    if(coord_list.headX == NULL)
    {
        return 0;
    }
    else
    {
        unsigned int count = 0;
        XListNode * currX = coord_list.headX;
        YListNode * currY = NULL;
        while(currX != NULL)
        {
            currY = currX->yList->headY;
            while(currY != NULL)
            {
                if(currY->data == y)
                {
                    count++;
                }
                currY = currY->next;
            }
            currX = currX->next;
        }
        return count;
    }
}


void freeList(List * coordList)
{
    XListNode *currX = coordList->headX;
    XListNode *nextX;
    YListNode *currY;
    YListNode *nextY;

    while (currX != NULL)
    {
        nextX = currX->next;
        currY = currX->yList->headY;
        while (currY != NULL)
        {
            nextY = currY->next;
            free(currY);
            currY = nextY;
        }
        free(currX->yList);
        free(currX);
        currX = nextX;
    }
}



