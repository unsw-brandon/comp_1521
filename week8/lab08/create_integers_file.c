// Tested by [Brandon Chikandiwa (z5495844) on 06/04/2024]

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

  const char *filename = argv[1];
  int start = atoi(argv[2]);
  int end = atoi(argv[3]);

  FILE *file = fopen(filename, "w");
  for (int i = start; i < end + 1; i++){
    fprintf(file, "%d", i);
    fprintf(file, "\n");
  }
  
  fclose(file);
  return 0;
}
