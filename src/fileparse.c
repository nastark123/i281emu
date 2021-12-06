#include "fileparse.h"

int parse_binary_bin(char *filename, uint16_t *out, size_t len) {
    FILE *in = fopen(filename, "r");
    if(in == NULL) return -1;
    char *buff = malloc(sizeof(char) * 128);

    bool found_code_section = false; // whether or not the parser has located the header for the machine code section

    size_t out_index = 0; // current index in the output array
    while(fgets(buff, 128, in) != NULL || out_index >= len) {

        buff[strlen(buff) - 1] = '\0'; // remove the trailing newline

        if(found_code_section) {
            if(buff[0] == '\0') break; // we read a blank line, which separates the code section from the next one (usually data segment)

            uint8_t num_bits = 0; // number of bits parsed from current line
            uint16_t parsed_line = 0; // the current line as binary

            for(uint8_t i = 0; i < strlen(buff); i++) {
                if(buff[i] == '1') {
                    parsed_line |= (1 << (15 - num_bits));
                    num_bits++;
                } else if(buff[i] == '0') {
                    num_bits++;
                }
            }

            if(num_bits != 16) {
                fclose(in);
                free(buff);
                return -1; // we didn't get a full line
            }
            out[out_index++] = parsed_line;
        }

        if(strcmp(buff, "-----MACHINE CODE-----") == 0) found_code_section = true;
    }

    fclose(in);
    free(buff);

    return out_index;
}

int parse_d_mem_bin(char *filename, int8_t *out, size_t len) {
    FILE *in = fopen(filename, "r");
    if(in == NULL) return -1;
    char *buff = malloc(sizeof(char) * 128);

    bool found_data_section = false; // whether or not the parser has located the header for the data segment section

    size_t out_index = 0; // current index in the output array
    while(fgets(buff, 128, in) != NULL || out_index >= len) {

        buff[strlen(buff) - 1] = '\0'; // remove the trailing newline

        if(found_data_section) {
            if(buff[0] == '\0') break; // we read a blank line, which separates the code section from the next one (usually data segment)

            uint8_t i = 0;

            while(!isdigit(buff[i])) i++;

            char *tok = strtok(&(buff[i]), ",");

            int cur_entry = 0;
            while(tok != NULL) {
                if(sscanf(tok, " %d ", &cur_entry) == 0) { // read the first entry
                    fclose(in);
                    free(buff);
                    return -1;
                }
                out[out_index++] = (int8_t) cur_entry;
                tok = strtok(NULL, ",");
            }

            break; // exit the loop after the line
        }

        if(strcmp(buff, "-----DATA SEGMENT-----") == 0) found_data_section = true;
    }

    fclose(in);
    free(buff);

    return out_index;
}