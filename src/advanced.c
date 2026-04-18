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
