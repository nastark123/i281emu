#include "hardwaredefs.h"

void print_regs_bin(HardwareInfo hi) {
    printf("Register A: ");
    print_bin((uint8_t) hi.regs[0]);

    printf("\tRegister B: ");
    print_bin((uint8_t) hi.regs[1]);

    printf("\nRegister C: ");
    print_bin((uint8_t) hi.regs[2]);

    printf("\tRegister D: ");
    print_bin((uint8_t) hi.regs[3]);

    printf("\n");
}

void print_regs_hex(HardwareInfo hi) {
    printf("Register A: 0x%02x", hi.regs[0]);

    printf("\tRegister B: 0x%02x", hi.regs[1]);

    printf("\nRegister C: 0x%02x", hi.regs[2]);

    printf("\tRegister D: 0x%02x", hi.regs[3]);

    printf("\n");
}

void print_d_mem_bin(HardwareInfo hi) {
    for(int i = 0; i < D_MEM_SIZE - 1; i++) {
        print_bin((uint8_t) hi.d_mem[i]);
        printf(" ");
        if((i + 1) != 0 && (i + 1) % 8 == 0) printf("\n");
    }
    print_bin((uint8_t) hi.d_mem[D_MEM_SIZE - 1]);
    printf("\n");
}

void print_d_mem_hex(HardwareInfo hi) {
    for(int i = 0; i < D_MEM_SIZE - 1; i++) {
        printf("0x%02x ", hi.d_mem[i]);
        if((i -+ 1) != 0 && (i + 1) % 8 == 0) printf("\n"); // add a newline every 8 values
    }
    printf("0x%02x\n", hi.d_mem[D_MEM_SIZE - 1]);
}

void print_c_mem_hex(HardwareInfo hi) {
    for(int i = 0; i < D_MEM_SIZE - 1; i++) {
        printf("0x%04x ", hi.c_mem[i]);
        if((i -+ 1) != 0 && (i + 1) % 4 == 0) printf("\n"); // add a newline every 4 values
    }
    printf("0x%04x\n", hi.d_mem[D_MEM_SIZE - 1]);
}

void print_bin(uint8_t bin) {
    // I was going to use recursion for this but it doesn't seem to like leading 0's
    for(int8_t i = 7; i >= 0; i--) {
        uint8_t digit = (bin & (1 << i)) >> i;
        printf("%d", digit);
    }
}