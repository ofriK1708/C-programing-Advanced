//------------------------------Includes & defines----------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DELETED_SINGLE_FOUND 3
#define DELETED_MULTIPLE_FOUND 2
#define NOT_DELETED_NOT_FOUND 1
#define INVALID 0
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

//unsigned int getPairOccurrences(List coord_list,int x, int y);
//unsigned int getYOccurrences(List coord_list, int y);
//unsigned int getXOccurrences(List coord_list, int x);
//int insertCoordinate(List *coord_list, int x, int y);

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
//unsigned int getPairOccurrences(List coord_list,int x, int y)
//{
//   if(coord_list.headX == NULL)
//   {
//       return 0;
//   }
//   else
//   {
//    XListNode * currX = coord_list.headX;
//    YListNode * currY;
//    unsigned int count = 0;
//    while (currX != NULL)
//    {
//        if (currX->data == x)
//        {
//            currY = currX->yList->headY;
//            while (currY != NULL)
//            {
//                if (currY->data == y)
//                {
//                    count++;
//                }
//                currY = currY->next;
//            }
//        }
//           currX = currX->next;
//    }
//       return count;
//   }
//}
//unsigned int getYOccurrences(List coord_list, int y)
//{
// if(coord_list.headX == NULL)
// {
//     return 0;
// }
// else
// {
//    unsigned int count = 0;
//    XListNode * currX = coord_list.headX;
//    YListNode * currY = NULL;
//    while(currX != NULL)
//    {
//        currY = currX->yList->headY;
//        while(currY != NULL)
//        {
//            if(currY->data == y)
//            {
//                count++;
//            }
//            currY = currY->next;
//        }
//        currX = currX->next;
//    }
//    return count;
// }
//}
//
//unsigned int getXOccurrences(List coord_list, int x)
//{
//    if(coord_list.headX == NULL)
//    {
//        return 0;
//    }
//    else
//    {
//        unsigned int count = 0;
//        XListNode * currX = coord_list.headX;
//        while(currX != NULL)
//        {
//            if(currX->data == x)
//            {
//             count++;
//            }
//            currX = currX->next;
//        }
//        return count;
//    }
//}
//int insertCoordinate(List *coord_list, int x, int y)
//{
// int foundFlag;
// bool didInsertPoint = false;
// int pointX,pointY;
// XListNode * currX = coord_list->headX;
// YListNode * currY = NULL;
// YListNode * beforeY = NULL;
// while(currX != NULL && !(didInsertPoint))
// {
//     pointX = currX->data;
//     if(pointX > x)
//     {
//         foundFlag = NOT_FOUND;
//         if(currX == coord_list->headX)
//         {
//             insertDataToStart_X_List(coord_list,x);
//             insertDataToStart_Y_List(coord_list->headX->yList,y);
//         }
//         else
//         {
//             insertDataToPlaceIn_X_List(x,currX->prev);
//             insertDataToStart_Y_List(currX->prev->yList,y);
//         }
//
//         didInsertPoint = true;
//     }
//     else if(pointX == x)
//     {
//             currY = currX->yList->headY;
//             while (currY != NULL && !(didInsertPoint))
//             {
//                 pointY = currY->data;
//                 if (pointY > y)
//                 {
//                     foundFlag = NOT_FOUND;
//                     if(currY == currX->yList->headY) // if we are at the start of Y list
//                     {
//                         insertDataToStart_Y_List(currX->yList,y);
//                     }
//                     else
//                     {
//                         insertDataToPlaceIn_Y_List(y,beforeY);
//                     }
//                     didInsertPoint = true;
//                 }
//
//                 else if(pointY == y)
//                 {
//                   foundFlag = FOUND;
//                   if(currY == currX->yList->headY) // if we are at the start of Y list
//                   {
//                       insertDataToStart_Y_List(currX->yList,y);
//                   }
//                   else
//                   {
//                       insertDataToPlaceIn_Y_List(y,beforeY);
//                   }
//                   didInsertPoint = true;
//                 }
//                 else
//                 {
//                     beforeY = currY;
//                     currY = currY->next;
//                 }
//             }
//             if(!didInsertPoint) // we finished with the Y List but still haven't found a larger or equal Y point
//             {
//                 foundFlag = false;
//                 insertDataToEnd_Y_List(currX->yList,y);
//                 didInsertPoint = true;
//             }
//         }
//     else
//     {
//         currX = currX->next;
//     }
// }
//    if(didInsertPoint == false) // we finished with the X List but still haven't found a larger or equal X point
//    {
//        foundFlag = false;
//        insertDataToEnd_X_List(coord_list, x);
//        insertDataToStart_Y_List(coord_list->tailX->yList,y);
//    }
//    return foundFlag;
//}
int removeCoordinate(List *coord_list, int x, int y)
{
 int deleteFlag = NOT_DELETED_NOT_FOUND;
 XListNode * currX = coord_list->headX;
 YListNode * currY = NULL;
 YListNode * beforeY = NULL;
 if(coord_list->headX == NULL) // checks to see if got an empty list
 {
     deleteFlag = INVALID;
     return deleteFlag;
 }
 while(currX != NULL && deleteFlag == NOT_DELETED_NOT_FOUND)
 {
     if(currX->data == x)
     {
         currY = currX->yList->headY;
         while (currY != NULL && deleteFlag == NOT_DELETED_NOT_FOUND)
         {
             if (currY->data == y)
             {
                 deletedFrom_Y_LIST(currX->yList,currY,beforeY,&deleteFlag);
                 if(currX->yList->headY == NULL) // if there was only one Y node inside the Ylist of the X node we need to remove the X node too
                 {
                     deletedFrom_X_LIST(coord_list,currX);
                 }
                 // we don't need to do anything else if the Y list inside the X node isn't empty
             }
             else
             {
                 beforeY = currY;
                 currY = currY->next;
             }
         }
     }
     else
     {
         currX = currX->next;
     }
 }
    return deleteFlag;
}
bool deletedFrom_Y_LIST(YList * lst,YListNode * delete,YListNode * before,int * flag)
{
    if(lst->headY == NULL || delete == NULL) // checks if we got empty list or empty delete node
    {
      return false;
    }
    if(lst->headY == delete && delete->next == NULL)// delete the only one node of the list
    {
        lst->headY = lst->tailY = NULL;
        *flag = DELETED_SINGLE_FOUND;
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
            *flag = DELETED_SINGLE_FOUND;
        }
       }
    else if(delete->next == NULL) // delete from the end
    {
      *flag = DELETED_SINGLE_FOUND;
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
          *flag = DELETED_SINGLE_FOUND;
      }
      before->next = delete->next;
    }
    free(delete);
    return true;
}
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



