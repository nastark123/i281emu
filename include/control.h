/**
 * 
 * This header file defines function prototypes for functions that will be used to implement large portions of the program.  This allows for the main() function to be
 * less cluttered and makes the code more modular and readable.
 * 
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <string.h>
#include <time.h>
#include "instructions.h"
#include "vector.h"

// array of all recognized commands that can be inputted by user
extern const char *cmds[];

// head of linked list that will store breakpoints


#define RUN 0x00
#define BREAK 0x01
#define CLEAR 0x02
#define CONT 0x03
#define NEXT 0x04
#define PRINT 0x05
#define TIME 0x06

// converts the string representation of a command to its id
int cmd_to_id(const char *cmd);

// parses and executes an instruction
void parse_and_exec(uint16_t inst);



#endif