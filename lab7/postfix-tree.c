#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define SEQ_SIZE 128

typedef struct Node
{
    char info;
    struct Node *lson;
    struct Node *rson;
} Node;

Node *stack[MAX];
int top = -1;

/* Create Node */
Node *CreateNode(char ch) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->info = ch;
    p->lson = NULL;
    p->rson = NULL;
    return p;
}

/* Check Operator */
int IsOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

/* Push */
void Push(Node *p) {
    if (top >= MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = p;
}

/* Pop */
Node *Pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

/* Create Expression Tree */
Node *CreateTree(char postfix[]) {
    int i;
    char ch;
    Node *left, *right, *p;
    top = -1;
    for (i = 0; postfix[i] != '\0'; i++) {
        ch = postfix[i];
        if (!IsOperator(ch)) { // Check is ch a Operand
            Push(CreateNode(ch)); // Create new node and Push into stack
        } else { // Check is ch a Operator
            if (top < 1) { // Operator must has Operand at least 2 stack
                printf("Invalid Postfix Expression\n");
                exit(1);
            }
            right = Pop(); // Get Operand top pop right
            left = Pop(); // Get Operand top-1 pop left
            p = CreateNode(ch); // Create Node Operator
            p->lson = left; // Node Operator lson link to left
            p->rson = right; // Node Operator rson link to right
            Push(p); // Push Node P into stack
        }
    }
    if (top != 0) { // When end for() must have only 1 tree
        printf("Invalid Postfix Expression\n");
        exit(1);
    }
    return Pop();
}

/* Tree Height */
int Height(Node *p) {
    int lh, rh; // Store height tree into lh and rh
    if (p == NULL) { // If tree has no Node 
        return 0; // Height = 0
    }
    lh = Height(p->lson); // Get Height from Subtree left
    rh = Height(p->rson); // Get Height from Subtree right
    return (lh > rh ? lh : rh) + 1; // Get Hieghtest+1 for Node current
}

/* Convert Pointer Tree to Sequence */
void MakeSequence(Node *p, Node *seq[], int pos) {
    if (p == NULL || pos >= SEQ_SIZE) { // Stop when Node is NULL OR position >= SEQ_SIZE
        return;
    }
    seq[pos] = p;
    MakeSequence(p->lson, seq, pos * 2); // Store Node lson into Array
    MakeSequence(p->rson, seq, pos * 2 + 1); // Store Node rson into Array
}

/* Show Tree Vertically */
void ShowTree(Node *T) {
    Node *seq[SEQ_SIZE] = {NULL}; // Create Array store Node and set NULL

    int h;
    int level;
    int start, end;
    int j;
    int leftPadding;
    int betweenPadding;

    MakeSequence(T, seq, 1); // Convert Tree into Sequence

    h = Height(T); // Store Hight T into h

    for (level = 1; level <= h; level++) { // for level to h
    
        // If level = 1, h = 2 (AB+)
        start = 1 << (level - 1); // Find first position from every level 
        // start = 1 << (1 - 1);
        // start = 1 << 0;
        // start = 1;
        end   = (1 << level) - 1; // Find last position from every level
        // end = (1 << 1) - 1;
        // end = 2 - 1;
        // end = 1;

        leftPadding    = (1 << (h - level + 1)) - 1; // Calculate space from left screen for Center Root
        // leftPadding = (1 << (2 - 1 + 1)) - 1;
        // leftPadding = (1 << 2) - 1;
        // leftPadding = 4 - 1;
        // leftPadding = 3;
        betweenPadding = (1 << (h - level + 2)) - 1; // Calculare space between Node
        // betweenPadding = (1 << (2 - 1 + 2)) - 1;
        // betweenPadding = (1 << 3) - 1;
        // betweenPadding = 8 - 1;
        // betweenPadding = 7;

        printf("%*s", leftPadding, ""); // Space before printf First Node

        for (j = start; j <= end; j++) {
            if (seq[j] != NULL) // If has Node printf data
                printf("%c", seq[j]->info);
            else // If not printf space for safe position
                printf(" ");
            if (j != end) // Make space between Node in same level
                printf("%*s", betweenPadding, "");
        }

        printf("\n"); // New line when end of level
    }
}

/* PreOrder Traversal R->TL->TR */
void PreOrder(Node *p) {
    if (p != NULL) { // p = B
        printf(" %c", p->info); 
        PreOrder(p->lson);
        PreOrder(p->rson);
    }
}

/* InOrder Traversal TL->R->TR */
void InOrder(Node *p) {
    if (p != NULL) {
        InOrder(p->lson);
        printf(" %c", p->info);
        InOrder(p->rson);
    }
}

/* PostOrder Traversal TL->TR->R*/
void PostOrder(Node *p) {
    if (p != NULL) { // p = B
        PostOrder(p->lson);
        PostOrder(p->rson);
        printf(" %c", p->info);
    }
}

/* Free Memory */
void FreeTree(Node *p) {
    if (p != NULL) { // p = A
        FreeTree(p->lson);
        FreeTree(p->rson);
        free(p);
    }
}

/* Main */
int main() {
    char postfix[MAX];
    Node *T;
    printf("Enter Postfix : ");

    scanf("%s",&postfix);

    T = CreateTree(postfix);

    printf("=====================================\n");
    printf("TREE STRUCTURE\n");
    printf("=====================================\n");

    ShowTree(T);

    printf("=====================================\n");
    printf("PRE ORDER  : ");
    PreOrder(T);
    printf("\nIN ORDER   : ");
    InOrder(T);
    printf("\nPOST ORDER : ");
    PostOrder(T);
    printf("\n=====================================\n");
    FreeTree(T);

    return 0;
}