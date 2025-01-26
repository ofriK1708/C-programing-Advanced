#include "ListFun.h"
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
    res->data = data;
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
void makeEmptyList(List *lst)
{
    lst->head = lst->tail = NULL;
}
void freeList(List * lst)
{
    ListNode * temp;

    while (lst->head != NULL)
    {
        temp = lst->head;
        lst->head = lst->head->next;
        free(temp);
    }

}
