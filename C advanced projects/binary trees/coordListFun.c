#include "coordListFun.h"
void makeEmptyLevelList(LevelList *lst)
{
    lst->headLevel = lst->tailLevel = NULL;
}
void makeEmptyValueList(ValueList * lst)
{
    lst->headValue = lst->tailValue = NULL;
}
void insertDataToEndLevelList(LevelList * lst, unsigned int data)
{
    LevelListNode *newTail;
    newTail = createNewLevelListNode(data,NULL,NULL);
    insertNodeToEndLevelList(lst,newTail);

}
void insertDataToEndValueList(ValueList *lst, unsigned int data)
{
    ValueListNode  * newTail;
    newTail = createNewValueListNode(data, NULL);
    insertNodeToEndValueList(lst, newTail);
}

LevelListNode * createNewLevelListNode(unsigned int data, LevelListNode * next,LevelListNode * prev)
{
    LevelListNode *res;
    res = (LevelListNode *)malloc(sizeof(LevelListNode));
    if(res == NULL)
    {
        printf("Memory allocation failed!!!");
        exit(1);
    }
    res->valList =(ValueList * )malloc(sizeof(ValueList));
    if(res->valList == NULL)
    {
        printf("Memory allocation failed!!!");
        exit(1);
    }
    res->prev = prev;
    res->data = data;
    makeEmptyValueList(res->valList);
    res->next = next;

    return res;
}
ValueListNode * createNewValueListNode(unsigned int data, ValueListNode * next)
{
    ValueListNode * res;
    res = (ValueListNode * )malloc(sizeof(ValueListNode));
    if(res == NULL)
    {
        printf("Memory Allocation Failed!!!");
        exit(1);
    }
    res->data = data;
    res->next = next;
    return res;
}
void insertNodeToEndLevelList(LevelList * lst, LevelListNode *tail)
{
    if (isEmptyLevelList(lst) == true)
    {
        lst->headLevel = lst->tailLevel = tail;
        tail->prev = NULL;
    }
    else
    {
        lst->tailLevel->next = tail;
        tail->prev = lst->tailLevel;
        lst->tailLevel = tail;
    }
    tail->next = NULL;
}
void insertNodeToEndValueList(ValueList *lst, ValueListNode *tail)
{
    if (isEmptyValueList(lst) == true)
    {
        lst->headValue = lst->tailValue = tail;
    }
    else
    {
        lst->tailValue->next = tail;
        lst->tailValue = tail;
    }
    tail->next = NULL;
}

bool isEmptyLevelList(LevelList *lst)
{
    if (lst->headLevel == NULL)
        return true;
    else
        return false;
}
bool isEmptyValueList(ValueList *lst)
{
    if (lst->headValue == NULL)
        return true;
    else
        return false;
}
void printList(LevelList * list)
{
    LevelListNode *currLev;
    ValueListNode *currVal;
    currLev = list->headLevel;
    while (currLev != NULL)
    {
        currVal = currLev->valList->headValue;
        while (currVal != NULL)
        {
            printf("%d ",currVal->data);
            currVal = currVal->next;
        }
        currLev = currLev->next;
    }
    printf("\n");
    freeCoordList(list);
}
void freeCoordList(LevelList * coordList)
{
    LevelListNode *currLevel = coordList->headLevel;
    LevelListNode *nextLevel;
    ValueListNode *currValue;
    ValueListNode *nextValue;

    while (currLevel != NULL)
    {
        nextLevel = currLevel->next;
        currValue = currLevel->valList->headValue;
        while (currValue != NULL)
        {
            nextValue = currValue->next;
            free(currValue);
            currValue = nextValue;
        }
        free(currLevel->valList);
        free(currLevel);
        currLevel = nextLevel;
    }
}