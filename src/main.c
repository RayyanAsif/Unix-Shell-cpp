#include "shell.h"

int main() {
    char input[1024];
    char *args[100];

    while (1) {
        printf("myShell> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;

        // Ignore empty input
        if (strlen(input) == 0) continue;

        // Check for pipes first
        if (strchr(input, '|')) {
            handle_pipes(input);
            continue;
        }

        parse_input(input, args);

        if (handle_builtin(args)) continue;

        execute_command(args);
    }

    return 0;
}
