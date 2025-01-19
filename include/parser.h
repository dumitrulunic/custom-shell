#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

typedef struct {
    char **args;         // Array of command arguments
    char *output_file;   // Output redirection file (if any)
    int background;      // Background execution flag
    int arg_count;       // Number of arguments
} Command;

Command* parse_command(char *input);
void free_command(Command *cmd);

#endif // PARSER_H