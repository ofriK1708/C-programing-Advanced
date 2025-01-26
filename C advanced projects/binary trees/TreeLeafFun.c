#include "TreeLeafFun.h"
TreeNode * findParent(Tree tr, int parentData, int branchSelect)
{
    return (findParentHelper(tr.root,parentData,branchSelect));
}
TreeNode * findParentHelper(TreeNode * root, int parentData, int branchSelect)
{
    if(root == NULL)
    {
        return NULL;
    }
    else if(root->data == parentData)
    {
        if((root->left == NULL && branchSelect == LEFT) || (root->right == NULL && branchSelect == RIGHT))
        {
            return root;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        TreeNode * res;
        res = findParentHelper(root->left,parentData,branchSelect);
        if(res != NULL)
        {
            return res;
        }
        else
        {
            return findParentHelper(root->right,parentData,branchSelect);
        }
    }
}
Tree AddLeaf (Tree tr, TreeNode *p, int branchSelect, int data)
{
    AddLeafHelper(tr.root,p,branchSelect,data);
    List newLeafList = makeLeafList(tr);
    freeList(&tr.leafList);
    tr.leafList = newLeafList;
    return tr;
}
bool AddLeafHelper (TreeNode * root, TreeNode *dest, int branchSelect, int data)
{
    bool foundLeaf;
    if(root == NULL)
    {
        return false;
    }
    else if(root->left == NULL || root->right == NULL)
    {
        if(root->left == root->right) // == NULL (a real leaf)
        {
            if(root != dest)
            {
                return false;
            }
            else // root == dest
            {
                if(branchSelect == LEFT)
                    root->left = insertNewTreeLeaf(root, data);
                else // branchSelect == RIGHT
                    root->right = insertNewTreeLeaf(root, data);
                return true;
            }
        }
        else
        {
            if(root != dest)
            {
                foundLeaf = AddLeafHelper(root->left, dest, branchSelect, data);
                if (foundLeaf == true)
                    return true;
                foundLeaf = AddLeafHelper(root->right, dest, branchSelect, data);
                return foundLeaf;
            }
            else
            {
                if(branchSelect == LEFT)
                {
                    root->left =  insertNewTreeLeaf(root, data);
                }
                else
                {
                    root->right = insertNewTreeLeaf(root, data);
                }
                return true;
            }
        }
    }
    else
    {
        foundLeaf = AddLeafHelper(root->left, dest, branchSelect, data);
        if (foundLeaf == true)
            return true;
        foundLeaf = AddLeafHelper(root->right, dest, branchSelect, data);
        return foundLeaf;
    }
}
List makeLeafList(Tree tr)
{
    List leafList;
    makeEmptyList(&leafList);
    makeLeafListHelper(&leafList,tr.root);
    return leafList;
}
void makeLeafListHelper(List * ls,TreeNode * root)
{
    if(root == NULL)
    {
        return;
    }
    else if(root->right == NULL && root->left == NULL) // we are on a leaf
    {
        insertDataToEndList(ls,root->data);
    }
    else
    {
        makeLeafListHelper(ls,root->left);
        makeLeafListHelper(ls,root->right);
    }
}
TreeNode * insertNewTreeLeaf(TreeNode * parent,int data)
{
    TreeNode * leaf = (TreeNode*) malloc(sizeof(TreeNode));
    CheckAllocation(leaf)
    leaf->parent = parent;
    leaf->data = data;
    leaf->right = leaf->left = NULL;
    return leaf;

}

Tree BuildTreeFromArrayWithLeafList(int * arr, int size)
{
    Tree tr;
    tr.root = BuildTreeFromArrayWithLeafListHelper(arr,size,&tr.leafList,NULL);
    return tr;
}
TreeNode * BuildTreeFromArrayWithLeafListHelper(int * arr, int size,List * ls,TreeNode * parent)
{
    if(size <= 0 || arr[(size/2)] == -1 )
    {
        return NULL;
    }
    else
    {
        TreeNode * root = createNewTNode(arr[size/2],NULL,NULL);
        CheckAllocation(root)
        root->parent = parent;
        if(size == 1 || ((size == 3) && (arr[size/2 + 1] == -1) && (arr[size/2 - 1])))
        {
            insertDataToEndList(ls,arr[size/2]);
        }
        root->left = BuildTreeFromArrayWithLeafListHelper(arr,size - size/2 - 1,ls,root);
        root->right = BuildTreeFromArrayWithLeafListHelper(arr+size/2+1,size - size/2 - 1,ls,root);
        return root;
    }
}

TreeNode * createNewTNode(int data,TreeNode* left,TreeNode* right)
{
    TreeNode * TNode = (TreeNode *)malloc(sizeof(TreeNode));
    CheckAllocation(TNode)

    TNode->data = data;
    TNode->left = left;
    TNode->right = right;

    return TNode;
}

void printTreeInorder(Tree tr)
{
    printTreeInorderHelper(tr.root);
    printf("\n");
}
void printTreeInorderHelper(TreeNode * root)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        printTreeInorderHelper(root->left);
        printf("%d ",root->data);
        printTreeInorderHelper(root->right);
    }
}
void printLeafList(Tree  tr)
{
    ListNode *curr;
    curr = tr.leafList.head;
    while (curr != NULL)
    {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");

}
void freeTree(Tree tr)
{
    freeList(&tr.leafList);
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