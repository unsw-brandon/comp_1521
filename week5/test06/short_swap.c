// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    // PUT YOUR CODE HERE
    uint16_t left_shift = value << 8;
    uint16_t right_shift = value >> 8;
    return  left_shift | right_shift;
}
