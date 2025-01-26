#include "expressionTreeFun.h"
char getMainOperator(char * arr,unsigned int size,int * mainOpIndex)
{
    int parentheses=0 ,i = 1;
    char mainOperator;
    BOOL found = FALSE;
    while(!found && i<size)
    {
        if(arr[i] == '(')
        {
            parentheses++;
        }
        else if(arr[i] == ')')
        {
            parentheses--;
        }
        i++;

        if(parentheses==0)
        {
            mainOperator = arr[i];
            *mainOpIndex = i;
            found = TRUE;
        }

    }
    if(checkIfValidOperator(mainOperator))
    {
        return mainOperator;
    }
    else
    {
        return ERROR;
    }


}
BOOL checkIfValidOperator(char ch)
{
    if(ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '%')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
BOOL buildExpressionTree(char * str, Tree * tr)
{

    unsigned int size = strlen(str);
    if(str[0] == '\0' || size < 3)
    {
        return FALSE;
    }
    else
    {
        tr->root = buildExpressionTreeHelper(str,tr->root,size);
        if(tr->root != NULL)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}
TreeNode * buildExpressionTreeHelper(char * str, TreeNode * root,unsigned int size)
{
    if(size == 1)
    {
        if(isANum(str[0]))
        {
            root = createNewTNode(str[0],NULL,NULL);
            return root;
        }
        else
        {
            return NULL;
        }
    }
    else if(str[0] != '(' || str[size-1] != ')')
    {
        return NULL;
    }
    else
    {
        int mainOpIndex;
        char mainOp = getMainOperator(str,size,&mainOpIndex);
        if(mainOp == ERROR)
        {
            return NULL;
        }
        else
        {

            root = createNewTNode(mainOp,NULL,NULL);
            root-> left = buildExpressionTreeHelper(str+1,root->left, mainOpIndex-1);
            if(root->left == NULL)
            {
                return NULL;
            }
            else
            {
                root->right = buildExpressionTreeHelper(str+mainOpIndex+1,root->right,size-mainOpIndex-2);
                if(root->right == NULL)
                {
                    return NULL;
                }
            }
            return root;
        }
    }
}
BOOL isANum(char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int calcExpression(Tree tr)
{
    return calcExpressionHelper(tr.root);
}
int calcExpressionHelper(TreeNode * root)
{
    if(root == NULL)
    {
        return 0;
    }
    else if(root->right == NULL && root->left == NULL)
    {
        return root->data - '0';
    }
    else
    {
        int left,right,res;
        left = calcExpressionHelper(root->left);
        right = calcExpressionHelper(root->right);
        switch (root->data)
        {
            case '+':
                res = left + right;
                break;
            case '-':
                res = left - right;
                break;
            case '*':
                res = left * right;
                break;
            case '/':
                res = left/right;
                break;
            case '%':
                res = left % right;
                break;
        }
        return res;
    }
}