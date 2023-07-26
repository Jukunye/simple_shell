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
		{"cd", &change_directory},
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

/**
 * change_directory - Builtin function to change the current directory.
 * @shell: Pointer to the shell data structure.
 *
 * Return: Always returns 1.
 */
int change_directory(sh_data *shell)
{
	if (shell->tokens[1] == NULL)
	{
		char *home_path = getenv("HOME");

		if (home_path != NULL)
		{
			chdir(home_path);
			setenv("PWD", home_path, 1);

			fprintf(stderr, "Home directory not set.\n");
		}
	} else if (_strcmp(shell->tokens[1], "-") == 0)
	{
		char *previous_path = _getenv("OLDPWD");

		if (previous_path != NULL)
		{
			chdir(previous_path);
			setenv("PWD", previous_path, 1);

			fprintf(stderr, "Previous directory not set.\n");
		}
	} else
	{
		char current_path[1024];

		if (getcwd(current_path, sizeof(current_path)) != NULL)
		{
			if (chdir(shell->tokens[1]) == 0)
			{
				setenv("OLDPWD", current_path, 1);
				setenv("PWD", shell->tokens[1], 1);

				perror("cd");
			}
		} else
			perror("getcwd");
	}
	free_array(shell->tokens);
	return (1);
}
