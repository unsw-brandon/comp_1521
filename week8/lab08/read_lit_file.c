// Tested by [Brandon Chikandiwa (z5495844) on 07/04/2024]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE 3

void print_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main(int argc, char *argv[]) {
    // Check if filename argument is provided
    if (argc != 2) {
        print_error("Usage: read_lit_file <filename>");
    }

    // Open the file
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        print_error("Failed to open file");
    }

    // Read and check the magic number
    char magic[HEADER_SIZE + 1]; // +1 for null terminator
    if (fread(magic, sizeof(char), HEADER_SIZE, file) != HEADER_SIZE ||
        strncmp(magic, "LIT", HEADER_SIZE) != 0) {
        print_error("Failed to read magic");
    }

    // Read and print integers
    while (!feof(file)) {
        unsigned char num_bytes;
        if (fread(&num_bytes, sizeof(unsigned char), 1, file) != 1) {
            if (!feof(file)) {
                print_error("Failed to read record");
            } else {
                break; // Reached end of file
            }
        }

        if (num_bytes < 1 || num_bytes > sizeof(long long)) {
            print_error("Invalid record length");
        }

        unsigned long long value = 0;
        if (fread(&value, 1, num_bytes, file) != num_bytes) {
            print_error("Failed to read record");
        }

        // Convert to little-endian
        unsigned long long result = 0;
        for (int i = 0; i < num_bytes; i++) {
            result |= ((value >> (i * 8)) & 0xFF) << (num_bytes - 1 - i) * 8;
        }

        printf("%llu\n", result);
    }

    fclose(file);
    return 0;
}

