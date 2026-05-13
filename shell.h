#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define DELMITERS " \t\r\n\a"
#define MAX_ARGS 64

void shell_loop(char **envp);
char **tokenize(char *line);
char *get_env_value(char *name, char **envp);
char *find_path(char *cmd, char **envp);
int execute(char **args, char **envp, char *prog_name);

#endif
