#include "shell.h"

void parse_input(char *input, char **args) {
    char *token = strtok(input, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}
