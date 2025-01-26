//-----------------------------------Includes----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedValue"
#pragma ide diagnostic ignored "UnreachableCode"
//-----------------------------------structs-----------------------------------------------
typedef struct listNode
{
    int *dataPtr;
    struct listNode *next;
} ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail;
} List;

//-----------------------------------Prototypes--------------------------------------------------
List getList();
void insertDataToEndList(List *lst, int data);
void makeEmptyList(List *lst);
ListNode *createNewListNode(int data, ListNode *next);
void insertNodeToEndList(List *lst, ListNode *tail);
bool isEmptyList(List *lst);
void printList(List *list);
List merge(List ls1, List ls2);
void mergeHelper(List * res,ListNode * node1,ListNode * node2);
void freeList(List *lst);

int main()
{

        List lst1, lst2, mergedList;

        lst1 = getList();

        lst2 = getList();

        mergedList = merge(lst1,lst2);

        printf("Merged list:\n");

        printList(&mergedList);



        freeList(&mergedList);

    return 0;
}

List getList()

{

    List res;

    int size, num, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");

    scanf("%d", &size);

    printf("Please enter the numbers:\n");

    for (i = 0; i < size; i++)

    {

        scanf("%d", &num);

        insertDataToEndList(&res, num);
    }

    return res;
}

void makeEmptyList(List *lst)
{
    lst->head = lst->tail = NULL;
}

void insertDataToEndList(List *lst, int data)
{
    ListNode *newTail;
    newTail = createNewListNode(data, NULL);
    insertNodeToEndList(lst, newTail);
}
ListNode *createNewListNode(int data, ListNode *next)
{
    ListNode *res;
    res = (ListNode *)malloc(sizeof(ListNode));
    res->dataPtr = (int *)malloc(sizeof(int));
    *(res->dataPtr) = data;
    res->next = next;
    return res;
}

void insertNodeToEndList(List *lst, ListNode *tail)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

bool isEmptyList(List *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}
void printList(List *list)
{
    ListNode *curr;
    curr = list->head;
    while (curr != NULL)
    {
        printf("%d ", *(curr->dataPtr));
        curr = curr->next;
    }
    printf("\n");
}
List merge(List ls1, List ls2)
{
   if(ls1.head == NULL)
   {
       return ls2;
   }
   else if(ls2.head == NULL)
   {
       return ls1;
   }
   else
   {
     List mergelst;
     makeEmptyList(&mergelst);
     mergeHelper(&mergelst,ls1.head,ls2.head);
       return mergelst;

   }
}
void mergeHelper(List * res,ListNode * node1,ListNode * node2)
{
    ListNode * saver;
    if(node1 == NULL || node2 == NULL) {
        while (node1 != NULL) {
            saver = node1->next;
            insertNodeToEndList(res, node1);
            node1 = saver;
        }
        while (node2 != NULL) {
            saver = node2->next;
            insertNodeToEndList(res, node2);
            node2 = saver;
        }

    }
    else
    {
        if(*(node1->dataPtr) >= *(node2->dataPtr))
        {
            saver = node1->next;
            insertNodeToEndList(res,node1);
            mergeHelper(res,saver,node2);
        }
        else
        {
            saver = node2->next;
            insertNodeToEndList(res,node2);
            mergeHelper(res,node1,saver);
        }
    }
}

void freeList(List *lst)
{
    ListNode *temp;

    while (lst->head != NULL)
    {
        temp = lst->head;
        lst->head = lst->head->next;
        free(temp->dataPtr);
        free(temp);
    }
}

#pragma clang diagnostic pop