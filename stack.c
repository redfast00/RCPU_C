#include <stdint.h>
#include "constants.h"

void stack_push(uint16_t* stack, uint16_t* stack_pointer, uint16_t value, int* error) {
  (*stack_pointer)++;
  if (*stack_pointer < STACKSIZE) {
    stack[*stack_pointer] = value;
  }
  else {
    *error = ERR_STACK_OVERFLOW;
  }
}

uint16_t stack_pop(uint16_t* stack, uint16_t* stack_pointer, int* error) {
  if ((*stack_pointer) == 0) {
    *error = ERR_STACK_UNDERFLOW;
    return 0;
  }
  else {
    (*stack_pointer)--;
    return stack[(*stack_pointer)];
  }
}
