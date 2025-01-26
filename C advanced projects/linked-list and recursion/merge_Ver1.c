//-----------------------------------Includes----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
void freeList(List * lst);

int main()

{

    List lst1, lst2, mergedList;

    lst1 = getList();

    lst2 = getList();

    printList(&lst1);

    printList(&lst2);

    mergedList = merge(lst1, lst2);

    printf("Merged list:\n");

    printList(&mergedList);

     freeList(&lst1);

     freeList(&lst2);

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
    List mergedList;
    makeEmptyList(&mergedList);
    ListNode *curr1 = ls1.head;
    ListNode *curr2 = ls2.head;
    while (curr1 != NULL && curr2 != NULL)
    {
        if (*(curr1->dataPtr) > *(curr2->dataPtr))
        {
            insertDataToEndList(&mergedList,*(curr1->dataPtr));
            curr1 = curr1->next;
        }
        else
        {
            insertDataToEndList(&mergedList,*(curr2->dataPtr));
            curr2 = curr2->next;
        }
    }
    while (curr1 != NULL)
    {
        insertDataToEndList(&mergedList,*(curr1->dataPtr));
        curr1 = curr1->next;
    }
    while (curr2 != NULL)
    {
        insertDataToEndList(&mergedList,*(curr2->dataPtr));
        curr2 = curr2->next;
    }
    return mergedList;
}
void freeList(List * lst)
{
    ListNode * temp;

    while (lst->head != NULL)
    {
        temp = lst->head;
        lst->head = lst->head->next;
        free(temp->dataPtr);
        free(temp);
    }

}