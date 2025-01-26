#ifndef ASSIGNMENT_4_LISTFUN_H
#define ASSIGNMENT_4_LISTFUN_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct listNode  {
    int data;
    struct listNode* next;
} ListNode;

typedef struct list  {
    ListNode* head;
    ListNode* tail;
} List;

void insertDataToEndList(List *lst, int data);
ListNode *createNewListNode(int data, ListNode *next);
void insertNodeToEndList(List *lst, ListNode *tail);
bool isEmptyList(List *lst);
void makeEmptyList(List *lst);
void freeList(List * lst);
#endif //ASSIGNMENT_4_LISTFUN_H
