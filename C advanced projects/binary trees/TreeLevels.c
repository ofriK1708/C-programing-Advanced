#include "TreeLevels.h"
void printByLevels(Tree tr)
{
    LevelList levList;
    makeEmptyLevelList(&levList);
    printByLevelsHelper(tr.root,&levList,levList.headLevel,0);
    printList(&levList);


}
void printByLevelsHelper(TreeNode * root,LevelList * levList,LevelListNode * levListNode,int level)
{
    if (root == NULL)
    {
        return;
    }
    else
    {
        if(levListNode == NULL) // we reached a new level
        {
            insertDataToEndLevelList(levList,level);
            levListNode = levList->tailLevel;
        }
        insertDataToEndValueList(levListNode->valList,root->data);
        printByLevelsHelper(root->left,levList,levListNode->next,level+1);
        printByLevelsHelper(root->right,levList,levListNode->next,level+1);

    }
}