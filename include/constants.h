#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MEMSIZE 1 << 16
#define STACKSIZE 256

// Error codes
#define ERR_FILE_ACCESS 1
#define ERR_FILE_SIZE 2

// Emulator error codes
#define ERR_STACK_OVERFLOW 3
#define ERR_STACK_UNDERFLOW 4
#define ERR_ATH_SUBINSTRUCTION 5
#define ERR_SYSCALL_PRINTF_FMT_STRING 6
#define ERR_SYSCALL_UNKNOWN 7

// Not implemented error codes
#define ERR_NOT_IMPLEMENTED 101
#endif /* CONSTANTS_H */
