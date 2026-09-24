#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MaxData 100
#define MaxRow 10
#define MaxCol 20

int OriginalData[MaxData + 1];
int Data[MaxData + 1];
int Radix[MaxRow][MaxCol];

int N = 12;


/* =========================================================
   Common Function
   ========================================================= */

void PrepareRawData(int N)
{
    int i, j;
    int Number;
    int Duplicate;

    for (i = 1; i <= N; i++)
    {
        do
        {
            Number = 1 + rand() % 99;
            Duplicate = 0;

            for (j = 1; j < i; j++)
            {
                if (OriginalData[j] == Number)
                {
                    Duplicate = 1;
                    break;
                }
            }

        } while (Duplicate == 1);

        OriginalData[i] = Number;
    }
}


void CopyOriginalData(int N)
{
    int i;

    for (i = 1; i <= N; i++)
        Data[i] = OriginalData[i];
}


void DispOriginalData(int N)
{
    int i;

    for (i = 1; i <= N; i++)
        printf("%2d ", OriginalData[i]);

    printf("\n");
}


void DispData(int N)
{
    int i;

    for (i = 1; i <= N; i++)
        printf("%2d ", Data[i]);

    printf("\n");
}


/* =========================================================
   1. BUBBLE SORT
   ใช้โค้ดเดิม
   ========================================================= */

void BubbleSort(int N)
{
    int i, j, temp;

    printf("\n================ BUBBLE SORT ================\n");

    printf(" i ");
    for(i = 1; i <= N; i++)
        printf(" (%2d)", i);

    printf("\n");
    printf("---------------------------------------------------------------------\n");

    printf("%2d. ", 0);
    DispData(N);

    for(i = 1; i < N; i++)
    {
        if(Data[i] > Data[i + 1])
        {
            j = i + 1;

            while(j > 1 && Data[j] < Data[j - 1])
            {
                temp = Data[j];
                Data[j] = Data[j - 1];
                Data[j - 1] = temp;

                printf("%2d. ", i);
                DispData(N);

                j = j - 1;
            }
        }
    }
}


/* =========================================================
   2. INSERTION SORT
   ใช้โค้ดเดิม
   ========================================================= */

void InsertionSort(int N)
{
    int i, j, temp;

    printf("\n================ INSERTION SORT ================\n");

    printf(" i ");
    for(i = 1; i <= N; i++)
        printf(" (%2d)", i);

    printf("\n");
    printf("---------------------------------------------------------------------\n");

    printf("%2d. ", 0);
    DispData(N);

    for (i = 1; i < N; i++)
    {
        if (Data[i + 1] < Data[i])
        {
            temp = Data[i + 1];
            Data[i + 1] = 0;

            j = i;

            while (j >= 1 && temp < Data[j])
            {
                Data[j + 1] = Data[j];
                Data[j] = 0;

                printf("%2d. ", i + 1);
                DispData(N);

                j = j - 1;
            }

            Data[j + 1] = temp;

            printf("%2d. ", i + 1);
            DispData(N);
        }
    }
}


/* =========================================================
   3. HEAP SORT
   ใช้โครงสร้างเดิม
   ========================================================= */

int Maximum(int a, int b)
{
    if (Data[a] > Data[b])
        return a;
    else
        return b;
}


void AdjustTree(int Root, int LastNode)
{
    int i = Root;
    int MaxChild;
    int temp;

    while(2 * i <= LastNode)
    {
        if(2 * i + 1 <= LastNode)
            MaxChild = Maximum(2 * i, 2 * i + 1);
        else
            MaxChild = 2 * i;

        if(Data[i] < Data[MaxChild])
        {
            temp = Data[i];
            Data[i] = Data[MaxChild];
            Data[MaxChild] = temp;

            printf("Adjust (%2d,%2d) : ",
                    i,
                    MaxChild);
            DispData(N);

            i = MaxChild;
        }
        else
            break;
    }
}


void CreateHeapTree(int LastNode)
{
    int i;

    for(i = LastNode / 2 ; i >= 1 ; i--)
        AdjustTree(i, LastNode);
}


void HeapSort(int N)
{
    int i;
    int temp;

    printf("\n================ HEAP SORT ================\n");

    CreateHeapTree(N);

    printf("Heap Tree : ");
    DispData(N);

    for (i = N; i >= 2; i--)
    {
        temp = Data[1];
        Data[1] = Data[i];
        Data[i] = temp;

        AdjustTree(1, i - 1);
    }

    printf("Sorted Data : ");
    DispData(N);
}


/* =========================================================
   4. QUICK SORT
   ใช้โครงสร้างเดิม
   ========================================================= */

void swap(int a, int b)
{
    int temp;

    temp = Data[a];
    Data[a] = Data[b];
    Data[b] = temp;
}


void QuickSort(int f, int r)
{
    int f1, r1;
    bool direction;

    f1 = f;
    r1 = r;
    direction = true;

    while (f != r)
    {
        if (Data[f] > Data[r])
        {
            printf("%2d %2d : ", f, r);
            DispData(N);

            swap(f, r);

            printf("%2d %2d : ", f, r);
            DispData(N);

            direction = !direction;
        }

        if (direction)
            r--;
        else
            f++;
    }

    if ((f > f1) && (f - 1 != f1))
        QuickSort(f1, f - 1);

    if ((r < r1) && (r + 1 != r1))
        QuickSort(r + 1, r1);
}


/* =========================================================
   5. RADIX SORT
   ใช้โครงสร้างเดิม
   ========================================================= */

void ClearStackPT()
{
    int i;

    for (i = 0; i < MaxRow; i++)
        Radix[i][0] = 0;
}


void Push(int Rad, int Dat)
{
    int Location;

    Location = Radix[Rad][0] + 1;

    Radix[Rad][Location] = Dat;
    Radix[Rad][0] = Location;
}


void ReadStack(int N)
{
    int i, j, k;

    k = 1;

    for (i = 0; i < MaxRow; i++)
    {
        for (j = 1; j <= Radix[i][0]; j++)
        {
            Data[k] = Radix[i][j];
            k++;
        }
    }
}


void RadixSort(int N)
{
    int Digit;
    int i;
    int RadixNo;
    int Divisor;

    printf("\n================ RADIX SORT ================\n");

    Divisor = 1;

    for (Digit = 1; Digit <= 2; Digit++)
    {
        ClearStackPT();

        for (i = 1; i <= N; i++)
        {
            RadixNo = (Data[i] / Divisor) % 10;

            Push(RadixNo, Data[i]);
        }

        ReadStack(N);

        printf("Digit %d : ", Digit);
        DispData(N);

        Divisor = Divisor * 10;
    }

    printf("Sorted Data : ");
    DispData(N);
}


/* =========================================================
   6. SELECTION SORT
   ใช้โครงสร้างเดิม
   ========================================================= */

int Minimum(int j, int N)
{
    int i;
    int Location;

    Location = j;

    for (i = j + 1; i <= N; i++)
    {
        if (Data[i] < Data[Location])
            Location = i;
    }

    return Location;
}


void SelectionSort(int N)
{
    int i;
    int Location;
    int temp;

    printf("\n================ SELECTION SORT ================\n");

    printf(" i ");
    for(i = 1; i <= N; i++)
        printf(" (%2d)", i);

    printf("\n");
    printf("---------------------------------------------------------------------\n");

    printf("%2d. ", 0);
    DispData(N);

    for (i = 1; i < N; i++)
    {
        Location = Minimum(i, N);

        if (Location != i)
        {
            temp = Data[i];
            Data[i] = Data[Location];
            Data[Location] = temp;
        }

        printf("%2d. ", i);
        DispData(N);
    }

    printf("Sorted Data : ");
    DispData(N);
}


/* =========================================================
   MAIN PROGRAM
   ========================================================= */

int main()
{
    int choice;

    srand(time(NULL));

    /* สุ่มข้อมูลครั้งแรก */
    PrepareRawData(N);
    CopyOriginalData(N);

    printf("============================================================\n");
    printf("              SORTING ALGORITHMS PROGRAM\n");
    printf("============================================================\n");

    printf("Initial Random Data : ");
    DispOriginalData(N);

    do
    {
        printf("\n============================================================\n");
        printf("                 SORTING ALGORITHMS\n");
        printf("============================================================\n");

        printf("Current Random Data : ");
        DispOriginalData(N);

        printf("\n");
        printf("1. Bubble Sort\n");
        printf("2. Insertion Sort\n");
        printf("3. Heap Sort\n");
        printf("4. Quick Sort\n");
        printf("5. Radix Sort\n");
        printf("6. Selection Sort\n");
        printf("7. Generate New Random Data\n");
        printf("0. Exit\n");

        printf("\nChoose : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                CopyOriginalData(N);
                BubbleSort(N);
                break;

            case 2:
                CopyOriginalData(N);
                InsertionSort(N);
                break;

            case 3:
                CopyOriginalData(N);
                HeapSort(N);
                break;

            case 4:
                CopyOriginalData(N);

                printf("\n================ QUICK SORT ================\n");

                QuickSort(1, N);

                printf("Sorted Data : ");
                DispData(N);
                break;

            case 5:
                CopyOriginalData(N);
                RadixSort(N);
                break;

            case 6:
                CopyOriginalData(N);
                SelectionSort(N);
                break;

            case 7:
                PrepareRawData(N);
                CopyOriginalData(N);

                printf("\nNew Random Data : ");
                DispOriginalData(N);
                break;

            case 0:
                printf("\nExit Program...\n");
                break;

            default:
                printf("\nPlease choose 0 - 7 only.\n");
        }

    } while(choice != 0);

    return 0;
}