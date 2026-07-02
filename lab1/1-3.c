#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "ก";

    printf("text = %s\n", text);
    printf("strlen(text) = %zu bytes\n", strlen(text));

    for (size_t i = 0; i < strlen(text); i++) {
        printf("byte %zu = 0x%02X\n", i, (unsigned char)text[i]);
    }

    return 0;
}
