#include "parser.h"

// parse the command and return a Command dict
Command* parse_command(char *input) {
    Command *command = malloc(sizeof(Command));
    command->args = malloc(MAX_ARG_SIZE * sizeof(char*));
    command->output_file = NULL;
    command->background = 0;
    command->arg_count = 0;
    
    // copy input to avoid changing the original command
    char *input_ = strdup(input);
    char *current_word = strtok(input_, " ");
    
    // parse command and arguments
    while (current_word != NULL && command -> arg_count < MAX_ARG_SIZE - 1) {
        // check for output redirection to file
        if (strcmp(current_word, ">") == 0) {
            current_word = strtok(NULL, " ");
            if (current_word != NULL) {
                command -> output_file = strdup(current_word);
            }
            break;
        }
        
        // Check for background execution
        if (strcmp(current_word, "&") == 0) {
            command -> background = 1;
            break;
        }
        
        command -> args[command -> arg_count] = strdup(current_word);
        command -> arg_count++;
        current_word = strtok(NULL, " ");
    }
    
    command -> args[command -> arg_count] = NULL;  

    free(input_);
    
    return command;
}

// in order to free the memory allocated for the command
void free_command(Command *command) {
    if (command == NULL) return;
    
    for (int i = 0; i < command -> arg_count; i++) {
        free(command -> args[i]);
    }
    free(command -> args);
    
    if (command -> output_file != NULL) {
        free(command -> output_file);
    }
    
    free(command);
}