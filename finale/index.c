#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK 5

typedef struct {
    char id[10];
    char name[50];
    float gpa;
} Student;

typedef struct DNode {
    Student data;
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef struct {
    char type[10]; // INSERT or DELETE
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
        // Delete oldest list
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

void insertSorted(DNode **head, Student s, Stack *stack, int saveUndo) { // Insert sort GPA Max to Min
    DNode *newNode = createNode(s);

    if (*head == NULL) {
        *head = newNode;
    }
    else if (s.gpa > (*head)->data.gpa) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
    else {
        DNode *current = *head;
        while (current->next != NULL &&
               current->next->data.gpa >= s.gpa) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != NULL)
            current->next->prev = newNode;
        current->next = newNode;
    }
    if (saveUndo) {
        Operation op;
        strcpy(op.type, "INSERT");
        op.student = s;
        push(stack, op);
    }
}

int deleteById(DNode **head, char id[], Stack *stack, int saveUndo) { // Delete by ID

    DNode *current = *head;
    while (current != NULL &&
           strcmp(current->data.id, id) != 0) {
        current = current->next;
    }
    if (current == NULL) {
        return 0;
    }
    if (saveUndo) {
        Operation op;
        strcpy(op.type, "DELETE");
        op.student = current->data;
        push(stack, op);
    }
    if (current == *head) {
        *head = current->next;

        if (*head != NULL)
            (*head)->prev = NULL;
    }
    else {
        current->prev->next = current->next;
        if (current->next != NULL)
            current->next->prev = current->prev;
    }
    free(current);
    return 1;
}

void printForward(DNode *head) { // Display First to End
    printf("\nForward:\n");
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    while (head != NULL) {
        printf("[%s | %s | %.2f] -> ",
               head->data.id,
               head->data.name,
               head->data.gpa);
        head = head->next;
    }
    printf("NULL\n");
}

void printBackward(DNode *head) { // Display End to Front
    printf("\nBackward:\n");
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    DNode *tail = head;
    while (tail->next != NULL)
        tail = tail->next;
    while (tail != NULL) {
        printf("[%s | %s | %.2f] -> ",
               tail->data.id,
               tail->data.name,
               tail->data.gpa);
        tail = tail->prev;
    }
    printf("NULL\n");
}

void undo(DNode **head, Stack *stack) { // Undo
    if (isEmpty(stack)) {
        printf("No list to Undo\n");
        return;
    }
    Operation op = pop(stack);
    if (strcmp(op.type, "INSERT") == 0) {
        deleteById(head, op.student.id, stack, 0);
        printf("Undo: Insert %s\n",
               op.student.id);
    }
    else if (strcmp(op.type, "DELETE") == 0) {
        insertSorted(head, op.student, stack, 0);
        printf("Undo: Backup %s\n",
               op.student.id);
    }
}

int main() {
    DNode *head = NULL;
    Stack undoStack;
    initStack(&undoStack);
    int choice;
    do {
        printf("\n===== STUDENT MANAGEMENT =====\n");
        printf("1. Insert std\n");
        printf("2. Delete std\n");
        printf("3. Display (Forward)\n");
        printf("4. Display (Backward)\n");
        printf("5. Undo\n");
        printf("0. Exit\n");
        printf("Menu: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter 0-5\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }

        switch (choice) {
            case 1: {
                Student s;

                printf("std ID: ");
                scanf("%s", s.id);

                printf("std name: ");
                scanf(" %[^\n]", s.name);

                printf("GPA: ");
                scanf("%f", &s.gpa);

                insertSorted(&head, s, &undoStack, 1);

                printf("Insert Success!\n");
                break;
            }

            case 2: {
                char id[10];

                printf("Enter ID want to delete: ");
                scanf("%s", id);

                if (deleteById(&head, id,
                               &undoStack, 1))
                    printf("Delete Success!\n");
                else
                    printf("No Result std!\n");

                break;
            }

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
                printf("Exit Program\n");
                break;

            default:
                printf("Menu invalid\n");
        }

    } while (choice != 0);

    return 0;
}