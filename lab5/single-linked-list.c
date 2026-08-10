/* Program create SINGLY LINKED LIST by...
1. Create Node N Nodes
2. Can Insert node after data as defined
3. Can Delete node after data as defined
4. Show address of Node and LINK
*/
#include <stdio.h>  //use printf
#include <conio.h>  //use getch
#include <stdlib.h> //use molloc
typedef struct Node         // Declare structure of node
{
    int info;
    struct Node *link;
} Node;
struct Node *H, *H1, *p, *q; // Declare pointer node
int i, j, k, n, data;
char ch;
Node *Allocate() // Allocate 1 node from storage pool
{
    struct Node *temp;
    temp = (Node *)malloc(sizeof(Node)); // Allocate node by size declare
    return (temp);
}
void CreateNNode(int n) // Create N Node put data and link it
{
    int i, temp;
    H = NULL;
    H1 = NULL;
    for (i = 1; i <= n; i++) // Count N Node
    {
        p = Allocate();         // Allocate Node
        temp = 1 + rand() % 99; // random difference number 1..99
        p->info = temp;         // Put random data in to node
        if (i == 1)
            H = p; // Set H point to first node
        else
            H1->link = p; // Link first node to second node
        H1 = p;           // Let H1 point to last node
        H1->link = NULL;  // Set link of H1 to NULL
    }
}
void ShowAllNode()
{
    printf("H = %x\n", H); // Display address of pointer H
    p = H;                 // Set start point of p pointer
    i = 1;                 // set start value of counter
    while (p != NULL)      // While if NOT NULL
    {
        printf("%d) %x\t", i, p);       // Show COUNTER and POINTER
        printf("INFO : %d\t", p->info); // Show INFO
        printf("LINK : %x\n", p->link); // Show LINK
        p = p->link;                    // Skip to next node
        i++;                            // Skip Counter
    } // End While
} // Enf Fn.
void InsertAfter(int data1)
{
    int temp; // Temporary variable
    if (H == NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1 = H;            // Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) // if Found
            {
                p = Allocate();             // Allocate one node from storage pool
                printf("\nInsert data : "); // Input data for insert
                scanf("%d", &temp);         // Read from KBD
                p->info = temp;             // Entry temporary data into INFO of node
                p->link = H1->link;         // Change pointer 1st for insert node (FAR)
                H1->link = p; // Change pointer 2nd for insert node (NEAR)
            } // End if
            H1 = H1->link; // Skip H1 to next node
        } // End while
    } // End IF
} // End Fn.
void DeleteAfter(int data1)
{
    int temp; // Temporary variable
    if (H == NULL)
        printf("Linked List have no node!!..\n");
    else
    {
        H1 = H;            // Let H1 point at start node
        while (H1 != NULL) // Search for the data while H1<>NULL
        {
            if (H1->info == data1) // if Found
            {
                if (H1->link == NULL) // If no more node
                    printf("No more node from here,Can't delete it!!!\n");
                else
                {
                    p = H1->link;        // Mark at node for Delete
                    if (p->link == NULL) // If p is last node
                        H1->link = NULL; // Set link of H1 to NULL
                    else
                        H1->link = p->link; // If not set link of H1 point same address of p
                        free(p); // Free node to storage pool
                } // End if2
            } // End if1
            H1 = H1->link; // Skip H1 to next node
        } // End while
    } // End IF
} // End Fn.
int main() // MAIN Fn.
{
    n = 10;         // Set amount of node
    CreateNNode(n); // Call Fn. Create N nodes
    printf("PROGRAM SINGLY LINKED LIST \n");
    printf("================================== \n");
    printf("All Data in Linked List \n");
    ShowAllNode(); // Call Fn. Show all node
    ch = ' ';
    while (ch != 'E')
    {
        printf("MENU : [I:Insert D:Delete E:Exit]");
        scanf(" %c", &ch); // GCC/MinGW not working for conio.h -> getch()
        switch (ch)
        {
        case 'I':
            printf("\nInsert After data : "); // Input data for insert after
                scanf("%d", &data);
            InsertAfter(data); // Call Fn. Insert after data
            printf("\nAll Data in Linked List AFTER INSERTED\n");
            ShowAllNode(); // Call Fn. Show all node
            break;
        case 'D':
            printf("\nDelete After data : "); // Input data for Delete after
                scanf("%d", &data);
            DeleteAfter(data); // Call Fn. Delete after data
            printf("\nAll Data in Linked List AFTER DELETED\n");
            ShowAllNode(); // Call Fn. Show all node
            break;
        } // End Switch...case
    } // End While
    return (0);
} // End MAIN 