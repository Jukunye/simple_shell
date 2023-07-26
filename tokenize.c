#include "shell.h"

/**
 * count_tokens - finds the number of tokens
 * @line: pointer to line string
 * Return: number of tokens
 */
int count_tokens(char *line)
{
	const char *delim = " \t\a\r\n";
	int counter = 0;
	char *token, *line_copy;

	line_copy = _strdup(line);
	if (line_copy == NULL)
		return (-1);

	token = strtok(line_copy, delim);
	while (token != NULL)
	{
		counter++;
		token = strtok(NULL, delim);
	}

	free(line_copy);
	return (counter);
}

/**
 * tokenize - parses the line string into an array of string pointers
 * @line: pointer to  line string
 * Return: tokenized string
 */
char **tokenize(char *line)
{
	const char *delim = " \t\a\r\n";
	char **tokens;
	int i = 0, count;
	char *line_copy, *token;

	line_copy = _strdup(line);
	if (line_copy == NULL)
		return (NULL);

	count = count_tokens(line);
	if (count == -1 || count == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);

	token = strtok(line_copy, delim);
	while (token != NULL)
	{
		tokens[i] = _strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;
	free(line_copy);
	return (tokens);
}

