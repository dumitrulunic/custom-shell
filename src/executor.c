#include "executor.h"

void execute_builtin_command(Command *cmd) {
    if (strcmp(cmd->args[0], "globalusage") == 0) {
        printf("IMCSH Version %s created by Andrei-Flavius Văcaru and Dumitru Lunic\n", SHELL_VERSION);
    } else if (strcmp(cmd->args[0], "quit") == 0) {
        handle_quit();
    }
}

int is_builtin_command(const char *cmd) {
    return (strcmp(cmd, "globalusage") == 0 || 
            strcmp(cmd, "quit") == 0);
}

int execute_command(Command *cmd) {
    if (cmd->arg_count == 0) return 0;
    
    // Check for built-in commands
    if (is_builtin_command(cmd->args[0])) {
        execute_builtin_command(cmd);
        return 0;
    }
    
    // Check if it's an exec command
    if (strcmp(cmd->args[0], "exec") != 0) {
        printf("Error: Command must start with 'exec'\n");
        return 1;
    }
    
    // Remove "exec" from arguments
    for (int i = 0; i < cmd->arg_count - 1; i++) {
        cmd->args[i] = cmd->args[i + 1];
    }
    cmd->arg_count--;
    cmd->args[cmd->arg_count] = NULL;
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid == 0) {  // Child process
        // Handle output redirection
        if (cmd->output_file != NULL) {
            int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        
        execvp(cmd->args[0], cmd->args);
        perror("Execution failed");
        exit(1);
    }
    
    // Parent process
    if (!cmd->background) {
        int status;
        waitpid(pid, &status, 0);
        printf("[Process completed] PID: %d\n", pid);
    } else {
        handle_background_process(pid);
        printf("[Background process started] PID: %d\n", pid);
    }
    
    return 0;
}

int process_command(char *command) {
    Command *cmd = parse_command(command);
    int result = execute_command(cmd);
    free_command(cmd);
    return result;
}