#include "shell.h"

/*
 * main - entry point
 * argc: how many arguments were passed
 * argv: the arguments as strings
 * envp: environment variables
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	shell_loop(envp);

	return (0);
}

/*
 * shell_loop - the infinite read, parse, execute loop
 * envp: passed down so child processes inherit environemnt variables
 */
void shell_loop(char **envp)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char **args;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			if (isatty(STDIN_FILENO))
			write(TDOUT_FILENO, "\n", 1);
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

		if (_strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			exit(0);
		}

		if (_strcmp(args[0], "env") == 0)
		{
			print_env(envp);
			free(args);
			continue;
		}

		execute(args, envp, "./hsh", cmd_count);
		cmd_count++;
		free(args);
	}
	free(line);
}
