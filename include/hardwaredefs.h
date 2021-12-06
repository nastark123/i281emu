#ifndef HARDWAREDEFS_H
#define HARDWAREDEFS_H

#include <stdio.h>
#include <stdint.h>

// sizes of code and data memory
#define C_MEM_SIZE 256
#define D_MEM_SIZE 256

#define FLAG_Z 0x01 // zero flag
#define FLAG_N 0x02 // negative flag
#define FLAG_C 0x04 // carry flag
#define FLAG_O 0x08 // overflow flag

// struct that bundles data about the hardware on the CPU so it can be passed to functions
typedef struct {
    uint16_t c_mem[C_MEM_SIZE]; // code memory
    int8_t d_mem[D_MEM_SIZE]; // data memory
    int8_t regs[4]; // CPU registers
    uint8_t program_counter; // program counter, stores address of current instruction in code memory
    uint8_t alu_flag; // flag that stores different conditions that can occur from ALU processing
    uint8_t num_opcodes; // how many opcodes were read into the 
} HardwareInfo;

// prints the current values in all registers to the screen as binary
void print_regs_bin(HardwareInfo hi);

// prints the current values in all registers to the screen as hex
void print_regs_hex(HardwareInfo hi);

// prints the current values stored in data memory to the screen as binary
void print_d_mem_bin(HardwareInfo hi);

// prints the current values stoed in data memory to the screen as hex
void print_d_mem_hex(HardwareInfo hi);

// prints the current values stored in code memory to the screen as hex
void print_c_mem_hex(HardwareInfo hi);

// helper function to print binary
void print_bin(uint8_t bin);

#endif