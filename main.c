#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * @envp: environment variables
 *
 * Return: 0
 */

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	shell_loop(envp);

	return (0);
}

/**
 * shell_loop - shell main loop
 * @envp: environment variables
 *
 * Return: void
 */

void shell_loop(char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;
	int cmd_count = 1;
	int status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 4);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);

			free(line);
			exit(status);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		args = tokenize(line);

		if (args == NULL)
			continue;

		if (_strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(status);
		}

		if (handle_builtins(args, line, envp))
			continue;

		status = execute(args, envp, "./hsh", cmd_count);

		cmd_count++;
		free(args);
	}

	free(line);
}
