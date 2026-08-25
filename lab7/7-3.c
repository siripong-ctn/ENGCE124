#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100
#define MAXTREE 128

/*==================================
  Tree Node
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
  Tree Array
==================================*/
char treeArray[MAXTREE];

/*==================================
  Push
==================================*/
void push(Node *p)
{
    if(top >= MAX - 1)
    {
        printf("Error : Stack Overflow\n");
        exit(1);
    }

    stack[++top] = p;
}

/*==================================
  Pop
==================================*/
Node *pop()
{
    if(top < 0)
    {
        return NULL;
    }

    return stack[top--];
}

/*==================================
  Create Node
==================================*/
Node *createNode(char ch)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Memory Allocation Failed\n");
        exit(1);
    }

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

    top = -1;

    for(i = 0; postfix[i] != '\0'; i++)
    {
        char ch = postfix[i];

        if(ch == ' ' || ch == '\n')
            continue;

        if(isalnum(ch))
        {
            push(createNode(ch));
        }
        else
        {
            Node *right = pop();
            Node *left = pop();

            if(left == NULL || right == NULL)
            {
                printf("Invalid Postfix Expression\n");
                exit(1);
            }

            Node *op = createNode(ch);

            op->left = left;
            op->right = right;

            push(op);
        }
    }

    Node *root = pop();

    if(root == NULL || top != -1)
    {
        printf("Invalid Postfix Expression\n");
        exit(1);
    }

    return root;
}

/*==================================
  Tree To Array
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
  Display Tree
==================================*/
void showTree()
{
    int level, j;
    int start, end;

    printf("\n");

    for(level = 1; level <= 5; level++)
    {
        start = (int)pow(2, level - 1);
        end   = (int)pow(2, level) - 1;

        for(j = start; j <= end; j++)
        {
            if(treeArray[j] == 0)
                continue;

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

        printf("\n");
    }
}

/*==================================
  PreOrder
==================================*/
void preorder(Node *root)
{
    if(root == NULL)
        return;

    printf("%c ", root->data);

    preorder(root->left);
    preorder(root->right);
}

/*==================================
  InOrder (with parentheses)
==================================*/
void inorder(Node *root)
{
    if(root == NULL)
        return;

    if(!isalnum(root->data))
        printf("(");

    inorder(root->left);

    printf("%c", root->data);

    inorder(root->right);

    if(!isalnum(root->data))
        printf(")");
}

/*==================================
  PostOrder
==================================*/
void postorder(Node *root)
{
    if(root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);

    printf("%c ", root->data);
}

/*==================================
  Free Tree
==================================*/
void freeTree(Node *root)
{
    if(root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
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
    fgets(postfix, sizeof(postfix), stdin);

    root = buildTree(postfix);

    memset(treeArray, 0, sizeof(treeArray));
    fillArray(root, 1);

    printf("\nTREE STRUCTURE\n");
    printf("========================================\n");

    showTree();

    printf("\nPreOrder  : ");
    preorder(root);

    printf("\n");

    printf("InOrder   : ");
    inorder(root);

    printf("\n");

    printf("PostOrder : ");
    postorder(root);

    printf("\n");

    freeTree(root);

    return 0;
}