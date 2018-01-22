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

void printUsage() {
  printf("Usage: emulate_rcpu <executable>\n");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printUsage();
    return ERR_FILE_ACCESS;
  }
  FILE *executable;
  executable = fopen(argv[1], "r");

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
