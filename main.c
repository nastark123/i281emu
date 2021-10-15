#include <stdio.h>
#include <stdint.h>
#include "hardwaredefs.h"
#include "instructions.h"

/**
 * 
 * Main code that is responsible for the emulation of the i281 processor.  Reads one instruction at a time, parses it, and then executes the instruction.  Execution
 * begins by reading all of the data in from a file into the code memory in RAM on the host machine.
 * 
 */

int main() {
    // simple arithmetic program
    c_mem[0] = 0b1000000000000000;
    c_mem[1] = 0b0010100000000000;
    c_mem[2] = 0b0101100000000011;
    c_mem[3] = 0b1010100000000001;

    // initial data memory setup
    d_mem[0] = 2;

    while(program_counter < 4) {
        // current instruction to be executed
        ParsedInst inst = parse_opcode(c_mem[program_counter]);
        switch(inst.opcode) {
            case NOOP:
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
        printf("Contents of data memory:\n");
        print_d_mem_hex();
        print_regs_hex();

        program_counter++;
    }

    return 0;
}