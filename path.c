#include "shell.h"

char *find_path(char *cmd)
{
	char *path, *pathcp, *dir, *temp;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);
	pathcp = getenv("PATH");
	if (pathcp == NULL)
		return (NULL);

	path = _strdup(pathcp);

	temp = strtok(path, ":");

	while (temp != NULL)
	{
		dir = malloc(_strlen(temp) + _strlen(cmd) + 2);

		dir = _strcpy(dir, temp);
		dir = _strcat(dir, "/");
		dir = _strcat(dir, cmd);

		if (stat(dir, &st) == 0)
		{
			free(path);
			return (dir);
		}
		free(dir);

		temp = strtok(NULL, ":");
	}
	free(path);


	return (NULL);
}
