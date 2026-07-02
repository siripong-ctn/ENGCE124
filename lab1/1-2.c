#include <stdio.h>
#include <math.h>

int main(void) {
    double x = 0.1 + 0.2;
    double y = 0.3;

    printf("x = %.17f\n", x);
    printf("y = %.17f\n", y);

    if (x == y) {
        printf("equal\n");
    } else {
        printf("not equal\n");
    }

    if (fabs(x - y) < 1e-9) {
        printf("close enough\n");
    }

    return 0;
}
