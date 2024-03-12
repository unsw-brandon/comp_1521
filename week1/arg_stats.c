// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    int min = atoi(argv[1]);
    int max = atoi(argv[1]);
    int sum = 0;
    int prod = 1;
    int mean = atoi(argv[1]) / (argc - 1);
    if (argc <= 2) {
        sum = atoi(argv[1]);
        prod = atoi(argv[1]);
        mean = atoi(argv[1]);
    } else {

        for (int i = 1; i < argc; i++) {

            if (atoi(argv[i]) < min) {
                min = atoi(argv[i]);
            }

            if (atoi(argv[i]) > max) {
                max = atoi(argv[i]);
            }

            sum += atoi(argv[i]);
            prod *= atoi(argv[i]);
        }
        mean = sum / (argc - 1);
    }

    printf("MIN:  %d\n", min);
    printf("MAX:  %d\n", max);
    printf("SUM:  %d\n", sum);
    printf("PROD: %d\n", prod);
    printf("MEAN: %d\n", mean);
    return 0;
}
