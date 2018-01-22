#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "stack.h"

int error = 0;

uint16_t ath(uint8_t ath_operation, uint8_t ath_shift_amount, uint16_t source, uint16_t destination) {
  switch (ath_operation) {
    case 0b0000: // ADD
      return destination + source;
    break;

    case 0b0001: // SUB
      return destination - source;
    break;

    case 0b0010: // MUL
      return destination * source;
    break;

    case 0b0011: // DIV
      return destination / source;
    break;

    case 0b0100: // LSH
      return source << ath_shift_amount;
    break;

    case 0b0101: // RSH
      return source >> ath_shift_amount;
    break;

    case 0b0110: // AND
      return destination & source;
    break;

    case 0b0111: // OR
      return destination | source;
    break;

    case 0b1000: // XOR
      return destination ^ source;
    break;

    case 0b1001: // NOT
      return ~source;
    break;

    case 0b1010: // INC
      return destination + 1;
    break;

    case 0b1011: // DEC
      return destination - 1;
    break;

    default:
      printf("ATH subinstruction not implemented.\n");
      error = ERR_ATH_SUBINSTRUCTION;
      return 0;
  }
}

int emulate(uint16_t* memory) {
  uint16_t registers[1 << 2];
  uint16_t instruction_pointer = 0;
  uint16_t stack_pointer = 0;
  uint16_t stack[STACKSIZE];

  printf("Starting emulation\n");
  for(;;) {
    // Get current instruction
    uint16_t current_instruction = memory[instruction_pointer];
    // Decode instruction into parts
    uint8_t opcode = current_instruction & 0b1111;
    uint8_t destination = (current_instruction >> 4) & 0b11;
    uint8_t source = (current_instruction >> 6) & 0b11;
    uint16_t large_address = current_instruction >> 6;
    uint8_t ath_operation = (current_instruction >> 8) & 0b1111;
    bool ath_store_in_src = (current_instruction >> 12) & 0b1;
    uint8_t ath_shift_amount = (current_instruction >> 13) & 0b111;
    // Execute instruction
    switch (opcode) {
      case 0b0000: // MOV
        registers[destination] = registers[source];
      break;

      case 0b0001: // LDV
        registers[destination] = large_address;
      break;

      case 0b0010: // LDA
        registers[destination] = memory[large_address];
      break;

      case 0b0011: // LDM
        memory[large_address] = registers[destination];
      break;

      case 0b0100: // LDR
        registers[destination] = memory[registers[source]];
      break;

      case 0b0101: // LDP
         memory[registers[destination]] = registers[source];
      break;

      case 0b0110: // ATH
        ; // because C... https://stackoverflow.com/a/46341408/5431090
        uint16_t result = ath(ath_operation, ath_shift_amount, registers[source], registers[destination]);
        if (ath_store_in_src) {
          registers[source] = result;
        } else {
          registers[destination] = result;
        }
      break;

      case 0b0111: // CAL
        // Push instruction pointer onto the stack, so we can return to it later on
        stack_push(stack, &stack_pointer, instruction_pointer, &error);
        // Minus one because the instruction pointer will be incremented at the end of each instruction
        instruction_pointer = registers[destination] - 1;
      break;

      case 0b1000: // RET
        // Pop return address from stack
        instruction_pointer = stack_pop(stack, &stack_pointer, &error);
      break;

      case 0b1001: // JLT
        if (registers[0] < registers[destination]) {
          instruction_pointer = registers[source] - 1;
        }
      break;

      case 0b1010: // PSH
        stack_push(stack, &stack_pointer, registers[source], &error);
      break;

      case 0b1011: // POP
        registers[destination] = stack_pop(stack, &stack_pointer, &error);
      break;

      case 0b1100: // SYS
        // TODO
        printf("Syscall not implemented yet\n");
      break;

      case 0b1101: // HLT
        printf("Terminated\n");
        return 0;
      break;

      case 0b1110: // JMP
        instruction_pointer = large_address;
      break;

      case 0b1111: // JMR
        instruction_pointer = registers[source] - 1;
      break;

    }
    // Error checking
    if (error != 0) {
      return error;
    }
    // Increment instruction pointer
    instruction_pointer++;
  }
  return 0;
}
