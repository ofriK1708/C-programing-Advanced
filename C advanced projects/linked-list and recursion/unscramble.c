//-----------------------------------Includes----------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//-----------------------------------structs-----------------------------------------------
typedef struct list_node
{
    char *dataPtr;
    struct list_node *next;
} ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail;
} List;

typedef struct student
{
    List first;
    int grade;
} Student;

//-----------------------------------prototypes-----------------------------------------------
void makeEmptyList(List *lst);
ListNode *createNewListNode(char data, ListNode *next);
void insertDataToEndList(List *lst, char data);
void insertNodeToEndList(List *lst, ListNode *tail);
bool isEmptyList(List *lst);
void printStudent(Student *stud);
void printList(List *list);
bool isCharLetter(char ch);
Student unScramble(List lst);
ListNode*  removeNodeFromList(List *lst, ListNode *node, int i);
int convertCharToInt(char ch);
ListNode *getListNode(List *lst, int i);
void freeList(List * lst);

int main()

{

    List lst;

    Student student;

    char ch;

    makeEmptyList(&lst);

    printf("Please enter the scrambled student:\n");

    ch = (char)getchar();

    while (ch != '\n')

    {

        insertDataToEndList(&lst, ch);

        ch = (char)getchar();
    }

    student = unScramble(lst);

    printStudent(&student);

    freeList(&student.first);

    return 0;
}
void makeEmptyList(List *lst)
{
    lst->head = lst->tail = NULL;
}

void insertDataToEndList(List *lst, char data)
{
    ListNode *newTail;
    newTail = createNewListNode(data, NULL);
    insertNodeToEndList(lst, newTail);
}
ListNode *createNewListNode(char data, ListNode *next)
{
    ListNode *res;
    res = (ListNode *)malloc(sizeof(ListNode));
    res->dataPtr = (char *)malloc(sizeof(char));
    *(res->dataPtr) = data;
    res->next = next;
    return res;
}
void insertNodeToEndList(List *lst, ListNode *tail)
{
    if (isEmptyList(lst) == true)
        lst->head = lst->tail = tail;
    else
    {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

bool isEmptyList(List *lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

bool isCharLetter(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}
Student unScramble(List lst)
{
    Student stud;
    int nodeIndex = 0;
    int grade = 0;
    int num;
    ListNode *curr;
    curr = lst.head;
    while (curr != NULL)
    {
        if((isCharLetter(*(curr->dataPtr)))) // if char is a letter
        {
          curr = curr->next;
          nodeIndex++;
        }
        else
        {
            num = convertCharToInt(*(curr->dataPtr));
            grade *= 10;
            grade += num;
            curr = removeNodeFromList(&lst, curr, nodeIndex);
        }

    }
    stud.first = lst;
    stud.grade = grade;
    return stud;
}
ListNode* removeNodeFromList(List *lst, ListNode *node, int i)
{
    ListNode * saver = node->next;
    ListNode *before = getListNode(lst, i - 1);
    if (lst->head == lst->tail) // if the list have only one node
    {
        makeEmptyList(lst);
    }
    else if (lst->head == node) // remove the first element of the list
    {
        lst->head = node->next;
    }
    else if (lst->tail == node) // remove the last element of the list
    {
        before->next = NULL;
        lst->tail = before;
    }
    else // remove middle part of the list
    {
        before->next = node->next;
    }
    free(node->dataPtr);
    free(node);
    return saver;
}

ListNode *getListNode(List *lst, int i)
{
    ListNode *curr;
    curr = lst->head;
    while (curr != NULL && i > 0)
    {
        curr = curr->next;
        i--;
    }
    return curr;
}
int convertCharToInt(char ch)
{
    return (ch - '0');
}
void freeList(List * lst)
{
        ListNode * temp;

        while (lst->head != NULL)
        {
            temp = lst->head;
            lst->head = lst->head->next;
            free(temp->dataPtr);
            free(temp);
        }

}
void printStudent(Student *stud)
{
    printf("First name: ");
    printList(&(stud->first));
    printf("Grade: ");
    printf("%d\n", stud->grade);
}
void printList(List *list)
{
    ListNode *curr;
    curr = list->head;
    while (curr != NULL)
    {
        printf("%c", *(curr->dataPtr));
        curr = curr->next;
    }
    printf("\n");
}