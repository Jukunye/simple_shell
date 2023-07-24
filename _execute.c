#include "_shell.h"

int execCmd(sh_data *shell)
{
	pid_t pid;
	int status;
	char **env = environ;

	pid = fork();

	if (pid == -1)
	{
		perror("fork failed");
		free_array(shell->tokens);
		free(shell->line);
		exit(EXIT_FAILURE);
	}

	else if (pid == 0)
	{
		/* child process */
		if (execve(shell->tokens[0], shell->tokens, env) < 0)
		{
			perror("execve failed");
			free_array(shell->tokens);
			free(shell->line);
			exit(EX_BADUSAGE);
		}
	}

	else
		/* parent process */
		wait(&status);

	if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);

	return (status);
}
