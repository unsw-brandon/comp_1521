// Multiply a float by 2048 using bit operations only
// Tested by [Brandon Chikandiwa (z5495844) on 01/04/2024]
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {

    uint32_t sign = (f >> 31) & 0x01;
    uint32_t expo = (f >> 23) & 0xFF;
    uint32_t frac = f & 0x7FFFFF;

    float_components_t fct = {
        .sign = sign,
        .exponent = expo,
        .fraction = frac
    };


    if ((fct.exponent == 0xFF && fct.fraction != 0) ||
        (fct.exponent == 0 && fct.fraction == 0) ||
        (fct.sign == 1 && fct.exponent == 0xFF && fct.fraction == 0) ||
        (fct.sign == 0 && fct.exponent == 0xFF && fct.fraction == 0)){
        return f;
    }

    int32_t exponent_diff = 11;
    int32_t new_exponent = expo + exponent_diff;

    if (new_exponent >= 0xFF) {
        return (sign << 31) | (0xFF << 23);
    }

    uint32_t result = (sign << 31) | (new_exponent << 23) | (frac);
    return result;

}