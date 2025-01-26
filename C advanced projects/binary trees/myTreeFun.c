
#include "myTreeFun.h"
TreeNode * createNewTNode(int data,TreeNode* left,TreeNode* right)
{
    TreeNode * TNode = (TreeNode *)malloc(sizeof(TreeNode));
    CheckAllocation(TNode)

    TNode->data = data;
    TNode->left = left;
    TNode->right = right;

    return TNode;
}

Tree BuildTreeFromArray(int * arr, int size)
{
    Tree tr;
    tr.root = BuildTreeFromArrayHelper(arr,size);
    return tr;
}
TreeNode * BuildTreeFromArrayHelper(int * arr, int size)
{
    if(size <= 0 || arr[(size/2)] == -1 )
    {
        return NULL;
    }
    else
    {
        TreeNode * root = createNewTNode(arr[size/2],NULL,NULL);
        CheckAllocation(root)
        root->left = BuildTreeFromArrayHelper(arr,size - size/2 - 1);
        root->right = BuildTreeFromArrayHelper(arr+size/2+1,size - size/2 - 1);
        return root;
    }
}

void printTreeInorder(Tree tr)
{
    printTreeInorderHelper(tr.root);
}
void printTreeInorderHelper(TreeNode * root)
{
    if (root == NULL)
    {
        return;
    }else
    {
        printTreeInorderHelper(root->left);
        printf("%d ", root->data);
        printTreeInorderHelper(root->right);
    }

}
void freeTree(Tree tr)
{
    freeTreeHelper(tr.root);
}
void freeTreeHelper(TreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        freeTreeHelper(root->left);
        root->left = NULL;
        freeTreeHelper(root->right);
        root->right = NULL;
        free(root);
    }
}