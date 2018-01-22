#ifndef SYSCALL_H
#define SYSCALL_H

void syscall(uint16_t* memory, uint16_t* stack, uint16_t* stack_pointer, int* error);

#endif /* SYSCALL_H */
