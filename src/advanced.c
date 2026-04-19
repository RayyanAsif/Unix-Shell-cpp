#include "shell.h"

int handle_background(char **args) {
    int i = 0;
    while (args[i] != NULL) i++;

    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        args[i - 1] = NULL;
        return 1;
    }
    return 0;
}

void handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd >= 0) { dup2(fd, STDOUT_FILENO); close(fd); }
            args[i] = NULL;
        }
        else if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd >= 0) { dup2(fd, STDOUT_FILENO); close(fd); }
            args[i] = NULL;
        }
        else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            if (fd >= 0) { dup2(fd, STDIN_FILENO); close(fd); }
            args[i] = NULL;
        }
    }
}

// Updated: Supports infinite pipes (cmd1 | cmd2 | cmd3...)
void handle_pipes(char *input) {
    int num_cmds = 0;
    char *cmds[10];
    char *token = strtok(input, "|");
    
    while (token != NULL && num_cmds < 10) {
        cmds[num_cmds++] = token;
        token = strtok(NULL, "|");
    }

    int pipefds[2 * (num_cmds - 1)];
    for (int i = 0; i < (num_cmds - 1); i++) {
        if (pipe(pipefds + i * 2) < 0) return;
    }

    for (int i = 0; i < num_cmds; i++) {
        if (fork() == 0) {
            if (i > 0) dup2(pipefds[(i - 1) * 2], STDIN_FILENO);
            if (i < num_cmds - 1) dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
            
            for (int j = 0; j < 2 * (num_cmds - 1); j++) close(pipefds[j]);

            char *args[100];
            parse_input(cmds[i], args);
            expand_variables(args); // Ensure $vars work in pipes too
            execvp(args[0], args);
            exit(1);
        }
    }

    for (int i = 0; i < 2 * (num_cmds - 1); i++) close(pipefds[i]);
    for (int i = 0; i < num_cmds; i++) wait(NULL);
}
