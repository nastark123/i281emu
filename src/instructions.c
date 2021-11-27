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

char* opcode_to_str(ParsedInst inst) {
    switch(inst.opcode) {
        case NOOP:
            return "NOOP";

        case INPUT:
            return "INPUT";

        case MOVE:
            return "MOVE";

        case LOADI:
            return "LOADI";

        case ADD:
            return "ADD";

        case ADDI:
            return "ADDI";

        case SUB:
            return "SUB";

        case SUBI:
            return "SUBI";

        case LOAD:
            return "LOAD";

        case LOADF:
            return "LOADF";

        case STORE:
            return "STORE";

        case STOREF:
            return "STOREF";

        case SHIFT:
            return "SHIFT";

        case CMP:
            return "CMP";

        case JUMP:
            return "JUMP";

        case BR:
            return "BR";

        default:
            return "INVALID";
    }
}

void input(ParsedInst inst, HardwareInfo *hi) {
    // TODO change this to be automatic
    if(inst.b01 == INPUTC || inst.b01 == INPUTCF) {
        printf("Input instruction reached, input a 16 bit binary number: ");
        char in[18];
        fgets(in, 18, stdin);
        in[16] = '\0'; // remove the newline
        uint16_t val = strtol(in, NULL, 2) & 0xFF;
        if(inst.b01 == INPUTC) {
            hi->c_mem[inst.data] = val;
        } else {
            hi->c_mem[inst.data + hi->regs[inst.b23]] = val;
        }
    } else {
        printf("Input instruction reached, input an 8 bit binary number: ");
        char in[10];
        fgets(in, 10, stdin);
        in[8] = '\0'; // remove the newline
        int8_t val = strtol(in, NULL, 2) & 0xFF;
        if(inst.b01 == INPUTD) {
            hi->d_mem[inst.data] = val;
        } else {
            hi->d_mem[inst.data + hi->regs[inst.b23]] = val;
        }
    }
}

void move(ParsedInst inst, HardwareInfo *hi) {
    // the assembly data says that this is implemented as an addition with 0
    // this should execute faster so I wrote it this way
    hi->regs[inst.b23] = hi->regs[inst.b01];    
}

void loadi(ParsedInst inst, HardwareInfo *hi) {
    hi->regs[inst.b23] = inst.data;
}

void add(ParsedInst inst, HardwareInfo *hi) {
    int16_t sum = hi->regs[inst.b23] + hi->regs[inst.b01];
    hi->alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        hi->alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((hi->regs[inst.b23] < 0 && hi->regs[inst.b01] < 0) && sum >= 0) {
        hi->alu_flag |= FLAG_O;
    } else if((hi->regs[inst.b23] < 0 && hi->regs[inst.b01] < 0) && sum <= 0) {
        hi->alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        hi->alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        hi->alu_flag |= FLAG_N;
    }

    hi->regs[inst.b23] = sum & 0xFF;
}

void addi(ParsedInst inst, HardwareInfo *hi) {
    int16_t sum = hi->regs[inst.b23] + (int8_t) inst.data;
    hi->alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        hi->alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((hi->regs[inst.b23] < 0 && (int8_t) inst.data < 0) && sum >= 0) {
        hi->alu_flag |= FLAG_O;
    } else if((hi->regs[inst.b23] < 0 && (int8_t) inst.data < 0) && sum <= 0) {
        hi->alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        hi->alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        hi->alu_flag |= FLAG_N;
    }

    hi->regs[inst.b23] = sum & 0xFF;
}

void sub(ParsedInst inst, HardwareInfo *hi) {
    int8_t neg = -hi->regs[inst.b01];
    int16_t sum = hi->regs[inst.b23] + neg;
    hi->alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        hi->alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((hi->regs[inst.b23] < 0 && neg < 0) && sum >= 0) {
        hi->alu_flag |= FLAG_O;
    } else if((hi->regs[inst.b23] < 0 && neg < 0) && sum <= 0) {
        hi->alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        hi->alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        hi->alu_flag |= FLAG_N;
    }

    hi->regs[inst.b23] = sum & 0xFF;
}

void subi(ParsedInst inst, HardwareInfo *hi) {
    int16_t neg = -((int8_t) inst.data);
    int16_t sum = hi->regs[inst.b23] + neg;
    hi->alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        hi->alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((hi->regs[inst.b23] < 0 && neg < 0) && sum >= 0) {
        hi->alu_flag |= FLAG_O;
    } else if((hi->regs[inst.b23] < 0 && neg < 0) && sum <= 0) {
        hi->alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        hi->alu_flag |= FLAG_C;
    }

    // check negative
    if((sum & 0xFF) < 0) {
        hi->alu_flag |= FLAG_N;
    }

    hi->regs[inst.b23] = sum & 0xFF;
}

void load(ParsedInst inst, HardwareInfo *hi) {
    hi->regs[inst.b23] = hi->d_mem[inst.data];
}

void loadf(ParsedInst inst, HardwareInfo *hi) {
    uint16_t offset = inst.data + hi->regs[inst.b01];
    if(offset > 255) {
        printf("Error loading from data memory, address out of range\n");
        return;
    }
    hi->regs[inst.b23] = hi->d_mem[offset];
}

void store(ParsedInst inst, HardwareInfo *hi) {
    hi->d_mem[inst.data] = hi->regs[inst.b23];
}

void storef(ParsedInst inst, HardwareInfo *hi) {
    uint16_t offset = inst.data + hi->regs[inst.b01];
    hi->d_mem[offset] = hi->regs[inst.b23];
}

void shift(ParsedInst inst, HardwareInfo *hi) {
    if((inst.b01 & 1) == SHIFTL) hi->regs[inst.b23] <<= 1;
    else if((inst.b01 & 1) == SHIFTR) hi->regs[inst.b23] >>= 1;
    else printf("Error: invalid shift specified");
}

void cmp(ParsedInst inst, HardwareInfo *hi) {
    int8_t neg = -hi->regs[inst.b01];
    int16_t sum = hi->regs[inst.b23] + neg;
    hi->alu_flag = 0;
    // check zero
    if((sum & 0xFF) == 0) {
        hi->alu_flag |= FLAG_Z;
    }
    // TODO make this better
    // check overflow
    if((hi->regs[inst.b23] < 0 && neg < 0) && sum >= 0) {
        hi->alu_flag |= FLAG_O;
    } else if((hi->regs[inst.b23] < 0 && neg < 0) && sum <= 0) {
        hi->alu_flag |= FLAG_O;
    }

    // check carry
    if((sum >> 8) & 1) {
        hi->alu_flag |= FLAG_C;
    }

    // check negative
    if((int8_t) sum < 0) {
        hi->alu_flag |= FLAG_N;
    }
}

void jump(ParsedInst inst, HardwareInfo *hi) {
    // hi->program_counter += 1 + ((int8_t) inst.data);
    hi->program_counter += ((int8_t) inst.data);
}

void br(ParsedInst inst, HardwareInfo *hi) {
    switch(inst.b01) {
        case BRE:
            if((hi->alu_flag & FLAG_Z) != 0) {
                // hi->program_counter += 1 + ((int8_t) inst.data);
                hi->program_counter += ((int8_t) inst.data);
            }
            break;

        case BRNE:
            if((hi->alu_flag & FLAG_Z) == 0) {
                // hi->program_counter += 1 + ((int8_t) inst.data);
                hi->program_counter += ((int8_t) inst.data);
            }
            break;

        case BRG:
            if(((hi->alu_flag & FLAG_Z) == 0 && (hi->alu_flag & (FLAG_O | FLAG_N)) == 0)
                || (hi->alu_flag & (FLAG_O | FLAG_N)) == (FLAG_O | FLAG_N)) {
                
                // hi->program_counter += 1 + ((int8_t) inst.data);
                hi->program_counter += ((int8_t) inst.data);
            }
            break;

        case BRGE:
            if((hi->alu_flag & (FLAG_O | FLAG_N)) == 0 || (hi->alu_flag & (FLAG_O | FLAG_N)) == (FLAG_O | FLAG_N)) {
                
                // hi->program_counter += 1 + ((int8_t) inst.data);
                hi->program_counter += ((int8_t) inst.data);
            }
            break;
    }
}