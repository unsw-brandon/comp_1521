// Tested by [Brandon Chikandiwa (z5495844) on 06/04/2024]

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STR_LEN 255

int main(int argc, char const *argv[]){

  const char *filename = argv[1];


  FILE *file = fopen(filename, "r");

  int next;
  size_t pos = 0;
  while ((next = fgetc(file)) != EOF) {
    printf("byte %4lu: %3d 0x%02x", pos, next, next);

    if (isprint(next)) {
      printf(" \'%c\'", next);
    }

    printf("\n");
    pos++;
  }

  fclose(file);
  return 0;
}
