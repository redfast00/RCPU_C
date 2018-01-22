#include <stdio.h>
#include <stdint.h>
#include "emulate.h"
#include "constants.h"

uint16_t emulator_memory[MEMSIZE];

int filesize(FILE* fp) {
  fseek(fp, 0L, SEEK_END);
  int sz = ftell(fp);
  rewind(fp);
  return sz;
}

int main() {
  FILE *executable;
  executable = fopen("asm/printf.out", "r");

  if (executable == NULL) {
    printf("File could not be opened\n");
    return ERR_FILE_ACCESS;
  }
  else {
    int sz = filesize(executable);
    if (sz > MEMSIZE) {
      printf("File too big\n");
      return ERR_FILE_SIZE;
    }
      fread(emulator_memory, 2, sz, executable);
      fclose(executable);
      return emulate(emulator_memory);
    }
}
