#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

// dict of commands
typedef struct {
    char **args;         // array of command args
    char *output_file;   // output redirection file
    int background;      // background exec  flag
    int arg_count;       // number of args
} Command;

Command* parse_command(char *input);
void free_command(Command *cmd);

#endif