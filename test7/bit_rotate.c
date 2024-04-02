#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    int rotations = n_rotations % 16;

    if (rotations == 0) return bits;

    uint16_t initial_mask = 0xFFFF;
    uint16_t rotated, overflow;

    if (rotations > 0) {
        uint16_t overflow_mask = (initial_mask << (16 - rotations));
        overflow = (overflow_mask & bits) >> (16 - rotations);
        uint16_t mask = (initial_mask >> rotations);
        rotated = (bits & mask) << rotations;
    } else {
        rotations *= -1;
        uint16_t overflow_mask = (initial_mask >> (16 - rotations));
        overflow = (overflow_mask & bits) << (16 - rotations);
        uint16_t mask = (initial_mask << rotations);
        rotated = (bits & mask) >> rotations;
    }

    return (rotated | overflow);
}


