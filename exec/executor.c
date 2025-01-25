#include "executor.h"


// the functions 
void execute_builtin_command(Command *command) {
    if (strcmp(command -> args[0], "globalusage") == 0) {
        if (command -> output_file != NULL) {
            int fd = open(command -> output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                return;
            }
            int stdout_ = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            printf("IMCSH Version %s created by Andrei-Flavius Văcaru & Dumitru Lunic\n", SHELL_VERSION);
            fflush(stdout);
            dup2(stdout_, STDOUT_FILENO);
            close(fd);
            close(stdout_);
        } else {
            printf("IMCSH Version %s created by Andrei-Flavius Văcaru & Dumitru Lunic\n", SHELL_VERSION);
        }
    } else if (strcmp(command ->args[0], "quit") == 0) {
        handle_quit();
    }
}

int execute_command(Command *command) {
    if (command -> arg_count == 0) return 0;
    
    // check for already defined commands first
    if (strcmp(command -> args[0], "globalusage") == 0 || 
        strcmp(command -> args[0], "quit") == 0) {
        execute_builtin_command(command);
        return 0;
    }
    
    // check for exec
    if (strcmp(command -> args[0], "exec") != 0) {
        printf("Error: Command must start with 'exec'\n");
        return 1;
    }
    
    // remove exec from command args
    for (int i = 0; i < command -> arg_count - 1; i++) {
        command -> args[i] = command -> args[i + 1];
    }
    command -> arg_count--;
    command -> args[command->arg_count] = NULL;
    
    // check for background process
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    
    if (pid == 0) {  // child process
        // Handle output redirection
        if (command -> output_file != NULL) {
            int fd = open(command -> output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("Failed to open output file");
                exit(1);
            }
            if (dup2(fd, STDOUT_FILENO) < 0) {
                perror("Failed to redirect output");
                close(fd);
                exit(1);
            }
            close(fd);
        }
        
        execvp(command -> args[0], command -> args);
        perror("Execution failed");
        exit(1);
    }
    
    // Parent process
    if (!command -> background) {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Process with PID: %d, finished having exit status: %d\n", 
                   pid, WEXITSTATUS(status));
        } else {
            printf("Process with PID: %d\n, is terminated", pid);
        }
    } else {
        handle_background_process(pid);
        printf("Background process started with PID: %d\n", pid);
    }
    
    return 0;
}

int process_command(char *command) {
    Command *cmd = parse_command(command);
    int result = execute_command(cmd);
    free_command(cmd);
    return result;
}