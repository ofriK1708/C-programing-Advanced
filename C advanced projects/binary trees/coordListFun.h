
#ifndef ASSIGNMENT_4_COORDLISTFUN_H
#define ASSIGNMENT_4_COORDLISTFUN_H
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

typedef struct valueListNode
{
    unsigned int data;
    struct valueListNode * next;
} ValueListNode;

typedef struct valueList
{
    ValueListNode * headValue;
    ValueListNode * tailValue;
} ValueList;

typedef struct levelListNode
{
    unsigned int data;
    ValueList * valList;
    struct levelListNode * next;
    struct levelListNode * prev;

} LevelListNode;
typedef struct levelList
{
    LevelListNode * headLevel;
    LevelListNode * tailLevel;
} LevelList;

void makeEmptyLevelList(LevelList *lst);
void makeEmptyValueList(ValueList * lst);
void insertDataToEndLevelList(LevelList * lst, unsigned int data);
void insertDataToEndValueList(ValueList *lst, unsigned int data);
LevelListNode * createNewLevelListNode(unsigned int data, LevelListNode * next,LevelListNode * prev);
ValueListNode * createNewValueListNode(unsigned int data, ValueListNode * next);
void insertNodeToEndLevelList(LevelList * lst, LevelListNode *tail);
void insertNodeToEndValueList(ValueList *lst, ValueListNode *tail);
bool isEmptyLevelList(LevelList *lst);
bool isEmptyValueList(ValueList *lst);
void printList(LevelList * list);
void freeCoordList(LevelList * coordList);


#endif //ASSIGNMENT_4_COORDLISTFUN_H
