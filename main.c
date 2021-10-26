#include <stdio.h>
#include <stdint.h>
#include "hardwaredefs.h"
#include "instructions.h"
#include "fileparse.h"

/**
 * 
 * Main code that is responsible for the emulation of the i281 processor.  Reads one instruction at a time, parses it, and then executes the instruction.  Execution
 * begins by reading all of the data in from a file into the code memory in RAM on the host machine.
 * 
 */

int main() {
    printf("Enter a binary file to emulate: ");
    char buff[128];
    fgets(buff, 128, stdin);

    buff[strlen(buff) - 1] = '\0'; // remove newline

    int num_opcodes = parse_binary_bin(buff, c_mem, C_MEM_SIZE);

    int num_data = parse_d_mem_bin(buff, d_mem, D_MEM_SIZE);

    printf("Read %d opcodes from file\n", num_opcodes);
    printf("Read %d bytes from data segment\n\n", num_data);

    for(int i = 0; i < C_MEM_SIZE; i++) {
        print_bin((uint8_t)(c_mem[i] >> 8));
        print_bin((uint8_t) c_mem[i]);
        printf("\n");
    }

    while(program_counter < num_opcodes) {
        // current instruction to be executed
        ParsedInst inst = parse_opcode(c_mem[program_counter]);
        switch(inst.opcode) {
            case NOOP:
                printf("NOOP\n");
                break;

            case INPUT:
                input(inst);
                break;

            case MOVE:
                move(inst);
                break;

            case LOADI:
                loadi(inst);
                break;

            case ADD:
                add(inst);
                break;

            case ADDI:
                addi(inst);
                break;

            case SUB:
                sub(inst);
                break;

            case SUBI:
                subi(inst);
                break;

            case LOAD:
                load(inst);
                break;

            case LOADF:
                loadf(inst);
                break;

            case STORE:
                store(inst);
                break;

            case STOREF:
                storef(inst);
                break;

            case SHIFT:
                shift(inst);
                break;

            case CMP:
                cmp(inst);
                break;

            case JUMP:
                jump(inst);
                break;

            case BR:
                br(inst);
                break;
        }

        printf("Program counter: %d\n", program_counter);
        printf("Current instruction at program counter: %s\n", opcode_to_str(inst));
        printf("Contents of data memory:\n");
        print_d_mem_hex();
        print_regs_hex();
        printf("ALU flags: %d", alu_flag);
        printf("\n\n");

        program_counter++;

        getchar();
    }

    return 0;
}