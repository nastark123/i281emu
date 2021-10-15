#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// constant definitions for each of the opcodes
// the opcodes are stored in the upper 4 bits of the most significant byte
#define NOOP 0x00 // no operation

#define INPUT 0x01 // take an input from switches
// additional definitions, stored in the lower 2 bits of the most significant byte
#define INPUTC 0x00
#define INPUTCF 0x01
#define INPUTD 0x02
#define INPUTDF 0x03

#define MOVE 0x02 // copies the value stored in one register to another

#define LOADI 0x03 // loads an immediate value (stored in the least significant byte) into a register

#define ADD 0x04 // adds two registers and stores the result in the first register

#define ADDI 0x05 // adds an immediate value to a register and stores the result back in the register

#define SUB 0x06 // subtracts the second register from the first register, and stores the result in the first register

#define SUBI 0x07 // subtracts an immediate value from a register and stores the result back in the register

#define LOAD 0x08 // loads a value from a data address (stored in the least significant byte) to a register

#define LOADF 0x09 // loads a value from a data address plus an offset stored in a register into another register

#define STORE 0x0A // stores a value from a register to a data address

#define STOREF 0x0B // stores a value from a register to a data address plus an offset

#define SHIFT 0x0C // shifts a register left or right by 1 bit, direction depends on least significant bit in the most significant byte
#define SHIFTL 0x00
#define SHIFTR 0x01

#define CMP 0x0D // compares two registers and sets flags

#define JUMP 0x0E // unconditional jump, moves PC to PC + 1 + offset (offset is signed)

#define BR 0x0F // branching instructions, type is stored in lower 2 bits of most significant byte, all branch instructions branch to PC + 1 + offset
#define BRE 0x00 // branch if equal or zero
#define BRNE 0x01 // branch if not equal or not zero
#define BRG 0x02 // branch if greater than
#define BRGE 0x03 // branch if greater than or equal to

// struct that contains parsed info about an machine instruction
typedef struct {
    // opcode
    uint8_t opcode;
    // bits 2-3 of the MSB
    uint8_t b23;
    // bits 0-1 of the MSB
    uint8_t b01;
    // extra data from the LSB
    uint8_t data;
} ParsedInst;

// function to return the opcode from 
ParsedInst parse_opcode(uint16_t inst);

// function prototypes for each of the instructions
void input(ParsedInst inst);

void move(ParsedInst inst);

void loadi(ParsedInst inst);

void add(ParsedInst inst);

void addi(ParsedInst inst);

void sub(ParsedInst inst);

void subi(ParsedInst inst);

void load(ParsedInst inst);

void loadf(ParsedInst inst);

void store(ParsedInst inst);

void storef(ParsedInst inst);

void shift(ParsedInst inst);

void cmp(ParsedInst inst);

void jump(ParsedInst inst);

void br(ParsedInst inst);

#endif