#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "control.h"
#include "hardwaredefs.h"
#include "instructions.h"
#include "fileparse.h"

/**
 * 
 * Main code that is responsible for the emulation of the i281 processor.  Reads one instruction at a time, parses it, and then executes the instruction.  Execution
 * begins by reading all of the data in from a file into the code memory in RAM on the host machine.
 * 
 */

int main(int argc, char *argv[]) {

    // struct that will store the program counter, alu flag, registers, data memory, and code memory
    HardwareInfo hi;
    memset(&hi, 0, sizeof(hi));

    int instructions_executed = 0;

    int num_opcodes = parse_binary_bin(argv[1], hi.c_mem, C_MEM_SIZE);

    int num_data = parse_d_mem_bin(argv[1], hi.d_mem, D_MEM_SIZE);

    printf("Read %d opcodes from file\n", num_opcodes);
    printf("Read %d bytes from data segment\n\n", num_data);

    for(int i = 0; i < num_opcodes; i++) {
        print_bin((uint8_t)(hi.c_mem[i] >> 8));
        print_bin((uint8_t) hi.c_mem[i]);
        printf("\n");
    }

    clock_t start = clock();

    while(hi.program_counter < num_opcodes) {
        
        parse_and_exec(hi.c_mem[hi.program_counter], &hi);

        hi.program_counter++;
        instructions_executed++;
    }

    clock_t end = clock();

    printf("Final contents of data memory:\n");
    print_d_mem_hex(hi);
    print_regs_hex(hi);
    printf("ALU flags: %d", hi.alu_flag);
    printf("\n\n");

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double inst_per_sec = instructions_executed / time_sec;

    printf("Program done\n");
    printf("%d instructions executed in ~%.03lf milliseconds (~%.02lf million instructions per second)\n", instructions_executed, time_sec * 1e3, inst_per_sec / 1e6);


    return 0;
}