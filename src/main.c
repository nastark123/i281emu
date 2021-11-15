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

    int instructions_executed = 0;

    int num_opcodes = parse_binary_bin(argv[1], c_mem, C_MEM_SIZE);

    int num_data = parse_d_mem_bin(argv[1], d_mem, D_MEM_SIZE);

    printf("Read %d opcodes from file\n", num_opcodes);
    printf("Read %d bytes from data segment\n\n", num_data);

    for(int i = 0; i < C_MEM_SIZE; i++) {
        print_bin((uint8_t)(c_mem[i] >> 8));
        print_bin((uint8_t) c_mem[i]);
        printf("\n");
    }

    clock_t start = clock();

    while(program_counter < num_opcodes) {
        
        parse_and_exec(c_mem[program_counter]);

        program_counter++;
        instructions_executed++;
    }

    clock_t end = clock();

    printf("Final contents of data memory:\n");
    print_d_mem_hex();
    print_regs_hex();
    printf("ALU flags: %d", alu_flag);
    printf("\n\n");

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double inst_per_sec = instructions_executed / time_sec;

    printf("Program done\n");
    printf("%d instructions executed in ~%.03lf milliseconds (~%.02lf million instructions per second)\n", instructions_executed, time_sec * 1e3, inst_per_sec / 1e6);


    return 0;
}