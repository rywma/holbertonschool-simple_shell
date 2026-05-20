#include "shell.h"

/**
 * execute - forks a child process then runs command
 * @args: NULL terminated array of strings
 * @envp: environmental variables
 * @prog_name: shell name
 * @cmd_count: command number
 *
 * Return: exit status
 */

int execute(char **args, char **envp, char *prog_name, int cmd_count)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = find_path(args[0], envp);

	if (full_path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, cmd_count, args[0]);
		return (127);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(full_path);
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(full_path, args, envp) == -1)
		{
			perror(prog_name);
			free(full_path);
			exit(1);
		}
	}

	waitpid(pid, &status, 0);

	free(full_path);

	return (WEXITSTATUS(status));
}
