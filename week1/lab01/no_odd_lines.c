// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main(void) {

    char str[MAX_LENGTH];

    while (fgets(str, MAX_LENGTH, stdin) != 0) {
        if (strlen(str) % 2 == 0) {
            fputs(str, stdout);
        }
    }

    return 0;
}
