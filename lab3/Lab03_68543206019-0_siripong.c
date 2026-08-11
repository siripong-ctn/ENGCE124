#include <stdio.h>

#define MAX_SIZE 5 // ขนาด Array ที่ใช้เก็บข้อมูล

/* =======================
   Global Data
======================= */

/*คนที่ 2: โครงสร้างข้อมูลและตัวแปรควบคุม
    นำเสนอประเด็นต่อไปนี้
    Array ที่ใช้เก็บข้อมูล
    การกำหนดความจุด้วย MAX_SIZE
    หน้าที่ของตัวแปร SP หรือ Top
    หน้าที่ของตัวแปร Front
    หน้าที่ของตัวแปร Rear
    ค่าเริ่มต้นของตัวแปรแต่ละตัว
    ควรสาธิต
    แสดงค่าตัวแปรก่อนเพิ่มข้อมูลและหลังเพิ่มข้อมูล 1–2 ค่า พร้อมชี้ตำแหน่ง Index ใน Array
    ข้อกำหนดสำหรับผู้เสนอแต่ละคน

    นักศึกษาแต่ละคนควรปฏิบัติดังนี้

    เปิดโปรแกรมหรือ Source Code ประกอบการอธิบาย
    อธิบายด้วยความเข้าใจ ไม่อ่านจากรายงานทั้งหมด
    แสดงตัวอย่างการทำงานอย่างน้อย 1 กรณี
    ระบุค่าตัวแปรก่อนและหลังการทำงาน
    อธิบายเหตุผลว่าทำไมผลลัพธ์จึงเป็นเช่นนั้น
    ตอบคำถามเกี่ยวกับส่วนที่ตนเองนำเสนอได้
    คำถามสุ่มหลังการนำเสนอ

    ผู้สอนสามารถสุ่มถามสมาชิกคนใดก็ได้ เช่น

    หลังจาก Push แล้ว ค่า Top เปลี่ยนอย่างไร
    เพราะเหตุใด Queue ต้องมีทั้ง Front และ Rear
    ข้อมูลใดถูกนำออกก่อนใน Stack
    ข้อมูลใดถูกนำออกก่อนใน Queue
    เงื่อนไขใดทำให้เกิด Overflow
    เงื่อนไขใดทำให้เกิด Underflow
    ฟังก์ชันใดช่วยลดการเขียนโค้ดซ้ำ
    หากเปลี่ยนขนาดจาก 5 เป็น 10 ต้องแก้ส่วนใด
    เพราะเหตุใดจึงไม่ควรเขียนโปรแกรมทั้งหมดไว้ใน main()
    Push, Pop, Insert และ Delete มี Time Complexity เท่าใด
*/

int stack[MAX_SIZE]; // Array ที่ใช้เก็บข้อมูล stack
int top = -1; // (*1) ใช้ควบคุมตำแหน่งข้อมูลบนสุดของ Stack 
// top = -1 หมายถึง stack มีค่าว่าง
// เมื่อมีการ push ข้อมูล; top++; ค่า top จะเพิ่มขึ้น
// เมื่อมีการ pop ข้อมูล; top--; ค่า top จะลดลง
// ตัวอย่างเช่น 
// Push 10
// Top = 0
// Push 20
// Top = 1

int queue[MAX_SIZE]; // Array ที่ใช้เก็บข้อมูล queue
int front = 0; // ใช้ชี้ตำแหน่งข้อมูลตัวแรกของ Queue ข้อมูลที่ตำแหน่ง Front จะเป็นข้อมูลที่ถูกนำออกก่อนเมื่อใช้คำสั่ง Delete
// 10 -> 20 -> 30
// ↑
// Front
// เมื่อ Delete 10 ออก
// 20 -> 30
// ↑
// Front;
// ค่า Front จะเลื่อนไปยังข้อมูลตัวถัดไป
int rear = -1; // ใช้ชี้ตำแหน่งข้อมูลตัวล่าสุดที่ถูกเพิ่มเข้าสู่ Queue เมื่อมีการ Insert ข้อมูลใหม่
// rear++; ตัวแปร Rear จะเพิ่มค่าขึ้น
// ตัวอย่าง
// 10 -> 20 -> 30
//             ↑
//           Rear
// | ตัวแปร      | ค่าเริ่มต้น | ความหมาย               | 
// | ---------- | ------- | ---------------------- |
// | top        |   -1    | Stack ว่าง              |
// | front      |    0    | ตำแหน่งเริ่มต้นของ Queue   |
// | rear       |   -1    | Queue ว่าง              |
// | queueCount |    0    | ยังไม่มีข้อมูลใน Queue     | 
// 
// ตัวอย่างการทำงานของ Stack
// ก่อนเพิ่มข้อมูล
// top = -1
// Array
// Index :  0   1   2   3   4
// Data  : [ ] [ ] [ ] [ ] [ ]
// Push 10
// Array
// Index :  0    1   2   3   4
// Data  : [10] [ ] [ ] [ ] [ ]
//          ↑
//         Top
// Push 20
// Array
// Index :  0    1   2   3   4
// Data  : [10] [20] [ ] [ ] [ ]
//               ↑
//              Top
// ตัวอย่างการทำงานของ Queue
// ก่อนเพิ่มข้อมูล
// front = 0; rear = -1; queueCount = 0
// Array
// Index :  0   1   2   3   4
// Data  : [ ] [ ] [ ] [ ] [ ]
// Insert 10
// front = 0
// rear = 0
// Index :  0    1   2   3   4
// Data  : [10] [ ] [ ] [ ] [ ]
//          F/R
// Insert 20
// front = 0
// rear = 1
// Index :  0    1   2   3   4
// Data  : [10] [20] [ ] [ ] [ ]
//          F    R
// Insert 30
// front = 0
// rear = 2
// Index :  0    1    2    3   4
// Data  : [10] [20] [30] [ ] [ ]
//          F         R
/* 
Stack ใช้ Array และตัวแปร Top ในการควบคุมตำแหน่งข้อมูล
Queue ใช้ Array และตัวแปร Front กับ Rear ในการควบคุมตำแหน่งข้อมูล
ขนาดของโครงสร้างข้อมูลถูกกำหนดด้วย MAX_SIZE
การแสดงค่า Index ช่วยให้เห็นตำแหน่งการจัดเก็บข้อมูลและการเปลี่ยนแปลงของตัวแปรควบคุมได้อย่างชัดเจน
เมื่อมีการเพิ่มหรือนำข้อมูลออก ค่าของ Top, Front และ Rear จะเปลี่ยนแปลงตามหลักการ LIFO และ FIFO ตามลำดับ
*/


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