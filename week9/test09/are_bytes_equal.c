#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *f1 = fopen(argv[1], "rb");
    fseek(f1, atol(argv[2]), SEEK_SET);
    int c1 = fgetc(f1);
    
    fseek(f1, 0, SEEK_END);
    int n1 = ftell(f1);

    FILE *f2 = fopen(argv[3], "rb");
    fseek(f2, atol(argv[4]), SEEK_SET);
    int c2 = fgetc(f2);

    fseek(f2, 0, SEEK_END);
    int n2 = ftell(f2);

    if (c1 == c2 && n1 >= atol(argv[2]) && n2 >= atol(argv[4])) {
        printf("byte %ld in %s and byte %ld in %s are the same\n", atol(argv[2]), argv[1], atol(argv[4]), argv[3]);
    } else {
        printf("byte %ld in %s and byte %ld in %s are not the same\n", atol(argv[2]), argv[1], atol(argv[4]), argv[3]);
    }
    
    fclose(f1);
    fclose(f2);
    
    return 0;
}
