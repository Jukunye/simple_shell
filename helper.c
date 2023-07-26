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
