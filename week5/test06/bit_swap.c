// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    uint64_t swapped_result = 0;
    
    for (int bit_index = 0; bit_index < 64; bit_index += 2) {
        uint64_t current_even_bit = (value >> bit_index) & 1;
        uint64_t current_odd_bit = (value >> (bit_index + 1)) & 1;

        swapped_result |= (current_even_bit << (bit_index + 1)) | (current_odd_bit << bit_index);
    }

    return swapped_result;
}
