#include "shell.h"
#include "parser.h"
#include "executor.h"
#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

static int shell_status = SHELL_RUNNING;
static pid_t background_processes[100]; // array for background PIDs
static int process_count = 0;

// remove process from the array when finished
void remove_process(pid_t pid) {
    for (int k = 0; k < process_count; k++) {
        if (background_processes[k] == pid) {
            // move remaining processes to the left
            for (int j = k; j < process_count - 1; j++) {
                background_processes[j] = background_processes[j + 1];
            }
            process_count--;
            break;
        }
    }
}

// signal handler for tracking background processes by PID
void sigchld_handler(int sig) {
    (void)sig; // suppress warning
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("\nBackground process completed with PID: %d\n", pid);
        remove_process(pid); // remove  completed process from the array
        print_prompt(); // print the prompt again
        fflush(stdout);
    }
}

// function to show the prompt to the user
void print_prompt() {
    char hostname[1024];
    char username[1024];
    

    gethostname(hostname, sizeof(hostname));
    getlogin_r(username, sizeof(username));
    
    printf("%s@%s> ", username, hostname);
    fflush(stdout);
}

// in order to handle the command, we need to parse
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
            printf("\nBackground process completed with PID: %d\n", pid);
            // remove process from array and shift others to left
            for (int k = i; k < process_count - 1; k++) {
                background_processes[k] = background_processes[k + 1];
            }
            process_count--;
            i--; // change index to check the next process 
        }
    }
}

// when quiting, we need to check if there are any background processes
void handle_quit() {
    if (process_count > 0) {
        printf("The following processes are running, are you sure you want to quit? [Y/n]\n");
        for (int k = 0; k < process_count; k++) {
            printf("PID: %d\n", background_processes[k]);
        }
        
        char response;
        scanf(" %c", &response);
        
        if (response == 'Y' || response == 'y') {
            // Terminate all background processes
            for (int k = 0; k < process_count; k++) {
                kill(background_processes[k], SIGTERM);
            }
            shell_status = SHELL_EXIT;
        }
    } else {
        shell_status = SHELL_EXIT;
    }
}

void shell_loop() {
    char input[MAX_INPUT_SIZE];

    // register the  handler to track background processes
    struct sigaction sa;
    sa.sa_handler = sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    while (shell_status == SHELL_RUNNING) {
        print_prompt();

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            break;
        }

        // remove newline
        input[strcspn(input, "\n")] = 0;

        // proces the command
        if (strlen(input) > 0) {
            process_command(input);
        }
    }
}