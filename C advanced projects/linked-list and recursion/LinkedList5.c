//------------------------------Includes & defines----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DELETED_X_ALSO 3
#define DELETED_MULTIPLE_FOUND 2
#define NOT_DELETED_NOT_FOUND 1
#define OTHER 0
#define INIT_FLAG (-1)
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
int removeCoordinate(List *coord_list, int x, int y);
bool deletedFrom_Y_LIST(YList * lst,YListNode * delete,YListNode * before,int * flag);
bool deletedFrom_X_LIST(List * lst,XListNode * delete);
void freeList(List * coordList);




int main()

{

    List coordList;

    int x, y;

    int res;

    coordList = getCoordList();

// get the (x,y) to remove

    scanf("%d%d", &x, &y);



    res = removeCoordinate(&coordList, x, y);

    if(res == 1)

        printf("The point (%d,%d) didn't appear\n",x,y);

    else if(res == 2)

        printf("The point (%d,%d) has another occurrence\n",x,y);

    else if(res == 3)

        printf("The point (%d,%d) was the only point with this x\n",x,y);

    else

        printf("Other\n");

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
    printf("\b\b\n");
}


// this function is in charge of taking a CoordList from the user, every time the user enter a new X point the function will make room, and same goes for y point
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
        while (i < numOfPoints)
        {
            insertDataToEnd_X_List(&Xlist, pointX);
            pointXFlag = pointX;
            while (pointXFlag == pointX && i < numOfPoints)
            {
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

int removeCoordinate(List *coord_list, int x, int y)
{
    int deleteFlag = INIT_FLAG;
    XListNode * currX = coord_list->headX;
    YListNode * currY = NULL;
    YListNode * beforeY = NULL;
    if(coord_list->headX == NULL) // checks to see if got an empty list
    {
        deleteFlag = NOT_DELETED_NOT_FOUND;
        return deleteFlag;
    }
    if(coord_list->tailX->data < x)
    {
        deleteFlag = NOT_DELETED_NOT_FOUND;
    }
    else
    {
    while(currX != NULL && deleteFlag == INIT_FLAG) // while there wasn't any changes to the delete flag (found only one/not found/other)
     {
        if(currX->data > x)
        {
            deleteFlag = NOT_DELETED_NOT_FOUND;
        }
        else if(currX->data == x)
        {
            currY = currX->yList->headY;
            if(currX->yList->tailY->data < y)
            {
                deleteFlag = NOT_DELETED_NOT_FOUND;
            }
            else
            {
                while (currY != NULL && deleteFlag == INIT_FLAG)
                {
                    if (currY->data > y)
                    {
                        deleteFlag = NOT_DELETED_NOT_FOUND;
                    }
                    else if (currY->data == y)
                    {
                        deletedFrom_Y_LIST(currX->yList, currY, beforeY, &deleteFlag);
                        if (currX->yList->headY == NULL) // if there was only one Y node inside the Ylist of the X node we need to remove the X node too
                        {
                            deletedFrom_X_LIST(coord_list, currX);
                            deleteFlag = DELETED_X_ALSO;
                        }
                    }
                    else
                    {
                        beforeY = currY;
                        currY = currY->next;
                    }
                }
            }
        }
        else
        {
            currX = currX->next;
        }
     }
    }
    return deleteFlag;
}

// this function receives singly linked list, a node to delete and his previous (if exist) node in the list, this  checks where the node is located in the list and then remove it from the list and deallocating the memory of it
bool deletedFrom_Y_LIST(YList * lst,YListNode * delete,YListNode * before,int * flag)
{
    if(lst->headY == NULL || delete == NULL) // checks if we got empty list or empty delete node
    {
        return false;
    }
    if(lst->headY == delete && delete->next == NULL)// delete the only one node of the list
    {
        lst->headY = lst->tailY = NULL;
    }
    else if(lst->headY == delete) // delete from the start and there are more points afterward
    {
        lst->headY = delete->next;

        if(lst->headY->data == delete->data)
        {
            *flag = DELETED_MULTIPLE_FOUND;
        }
        else
        {
            *flag = OTHER;
        }
    }
    else if(delete->next == NULL) // delete from the end
    {
        *flag = OTHER;
        before->next = NULL;
        lst->tailY = before;
    }
    else // delete from the middle of the list
    {
        if(delete->next->data == delete->data)
        {
            *flag = DELETED_MULTIPLE_FOUND;
        }
        else
        {
            *flag = OTHER;
        }
        before->next = delete->next;
    }
    free(delete);
    return true;
}

// this function receives doubly linked list and a node to delete from it, then it checks where the node is located at and remove it the list and deallocating the memory of it
bool deletedFrom_X_LIST(List * lst,XListNode * delete)
{
    if(lst->headX == NULL || delete == NULL) // checks if we got empty list or empty delete node
    {
        return false;
    }
    if(lst->headX == delete && delete->next == NULL) // remove the only one node of the list
    {
        lst->headX = lst->tailX = NULL;
    }
    else if(lst->headX == delete) // delete from the start but there are more afterward
    {
        lst->headX = delete->next;
        delete->next->prev = NULL;
    }

    else if(delete->next == NULL) // remove from the end of the list
    {
        delete->prev->next = NULL;
        lst->tailX = delete->prev;
    }
    else // remove from the middle of the list
    {
        delete->prev->next = delete->next;
        delete->next->prev = delete->prev;
    }
    free(delete->yList);
    free(delete);
    return true;
}

// this freeList function goes through the list and first frees all the y nodes, then the y list and then the x node and in the end the whole X list
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



