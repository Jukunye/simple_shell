#include "shell.h"

void non_interactive(sh_data *shell)
{
	char *path;
	size_t n = 0;
	ssize_t nread;
	int built_r, process = 0;

	while (1)
	{
		process++;
		nread = getline(&shell->line, &n, stdin);
		if (nread == -1)
		{
			/*perror("reading input");*/
			/*exit(EXIT_FAILURE);*/
			break;
		}

		removeNewline(shell->line);

		shell->tokens = tokenize(shell->line);
		if (shell->tokens == NULL)
			continue;

		built_r = builtins(shell);
		if (built_r == 1)
			continue;

		path = find_path(*shell->tokens);

		if (path != NULL)
		{
			if (strcmp(path, *shell->tokens) != 0)
			{
				free(*shell->tokens);
				*shell->tokens = strdup(path);
				free(path);
			}
			shell->status = execCmd(shell);
		}
		else
		{
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", shell->name, process, *shell->tokens);
			shell->status = EX_NOTFOUND;
		}

		free_array(shell->tokens);
	}
	free(shell->line);
}
