#include <stdio.h>
#include <conio.h>

int M,N;
long int ans;

long int Power(int m,int n) {
    long int y;
    if(n==0) {
        printf("...............Roll Back Point\n");
        return 1;
    } else {
        printf("%d^%d = %d * %d^%d\n",m,n,m,m,n-1);
        y = Power(m,n-1);
        printf("%d^%d = %d * %ld = %ld\n",m,n,m,y,m*y);
        return m*y;
    }
}

int main() {
    printf("RECURSION POWER PROGRAM\n");
    printf("=======================\n");
    printf("Enter M : ");
    scanf("%d",&M);
    printf("Enter N : ");
    scanf("%d",&N);
    ans = Power(M,N);
    printf("\nAnswer %d^%d = %ld\n", M,N,ans);
    getch();
    return 0;
}