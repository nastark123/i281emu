#include "control.h"

void parse_and_exec_cmd(char *str, CommandInfo *ci, HardwareInfo *hi) {
    Command cmd = parse_cmd(str);

    switch(cmd.id) {

        case RUN:
            run(ci);
            break;

        case BREAK:
            add_break(cmd, ci, hi);
            break;

        case CLEAR:
            clear(cmd, ci, hi);
            break;

        case CONT:
            cont(ci);
            break;

        case DUMP:
            dump(cmd, hi);
            break;

        case PRINT:
            print(cmd, hi);
            break;

        case TIME:
            print_time(ci);
            break;

        case HELP:
            help();
            break;

        case QUIT:
            quit();
            break;

        default:
            printf("Error: Unrecognized command\n");
            printf("Type \"help\" for a list of commands\n");
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

int prompt_cmd(char *custom_msg, char *str, int n) {
    if(custom_msg != NULL) {
        printf("%s\n", custom_msg);
    }

    printf("i281emu> ");
    if(fgets(str, n, stdin) == NULL) return -1;
    // remove the newline
    str[strlen(str) - 1] = '\0';
    return strlen(str);
}

void print_welcome() {
    printf("Welcome to i281emu version %d.%d.%d\n", VERSION_MAJOR, VERSION_MINOR, VERSION_BUGFIX);
    printf("Written by Nathan Stark for CPR E 281 Digital Logic Fall 2021\n");
    printf("Based on the i281 CPU designed by Prof. Alexander Stoytchev at Iowa State University\n");
    printf("Enter any command to begin operation\n\n");
}