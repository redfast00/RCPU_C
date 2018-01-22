#ifndef STACK_H
#define STACK_H

void stack_push(uint16_t* stack, uint16_t* stack_pointer, uint16_t value, int* error);
uint16_t stack_pop(uint16_t* stack, uint16_t* stack_pointer, int* error);

#endif /* STACK_H */
