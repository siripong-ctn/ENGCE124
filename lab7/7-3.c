#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNODE 100
char postfix[80] = {"862*-"};

typedef struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
}Node;

/* ================= STACK ================= */

Node *stack[MAXNODE];
int top = -1;

void push(Node *p)
{
    stack[++top] = p;
}

Node *pop()
{
    return stack[top--];
}

/* ================= CREATE NODE ================= */

Node *newNode(char ch)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->data = ch;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/* ================= BUILD TREE ================= */

Node *buildTree(char postfix[])
{
    int i = 0;
    while(postfix[i] != '\0')
    {
        char ch = postfix[i];
        if(isalnum(ch))
        {
            push(newNode(ch));
        }
        else
        {
            Node *op = newNode(ch);
            op->right = pop();
            op->left = pop();
            push(op);
        }
        i++;
    }
    return pop();
}

/* ================= ARRAY FOR SHOW TREE ================= */

char treeArray[MAXNODE];

/* แปลง Pointer Tree -> Array */

void FillArray(Node *root,int index)
{
    if(root == NULL) {
        return;
    }
    treeArray[index] = root->data;
    FillArray(root->left,index*2);
    FillArray(root->right,index*2+1);
}

/* ================= SHOW TREE ================= */

void ShowTree()
{
    int level,start,end,j;
    level = 1;
    j = 1;
    printf("\n");
    while(j < MAXNODE && treeArray[j] != '\0')
    {
        start = (1 << (level-1));
        end   = (1 << level) - 1;
        for(j=start;j<=end;j++)
        {
            if(treeArray[j] != '\0')
            {
                switch(level)
                {
                    case 1 :
                        printf("%40c",treeArray[j]);
                        break;
                    case 2 :
                        if(j==2) {
                            printf("%20c",treeArray[j]);
                        } else {
                            printf("%40c",treeArray[j]);
                        }
                        break;
                    case 3 :
                        if(j==4) {
                            printf("%10c",treeArray[j]);
                        } else {
                            printf("%20c",treeArray[j]); 
                        } 
                        break;
                    case 4 :
                        if(j==8) {
                            printf("%5c",treeArray[j]);
                        } else {
                            printf("%10c",treeArray[j]); 
                        } 
                        break;
                    case 5 :
                        if(j==16) {
                            printf("%c",treeArray[j]);
                        } else {
                            printf("%5c",treeArray[j]); 
                        } 
                        break;
                }
            }
        }
        printf("\n");
        level++;
    }
}

/* ================= TRAVERSAL ================= */

void PreOrder(Node *root)
{
    if(root != NULL)
    {
        printf(" %c",root->data);
        PreOrder(root->left);
        PreOrder(root->right);
    }
}

void InOrder(Node *root)
{
    if(root != NULL)
    {
        InOrder(root->left);
        printf(" %c",root->data);
        InOrder(root->right);
    }
}

void PostOrder(Node *root)
{
    if(root != NULL)
    {
        PostOrder(root->left);
        PostOrder(root->right);
        printf(" %c",root->data);
    }
}

/* ================= MAIN ================= */

int main()
{
    char menu=' ';
    Node *T;
    T = buildTree(postfix);
    memset(treeArray,'\0',sizeof(treeArray));
    FillArray(T,1);
    while(menu != 'E' && menu != 'e') {
        printf("\nPROGRAM TREE (POSTFIX POINTER)");
        printf("\n==================================");
        ShowTree();
        printf("\nMENU => P:PreOrder I:InOrder O:PostOrder E:Exit");
        printf("\n--------------------------------------------------\n");
        scanf(" %c",&menu);
        switch(menu) {
            case 'P':
                printf("\nPRE ORDER TRAVERSAL : ");
                PreOrder(T);
                printf("\n");
                break;
            case 'I':
                printf("\nIN ORDER TRAVERSAL : ");
                InOrder(T);
                printf("\n");
                break;
            case 'O':
                printf("\nPOST ORDER TRAVERSAL : ");
                PostOrder(T);
                printf("\n");
                break;
        }
    }
    return 0;
}