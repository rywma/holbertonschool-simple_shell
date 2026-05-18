#include "shell.h"

/**
 * main - entry point
 * @argc: how many arguments were passed
 * @argv: the arguments as strings
 * @envp: environment variables
 *
 * Return: 0 on success
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	shell_loop(envp);

	return (0);
}

/**
 * shell_loop - the infinite read, parse, execute loop
 * @envp: passed down so child processes inherit environemnt variables
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
			exit(0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		args = tokenize(line);
		if (args == NULL)
			continue;

		if (handle_builtins(args, line, envp))
			continue;

		execute(args, envp, "./hsh", cmd_count);
		cmd_count++;
		free(args);
	}
	free(line);
}
