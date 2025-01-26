#ifndef ASSIGNMENT_4_MYTREEFUN_H
#define ASSIGNMENT_4_MYTREEFUN_H
#include <stdio.h>
#include <stdlib.h>

#define CheckAllocation(c) if(c==NULL){ \
printf("Memory Allocation Failed!!!");   \
exit(1);                                \
}

typedef struct treeNode {
    unsigned int data;
    struct treeNode *left;
    struct treeNode *right;
}TreeNode;

typedef struct tree
{
    TreeNode *root;
}Tree;

TreeNode * createNewTNode(int data,TreeNode* left,TreeNode* right);
Tree BuildTreeFromArray(int * arr, int size);
TreeNode * BuildTreeFromArrayHelper(int * arr, int size);
void printTreeInorder(Tree tr);
void printTreeInorderHelper(TreeNode * root);
void freeTree(Tree tr);
void freeTreeHelper(TreeNode * root);

#endif //ASSIGNMENT_4_MYTREEFUN_H
