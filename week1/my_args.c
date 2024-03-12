// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printf("Program name: %s\n", argv[0]);
        printf("There are no other arguments\n");
    } else {
        printf("Program name: %s\n", argv[0]);
        printf("There are %d arguments:\n", argc - 1);
        for (int i = 1; i < argc; i++) {
            printf("\tArgument %d is \"%s\"\n", i, argv[i]);
        }
    }

    return 0;
}
