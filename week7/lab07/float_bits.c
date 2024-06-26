// Extract the 3 parts of a float using bit operations only
// Tested by [Brandon Chikandiwa (z5495844) on 01/04/2024]
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    
    uint32_t sign = (f >> 31) & 0x01;
    uint32_t expo = (f >> 23) & 0xFF;
    uint32_t frac = f & 0x7FFFFF;

    float_components_t fct = {
        .sign = sign,
        .exponent = expo,
        .fraction = frac
    };

    return fct;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    if (f.exponent == 0xFF && f.fraction != 0){
        return 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    if (f.sign == 0 && f.exponent == 0xFF && f.fraction == 0){
        return 1;
    }

    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    if (f.sign == 1 && f.exponent == 0xFF && f.fraction == 0){
        return 1;
    }
    
    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    if (f.exponent == 0 && f.fraction == 0){
       return 1;
    }
    
    
    return 0;
}
