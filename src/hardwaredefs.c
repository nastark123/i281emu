#include "hardwaredefs.h"

// initialize program counter to 
uint8_t program_counter = 0;

int8_t regs[4] = {0, 0, 0, 0};

uint8_t alu_flag = 0;

uint16_t c_mem[C_MEM_SIZE];

int8_t d_mem[D_MEM_SIZE];

void print_regs_bin() {
    printf("Register A: ");
    print_bin((uint8_t) regs[0]);

    printf("\tRegister B: ");
    print_bin((uint8_t) regs[1]);

    printf("\nRegister C: ");
    print_bin((uint8_t) regs[2]);

    printf("\tRegister D: ");
    print_bin((uint8_t) regs[3]);

    printf("\n");
}

void print_regs_hex() {
    printf("Register A: 0x%02x", regs[0]);

    printf("\tRegister B: 0x%02x", regs[1]);

    printf("\nRegister C: 0x%02x", regs[2]);

    printf("\tRegister D: 0x%02x", regs[3]);

    printf("\n");
}

void print_d_mem_bin() {
    for(int i = 0; i < D_MEM_SIZE - 1; i++) {
        print_bin((uint8_t) d_mem[i]);
        printf(" ");
        if((i + 1) != 0 && (i + 1) % 8 == 0) printf("\n");
    }
    print_bin((uint8_t) d_mem[D_MEM_SIZE - 1]);
    printf("\n");
}

void print_d_mem_hex() {
    for(int i = 0; i < D_MEM_SIZE - 1; i++) {
        printf("0x%02x ", d_mem[i]);
        if((i -+ 1) != 0 && (i + 1) % 8 == 0) printf("\n");
    }
    printf("0x%02x\n", d_mem[D_MEM_SIZE - 1]);
}

void print_bin(uint8_t bin) {
    // I was going to use recursion for this but it doesn't seem to like leading 0's
    for(int8_t i = 7; i >= 0; i--) {
        uint8_t digit = (bin & (1 << i)) >> i;
        printf("%d", digit);
    }
}