#include "shell.h"

void execute_command(char **args) {
    if (args[0] == NULL) return;

    // Check for '&' before forking so the parent knows whether to wait
    int background = handle_background(args);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process: handle I/O redirection then execute
        handle_redirection(args);
        if (execvp(args[0], args) == -1) {
            perror("Execution failed");
        }
        exit(1); 
    } else if (pid > 0) {
        // Parent process
        if (!background) {
            waitpid(pid, NULL, 0);
        } else {
            printf("[Process running in background: PID %d]\n", pid);
        }
    } else {
        perror("fork failed");
    }
}
