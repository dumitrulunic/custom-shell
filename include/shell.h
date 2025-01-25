#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64
#define SHELL_VERSION "1.1"

// Shell status codes
#define SHELL_RUNNING 1
#define SHELL_EXIT 0

// Function declarations
void shell_loop(void);
void print_prompt(void);
int process_command(char *command);
void handle_quit(void);
void handle_background_process(pid_t pid);

#endif // SHELL_H