#include "shell.h"

/**
 * non_interactive - handles the shell when the terminal is not used
 * @shell: pointer to shell struct
 * Return: nothing
 */
void non_interactive(sh_data *shell)
{
	char *path;
	size_t n = 0;
	/*ssize_t nread;*/
	int built_r;

	while (getline(&shell->line, &n, stdin) != -1)
	{
		shell->process++;

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
				*shell->tokens = strdup(path);
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
