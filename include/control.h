/**
 * 
 * This header file defines function prototypes for functions that will be used to implement large portions of the program.  This allows for the main() function to be
 * less cluttered and makes the code more modular and readable.
 * 
 */

#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include "instructions.h"

// parses and executes an instruction
void parse_and_exec(uint16_t inst);



#endif