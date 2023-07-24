#include "_shell.h"

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
		if (strcmp(built_s[i].builtin, *shell->tokens) == 0)
		{
			built_r = (*built_s[i].fun_p)(shell);
			return (built_r);
		}
		i++;
	}

	return (0);
}

int shell_exit(sh_data *shell)
{
	int arg;

	if (shell->tokens[1])
	{
		arg = atoi(shell->tokens[1]);
		if (arg <= 0)
		{
			dprintf(2, "misuse of exit\n");
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

int print_env(sh_data *shell)
{
	char **env = environ;

	while (*env)
		printf("%s\n", *env++);

	free_array(shell->tokens);

	return (1);
}
