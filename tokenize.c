#include "shell.h"

/**
 * tokenize - splits a line into array of strings
 * @line: input of string from user
 *
 * Return: array of strings ended in NULL, or NULL on failure
 */
char **tokenize(char *line)
{
	char **tokens;
	char *token;
	int i = 0;

	tokens = malloc(sizeof(char *) * MAX_ARGS);
	if (tokens == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(line, DELIMITERS);

	while (token != NULL && i < MAX_ARGS - 1)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, DELIMITERS);
	}

	tokens[i] = NULL;

	if (i == 0)
	{
		free(tokens);
		return (NULL);
	}

	return (tokens);
}
