#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100
#define MAXTREE 32

/*==================================
  Structure of Tree Node
==================================*/
typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
} Node;

/*==================================
  Stack
==================================*/
Node *stack[MAX];
int top = -1;

/*==================================
  Array Representation For ShowTree
==================================*/
char treeArray[MAXTREE];

/*==================================
  Push
==================================*/
void push(Node *p)
{
    if(top < MAX - 1)
    {
        stack[++top] = p;
    }
}

/*==================================
  Pop
==================================*/
Node *pop()
{
    if(top < 0)
        return NULL;

    return stack[top--];
}

/*==================================
  Create Node
==================================*/
Node *createNode(char ch)
{
    Node *newNode;

    newNode = (Node *)malloc(sizeof(Node));

    newNode->data = ch;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

/*==================================
  Build Expression Tree
==================================*/
Node *buildTree(char postfix[])
{
    int i;

    for(i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if(ch == ' ')
            continue;

        if(isalnum(ch))
        {
            push(createNode(ch));
        }
        else
        {
            Node *right = pop();
            Node *left = pop();

            Node *op = createNode(ch);

            op->left = left;
            op->right = right;

            push(op);
        }
    }

    return pop();
}

/*==================================
  Tree -> Array
==================================*/
void fillArray(Node *root, int index)
{
    if(root == NULL)
        return;

    if(index >= MAXTREE)
        return;

    treeArray[index] = root->data;

    fillArray(root->left, index * 2);
    fillArray(root->right, index * 2 + 1);
}

/*==================================
  Show Tree (Same Style as Document)
==================================*/
void showTree()
{
    int j, level, start, ends;

    j = 1;
    level = 1;

    printf("\n");

    while(level <= 5)
    {
        start = (int)pow(2, level) / 2;
        ends = (int)pow(2, level) - 1;

        for(j = start; j <= ends; j++)
        {
            if(treeArray[j] != 0)
            {
                switch(level)
                {
                    case 1:
                        printf("%40c", treeArray[j]);
                        break;

                    case 2:
                        if(j == 2)
                            printf("%20c", treeArray[j]);
                        else
                            printf("%40c", treeArray[j]);
                        break;

                    case 3:
                        if(j == 4)
                            printf("%10c", treeArray[j]);
                        else
                            printf("%20c", treeArray[j]);
                        break;

                    case 4:
                        if(j == 8)
                            printf("%5c", treeArray[j]);
                        else
                            printf("%10c", treeArray[j]);
                        break;

                    case 5:
                        if(j == 16)
                            printf("%c", treeArray[j]);
                        else
                            printf("%5c", treeArray[j]);
                        break;
                }
            }
        }
        printf("\n");
        level++;
    }
}

/*==================================
  PreOrder
==================================*/
void preorder(Node *root)
{
    if(root != NULL)
    {
        printf("%c ", root->data);

        preorder(root->left);
        preorder(root->right);
    }
}

/*==================================
  InOrder
==================================*/
void inorder(Node *root)
{
    if(root != NULL)
    {
        inorder(root->left);

        printf("%c ", root->data);

        inorder(root->right);
    }
}

/*==================================
  PostOrder
==================================*/
void postorder(Node *root)
{
    if(root != NULL)
    {
        postorder(root->left);
        postorder(root->right);

        printf("%c ", root->data);
    }
}

/*==================================
  Main
==================================*/
int main()
{
    char postfix[MAX];
    Node *root;

    printf("========================================\n");
    printf(" Postfix To Binary Expression Tree\n");
    printf("========================================\n");

    printf("Enter Postfix : ");
    scanf("%99s", postfix);

    root = buildTree(postfix);

    memset(treeArray, 0, sizeof(treeArray));
    fillArray(root, 1);

    printf("\n");
    printf("TREE STRUCTURE\n");
    printf("========================================\n");

    showTree();

    printf("PreOrder  : ");
    preorder(root);

    printf("\n");

    printf("InOrder   : ");
    inorder(root);

    printf("\n");

    printf("PostOrder : ");
    postorder(root);

    printf("\n");

    return 0;
}