#include "shell.h"
#include "parser.h"
#include "executor.h"

static int shell_status = SHELL_RUNNING;
static pid_t background_processes[100];  // Store background process PIDs
static int process_count = 0;

void print_prompt() {
    char hostname[1024];
    char username[1024];
    
    gethostname(hostname, sizeof(hostname));
    getlogin_r(username, sizeof(username));
    
    printf("%s@%s> ", username, hostname);
    fflush(stdout);
}

void handle_background_process(pid_t pid) {
    if (process_count < 100) {
        background_processes[process_count++] = pid;
    }
}

void check_background_processes() {
    int status;
    pid_t pid;
    
    for (int i = 0; i < process_count; i++) {
        pid = waitpid(background_processes[i], &status, WNOHANG);
        if (pid > 0) {
            printf("[Process completed] PID: %d\n", pid);
            // Remove process from array and shift others
            for (int j = i; j < process_count - 1; j++) {
                background_processes[j] = background_processes[j + 1];
            }
            process_count--;
            i--; // Adjust index since we removed an element
        }
    }
}

void handle_quit() {
    if (process_count > 0) {
        printf("The following processes are running, are you sure you want to quit? [Y/n]\n");
        for (int i = 0; i < process_count; i++) {
            printf("PID: %d\n", background_processes[i]);
        }
        
        char response;
        scanf(" %c", &response);
        
        if (response == 'Y' || response == 'y') {
            // Terminate all background processes
            for (int i = 0; i < process_count; i++) {
                kill(background_processes[i], SIGTERM);
            }
            shell_status = SHELL_EXIT;
        }
    } else {
        shell_status = SHELL_EXIT;
    }
}

void shell_loop() {
    char input[MAX_INPUT_SIZE];
    
    while (shell_status == SHELL_RUNNING) {
        print_prompt();
        
        // Check if any background processes have completed
        check_background_processes();
        
        // Read input
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            break;
        }
        
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;
        
        // Process the command
        if (strlen(input) > 0) {
            process_command(input);
        }
    }
}