#ifndef FILEPARSE_H
#define FILEPARSE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

// parses the binary from a .bin file
int parse_binary_bin(char *filename, uint16_t *out, size_t len);

// parses the initial data memory from a .bin file
int parse_d_mem_bin(char *filename, int8_t *out, size_t len);

#endif