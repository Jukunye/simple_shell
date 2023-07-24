#include "shell.h"

void removeNewline(char *str)
{
	int len;

	len = strlen(str);

	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

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
