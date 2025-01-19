#include "parser.h"

Command* parse_command(char *input) {
    Command *cmd = malloc(sizeof(Command));
    cmd->args = malloc(MAX_ARG_SIZE * sizeof(char*));
    cmd->output_file = NULL;
    cmd->background = 0;
    cmd->arg_count = 0;
    
    // Copy input to avoid modifying original
    char *input_copy = strdup(input);
    char *token = strtok(input_copy, " ");
    
    // Parse command and arguments
    while (token != NULL && cmd->arg_count < MAX_ARG_SIZE - 1) {
        // Check for output redirection
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                cmd->output_file = strdup(token);
            }
            break;
        }
        
        // Check for background execution
        if (strcmp(token, "&") == 0) {
            cmd->background = 1;
            break;
        }
        
        cmd->args[cmd->arg_count] = strdup(token);
        cmd->arg_count++;
        token = strtok(NULL, " ");
    }
    
    cmd->args[cmd->arg_count] = NULL;  // Null terminate argument list
    free(input_copy);
    
    return cmd;
}

void free_command(Command *cmd) {
    if (cmd == NULL) return;
    
    for (int i = 0; i < cmd->arg_count; i++) {
        free(cmd->args[i]);
    }
    free(cmd->args);
    
    if (cmd->output_file != NULL) {
        free(cmd->output_file);
    }
    
    free(cmd);
}