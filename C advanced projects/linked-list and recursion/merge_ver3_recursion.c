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
void mergeHelper(List * lst,ListNode * node1,ListNode * node2);
void freeList(List *lst);

int main()

{

    List lst1, lst2, mergedList;

    lst1 = getList();

    lst2 = getList();

    mergedList = merge(lst1,lst2);

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
    if(res == NULL || res->dataPtr == NULL)
    {
        printf("Memory Allocation Failed!!!");
        exit(1);
    }
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
    List mergeList;
    makeEmptyList(&mergeList);
    mergeHelper(&mergeList, ls1.head, ls2.head);
    return mergeList;
}
void mergeHelper(List *lst, ListNode *node1, ListNode *node2)
{
    if (node1 == NULL || node2 == NULL)
    {
      while(node1 != NULL)
      {
          insertDataToEndList(lst,*(node1->dataPtr));
          node1 = node1->next;
      }
        while(node2 != NULL)
        {
            insertDataToEndList(lst,*(node2->dataPtr));
            node2 = node2->next;
        }
    }
    else
    {
        if (*(node1->dataPtr) > *(node2->dataPtr))
        {
            insertDataToEndList(lst,*(node1->dataPtr));
            mergeHelper(lst,node1->next,node2);
        }
        else
        {
            insertDataToEndList(lst, *(node2->dataPtr));
            mergeHelper(lst,node1,node2->next);
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