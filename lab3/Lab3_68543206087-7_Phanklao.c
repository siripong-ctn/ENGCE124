/*==========================================================================
  ENGCE124 โครงสร้างข้อมูลและขั้นตอนวิธี
  ใบงานที่ 3 : โปรแกรม Stack และ Queue (ใช้โค้ดร่วมกัน)

  - Stack : LIFO ใช้ตัวชี้ top  (เริ่มที่ -1 = ว่าง)
  - Queue : FIFO ใช้ตัวชี้ front และ rear (rear เริ่มที่ -1 = ว่าง)
  - เก็บข้อมูลด้วย array ขนาด MAX_SIZE

  หมายเหตุ
   * ชื่อฟังก์ชันบังคับ ตั้งชื่อตามใบงาน
   * ฟังก์ชันที่เพิ่มเอง จะมี comment [เพิ่มเติม] กำกับไว้
==========================================================================*/

#include <stdio.h>

#define MAX_SIZE 5        /* ความจุของ Stack และ Queue */

/* ---------- ตัวแปรของ Stack ---------- */
int stack[MAX_SIZE];      /* array เก็บข้อมูล Stack */
int top = -1;             /* ตำแหน่งบนสุด (Top), -1 = ว่าง */

/* ---------- ตัวแปรของ Queue ---------- */
int queue[MAX_SIZE];      /* array เก็บข้อมูล Queue */
int front = 0;            /* ตำแหน่งหัวคิว */
int rear = -1;            /* ตำแหน่งท้ายคิว, -1 = ว่าง */


/*==========================================================================
  ฟังก์ชันกลางที่ใช้ร่วมกัน
==========================================================================*/

/* [บังคับ] แสดงหัวโปรแกรม (กรอบใหญ่) */
void showProgramHeader(const char title[]) {
    printf("\n========================================\n");
    printf("        %s\n", title);
    printf("========================================\n");
}

/* [บังคับ] แสดงบรรทัดสรุปผลการทำงานว่าสำเร็จหรือไม่สำเร็จ
   หมายเหตุ: เก็บพารามิเตอร์ operation และ value ไว้ตามรูปแบบที่ใบงานกำหนด */
void showOperationResult(const char operation[], int value, int success) {
    if (success == 1) {
        printf("Result    : SUCCESS\n");
    } else {
        printf("Result    : FAILED\n");
    }
}

/* [เพิ่มเติม] รับค่าตัวเลขจากผู้ใช้ พร้อมตรวจสอบว่าเป็นตัวเลขจริง (เงื่อนไขข้อ 9) */
int inputNumber(const char prompt[]) {
    int n;
    int ok;
    printf("%s", prompt);
    ok = scanf("%d", &n);          /* scanf คืนค่า 1 ถ้าอ่านตัวเลขได้ */
    while (ok != 1) {              /* ถ้าผู้ใช้ป้อนไม่ใช่ตัวเลข */
        while (getchar() != '\n') {  /* ล้างตัวอักษรที่ค้างใน buffer */
            ;
        }
        printf("Invalid input, please enter a number.\n");
        printf("%s", prompt);
        ok = scanf("%d", &n);
    }
    return n;
}


/*==========================================================================
  ส่วนของ STACK (LIFO)
==========================================================================*/

/* ตรวจสอบว่า Stack เต็มหรือไม่ */
int isStackFull(void) {
    if (top == MAX_SIZE - 1) {
        return 1;
    } else {
        return 0;
    }
}

/* ตรวจสอบว่า Stack ว่างหรือไม่ */
int isStackEmpty(void) {
    if (top == -1) {
        return 1;
    } else {
        return 0;
    }
}

/* เพิ่มข้อมูลเข้า Stack */
void push(int value) {
    int beforeTop = top;          /* เก็บสถานะก่อนทำงาน */
    int beforeData = top + 1;

    printf("\n");
    printf("Operation : PUSH\n");
    printf("Input     : %d\n", value);

    if (isStackFull() == 1) {     /* Stack เต็ม -> Overflow */
        printf("Push failed: Stack Overflow\n");
        showOperationResult("PUSH", value, 0);
        return;
    }

    top = top + 1;                /* เลื่อน Top ขึ้น 1 */
    stack[top] = value;           /* เก็บข้อมูลลงตำแหน่งบนสุด */

    printf("Before    : Top = %d, Data = %d\n", beforeTop, beforeData);
    printf("After     : Top = %d, Data = %d\n", top, top + 1);
    showOperationResult("PUSH", value, 1);
}

/* นำข้อมูลออกจาก Stack */
int pop(void) {
    int beforeTop = top;
    int beforeData = top + 1;
    int value;

    printf("\n");
    printf("Operation : POP\n");

    if (isStackEmpty() == 1) {    /* Stack ว่าง -> Underflow */
        printf("Pop failed: Stack Underflow\n");
        showOperationResult("POP", 0, 0);
        return -1;
    }

    value = stack[top];           /* อ่านค่าตำแหน่งบนสุด */
    top = top - 1;                /* เลื่อน Top ลง 1 */

    printf("Output    : %d\n", value);
    printf("Before    : Top = %d, Data = %d\n", beforeTop, beforeData);
    printf("After     : Top = %d, Data = %d\n", top, top + 1);
    showOperationResult("POP", value, 1);
    return value;
}

/* แสดงข้อมูลใน Stack จากบนสุดลงล่างสุด */
void showStack(void) {
    int i;

    printf("\n========== STACK STATUS ==========\n");
    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", top + 1);
    printf("Top      : %d\n", top);
    if (isStackEmpty() == 1) {
        printf("Status   : EMPTY\n");
    } else if (isStackFull() == 1) {
        printf("Status   : FULL\n");
    } else {
        printf("Status   : NORMAL\n");
    }
    printf("------------------------------------\n");

    if (isStackEmpty() == 1) {
        printf("Stack is empty.\n");
        printf("------------------------------------\n");
        return;
    }

    for (i = top; i >= 0; i--) {          /* ไล่จากบนสุด (Top) ลงมา index 0 */
        if (i == top) {
            printf("TOP -> [%d]  index %d\n", stack[i], i);
        } else {
            printf("       [%d]  index %d\n", stack[i], i);
        }
    }
    printf("------------------------------------\n");
}

/* ล้างข้อมูลใน Stack */
void clearStack(void) {
    int i;
    for (i = 0; i < MAX_SIZE; i++) {      /* ล้างข้อมูลใน array */
        stack[i] = 0;
    }
    top = -1;
    printf("\nStack cleared.\n");
}


/*==========================================================================
  ส่วนของ QUEUE (FIFO) แบบ Linear Queue
==========================================================================*/

/* ตรวจสอบว่า Queue เต็มหรือไม่ */
int isQueueFull(void) {
    if (rear == MAX_SIZE - 1) {
        return 1;
    } else {
        return 0;
    }
}

/* ตรวจสอบว่า Queue ว่างหรือไม่ */
int isQueueEmpty(void) {
    if (rear < front) {
        return 1;
    } else {
        return 0;
    }
}

/* เพิ่มข้อมูลเข้าท้ายคิว */
void insertQueue(int value) {
    int beforeFront = front;      /* เก็บสถานะก่อนทำงาน */
    int beforeRear = rear;
    int beforeData = rear - front + 1;
    int afterData;

    if (isQueueEmpty() == 1) {
        beforeData = 0;
    }

    printf("\n");
    printf("Operation : INSERT QUEUE\n");
    printf("Input     : %d\n", value);

    if (isQueueFull() == 1) {     /* Queue เต็ม -> Overflow */
        printf("Insert failed: Queue Overflow\n");
        showOperationResult("INSERT QUEUE", value, 0);
        return;
    }

    rear = rear + 1;              /* เลื่อนท้ายคิวขึ้น 1 */
    queue[rear] = value;          /* เก็บข้อมูลลงท้ายคิว */

    afterData = rear - front + 1;
    printf("Before    : Front = %d, Rear = %d, Data = %d\n", beforeFront, beforeRear, beforeData);
    printf("After     : Front = %d, Rear = %d, Data = %d\n", front, rear, afterData);
    showOperationResult("INSERT QUEUE", value, 1);
}

/* นำข้อมูลออกจากหัวคิว */
int deleteQueue(void) {
    int beforeFront = front;
    int beforeRear = rear;
    int beforeData = rear - front + 1;
    int afterData;
    int value;

    if (isQueueEmpty() == 1) {
        beforeData = 0;
    }

    printf("\n");
    printf("Operation : DELETE QUEUE\n");

    if (isQueueEmpty() == 1) {    /* Queue ว่าง -> Underflow */
        printf("Delete failed: Queue Underflow\n");
        showOperationResult("DELETE QUEUE", 0, 0);
        return -1;
    }

    value = queue[front];         /* อ่านค่าหัวคิว */
    front = front + 1;            /* เลื่อนหัวคิวขึ้น 1 */
    if (front > rear) {           /* ถ้าคิวหมด ให้รีเซ็ตกลับค่าเริ่มต้น */
        front = 0;
        rear = -1;
    }

    afterData = rear - front + 1;
    if (isQueueEmpty() == 1) {
        afterData = 0;
    }

    printf("Output    : %d\n", value);
    printf("Before    : Front = %d, Rear = %d, Data = %d\n", beforeFront, beforeRear, beforeData);
    printf("After     : Front = %d, Rear = %d, Data = %d\n", front, rear, afterData);
    showOperationResult("DELETE QUEUE", value, 1);
    return value;
}

/* แสดงข้อมูลใน Queue ให้เห็นตำแหน่ง Front และ Rear ชัดเจน */
void showQueue(void) {
    int i;
    int count = rear - front + 1;

    if (isQueueEmpty() == 1) {
        count = 0;
    }

    printf("\n========== QUEUE STATUS ==========\n");
    printf("Capacity : %d\n", MAX_SIZE);
    printf("Data     : %d\n", count);
    printf("Front    : %d\n", front);
    printf("Rear     : %d\n", rear);
    if (isQueueEmpty() == 1) {
        printf("Status   : EMPTY\n");
    } else if (isQueueFull() == 1) {
        printf("Status   : FULL\n");
    } else {
        printf("Status   : NORMAL\n");
    }
    printf("------------------------------------\n");

    if (isQueueEmpty() == 1) {
        printf("Queue is empty.\n");
        printf("------------------------------------\n");
        return;
    }

    /* แถวหมายเลข index ของ array */
    printf("Index : ");
    for (i = 0; i < MAX_SIZE; i++) {
        printf(" %-4d", i);
    }
    printf("\n");

    /* แถวข้อมูล (ช่องที่ไม่มีข้อมูลแสดง [  ]) */
    printf("Data  : ");
    for (i = 0; i < MAX_SIZE; i++) {
        if (i >= front && i <= rear) {
            printf("[%2d] ", queue[i]);
        } else {
            printf("[  ] ");
        }
    }
    printf("\n");

    /* แถวตัวชี้ F (Front) และ R (Rear) */
    printf("        ");
    for (i = 0; i < MAX_SIZE; i++) {
        if (i == front && i == rear) {
            printf(" FR  ");
        } else if (i == front) {
            printf(" F   ");
        } else if (i == rear) {
            printf(" R   ");
        } else {
            printf("     ");
        }
    }
    printf("\n");
    printf("------------------------------------\n");

    /* ลำดับข้อมูลที่จะถูกนำออก (หัว -> ท้าย) */
    printf("Order : ");
    for (i = front; i <= rear; i++) {
        printf("%d", queue[i]);
        if (i < rear) {
            printf(" -> ");
        }
    }
    printf("\n");
}

/* ล้างข้อมูลใน Queue */
void clearQueue(void) {
    int i;
    for (i = 0; i < MAX_SIZE; i++) {      /* ล้างข้อมูลใน array */
        queue[i] = 0;
    }
    front = 0;
    rear = -1;
    printf("\nQueue cleared.\n");
}


/*==========================================================================
  ส่วนของเมนู
==========================================================================*/

/* เมนูย่อยของ Stack */
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
        printf("------------------------------------\n");
        choice = inputNumber("Select menu: ");

        switch (choice) {
            case 1:
                value = inputNumber("Enter value to push: ");
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
                printf("Invalid menu. Please try again.\n");
        }
    } while (choice != 0);
}

/* เมนูย่อยของ Queue */
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
        printf("------------------------------------\n");
        choice = inputNumber("Select menu: ");

        switch (choice) {
            case 1:
                value = inputNumber("Enter value to insert: ");
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
                printf("Invalid menu. Please try again.\n");
        }
    } while (choice != 0);
}

/* เมนูหลัก */
int main(void) {
    int choice;
    do {
        showProgramHeader("STACK AND QUEUE PROGRAM");
        printf("1. Stack\n");
        printf("2. Queue\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");
        choice = inputNumber("Select menu: ");

        switch (choice) {
            case 1:
                stackMenu();
                break;
            case 2:
                queueMenu();
                break;
            case 0:
                printf("\nExit program. Goodbye!\n");
                break;
            default:
                printf("Invalid menu. Please try again.\n");
        }
    } while (choice != 0);
    return 0;
}
