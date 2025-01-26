//------------------------------Includes & defines----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define FOUND 1
#define NOT_FOUND 0
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

void insertDataToStart_X_List(List *lst, int data);
void insertDataToStart_Y_List(YList *lst, int data);

void insertDataToEnd_X_List(List *lst, int data);
void insertDataToEnd_Y_List(YList *lst, int data);

void insertDataToPlaceIn_X_List(int data, XListNode * before);
void insertDataToPlaceIn_Y_List(int data, YListNode * before);

XListNode *createNew_X_ListNode(int data, XListNode *next,XListNode * prev);
YListNode *createNew_Y_ListNode(int data, YListNode *next);

void insertNodeToStart_X_List(List * lst, XListNode *head);
void insertNodeToStart_Y_List(YList * lst, YListNode *head);

void insertNodeToEnd_X_List(List *lst, XListNode *tail);
void insertNodeToEnd_Y_List(YList *lst, YListNode *tail);

void insertNodeToPlaceIn_X_List(XListNode * newNode,XListNode * before);
void insertNodeToPlaceIn_Y_List(YListNode * newNode,YListNode * before);

bool isEmpty_X_List(List *lst);
bool isEmpty_Y_List(YList *lst);

void printList(List *list);
List getCoordList();
int insertCoordinate(List *coord_list, int x, int y);
void freeList(List * coordList);




int main()

{

    List coordList;

    int x, y;

    int res;

    coordList = getCoordList();

// get the (x,y) to insert

    scanf("%d%d", &x, &y);



    res = insertCoordinate(&coordList, x, y);

    if(res == 0)

        printf("The point (%d,%d) didn't appear\n",x,y);

    else

        printf("The point (%d,%d) already appeared\n",x,y);

    printf("Updated list: ");

    printList(&coordList);

    freeList(&coordList);
    return 0;
}
void make_X_EmptyList(List *lst)
{
    lst->headX = lst->tailX = NULL;
}
void make_Y_EmptyList(YList *lst)
{
    lst->headY = lst->tailY = NULL;
}
void insertDataToStart_X_List(List *lst, int data)
{
    XListNode *newHead;
    newHead = createNew_X_ListNode(data,NULL,NULL);
    insertNodeToStart_X_List(lst,newHead);
}
void insertDataToStart_Y_List(YList *lst, int data)
{
    YListNode *newHead;
    newHead = createNew_Y_ListNode(data,NULL);
    insertNodeToStart_Y_List(lst,newHead);
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
void insertDataToPlaceIn_X_List(int data, XListNode * before)
{
    XListNode *newNode;
    newNode = createNew_X_ListNode(data,before->next,before);
    insertNodeToPlaceIn_X_List(newNode,before);
}
void insertDataToPlaceIn_Y_List(int data, YListNode * before)
{
    YListNode *newNode;
    newNode = createNew_Y_ListNode(data,NULL);
    insertNodeToPlaceIn_Y_List(newNode,before);
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
void insertNodeToStart_X_List(List * lst, XListNode *head)
{
    if (isEmpty_X_List(lst) == true)
    {
        head->next = NULL;
        lst->headX = lst->tailX = head;
    }
    else
    {
        head->next = lst->headX;
        lst->headX = head;
    }
}
void insertNodeToStart_Y_List(YList * lst, YListNode *head)
{
    if (isEmpty_Y_List(lst) == true)
    {
        head->next = NULL;
        lst->headY = lst->tailY = head;
    }
    else
    {
        head->next = lst->headY;
        lst->headY = head;
    }
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
void insertNodeToPlaceIn_X_List(XListNode * newNode,XListNode * before)
{
    before->next = newNode;
    newNode->next->prev = newNode;
}
void insertNodeToPlaceIn_Y_List(YListNode * newNode,YListNode * before)
{
    newNode->next = before->next;
    before->next = newNode;
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

int insertCoordinate(List *coord_list, int x, int y)
{
    int foundFlag;
    bool didInsertPoint = false;
    int pointX,pointY;
    XListNode * currX = coord_list->headX;
    YListNode * currY = NULL;
    YListNode * beforeY = NULL;
    while(currX != NULL && !(didInsertPoint))
    {
        pointX = currX->data;
        if(pointX > x)
        {
            foundFlag = NOT_FOUND;
            if(currX == coord_list->headX) // if we are at the start of X list
            {
                insertDataToStart_X_List(coord_list,x);
                insertDataToStart_Y_List(coord_list->headX->yList,y);
            }
            else
            {
                insertDataToPlaceIn_X_List(x,currX->prev);
                insertDataToStart_Y_List(currX->prev->yList,y);
            }

            didInsertPoint = true;
        }
        else if(pointX == x)
        {
            currY = currX->yList->headY;
            while (currY != NULL && !(didInsertPoint))
            {
                pointY = currY->data;
                if (pointY > y)
                {
                    foundFlag = NOT_FOUND;
                    if(currY == currX->yList->headY) // if we are at the start of Y list
                    {
                        insertDataToStart_Y_List(currX->yList,y);
                    }
                    else
                    {
                        insertDataToPlaceIn_Y_List(y,beforeY);
                    }
                    didInsertPoint = true;
                }

                else if(pointY == y)
                {
                    foundFlag = FOUND;
                    if(currY == currX->yList->headY) // if we are at the start of Y list
                    {
                        insertDataToStart_Y_List(currX->yList,y);
                    }
                    else
                    {
                        insertDataToPlaceIn_Y_List(y,beforeY);
                    }
                    didInsertPoint = true;
                }
                else
                {
                    beforeY = currY;
                    currY = currY->next;
                }
            }
            if(!didInsertPoint) // we finished with the Y List but still haven't found a larger or equal Y point
            {
                foundFlag = false;
                insertDataToEnd_Y_List(currX->yList,y);
                didInsertPoint = true;
            }
        }
        else
        {
            currX = currX->next;
        }
    }
    if(didInsertPoint == false) // we finished with the X List but still haven't found a larger or equal X point
    {
        foundFlag = false;
        insertDataToEnd_X_List(coord_list, x);
        insertDataToStart_Y_List(coord_list->tailX->yList,y);
    }
    return foundFlag;
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