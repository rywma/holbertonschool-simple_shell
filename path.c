#include "shell.h"

/**
 * get_env_value - finds the value of an environment variable
 * @name: variable name to search
 * @envp: array of environment strings
 *
 * Return: pointer to the value string, or NULL if not found
 */
char *get_env_value(char *name, char **envp)
{
	int i = 0;
	size_t name_len;

	if (!name || !envp)
		return (NULL);

	name_len = strlen(name);

	while (envp[i] != NULL)
	{
		if (strncmp(envp[i], name, name_len) == 0 &&
			envp[i][name_len] == '=')
		{
			return (envp[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

/**
 * search_dirs - searches directories in PATH for command
 * @cmd: command name
 * @path_copy: colon separated PATH string copy
 *
 * Return: full path if found, NULL if not
 */
char *search_dirs(char *cmd, char *path_copy)
{
	char *dir;
	char *full_path;
	size_t len;

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(cmd) + 2;
		full_path = malloc(len);
		if (full_path == NULL)
			return (NULL);
		sprintf(full_path, "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		dir = strtok(NULL, ":");
	}
	return (NULL);
}

/**
 * find_path - finds the full path of command PATH
 * @cmd: command name
 * @envp: environment variables
 *
 * Return: malloc full path string, or NULL if not found
 */
char *find_path(char *cmd, char **envp)
{
	char *path_env;
	char *path_copy;
	char *full_path;

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path_env = get_env_value("PATH", envp);
	if (path_env == NULL)
		return (NULL);

	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);

	full_path = search_dirs(cmd, path_copy);
	free(path_copy);
	return (full_path);
}
