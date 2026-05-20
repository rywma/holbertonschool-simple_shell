#include "shell.h"

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, positive or negative if different
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * print_env - prints all environment variables
 * @envp: array of environment variable strings
 *
 * Return: void
 */

void print_env(char **envp)
{
	int i = 0;

	while (envp[i] != NULL)
	{
		write(STDOUT_FILENO, envp[i], strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

/**
 * handle_builtins - checks and runs builtin commands
 * @args: array of argument strings
 * @line: input line
 * @envp: environment variables
 *
 * Return: 1 if builtin was handled, 0 if not
 */

int handle_builtins(char **args, char *line, char **envp)
{
	if (_strcmp(args[0], "exit") == 0)
	{
		free(args);
		free(line);
		exit(EXIT_SUCCESS);
	}

	if (_strcmp(args[0], "env") == 0)
	{
		print_env(envp);
		free(args);
		return (1);
	}

	return (0);
}
