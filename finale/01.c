#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 5
int command, saveUndo;

typedef struct Student {
    char id[10];
    char name[50];
    float gpa;
} Student;

typedef struct DNode {
    struct Student data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    char type[10];
    Student student;
} Operation;

typedef struct {
    Operation items[MAX_STACK];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Operation op) {
    if (s->top == MAX_STACK - 1) {
        for (int i = 0; i < MAX_STACK - 1; i++) {
            s->items[i] = s->items[i + 1];
        }
        s->top--;
    }
    s->items[++s->top] = op;
}

Operation pop(Stack *s) {
    Operation op;
    strcpy(op.type, "");
    if (!isEmpty(s)) {
        return s->items[s->top--];
    }
    return op;
}

DNode *createNode(Student s) {
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    newNode->data = s;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertSorted(DNode **head, Stack *stack) {
    Student s;
    printf("\nInsertSorted:\n");
    printf("std ID: ");
    scanf("%s", s.id);
    printf("std name: ");
    scanf(" %[^\n]", s.name);
    printf("GPA: ");
    scanf("%f", &s.gpa);

    DNode *newNode = createNode(s);
    if (*head == NULL) {
        *head = newNode;
    } else if (s.gpa > (*head)->data.gpa) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    } else {
        DNode *current = *head;
        while (current->next != NULL && current->next->data.gpa >= s.gpa) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }
    if (saveUndo) {
        Operation op;
        strcpy(op.type, "INSERT");
        op.student = s;
        push(stack, op);
    }
    printf("\nInsert Success\n");
}

void deleteById(DNode **head, Stack *stack) { // Delete by ID
    char id[10];
    printf("Enter std ID to Delete: ");
    scanf("%s", id);

    DNode *current = *head;
    while (current != NULL && strcmp(current->data.id, id) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        printf("\nNot found std ID\n");
    }
    if (saveUndo) {
        Operation op;
        strcpy(op.type, "DELETE");
        op.student = current->data;
        push(stack, op);
    }
    if (current == *head) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    }
    else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }
    free(current);
    printf("\nDelete Success\n");
}

void printForward(DNode *head) {
    printf("\nForward: ");
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    while (head != NULL) {
        printf("[%s|%s|%.2f] -> ",
               head->data.id,
               head->data.name,
               head->data.gpa);
        head = head->next;
    }
    printf("NULL\n");
}

void printBackward(DNode *head) {
    printf("\nBackward: ");
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    DNode *tail = head;
    while (tail->next != NULL)
        tail = tail->next;
    while (tail != NULL) {
        printf("[%s|%s|%.2f] -> ",
               tail->data.id,
               tail->data.name,
               tail->data.gpa);
        tail = tail->prev;
    }
    printf("NULL\n");
}

void undo(DNode **head, Stack *stack) {
    if (isEmpty(stack)) {
        printf("No list to Undo\n");
        return;
    }
    Operation op = pop(stack);
    if (strcmp(op.type, "INSERT") == 0) {
        deleteById(head, stack);
        printf("Undo: Insert %s\n", op.student.id);
    } else if (strcmp(op.type, "DELETE") == 0) {
        insertSorted(head, stack);
        printf("Undo: Backup %s\n", op.student.id);
    }
}

int main() {
    DNode *head = NULL;
    Stack undoStack;
    initStack(&undoStack);
    do {
        printf("\nStart Program\n");
        printf("1: Add std\n");
        printf("2: Del std\n");
        printf("3: Print std Forword\n");
        printf("4: Print std Backword\n");
        printf("5: Undo\n");
        printf("0: Close Program\n");
        printf("Choose MENU: ");
        scanf("%d", &command);
        switch (command) {
        case 1:
            insertSorted(&head, &undoStack);
            break;
        case 2:
            deleteById(&head, &undoStack);
            break;
        case 3:
            printForward(head);
            break;
        case 4:
            printBackward(head);
            break;
        case 5:
            undo(&head, &undoStack);
            break;
        case 0:
            printf("Close Program\n");
            break;
        default:
            printf("Invalid command\n");
            break;
        }
    } while (command != 0);

    return 0;
}