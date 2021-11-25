#include "control.h"

const char *cmds[] = {"run", "break", "clear", "cont", "next", "print", "time"};

int cmd_to_id(const char *cmd) {
    for(int i = 0; i < sizeof(cmds); i++) {
        if(strcmp(cmd, cmds[i]) == 0) {
            return i;
        }
    }

    return -1;
}



void parse_and_exec(uint16_t inst) {
    // current instruction to be executed
    ParsedInst parsed_inst = parse_opcode(inst);
    switch(parsed_inst.opcode) {

        case NOOP:
            printf("NOOP\n");
            break;

        case INPUT:
            input(parsed_inst);
            break;

        case MOVE:
            move(parsed_inst);
            break;

        case LOADI:
            loadi(parsed_inst);
            break;

        case ADD:
            add(parsed_inst);
            break;

        case ADDI:
            addi(parsed_inst);
            break;

        case SUB:
            sub(parsed_inst);
            break;

        case SUBI:
            subi(parsed_inst);
            break;

        case LOAD:
            load(parsed_inst);
            break;

        case LOADF:
            loadf(parsed_inst);
            break;

        case STORE:
            store(parsed_inst);
            break;

        case STOREF:
            storef(parsed_inst);
            break;

        case SHIFT:
            shift(parsed_inst);
            break;

        case CMP:
            cmp(parsed_inst);
            break;

        case JUMP:
            jump(parsed_inst);
            break;

        case BR:
            br(parsed_inst);
            break;
    }
}