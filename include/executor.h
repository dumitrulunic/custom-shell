#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"
#include "parser.h"

int process_command(char *command);
int execute_command(Command *cmd);
void execute_builtin_command(Command *cmd);

#endif // EXECUTOR_H