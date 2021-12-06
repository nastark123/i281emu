#ifndef COMMAND_H
#define COMMAND_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "hardwaredefs.h"
#include "linkedlist.h"
#include "instructions.h"

// struct that bundles the data necessary to execute commands
typedef struct {
    LLNode *break_head; // head of the linked list that stores the breakpoints
    clock_t time_taken; // amount of time spent actually executing the program
    int instructions_executed; // number of instructions executed
    bool run; // whether or not the program should resume execution of the file being emulated or prompt for another command
} CommandInfo;

// struct that represents a command
typedef struct {
    int id; // id of the command
    char *extra; // extra data passed with the command
} Command;

#define NUM_CMDS 9

// array of all recognized commands that can be inputted by user
extern const char *cmds[];

#define RUN 0x00
#define BREAK 0x01
#define CLEAR 0x02
#define CONT 0x03
#define DUMP 0x04
#define PRINT 0x05
#define TIME 0x06
#define HELP 0x07
#define QUIT 0x08

// converts the string representation of a command to its id
int cmd_to_id(const char *cmd);

// parses the command stored in str and returns a Command struct
Command parse_cmd(char *str);

// function prototypes for each of the commands that will have to be implemented

// run the program
void run(CommandInfo *ci);

// add a break_point
// corresponds to the break command, but break is a C keyword
void add_break(Command c, CommandInfo *ci, HardwareInfo *hi);

// clear a breakpoint
void clear(Command c, CommandInfo *ci, HardwareInfo *hi);

// continue from a breakpoint
void cont(CommandInfo *ci);

// dump the value of something either to the screen or to a file
// TODO add file dump
void dump(Command c, HardwareInfo *hi);

// print a value, can be from a register, data memory, or code memory addresss
void print(Command c, HardwareInfo *hi);

// print the current amount of time that the program has used
// called print_time to avoid naming conflicts
void print_time(CommandInfo *ci);

// displays the help dialog
void help();

// quits the emulator
void quit();

#endif