//
// Created by עופרי קופרברג on 13/02/2024.
//

#ifndef ASSIGNMENT_4_EXPRESSIONTREEFUN_H
#define ASSIGNMENT_4_EXPRESSIONTREEFUN_H
#include <stdlib.h>
#include <string.h>
#include "myTreeFun.h"
#define ERROR '!'

typedef int BOOL;

#define FALSE 0

#define TRUE 1

char getMainOperator(char arr[],unsigned int size,int *index);
BOOL checkIfValidOperator(char ch);
BOOL buildExpressionTree(char * str, Tree * tr);
TreeNode * buildExpressionTreeHelper(char * str, TreeNode * root,unsigned int size);
BOOL isANum(char ch);
int calcExpression(Tree tr);
int calcExpressionHelper(TreeNode * root);
#endif //ASSIGNMENT_4_EXPRESSIONTREEFUN_H
