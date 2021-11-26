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

    hi.num_opcodes = parse_binary_bin(argv[1], hi.c_mem, C_MEM_SIZE);

    // struct that will store info to be passed to the command interpreter
    CommandInfo ci;
    memset(&ci, 0, sizeof(ci));
    // TODO initialize breakpoint list
    ci.break_head = NULL;

    // buffer to store user commands
    char *cmd_buff = malloc(sizeof(char) * 1024);
    memset(cmd_buff, 0, 1024);

    int num_data = parse_d_mem_bin(argv[1], hi.d_mem, D_MEM_SIZE);

    print_welcome();

    printf("Read %d opcodes from file\n", hi.num_opcodes);
    printf("Read %d bytes from data segment\n\n", num_data);

    // for(int i = 0; i < hi.num_opcodes; i++) {
    //     print_bin((uint8_t)(hi.c_mem[i] >> 8));
    //     print_bin((uint8_t) hi.c_mem[i]);
    //     printf("\n");
    // }

    int cmd_len = 0;
    
    while(!ci.run) {
        // prompt the user for a command
        prompt_cmd(NULL, cmd_buff, 1024);
        // execute the command read from the user
        parse_and_exec_cmd(cmd_buff, &ci, &hi);
    }

    clock_t start = clock();

    while(hi.program_counter < hi.num_opcodes) {

        // check if we hit a breakpoint
        LLNodeData data;
        data.i = hi.program_counter;
        if(ll_contains(ci.break_head, data)) {
            printf("Hit breakpoint at instruction %d\n", hi.program_counter);
            ci.run = false;
            while(!ci.run) {
                // prompt the user for a command
                prompt_cmd(NULL, cmd_buff, 1024);
                // execute the command read from the user
                parse_and_exec_cmd(cmd_buff, &ci, &hi);
            }
        }
        
        parse_and_exec(hi.c_mem[hi.program_counter], &hi);

        hi.program_counter++;
        ci.instructions_executed++;
    }

    clock_t end = clock();

    printf("Final contents of data memory:\n");
    print_d_mem_hex(hi);
    print_regs_hex(hi);
    printf("ALU flags: %d", hi.alu_flag);
    printf("\n\n");

    double time_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double inst_per_sec = ci.instructions_executed / time_sec;

    printf("Program done\n");
    printf("%d instructions executed in ~%.03lf milliseconds (~%.02lf million instructions per second)\n", ci.instructions_executed, time_sec * 1e3, inst_per_sec / 1e6);


    return 0;
}