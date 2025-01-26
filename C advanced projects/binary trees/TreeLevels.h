
#ifndef ASSIGNMENT_4_TREELEVELS_H
#define ASSIGNMENT_4_TREELEVELS_H
#include "coordListFun.h"
#include "myTreeFun.h"
void printByLevels(Tree tr);
void printByLevelsHelper(TreeNode * root,LevelList * levList,LevelListNode * levListNode,int level);
#endif //ASSIGNMENT_4_TREELEVELS_H
