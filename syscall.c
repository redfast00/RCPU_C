#include <stdio.h>
#include <stdint.h>
#include "stack.h"
#include "constants.h"


void syscall_printf(uint16_t* memory, uint16_t* stack, uint16_t* stack_pointer, int* error) {
  uint16_t fmt_pointer = stack_pop(stack, stack_pointer, error);
  if (*error) return;
  while (memory[fmt_pointer] != 0) { // Strings are terminated with 0
    char character = (char) memory[fmt_pointer];
    switch (character) {
      case '%':
        ; // dirty hack
        char next_character = (char) memory[++fmt_pointer]; // get next memory cell content and increment at the same time
        switch (next_character) {
          case '%':
            printf("%%");
            break;
          case 'd':
            ; // dirty hack
            uint16_t number = stack_pop(stack, stack_pointer, error);
            if (*error) return;
            printf("%d", number);
            break;
          case 's':
            *error = ERR_NOT_IMPLEMENTED; //TODO
            return;
            break;
          default: // this also catches '\0'
            *error = ERR_SYSCALL_PRINTF_FMT_STRING;
            return;
        }
      break;
      default:
        printf("%c", character);
    }
    fmt_pointer++;
  }
}

void syscall(uint16_t* memory, uint16_t* stack, uint16_t* stack_pointer, int* error) {
  uint16_t syscall_number = stack_pop(stack, stack_pointer, error);
  if (*error) {
    return;
  }
  switch (syscall_number) {
    case 0:
      syscall_printf(memory, stack, stack_pointer, error);
    break;
    // TODO implement other syscalls
    default:
      *error = ERR_SYSCALL_UNKNOWN;
  }
}
