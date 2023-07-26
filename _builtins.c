#include "shell.h"

/**
 * builtins - Check if the given command is
 * a builtin and execute it if found.
 * @shell: Pointer to the shell data structure.
 *
 * Return: The value of the executed builtin command
 * or 0 if not found.
 */

int builtins(sh_data *shell)
{
	int i = 0, built_r;
	builtin_f built_s[] = {
		{"exit", &shell_exit},
		{"env", &print_env},
		{NULL, NULL}
	};

	while (built_s[i].builtin)
	{
		if (_strcmp(built_s[i].builtin, *shell->tokens) == 0)
		{
			built_r = (*built_s[i].fun_p)(shell);
			return (built_r);
		}
		i++;
	}
	return (0);
}

/**
 * shell_exit - Builtin function to exit the shell.
 * @shell: Pointer to the shell data structure.
 *
 * Return: This function does not return.
 * It exits the shell with a status code.
 */
int shell_exit(sh_data *shell)
{
	int arg;

	if (shell->tokens[1])
	{
		arg = _atoi(shell->tokens[1]);

		if (arg <= 0)
		{
			dprintf(2, "%s: %d: exit: Illegal number: %s\n",
					shell->name, shell->process, shell->tokens[1]);
			free_array(shell->tokens);
			free(shell->line);
			exit(MISUSAGE);
		}
		free_array(shell->tokens);
		free(shell->line);
		exit(arg);
	}
	free_array(shell->tokens);
	free(shell->line);
	exit(EXIT_SUCCESS);

	return (1);
}

/**
 * print_env - Builtin function to
 * print the environment variables.
 * @shell: Pointer to the shell data structure.
 *
 * Return: Always returns 1.
 */

int print_env(sh_data *shell)
{
	char **env = environ;

	while (*env)
		printf("%s\n", *env++);

	free_array(shell->tokens);

	return (1);
}
