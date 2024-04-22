#include <stdio.h>

int isVowel(char c);

int main(int argc, char const *argv[]) {
    const char *filename = argv[1];

    FILE *file = fopen(filename, "r");

    int c;
    int count = 0;

    while ((c = fgetc(file)) != EOF) {
        if (isVowel(c)) {
            count++;
        }
    }

    printf("%d\n", count);

    fclose(file);
    return 0;
}

int isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 1;
    }

    return 0;
}