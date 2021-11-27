#include "command.h"

const char *cmds[] = {"run", "break", "clear", "cont", "next", "print", "time"};

int cmd_to_id(const char *cmd) {
    for(int i = 0; i < NUM_CMDS; i++) {
        if(strncmp(cmd, cmds[i], strlen(cmds[i])) == 0) {
            return i;
        }
    }

    return -1;
}

Command parse_cmd(char *cmd) {
    Command c;

    c.id = cmd_to_id(cmd);

    char *extra = strchr(cmd, ' ');
    if(extra != NULL) {
        c.extra = malloc(sizeof(char) * (strlen(extra)));
        strcpy(c.extra, extra + 1);
    } else {
        c.extra = NULL;
    }

    return c;
}

void run(CommandInfo *ci) {
    ci->run = true;
}

void add_break(Command c, CommandInfo *ci, HardwareInfo *hi) {
    // char pointer to check for strtol errors
    char *end = NULL;
    int line = strtol(c.extra, &end, 10);

    if(*end == '\0') {
        // check if the instruction is out of bounds of valid range
        if(line >= hi->num_opcodes || line < 0) {
            printf("Error adding breakpoint: instruction number out of range\n");
            return;
        }

        LLNode *node = malloc(sizeof(LLNode));
        node->data.i = line;

        ci->break_head = ll_add(ci->break_head, node);

        printf("Breakpoint added for instruction %d\n", line);
    } else if(strcmp(end, c.extra) == 0) {
        printf("Error adding breakpoint: unable to parse instruction number\n");
        return;
    }
}

void clear(Command c, CommandInfo *ci, HardwareInfo *hi) {
    // char pointer to check for strtol errors
    char *end = NULL;
    int line = strtol(c.extra, &end, 10);

    if(*end == '\0') {
        // check if the instruction is out of bounds of valid range
        if(line >= hi->num_opcodes || line < 0) {
            printf("Error adding breakpoint: instruction number out of range\n");
            return;
        }

        LLNodeData data;
        data.i = line;
        int index = ll_contains(ci->break_head, data);
        if(index < 0) {
            printf("No breakpoint at specified line\n");
            return;
        }
        ci->break_head = ll_remove(ci->break_head, index);

        printf("Breakpoint removed for instruction %d\n", line);
    } else if(strcmp(end, c.extra) == 0) {
        printf("Error adding breakpoint: unable to parse instruction number\n");
        return;
    }
}

void cont(CommandInfo *ci) {
    ci->run = true;
    printf("Continuing...\n");
}

void next(CommandInfo *ci, HardwareInfo *hi) {
    // // this seems hacky, but its the cleanest way I can come up with to implement this
    // parse_and_exec(hi->c_mem[hi->program_counter], hi);
}

void print(Command c, HardwareInfo *hi) {
    // this is bad, but I didn't have time to implement a hash map, and didn't want to restrict myself to POSIX
    int address = -1; // address that will be read from
    if(strncmp(c.extra, "dmem", 4) == 0) {
        sscanf(c.extra, " %*s %d", &address);
        if(address < D_MEM_SIZE && address >= 0) {
            printf("Contents of data memory address %d: 0x%02x\n", address, hi->d_mem[address]);
            return;
        }
    } else if(strncmp(c.extra, "cmem", 4) == 0) {
        sscanf(c.extra, " %*s %d", &address);
        if(address < C_MEM_SIZE && address >= 0) {
            ParsedInst inst = parse_opcode(hi->c_mem[address]);
            printf("Contents of code memory address %d: 0x%04x (%s instruction)\n", address, hi->c_mem[address], opcode_to_str(inst));
            return;
        }
    } else if(strncmp(c.extra, "reg", 3) == 0) {
        sscanf(c.extra, " %*s %d", &address);
        if(address < 4 && address >= 0) {
            printf("Contents of register %c: 0x%02x\n", address + 'A', hi->regs[address]);
            return;
        }
    } else {
        printf("Invalid location specified.  Valid locations are dmem, cmem, and reg\n");
        return;
    }

    printf("Address out of range\n");
}

void print_time(CommandInfo *ci) {
    double time_secs = (double)ci->time_taken / CLOCKS_PER_SEC;
    printf("%d instructions executed in ~%.03lf milliseconds (this number is approximate for low instruction counts)\n", ci->instructions_executed, 1e3 * time_secs);
    printf("~%.02lf million instructions per second\n", ci->instructions_executed / time_secs / 1e6);
}