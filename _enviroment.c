#include "shell.h"

/**
 * setenv_command - Builtin function to set an environment variable.
 * @shell: Pointer to the shell data structure.
 *
 * Return: Always returns 1.
 */
int setenv_command(sh_data *shell)
{
	if (shell->tokens[1] == NULL || shell->tokens[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		free_array(shell->tokens);
		return (1);
	}
	if (setenv(shell->tokens[1], shell->tokens[2], 1) != 0)
		perror("setenv");

	free_array(shell->tokens);
	return (1);
}

/**
 * unsetenv_command - Builtin function to unset an environment variable.
 * @shell: Pointer to the shell data structure.
 *
 * Return: Always returns 1.
 */
int unsetenv_command(sh_data *shell)
{
	if (shell->tokens[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		free_array(shell->tokens);
		return (1);
	}
	if (unsetenv(shell->tokens[1]) != 0)
		perror("unsetenv");

	free_array(shell->tokens);
	return (1);
}

/**
 * _getenv - Get the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: A pointer to the value of the environment variable,
 *         or NULL if the variable is not found.
 */
char *_getenv(const char *name)
{
	char **env = environ;

	if (name == NULL || *name == '\0')
		return (NULL);

	while (*env)
	{
		if (_strcmp(*env, name) == 0)
		{
			char *value = *env;

			value += _strlen(name) + 1; /* Skip the variable name and '=' */
			return (value);
		}

		env++;
	}
	return (NULL);
}
