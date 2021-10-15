#ifndef HARDWAREDEFS_H
#define HARDWAREDEFS_H

#include <stdio.h>
#include <stdint.h>

// sizes of code and data memory
#define C_MEM_SIZE 256
#define D_MEM_SIZE 256

// program counter to keep track of execution
extern uint8_t program_counter;

// CPU registers
// defined as signed since the CPU treats all operations as 2's complement
extern int8_t regs[];

// flags for ALU operations
extern uint8_t alu_flag;

#define FLAG_Z 0x01 // zero flag
#define FLAG_N 0x02 // negative flag
#define FLAG_C 0x04 // carry flag
#define FLAG_O 0x08 // overflow flag

// code memory
extern uint16_t c_mem[];

// data memory
extern int8_t d_mem[];

// prints the current values in all registers to the screen as binary
void print_regs_bin();

// prints the current values in all registers to the screen as hex
void print_regs_hex();

// prints the current values stored in data memory to the screen as binary
void print_d_mem_bin();

// prints the current values stoed in data memory to the screen as hex
void print_d_mem_hex();

// helper function to print binary
void print_bin(uint8_t bin);

#endif