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
        c.extra = malloc(sizeof(char) * (strlen(extra) + 1));
        strcpy(c.extra, extra);
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
    char *end;
    int line = strtol(c.extra, end, 10);

    // end will be NULL if the conversion succeeded
    // TODO maybe clean this up
    if(end == NULL) {
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

void clear(Command c, CommandInfo *ci) {

}

void cont(CommandInfo *ci) {
    ci->run = true;
    printf("Continuing...\n");
}

void next(CommandInfo *ci, HardwareInfo *hi) {
    // this seems hacky, but its the cleanest way I can come up with to implement this
    parse_and_exec(hi->c_mem[hi->program_counter], hi);
}

void print(Command c) {


    // this is bad, but I didn't have time to implement a hash map, and didn't want to restrict myself to POSIX
}

void print_time(CommandInfo *ci) {
    double time_secs = (double)ci->time_taken / CLOCKS_PER_SEC;
    printf("~%.03lf milliseconds taken (this number is approximate for low instruction counts)\n", 1e3 * time_secs);
    printf("~%.02lf million instructions per second\n", ci->instructions_executed / time_secs);
}