/**
 * 
 * This header file defines function prototypes for functions that will be used to implement large portions of the program.  This allows for the main() function to be
 * less cluttered and makes the code more modular and readable.
 * 
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "instructions.h"
#include "command.h"
#include "hardwaredefs.h"
#include "version.h"

// parses and executes a command read from the user
// str is the string read from the user
// CommandInfo is a bundle of relevant context from the main program that may be modified by the commands
void parse_and_exec_cmd(char *str, CommandInfo *ci, HardwareInfo *hi);

// parses and executes an instruction
// TODO modify this to use a similar structure to the parse_and_exec_cmd() function to avoid globals
void parse_and_exec(uint16_t inst, HardwareInfo *hi);

// prompts the user to input a command and stores up to the first n bytes of it into str
// a custom message can also be sent to the user
// returns the number of characters read, or -1 on error
int prompt_cmd(char *custom_msg, char *str, int n);

// prints the welcome message
void print_welcome();

#endif