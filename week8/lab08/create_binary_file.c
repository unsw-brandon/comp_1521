// Tested by [Brandon Chikandiwa (z5495844) on 06/04/2024]

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){

  const char *filename = argv[1];

  FILE *file = fopen(filename, "w");

  for (int i = 2; i < argc; i++) {
      fputc(atoi(argv[i]), file);
  }
  
  fclose(file);
  return 0;
}
