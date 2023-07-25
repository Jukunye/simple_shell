#include "shell.h"

/**
 * calc_tokens - finds the number of tokens
 * @line: pointer to line string
 * Return: number of tokens
 */
int calc_tokens(char *line)
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
	char **arr_t;
	int i = 0, num_token;
	char *line_copy, *token;

	line_copy = _strdup(line);
	if (line_copy == NULL)
		return (NULL);

	num_token = calc_tokens(line);
	if (num_token == -1 || num_token == 0)
		return (NULL);

	arr_t = malloc(sizeof(char *) * (num_token + 1));
	if (arr_t == NULL)
		return (NULL);

	token = strtok(line_copy, delim);
	while (token != NULL)
	{
		arr_t[i] = _strdup(token);
		token = strtok(NULL, delim);
		i++;
	}
	arr_t[i] = NULL;
	if (arr_t == NULL)
	{
		free(line);
		return (NULL);
	}
	free(line_copy);
	return (arr_t);
}

