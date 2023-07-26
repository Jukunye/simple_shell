#include "shell.h"

/**
 * removeNewline - remove the newline character in a string
 * @str: pointer to string
 * Return: nothing
 */
void removeNewline(char *str)
{
	int len;

	len = _strlen(str);

	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

/**
 * free_array - frees an array with pointer to strings
 * @ptr: array of strings pointer
 * Return: nothing
 */
void free_array(char **ptr)
{
	int i;

	if (ptr != NULL)
	{
		for (i = 0; ptr[i]; i++)
		{
			free(ptr[i]);
		}
		free(ptr);
		ptr = NULL;
	}
}

/**
 * remove_comment - ignores everything after a '#' char
 * @line: pointer to line string
 *
 * Return: nothing
 */
void remove_comment(char *line)
{
	int i = 0;

	if (*line == '#')
		*line = '\0';

	while (line[i] != '\0')
	{
		if (line[i] == '#' && line[i - 1] == ' ')
			break;
		i++;
	}
	line[i] = '\0';
}
