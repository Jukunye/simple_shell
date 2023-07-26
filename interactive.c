#include "shell.h"

void interactive(sh_data *shell);
/**
 * interactive - Run the shell in interactive mode.
 * @shell: A pointer to the shell data structure.
 *
 * Return: Void
 */

void interactive(sh_data *shell)
{
	char *path;
	size_t n = 0;
	ssize_t nread;
	int built_r;

	while (1)
	{
		shell->process++;
		write(1, "$ ", 2);
		nread = _getline(&shell->line, &n, stdin);
		if (nread == -1)
		{
			perror("reading input");
			exit(EXIT_FAILURE);
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
			if (_strcmp(path, *shell->tokens) != 0)
			{
				free(*shell->tokens);
				*shell->tokens = _strdup(path);
				free(path);
			}
			shell->status = execCmd(shell);
		}
		else
		{
			dprintf(STDERR_FILENO, "%s: %d: %s: not found\n"
					, shell->name, shell->process, *shell->tokens);
			shell->status = EX_NOTFOUND;
		}
		free_array(shell->tokens);
	}
	free(shell->line);
}
