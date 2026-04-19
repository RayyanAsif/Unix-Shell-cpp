#include "shell.h"

// Added: Prevents Ctrl+C from killing the shell
void sigint_handler(int sig) {
    printf("\nmyShell> ");
    fflush(stdout);
}

int main() {
    char input[1024];
    char *args[100];

    // Added: Register signal handler
    signal(SIGINT, sigint_handler);

    while (1) {
        printf("myShell> ");
        if (!fgets(input, sizeof(input), stdin)) break;

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        // Existing pipe check (now points to advanced N-pipe logic)
        if (strchr(input, '|')) {
            handle_pipes(input);
            continue;
        }

        parse_input(input, args);

        // Added: Expand variables like $USER before executing
        expand_variables(args);

        if (handle_builtin(args)) continue;

        execute_command(args);
    }

    return 0;
}
