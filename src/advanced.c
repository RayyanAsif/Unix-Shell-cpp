#include "shell.h"

int handle_background(char **args) {
    int i = 0;
    while (args[i] != NULL) i++;

    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        args[i - 1] = NULL; // Remove '&' so execvp doesn't see it
        return 1;
    }
    return 0;
}

void handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        // Append mode >>
        if (strcmp(args[i], ">>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) { perror("File open failed"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        // Overwrite mode >
        else if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) { perror("File open failed"); exit(1); }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }
        // Input redirection <
        else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            if (fd < 0) { perror("File open failed"); exit(1); }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}

void handle_pipes(char *input) {
    char *cmds[2];
    cmds[0] = strtok(input, "|");
    cmds[1] = strtok(NULL, "|");

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    if (fork() == 0) {
        // Left side of pipe: Write to pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        char *args[100];
        parse_input(cmds[0], args);
        execvp(args[0], args);
        exit(1);
    }

    if (fork() == 0) {
        // Right side of pipe: Read from pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        char *args[100];
        parse_input(cmds[1], args);
        execvp(args[0], args);
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
}
