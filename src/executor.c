#include "shell.h"

void execute_command(char **args) {
    pid_t pid = fork();

    if (pid == 0) {
        handle_redirection(args);
        execvp(args[0], args);
        perror("Execution failed");
        exit(1);
    } else {
        int background = handle_background(args);

        if (!background) {
            wait(NULL);
        }
    }
}
