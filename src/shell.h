#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

// parser.c
void parse_input(char *input, char **args);
void expand_variables(char **args);

// executor.c
void execute_command(char **args);

// builtin.c
int handle_builtin(char **args);

// advanced.c
void handle_redirection(char **args);
int handle_background(char **args);
void handle_pipes(char *input);

#endif
