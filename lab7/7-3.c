/*
 Program Create Binary Expression Tree From POSTFIX

 Input :
 AB+C*

 Expression :
 (A+B)*C

 Show :
 1. Tree Structure
 2. PreOrder Traversal
 3. InOrder Traversal
 4. PostOrder Traversal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MaxNode 100

typedef struct Node
{
    char info;
    struct Node *lson;
    struct Node *rson;
}Node;

Node *stack[MaxNode];
int top=-1;

void Push(Node *p) {
    stack[++top]=p;
}

Node *Pop() {
    return stack[top--];
}

Node *Allocate(char ch) {
    Node *p;
    p=(Node*)malloc(sizeof(Node));
    p->info=ch;
    p->lson=NULL;
    p->rson=NULL;
    return p;
}

Node *CreateExpressionTree(char postfix[]) {
    int i=0;
    char ch;
    while(postfix[i]!='\0') {
        ch=postfix[i];
        if(isalnum(ch)) {
            Push(Allocate(ch));
        }
        else {
            Node *op=Allocate(ch);
            op->rson=Pop();
            op->lson=Pop();
            Push(op);
        }
        i++;
    }
    return Pop();
}

char TreeArray[MaxNode];

void FillArray(Node *root,int index) {
    if(root==NULL) {
        return;
    }
    TreeArray[index]=root->info;
    FillArray(root->lson,index*2);
    FillArray(root->rson,index*2+1);
}

void ShowTree() {
    int level = 1;
    int start, end;
    int j;
    int found;
    while(level <= 5) {
        start = (1 << (level - 1));
        end = (1 << level) - 1;
        found = 0;
        for(j = start; j <= end; j++) {
            if(TreeArray[j] != '\0') {
                found = 1;
                break;
            }
        }
        if(!found) {
            break;
        }
        for(j = start; j <= end; j++) {
            if(TreeArray[j] != '\0') {
                switch(level) {
                    case 1:
                        printf("%40c", TreeArray[j]);
                        break;
                    case 2:
                        if(j == 2)
                            printf("%20c", TreeArray[j]);
                        else
                            printf("%40c", TreeArray[j]);
                        break;
                    case 3:
                        if(j == 4)
                            printf("%10c", TreeArray[j]);
                        else
                            printf("%20c", TreeArray[j]);
                        break;
                    case 4:
                        if(j == 8)
                            printf("%5c", TreeArray[j]);
                        else
                            printf("%10c", TreeArray[j]);
                        break;
                    case 5:
                        if(j == 16)
                            printf("%c", TreeArray[j]);
                        else
                            printf("%5c", TreeArray[j]);
                        break;
                }
            }
        }
        printf("\n");
        level++;
    }
}

void PreOrder(Node *pt) {
    if(pt!=NULL) {
        printf("%c ",pt->info);
        PreOrder(pt->lson);
        PreOrder(pt->rson);
    }
}

void InOrder(Node *pt) {
    if(pt!=NULL) {
        InOrder(pt->lson);
        printf("%c ",pt->info);
        InOrder(pt->rson);
    }
}

void PostOrder(Node *pt) {
    if(pt!=NULL) {
        PostOrder(pt->lson);
        PostOrder(pt->rson);
        printf("%c ",pt->info);
    }
}

int main() {
    char postfix[100];
    Node *T;
    printf("Input Postfix : ");
    scanf("%s",postfix);
    T=CreateExpressionTree(postfix);
    memset(TreeArray,'\0',sizeof(TreeArray));
    FillArray(T,1);
    printf("===TREE EXPRESSION===\n");
    ShowTree();
    printf("\nPRE ORDER TRAVERSAL : ");
    PreOrder(T);
    printf("\nIN ORDER TRAVERSAL  : ");
    InOrder(T);
    printf("\nPOST ORDER TRAVERSAL: ");
    PostOrder(T);
    return 0;
}