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

// Added: Replaces $VAR with actual environment values
void expand_variables(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (args[i][0] == '$') {
            char *env_val = getenv(args[i] + 1);
            if (env_val) {
                args[i] = env_val;
            } else {
                args[i] = ""; // Clear if not found
            }
        }
    }
}
