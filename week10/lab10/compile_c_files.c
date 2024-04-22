#include <spawn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define DCC_PATH "/usr/local/bin/dcc"

extern char **environ;

int main(int argc, char **argv) {
    int status = EXIT_SUCCESS;

    for (int i = 1; i < argc; i++) {
        pid_t pid;
        char *arg1 = strdup(argv[i]); 
        
        char *dot_position = strrchr(arg1, '.');
        
        if (dot_position != NULL && dot_position - arg1 >= 2) {
            *dot_position = '\0';
        }

        char *arg[] = {DCC_PATH, argv[i], "-o", arg1, NULL};
        status = posix_spawn(&pid, DCC_PATH, NULL, NULL, arg, environ);
        printf("running the command: \"%s %s -o %s\"\n", arg[0], arg[1], arg[3]);
        free(arg1);
    }

    return status;
}
