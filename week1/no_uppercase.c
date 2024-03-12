// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]
#include <ctype.h>
#include <stdio.h>

int main(void) {
    int c;

    while ((c = getchar()) != EOF) {
        if (isupper(c)) {
            putchar(tolower(c));
        } else {
            putchar(c);
        }
    }

    return 0;
}
