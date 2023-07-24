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

	path = strdup(pathcp);

	temp = strtok(path, ":");

	while (temp != NULL)
	{
		dir = malloc(strlen(temp) + strlen(cmd) + 2);

		dir = strcpy(dir, temp);
		dir = strcat(dir, "/");
		dir = strcat(dir, cmd);

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
