// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]
#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 30

int fibonnaci(int n) {

    if (n == 0) {
        return 0;
    } else if (n == 1 || n == 2) {
        return 1;
    } else {
        return fibonnaci(n - 1) + fibonnaci(n - 2);
    }
}
int main(void) {
    int in;
    int i = scanf("%d", &in);

    while (i == 1) {
        printf("%d\n", fibonnaci(in));
        i = scanf("%d", &in);
    }

    return 0;
}
