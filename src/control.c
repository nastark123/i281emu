#include "control.h"

void parse_and_exec_cmd(char *str, CommandInfo *ci, HardwareInfo *hi) {
    Command cmd = parse_cmd(str);

    switch(cmd.id) {

        case RUN:
            run(ci);
            break;

        case BREAK:
            add_break(cmd, ci);
            break;

        case CLEAR:
            clear(cmd, ci);
            break;

        case CONT:
            cont(ci);
            break;

        case NEXT:
            next(ci);
            break;

        case PRINT:
            print(cmd);
            break;

        case TIME:
            print_time();
            break;
    }
}


void parse_and_exec(uint16_t inst, HardwareInfo *hi) {
    // current instruction to be executed
    ParsedInst parsed_inst = parse_opcode(inst);
    switch(parsed_inst.opcode) {

        case NOOP:
            printf("NOOP\n");
            break;

        case INPUT:
            input(parsed_inst, hi);
            break;

        case MOVE:
            move(parsed_inst, hi);
            break;

        case LOADI:
            loadi(parsed_inst, hi);
            break;

        case ADD:
            add(parsed_inst, hi);
            break;

        case ADDI:
            addi(parsed_inst, hi);
            break;

        case SUB:
            sub(parsed_inst, hi);
            break;

        case SUBI:
            subi(parsed_inst, hi);
            break;

        case LOAD:
            load(parsed_inst, hi);
            break;

        case LOADF:
            loadf(parsed_inst, hi);
            break;

        case STORE:
            store(parsed_inst, hi);
            break;

        case STOREF:
            storef(parsed_inst, hi);
            break;

        case SHIFT:
            shift(parsed_inst, hi);
            break;

        case CMP:
            cmp(parsed_inst, hi);
            break;

        case JUMP:
            jump(parsed_inst, hi);
            break;

        case BR:
            br(parsed_inst, hi);
            break;
    }
}