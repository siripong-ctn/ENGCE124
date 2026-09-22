/* Program Sequential Search can..
1. Random a difference data into 1 dimension Array and Sort it
2. Search by key
3. Count a time of searching
*/
#include <stdio.h>   //use printf
#include <conio.h>   //use getch
#include <stdlib.h>  //use random
#include <time.h>    //use time
#include <windows.h> //use Sound
#define MaxData 100  // Define Max Data
int Data[MaxData];
int N, key, Times;
bool result;
bool Duplicate(int i, int Data1) // Check Duplication Data
{
    int j;
    for (j = 1; j <= i; j++)
    {
        if (Data1 == Data[j])
            return (true);
    }
    return (false);
}
void PrepareRawKey(int N)
{
    int i, j, temp;
    srand(time(NULL)); // for difference random number in rand()
    for (i = 1; i <= N; i++)
    {
        temp = (rand() % 89) + 10;     // random difference number 10..99
        while (Duplicate(i - 1, temp)) // Loop if Still Duplicate
            temp = (rand() % 89) + 10; // random again
        Data[i] = temp;                // Keep new Number
    } // End for
} // End Fn.
void DispKey(int N)
{
    int i;
    for (i = 1; i <= N; i++)
        printf("(%2d)", i); // Show Subscript i
    printf("\n");
    for (i = 1; i <= N; i++)
        printf(" %2d ", Data[i]); // Show Data[]
    printf("\n");
}
bool SequentialSearch(int Key1)
{
    int i;
    Times = 0; // Initial Time for search
    i = 1;
    while (i <= N)
    {
        Times++; // Count Searching Time
        if (Key1 == Data[i])
            return (true); // if found
        i++;
    } // End while
    return (false); // If not found
} // End Fn.
int main()
{
    printf("SEQUENTIAL SEARCH\n");
    printf("===================================================\n");
    N = 16;
    PrepareRawKey(N);
    printf("Raw key :\n");
    DispKey(N); // Raw key
    printf("----------------------------------------------------------------\n");
    while (key != -999)
    {
        printf("\nEnter Key for Search(-999 for EXIT) = ");
        scanf("%d", &key); // Read key from KBD
        if (key != -999)
        {
            result = SequentialSearch(key); // Call Sequential Search
            if (result)
                printf("Result...FOUND\n"); // if found
            else
            {
                Beep(600, 600);
                printf("Result...NOT FOUND!!\n"); // if NOT found
            }
            printf("Searching Time : %d\n", Times);
            printf("----------------------------------------------------Searching Finished\n");
        } // End if
    } // End While
    return (0);
} // End Main
