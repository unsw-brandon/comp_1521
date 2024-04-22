// Tested by [Brandon Chikandiwa (z5495844) on 14/04/2024]

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  
    char *path = getenv("HOME");
    strcat(path, "/.diary");

    FILE *f = fopen(path, "a+");

    for (int i = 1; i < argc; i++) {
        if (i == (argc - 1)) {
            fprintf(f, "%s\n", argv[i]);
        } else {
            fprintf(f, "%s ", argv[i]);
        }
    }

    fclose(f);
    return 0;
}