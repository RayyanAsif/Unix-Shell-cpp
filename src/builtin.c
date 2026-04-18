#include "shell.h"

int handle_builtin(char **args) {
    if (args[0] == NULL) return 1;

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(args[0], "cd") == 0) {
        chdir(args[1]);
        return 1;
    }

    if (strcmp(args[0], "pwd") == 0) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        return 1;
    }

    return 0;
}
