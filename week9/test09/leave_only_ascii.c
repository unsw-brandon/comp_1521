#include <stdio.h>

int main(int argc, char const *argv[]) {

    FILE *in = fopen(argv[1], "r");
    FILE *temp = fopen("temp.txt", "w");

    int c;
    while ((c = fgetc(in)) != EOF) {
        if (!(128 <= c && c <= 255)) {
            fputc(c, temp);
        }
    }

    fclose(in);
    fclose(temp);

    in = fopen("temp.txt", "r");
    FILE *out = fopen(argv[1], "w");

    while ((c = fgetc(in)) != EOF) {
        fputc(c, out);
    }

    fclose(in);
    fclose(out);

    
    remove("temp.txt");

    return 0;
}
