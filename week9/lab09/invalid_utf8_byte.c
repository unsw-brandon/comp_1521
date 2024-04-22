#include <ctype.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Given an UTF-8 string, return the index of the first invalid byte.
// If there are no invalid bytes, return -1.

// Do NOT change this function's return type or signature.
int invalid_utf8_byte(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        // Check for ASCII characters
        if ((unsigned char)s[i] < 128) {
            i++;
        } else {
            // Determine the number of bytes in the UTF-8 sequence
            int num_bytes = 0;
            while ((s[i] >> (7 - num_bytes)) & 1) {
                num_bytes++;
            }

            // Check if the number of bytes is valid
            if (num_bytes < 2 || num_bytes > 4) {
                return i;
            }

            // Check if there are enough bytes left in the string
            int j;
            for (j = 1; j < num_bytes; j++) {
                if ((s[i + j] >> 6) != 0b10) {
                    return i;
                }
            }

            i += num_bytes;
        }
    }

    return -1;
}

