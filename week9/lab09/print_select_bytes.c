// Tested by [Brandon Chikandiwa (z5495844) on 14/04/2024]

#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h> 

int main(int argc, char const *argv[]){

  FILE *f = fopen(argv[1], "rb");

  for (int i = 2; i < argc; i++) {
      fseek(f, atol(argv[i]), SEEK_SET);

      int c = fgetc(f);

      printf("%d - 0x%02X", c, c);

      if (isprint(c)){
        printf(" - '%c'", c);
      }

      printf("\n");
  }
  
  fclose(f);
  return 0;
}
