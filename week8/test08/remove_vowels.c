#include <stdio.h>

int isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
        return 1;
    }
    
    return 0;
}

int main(int argc, char const *argv[]) {

    const char *filename = argv[1];
    const char *new_filename = argv[2];

    FILE *file = fopen(filename, "r");
    FILE *new_file = fopen(new_filename, "w");

    int c;

    while ((c = fgetc(file)) != EOF) {
        if (!isVowel(c)) {
            fprintf(new_file, "%c", c);
        }
    }

    fclose(file);
    fclose(new_file);

    return 0;
}