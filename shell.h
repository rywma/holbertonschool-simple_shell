#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define DELIMITERS " \t\r\n\a"
#define MAX_ARGS 64

void shell_loop(char **envp);
char **tokenize(char *line);
char *get_env_value(char *name, char **envp);
char *find_path(char *cmd, char **envp);
int execute(char **args, char **envp, char *prog_name, int cmd_count);
void print_env(char **envp);
int _strcmp(char *s1, char *s2);
int handle_builtins(char **args, char *line, char **envp);
char *search_dirs(char *cmd, char *path_copy);

#endif
