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

        // Append mode >>
        if (strcmp(args[i], ">>") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0) {
                perror("File open failed");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }

        // Overwrite mode >
        else if (strcmp(args[i], ">") == 0) {
            int fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("File open failed");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
        }

        // Input redirection <
        else if (strcmp(args[i], "<") == 0) {
            int fd = open(args[i+1], O_RDONLY);
            if (fd < 0) {
                perror("File open failed");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
        }
    }
}
