#include <stdio.h>

#define MAX_SIZE 5

/* =======================
   Global Data
======================= */

int stack[MAX_SIZE];
int top = -1; //*1

int queue[MAX_SIZE];
int front = 0;
int rear = -1;
int queueCount = 0;

/* =======================
   Shared Functions
======================= */

void showProgramHeader(const char title[]) {
    printf("\n========== %s ==========\n",title);
}

void clearArray(int arr[], int size) {
    int i;
    for(i=0;i<size;i++) {
        arr[i] = 0;
    }
}

void showOperationResult (
    const char operation[],
    const char detail[],
    const char before[],
    const char after[],int success) {

    printf("\nOperation : %s\n", operation);
    printf("%s\n", detail);
    printf("Before    : %s\n", before);
    printf("After     : %s\n", after);

    if(success) {
        printf("Result    : SUCCESS\n");
    } else {
        printf("Result    : FAILED\n");
    }
}

/* =======================
   Stack Functions
======================= */

int isStackFull(void) {
    return (top == MAX_SIZE - 1);
}

int isStackEmpty(void) {
    return (top == -1);
}

void push(int value) {
    char before[100];
    char after[100];
    char detail[100];

    sprintf(before,"Top = %d, Data = %d",top, top + 1);

    if(isStackFull()) {
        printf("\nPush failed: Stack Overflow\n");
        return;
    }

    top++;
    stack[top] = value;

    sprintf(after,"Top = %d, Data = %d", top, top + 1);
    sprintf(detail,"Input     : %d", value);

    showOperationResult(
        "PUSH",
        detail,
        before,
        after,
        1
    );
}

int pop(void) {
    int value;

    char before[100];
    char after[100];
    char detail[100];

    sprintf(before,"Top = %d, Data = %d", top, top + 1);

    if(isStackEmpty()) {
        printf("\nPop failed: Stack Underflow\n");
        return -9999;
    }

    value = stack[top];
    stack[top] = 0;
    top--;

    sprintf(after,"Top = %d, Data = %d",top,top + 1);
    sprintf(detail,"Output    : %d",value);

    showOperationResult("POP",detail,before,after,1);
    return value;
}

void clearStack(void) {
    clearArray(stack, MAX_SIZE);
    top = -1;

    printf("\nStack cleared successfully.\n");
}

void showStack(void) {
    int i;

    showProgramHeader("STACK STATUS");

    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", top + 1);
    printf("Top      : %d\n", top);

    if(isStackEmpty()) {
        printf("Status   : EMPTY\n");
        printf("----------------------------------\n");
        printf("Stack is empty.\n");
        printf("----------------------------------\n");
        return;
    }

    printf("Status   : NORMAL\n");
    printf("----------------------------------\n");

    for(i=top;i>=0;i--) {
        if(i==top) {
            printf("TOP -> [%d] index %d\n",stack[i], i);
        } else {
            printf("       [%d] index %d\n",stack[i], i);
        }
    }
    printf("----------------------------------\n");
}

/* =======================
   Queue Functions
======================= */

int isQueueFull(void) {
    return (queueCount == MAX_SIZE);
}

int isQueueEmpty(void) {
    return (queueCount == 0);
}

void insertQueue(int value) {
    char before[100];
    char after[100];
    char detail[100];

    sprintf(before,"Front = %d, Rear = %d, Data = %d",front,rear,queueCount);

    if(isQueueFull()) {
        printf("\nInsert failed: Queue Overflow\n");
        return;
    }

    rear++;
    queue[rear] = value;
    queueCount++;

    sprintf(after,"Front = %d, Rear = %d, Data = %d",front,rear,queueCount);
    sprintf(detail,"Input     : %d",value);

    showOperationResult("INSERT QUEUE",detail,before,after,1);
}

int deleteQueue(void) {
    int value;

    char before[100];
    char after[100];
    char detail[100];

    sprintf(before,"Front = %d, Rear = %d, Data = %d",front,rear,queueCount);

    if(isQueueEmpty()) {
        printf("\nDelete failed: Queue Underflow\n");
        return -9999;
    }

    value = queue[front];
    queue[front] = 0;
    front++;
    queueCount--;

    if(queueCount == 0) {
        front = 0;
        rear = -1;
    }

    sprintf(after,"Front = %d, Rear = %d, Data = %d",front,rear,queueCount);
    sprintf(detail,"Output    : %d",value);
    showOperationResult("DELETE QUEUE",detail,before,after,1);

    return value;
}

void clearQueue(void) {
    clearArray(queue, MAX_SIZE);

    front = 0;
    rear = -1;
    queueCount = 0;

    printf("\nQueue cleared successfully.\n");
}

void showQueue(void) {
    int i;
    showProgramHeader("QUEUE STATUS");

    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", queueCount);
    printf("Front    : %d\n", front);
    printf("Rear     : %d\n", rear);

    if(isQueueEmpty()) {
        printf("Status   : EMPTY\n");
        printf("------------------------------------\n");
        printf("Queue is empty.\n");
        printf("------------------------------------\n");
        return;
    }

    printf("Status   : NORMAL\n");
    printf("------------------------------------\n");
    printf("Index : ");

    for(i=0;i<MAX_SIZE;i++) {
        printf(" %3d ", i);
    }

    printf("\n");
    printf("Data  : ");

    for(i=0;i<MAX_SIZE;i++) {
        if(queue[i]==0) {
            printf("[ ]  ");
        } else {
            printf("[%d] ", queue[i]);
        }
    }

    printf("\n");
    printf("        ");

    for(i = 0 ; i < MAX_SIZE ; i++) {
        if(i == front && i == rear) {
            printf("FR   ");
        } else if(i == front) {
            printf("  F  ");
        } else if(i == rear) {
            printf("  R  ");
        } else {
            printf("     ");
        }
    }

    printf("\n");
    printf("Order : ");

    for(i=front;i<=rear;i++) {
        printf("%d", queue[i]);
        if(i<rear) {
            printf(" -> ");
        }
    }

    printf("\n");
    printf("------------------------------------\n");
}

/* =======================
   Menu
======================= */

void stackMenu(void) {
    int choice;
    int value;

    do {
        printf("\n========== STACK MENU ==========\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Show Stack\n");
        printf("4. Clear Stack\n");
        printf("0. Back to Main Menu\n");
        printf("--------------------------------\n");

        printf("Select menu : ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                printf("Input value : ");
                scanf("%d",&value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                showStack();
                break;
            case 4:
                clearStack();
                break;
            case 0:
                break;
            default:
                printf("\nInvalid menu.\n");
        }
    } while(choice!=0);
}

void queueMenu(void) {
    int choice;
    int value;

    do {
        printf("\n========== QUEUE MENU ==========\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Show Queue\n");
        printf("4. Clear Queue\n");
        printf("0. Back to Main Menu\n");
        printf("--------------------------------\n");

        printf("Select menu : ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                printf("Input value : ");
                scanf("%d",&value);
                insertQueue(value);
                break;
            case 2:
                deleteQueue();
                break;
            case 3:
                showQueue();
                break;
            case 4:
                clearQueue();
                break;
            case 0:
                break;
            default:
                printf("\nInvalid menu.\n");
        }

    } while(choice!=0);
}

int main(void) {
    int choice;

    do {
        printf("\n========================================\n");
        printf("      STACK AND QUEUE PROGRAM\n");
        printf("========================================\n");
        printf("1. Stack\n");
        printf("2. Queue\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");

        printf("Select menu : ");
        scanf("%d",&choice);

        switch(choice) {
            case 1:
                stackMenu();
                break;
            case 2:
                queueMenu();
                break;
            case 0:
                break;
            default:
                printf("\nInvalid menu.\n");
        }
    } while(choice!=0);

    return 0;
}