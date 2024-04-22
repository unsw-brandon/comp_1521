// Tested by [Brandon Chikandiwa (z5495844) on 16/02/2023]
#include <stdio.h>

int main() {
    char c;

    while (scanf("%c", &c) == 1) {
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' &&
            c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
            printf("%c", c);
        }
    }

    return 0;
}
