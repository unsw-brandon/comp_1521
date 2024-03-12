// Tested by [Brandon Chikandiwa (z5495844) on 18/02/2023]

#include <stdio.h>
#include <stdlib.h>

int collatz(int n) {
    printf("%d\n", n);
    if (n == 1) {
        return n;
    } else if (n % 2 == 0) {
        return collatz(n /= 2);
    } else {
        return collatz((n * 3) + 1);
    }
}

int main(int argc, char *argv[]) {
    collatz(atoi(argv[1]));
    return 0;
}
