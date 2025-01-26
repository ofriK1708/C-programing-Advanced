
#ifndef ASSIGNMENT_4_TREELEAFFUN_H
#define ASSIGNMENT_4_TREELEAFFUN_H
#include "ListFun.h"
#include <stdlib.h>
#include <stdio.h>
#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

#define LEFT  0
#define RIGHT 1

typedef struct  treeNode {
    int data;
    struct treeNode* parent;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree{
    TreeNode* root;
    List leafList;   /*רשימה מקושרת של כל העלים בעץ*/
} Tree;

Tree AddLeaf (Tree tr, TreeNode *p, int branchSelect, int data);
bool AddLeafHelper (TreeNode * root, TreeNode *dest, int branchSelect, int data);
List makeLeafList(Tree tr);
void makeLeafListHelper(List * ls,TreeNode * root);
TreeNode * findParent(Tree tr, int parentData, int branchSelect);
TreeNode * findParentHelper(TreeNode * root, int parentData, int branchSelect);
TreeNode * insertNewTreeLeaf(TreeNode * parent,int data);
Tree BuildTreeFromArrayWithLeafList(int * arr, int size);
TreeNode * BuildTreeFromArrayWithLeafListHelper(int * arr, int size,List * ls,TreeNode * parent);
TreeNode * createNewTNode(int data,TreeNode* left,TreeNode* right);
void printTreeInorder(Tree tr);
void printTreeInorderHelper(TreeNode * root);
void printLeafList(Tree  tr);
void freeTree(Tree tr);
void freeTreeHelper(TreeNode * root);

#endif //ASSIGNMENT_4_TREELEAFFUN_H
