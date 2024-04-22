#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
    int32_t my_bcd = (int32_t) bcd_value;
    int my_decimal = 0;
    my_decimal +=  my_bcd & 0xFF;
    my_decimal += 10 * (my_bcd & 0xFF00) >> 8;
    return my_decimal;
}

