/*
Program create array 1-3 dimension in function by..
1. Calculate and Allocate memory
2. Calculate the memoryaddress of array
3. Use point directed in to memory and read/write its
4. Formular useing
Element = (u-l+1)
Element = (u1-l1+1)*(u2-l2+1)
Element = (u1-l1+1)*(u2-l2+1)*(u3-l3+1)
Total_mem = Element*C
Address of Array
A(i) =BA+(i-l)C
A(i,j) =BA+(i-l1)*(u2-l2+1)C+(j-l2)C
A(i,j,k)=BA+(i-l1)*(u2-l2+1)(u3-l3+1)C+(j-l2)(u3-l3+1)C+(k-l3)C
===================================================================*/
#include <stdio.h>  //use printf()
#include <conio.h>  //use getch()
#include <stdlib.h> //use malloc()
#define l 1         // lower Bound
#define u 5         // Upper Bound
#define l1 1        // lower Bound 1
#define u1 3        // Upper Bound 1
#define l2 1        // Lower Bound 2
#define u2 4        // Upper Bound 2
#define l3 1        // Lower Bound 3
#define u3 5        // Upper Bound 3

int *BA1, *BA2, *BA3, *BA4, *p; // Base address of each dimension and moving pointer
int i, j, k;                    // subscript of Array
void Create1DArray()
{                                   // Create Array 1 dimension
    int element, c, total_mem;      // Variable uses
    element = (u - l + 1);          // Calculate element
    c = sizeof(*BA1);               // Calculate Size each block of Array
    total_mem = element * c;        // Calculate Total Size
    BA1 = (int *)malloc(total_mem); // Memory allocate and use  BA1 point its

    printf("Create1DArray");
    printf("\nElement = %d", element);
    printf("\nBytes/Element = %d", c);
    printf("\nTotal Memory = %d x %d = %d", element, c, total_mem);
    printf("\nMemory Start = %p", (void *)BA1);
    printf("\nMemory End = %p", (void *)((char *)BA1 + total_mem));
    printf("\n\n");
}
void A1(int i, int x)
{                      // Put data into Array 1 Dimension
    p = BA1 + (i - l); // Calculate pointer
    *p = x;            // Put data
}
int ReadA1(int i)
{                      // Read data from Array 1 Dimension
    p = BA1 + (i - l); // Calculate pointer
    return (*p);       // Return value in Array
}
//---------------------------------------------------------------------
void Create2DArray()
{
    int element, c, total_mem;
    element = (u1 - l1 + 1) * (u2 - l2 + 1);
    c = sizeof(*BA2);
    total_mem = element * c;
    BA2 = (int *)malloc(total_mem);
    printf("Create2DArray");
    printf("\nElement = %d", element);
    printf("\nBytes/Element = %d", c);
    printf("\nTotal Memory = %d x %d = %d", element, c, total_mem);
    printf("\nMemory Start = %p", (void *)BA2);
    printf("\nMemory End = %p", (void *)((char *)BA2 + total_mem));
    printf("\n\n");
}

//------------------------------------------------------
void A2(int i, int j, int x)
{
    p = BA2 + ((i - l1) * (u2 - l2 + 1) + (j - l2));
    *p = x;
}

//------------------------------------------------------
int ReadA2(int i, int j)
{
    p = BA2 + ((i - l1) * (u2 - l2 + 1) + (j - l2));
    return *p;
}
//------------------------------------------------------
// Create 3D Array (Plane-Row-Column)
//------------------------------------------------------
void Create3DArray()
{
    int element, c, total_mem;
    element = (u1 - l1 + 1) * (u2 - l2 + 1) * (u3 - l3 + 1);
    c = sizeof(*BA3);
    total_mem = element * c;
    BA3 = (int *)malloc(total_mem);
    printf("Create3DArray");
    printf("\nElement = %d", element);
    printf("\nBytes/Element = %d", c);
    printf("\nTotal Memory = %d x %d = %d", element, c, total_mem);
    printf("\nMemory Start = %p", (void *)BA3);
    printf("\nMemory End = %p", (void *)((char *)BA3 + total_mem));
    printf("\n\n");
}

//------------------------------------------------------
void A3(int i, int j, int k, int x)
{
    int offset;
    offset = (i - l1) * (u2 - l2 + 1) * (u3 - l3 + 1) + (j - l2) * (u3 - l3 + 1) + (k - l3);
    p = BA3 + offset;
    *p = x;

    printf("\nA3 Offset = %d", offset);
    printf("\nA3 Address = %p", (void *)p);
}

//------------------------------------------------------
int ReadA3(int i, int j, int k)
{
    int offset;
    offset = (i - l1) * (u2 - l2 + 1) * (u3 - l3 + 1) + (j - l2) * (u3 - l3 + 1) + (k - l3);
    p = BA3 + offset;
    printf("\nReadA3 Address = %p", (void *)p);
    return *p;
}
//------------------------------------------------------
// Create 3D Array Way 2 (Row-Plane-Column)
//------------------------------------------------------
void Create3DArray_way2()
{
    int element, c, total_mem;
    element = (u1 - l1 + 1) * (u2 - l2 + 1) * (u3 - l3 + 1);
    c = sizeof(*BA4);
    total_mem = element * c;
    BA4 = (int *)malloc(total_mem);
    printf("Create3DArray_way2");
    printf("\nElement = %d", element);
    printf("\nBytes/Element = %d", c);
    printf("\nTotal Memory = %d x %d = %d", element, c, total_mem);
    printf("\nMemory Start = %p", (void *)BA4);
    printf("\nMemory End = %p", (void *)((char *)BA4 + total_mem));
    printf("\n");
}

//------------------------------------------------------
void A3_way2(int i, int j, int k, int x)
{
    int offset;
    offset = (j - l2) * (u1 - l1 + 1) * (u3 - l3 + 1) + (i - l1) * (u3 - l3 + 1) + (k - l3);
    p = BA4 + offset;
    *p = x;
    printf("\nA3_way2 Offset = %d", offset);
    printf("\nA3_way2 Address = %p", (void *)p);
}

//------------------------------------------------------
int ReadA3_way2(int i, int j, int k)
{
    int offset;
    offset = (j - l2) * (u1 - l1 + 1) * (u3 - l3 + 1) + (i - l1) * (u3 - l3 + 1) + (k - l3);
    p = BA4 + offset;
    printf("\nReadA3_way2 Address = %p", (void *)p);
    return *p;
}

//---------------------------------------------------------------------
int main()
{
    // =====================================
    // Create Arrays
    // =====================================
    Create1DArray();
    Create2DArray();
    Create3DArray();
    Create3DArray_way2();

    printf("\n========================================");
    printf("\n      ARRAY TEST RESULTS");
    printf("\n========================================");

    // ---------- 1D Array ----------
    i = 2;
    A1(i, 9);

    printf("\n\n[1D Array]");
    printf("\nA1(%d) = %d", i, ReadA1(i));

    // ---------- 2D Array ----------
    i = 2;
    j = 3;
    A2(i, j, 99);

    printf("\n\n[2D Array]");
    printf("\nA2(%d,%d) = %d", i, j, ReadA2(i, j));

    // ---------- 3D Array ----------
    i = 1;
    j = 2;
    k = 3;
    A3(i, j, k, 999);

    printf("\n\n[3D Array]");
    printf("\nA3(%d,%d,%d) = %d",
           i, j, k, ReadA3(i, j, k));

    // ---------- 3D Array (Way 2) ----------
    i = 1;
    j = 2;
    k = 3;
    A3_way2(i, j, k, 999);

    printf("\n\n[3D Array - Way 2]");
    printf("\nA3_way2(%d,%d,%d) = %d",
           i, j, k, ReadA3_way2(i, j, k));

    printf("\n========================================\n");

    getch();

    free(BA1);
    free(BA2);
    free(BA3);
    free(BA4);

    return 0;
} // End MAIN Fn.