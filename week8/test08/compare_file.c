#include <stdio.h>

int main(int argc, char const *argv[]) {

    const char *filename_one = argv[1];
    const char *filename_two = argv[2];

    FILE *file_one = fopen(filename_one, "r");
    FILE *file_two = fopen(filename_two, "r");

    int c_one;
    int c_two;

    int pos = 0;

    while (1) {
        c_one = fgetc(file_one);
        c_two = fgetc(file_two);

        if ((c_one == c_two) &&
            (c_one == EOF) &&
            (c_two == EOF)) {
            printf("Files are identical\n");
            break;
        } else if (c_one == EOF) {
            printf("EOF on %s\n", filename_one);
            break;
        } else if (c_two == EOF) {
            printf("EOF on %s\n", filename_two);
            break;
        } else if (c_one != c_two) {
            printf("Files differ at byte %d\n", pos);
            break;
        }

        pos++;
    }

    fclose(file_one);
    fclose(file_two);

    return 0;
}
