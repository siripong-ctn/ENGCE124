#include <stdio.h>
#include <stdbool.h>

int main(void) {
    printf("sizeof(char) = %zu\n", sizeof(char));
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(float) = %zu\n", sizeof(float));
    printf("sizeof(double) = %zu\n", sizeof(double));
    printf("sizeof(bool) = %zu\n", sizeof(bool));
    printf("sizeof(int*) = %zu\n", sizeof(int*));
    printf("sizeof(char*) = %zu\n", sizeof(char*));

    return 0;
}