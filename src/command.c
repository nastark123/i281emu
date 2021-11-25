#include "command.h"

const char *cmds[] = {"run", "break", "clear", "cont", "next", "print", "time"};

int cmd_to_id(const char *cmd) {
    for(int i = 0; i < sizeof(cmds); i++) {
        if(strcmp(cmd, cmds[i]) == 0) {
            return i;
        }
    }

    return -1;
}

Command parse_cmd(char *cmd) {
    Command c;

    c.id = cmd_to_id(cmd);

    char *extra = strchr(cmd, ' ');
    c.extra = malloc(sizeof(char) * (strlen(extra) + 1));
    strcpy(c.extra, extra);

    return c;
}

void run(CommandInfo *info) {

}

void add_break(Command c, CommandInfo *info) {

}

void clear(Command c, CommandInfo *info) {

}

void cont(CommandInfo *info) {

}

void next(CommandInfo *info) {

}

void print(Command c) {

}

void print_time() {

}