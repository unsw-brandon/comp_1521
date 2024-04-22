#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char **argv) {

    ino_t inodes[argc - 1];

    for (int i = 1; i < argc; i++) {
        struct stat filestats;
        stat(argv[i], &filestats);

        int found = 0;
        
        for (int j = 0; j < i - 1; j++) {
            if (inodes[j] == filestats.st_ino) {
                found = 1;
            }
        }

        if (!found) {
            printf("%s\n", argv[i]);
        }

        inodes[i - 1] = filestats.st_ino;
    }

    return EXIT_SUCCESS;
}
