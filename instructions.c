#include "instructions.h"
#include "hardwaredefs.h"

ParsedInst parse_opcode(uint16_t inst) {
    ParsedInst p;
    p.opcode = (inst >> 12) & 0x0F;
    p.b23 = (inst >> 10) & 0x03;
    p.b01 = (inst >> 8) & 0x03;
    p.data = inst & 0xFF;

    return p;
}

void input(ParsedInst inst) {
    // TODO change this to be automatic
    if(inst.b01 == INPUTC || inst.b01 == INPUTCF) {
        printf("Input instruction reached, input a 16 bit binary number: ");
        char in[18];
        fgets(in, 18, stdin);
        in[16] = '\0'; // remove the newline
        uint16_t val = strtol(in, NULL, 2) & 0xFF;
        if(inst.b01 == INPUTC) {
            c_mem[inst.data] = val;
        } else {
            c_mem[inst.data + regs[inst.b23]] = val;
        }
    } else {
        printf("Input instruction reached, input an 8 bit binary number: ");
        char in[10];
        fgets(in, 10, stdin);
        in[8] = '\0'; // remove the newline
        int8_t val = strtol(in, NULL, 2) & 0xFF;
        if(inst.b01 == INPUTD) {
            d_mem[inst.data] = val;
        } else {
            d_mem[inst.data + regs[inst.b23]] = val;
        }
    }
}

void move(ParsedInst inst) {
    // the assembly data says that this is implemented as an addition with 0
    // this should execute faster so I wrote it this way
    regs[inst.b23] = regs[inst.b01];    
}

void loadi(ParsedInst inst) {
    regs[inst.b23] = inst.data;
}

void add(ParsedInst inst) {
    int16_t sum = regs[inst.b23] + regs[inst.b01];
    alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((regs[inst.b23] < 0 && regs[inst.b01] < 0) && sum >= 0) {
        alu_flag |= FLAG_O;
    } else if((regs[inst.b23] < 0 && regs[inst.b01] < 0) && sum <= 0) {
        alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        alu_flag |= FLAG_N;
    }

    regs[inst.b23] = sum & 0xFF;
}

void addi(ParsedInst inst) {
    int16_t sum = regs[inst.b23] + (int8_t) inst.data;
    alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((regs[inst.b23] < 0 && (int8_t) inst.data < 0) && sum >= 0) {
        alu_flag |= FLAG_O;
    } else if((regs[inst.b23] < 0 && (int8_t) inst.data < 0) && sum <= 0) {
        alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        alu_flag |= FLAG_N;
    }

    regs[inst.b23] = sum & 0xFF;
}

void sub(ParsedInst inst) {
    int8_t neg = -regs[inst.b01];
    int16_t sum = regs[inst.b23] + neg;
    alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((regs[inst.b23] < 0 && neg < 0) && sum >= 0) {
        alu_flag |= FLAG_O;
    } else if((regs[inst.b23] < 0 && neg < 0) && sum <= 0) {
        alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        alu_flag |= FLAG_N;
    }

    regs[inst.b23] = sum & 0xFF;
}

void subi(ParsedInst inst) {
    int16_t neg = -((int8_t) inst.data);
    int16_t sum = regs[inst.b23] + neg;
    alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((regs[inst.b23] < 0 && neg < 0) && sum >= 0) {
        alu_flag |= FLAG_O;
    } else if((regs[inst.b23] < 0 && neg < 0) && sum <= 0) {
        alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        alu_flag |= FLAG_N;
    }

    regs[inst.b23] = sum & 0xFF;
}

void load(ParsedInst inst) {
    regs[inst.b23] = d_mem[inst.data];
}

void loadf(ParsedInst inst) {
    uint16_t offset = inst.data + regs[inst.b01];
    if(offset > 255) {
        printf("Error loading from data memory, address out of range\n");
        return;
    }
    regs[inst.b23] = d_mem[offset];
}

void store(ParsedInst inst) {
    d_mem[inst.data] = regs[inst.b23];
}

void storef(ParsedInst inst) {
    uint16_t offset = inst.data + regs[inst.b01];
    d_mem[offset] = regs[inst.b23];
}

void shift(ParsedInst inst) {
    if((inst.b01 & 1) == SHIFTL) regs[inst.b23] <<= 1;
    else if((inst.b01 & 1) == SHIFTR) regs[inst.b23] >>= 1;
    else printf("Error: invalid shift specified");
}

void cmp(ParsedInst inst) {
    sub(inst);
    // int8_t res = regs[inst.b23] - regs[inst.b01];
    // alu_flags = 0;
    // if(res == 0) {
    //     alu_flags |= FLAG_Z;
    // }
    // if(res < 0) {
    //     alu_flags |= FLAG_N;
    // }
}

void jump(ParsedInst inst) {
    program_counter += 1 + ((int8_t) inst.data);
}

void br(ParsedInst inst) {
    switch(inst.b01) {
        case BRE:
            if((alu_flag & FLAG_Z) != 0) {
                program_counter += 1 + ((int8_t) inst.data);
            }
            break;

        case BRNE:
            if((alu_flag & FLAG_Z) == 0) {
                program_counter += 1 + ((int8_t) inst.data);
            }
            break;

        case BRG:
            if((alu_flag & FLAG_Z) == 0 && (alu_flag & (FLAG_O | FLAG_N)) == 0
                || (alu_flag & (FLAG_O | FLAG_N)) == (FLAG_O | FLAG_N)) {
                
                program_counter += 1 + ((int8_t) inst.data);
            }
            break;

        case BRGE:
            if((alu_flag & (FLAG_O | FLAG_N)) == 0 || (alu_flag & (FLAG_O | FLAG_N)) == (FLAG_O | FLAG_N)) {
                
                program_counter += 1 + ((int8_t) inst.data);
            }
            break;
    }
}