// generate the encoded binary for an addi instruction, including opcode and operands
// Tested by [Brandon Chikandiwa (z5495844) on 01/04/2024]
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the encoded binary MIPS for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    uint32_t in = 0;

    in |= 0x08 << 26;
    in |= s << 21;
    in |= t << 16;
    in |= (uint16_t) i;
    
    return in;
}
