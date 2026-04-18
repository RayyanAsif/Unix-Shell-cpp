// shell.h
#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

// parser
void parse_input(char *input, char **args);

// executor
void execute_command(char **args);

// built-in commands
int handle_builtin(char **args);

// advanced features
void handle_redirection(char **args);
int handle_background(char **args);
void handle_pipes(char *input);

#endif
