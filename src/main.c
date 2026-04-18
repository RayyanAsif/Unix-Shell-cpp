#include "shell.h"

int main() {
    char input[1024];
    char *args[100];

    while (1) {
        printf("myShell> ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = 0;

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
