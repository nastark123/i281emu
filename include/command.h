#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// struct that bundles the data necessary to execute commands
typedef struct {
    LLNode *head;
    bool break_after_next;
} CommandInfo;

// struct that represents a command
typedef struct {
    int id; // id of the command
    char *extra; // extra data passed with the command
} Command;

// number of commands
#define NUM_CMDS 

// array of all recognized commands that can be inputted by user
extern const char *cmds[];

#define RUN 0x00
#define BREAK 0x01
#define CLEAR 0x02
#define CONT 0x03
#define NEXT 0x04
#define PRINT 0x05
#define TIME 0x06

// converts the string representation of a command to its id
int cmd_to_id(const char *cmd);

// parses the command stored in str and returns a Command struct
Command parse_cmd(char *str);

// function prototypes for each of the commands that will have to be implemented

// run the program
void run(CommandInfo *info);

// add a break_point
// corresponds to the break command, but break is a C keyword
void add_break(Command c, CommandInfo *info);

// clear a breakpoint
void clear(Command c, CommandInfo *info);

// continue from a breakpoint
void cont(CommandInfo *info);

// execute the next instruction
void next(CommandInfo *info);

// print a value, can be from a register, data memory, or code memory addresss
void print(Command c);

// print the current amount of time that the program has used
// called print_time to avoid naming conflicts
void print_time();

#endif