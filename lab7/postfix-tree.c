#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100
#define MAXTREE 128

/* Node ของ Binary Tree */
typedef struct Node {
    char data;          // เก็บข้อมูล เช่น A, B, +, -
    struct Node *left;  // ชี้ไป Node ซ้าย
    struct Node *right; // ชี้ไป Node ขวา
} Node;

/* Stack สำหรับเก็บ Node */
Node *stack[MAX];
int top = -1;

/* Array สำหรับเก็บ Tree */
char treeArray[MAXTREE];

/* เพิ่ม Node ลง Stack */
void push(Node *p) {
    if (top == MAX - 1) { // ตรวจสอบ Stack เต็ม
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = p; // เพิ่ม Node และเลื่อน top
}

/* นำ Node ออกจาก Stack */
Node *pop() {
    if (top < 0) {// ถ้า Stack ว่าง
        return NULL;
    }
    return stack[top--]; // คืน Node และลด top
}

/* สร้าง Node ใหม่ */
Node *createNode(char ch) {
    Node *p = malloc(sizeof(Node)); // จองหน่วยความจำ
    if (p == NULL) {// ตรวจสอบการจอง Memory
        printf("Memory Allocation Failed\n");
        exit(1);
    }
    p->data = ch;    // เก็บข้อมูล
    p->left = NULL;  // เริ่มต้นไม่มีลูกซ้าย
    p->right = NULL; // เริ่มต้นไม่มีลูกขวา
    return p; // ส่ง Node กลับ
}

/* สร้าง Expression Tree จาก Postfix */
Node *buildTree(char postfix[]) {
    top = -1; // ล้าง Stack ก่อนเริ่ม
    for (int i = 0; postfix[i]; i++) {// อ่าน Postfix ทีละตัว
        char ch = postfix[i];
        if (isspace(ch)) {// ข้ามช่องว่างและ Enter
            continue;
        }
        if (isalnum(ch)) { // ถ้าเป็น Operand
            push(createNode(ch)); // สร้าง Node แล้ว Push
        } else { // ถ้าเป็น Operator
            Node *right = pop(); // Operand ขวา
            Node *left = pop();  // Operand ซ้าย
            if (left == NULL || right == NULL) {
                printf("Invalid Postfix Expression\n");
                exit(1);
            }
            Node *op = createNode(ch); // สร้าง Node Operator
            op->left = left;   // เชื่อมลูกซ้าย
            op->right = right; // เชื่อมลูกขวา
            push(op); // Push Tree กลับเข้า Stack
        }
    }
    Node *root = pop(); // Node สุดท้ายคือ Root
    if (root == NULL || top != -1) {// ตรวจสอบ Expression
        printf("Invalid Postfix Expression\n");
        exit(1);
    }
    return root; // ส่ง Root กลับ
}

/* นำ Tree มาเก็บใน Array */
void fillArray(Node *root, int i) {
    if (root == NULL || i >= MAXTREE) { // ถ้าไม่มี Node หรือเกินขนาด
        return;
    }
    treeArray[i] = root->data; // เก็บข้อมูลลง Array
    fillArray(root->left, i * 2);      // ลูกซ้าย = 2i
    fillArray(root->right, i * 2 + 1); // ลูกขวา = 2i+1
}

/* แสดงโครงสร้าง Tree */
void showTree() {
    for (int level = 1; level <= 5; level++) {
        int start = 1 << (level - 1); // จุดเริ่มต้นของแต่ละ Level
        int end = (1 << level) - 1;   // จุดสิ้นสุดของแต่ละ Level
        for (int i = start; i <= end; i++) {
            if (treeArray[i] == 0) {// ถ้าไม่มี Node
                continue;
            }
            /* กำหนดระยะห่างเพื่อให้มีลักษณะเป็น Tree */
            if (i == start) {
                printf("%*c", 40 / (1 << (level - 1)), treeArray[i]);
            }
            else {
                printf("%*c", 40 / (1 << (level - 2 > 0 ? level - 2 : 0)), treeArray[i]);
            }
        }
        printf("\n");
    }
}

/* แสดง Preorder : Root -> Left -> Right */
void preorder(Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data); // แสดง Root
    preorder(root->left);      // ไปซ้าย
    preorder(root->right);     // ไปขวา
}
/* แสดง Inorder : Left -> Root -> Right */
void inorder(Node *root) {
    if (root == NULL) {
        return;
    }
    if (!isalnum(root->data)) {// ถ้าเป็น Operator
        printf("(");          // ใส่วงเล็บเปิด
    }
    inorder(root->left);      // ไปซ้าย
    printf("%c", root->data); // แสดง Root
    inorder(root->right);     // ไปขวา
    if (!isalnum(root->data)) {// ถ้าเป็น Operator
        printf(")");          // ใส่วงเล็บปิด
    }
}

/* แสดง Postorder : Left -> Right -> Root */
void postorder(Node *root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);     // ไปซ้าย
    postorder(root->right);    // ไปขวา
    printf("%c ", root->data); // แสดง Root
}

/* ลบ Node ทั้งหมดใน Tree */
void freeTree(Node *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);  // ลบ Subtree ซ้าย
    freeTree(root->right); // ลบ Subtree ขวา
    free(root);            // ลบ Node ปัจจุบัน
}

/* โปรแกรมหลัก */
int main() {
    char postfix[MAX];
    Node *root;

    printf("Enter Postfix : ");
    fgets(postfix, MAX, stdin); // รับ Postfix จากผู้ใช้

    root = buildTree(postfix); // สร้าง Expression Tree

    memset(treeArray, 0, sizeof(treeArray)); // เคลียร์ Array
    fillArray(root, 1);                      // เก็บ Tree เริ่มที่ตำแหน่ง 1

    printf("TREE STRUCTURE\n");
    printf("========================================\n");
    showTree(); // แสดง Tree

    printf("\nPreOrder  : ");
    preorder(root); // แสดง Preorder
    printf("\nInOrder   : ");
    inorder(root); // แสดง Inorder
    printf("\nPostOrder : ");
    postorder(root); // แสดง Postorder
    freeTree(root); // คืน Memory

    return 0; // จบโปรแกรม
}