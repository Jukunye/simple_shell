#include "shell.h"

/**
 * main - The main entry point of the shell program.
 * @ac: The number of command-line arguments.
 * @av: An array of pointers to the command-line arguments.
 *
 * Return: The status code of the shell process.
 */

int main(int ac, char **av)
{
	sh_data shell;
	(void)ac;

	shell.process = 0;
	shell.status = 0;
	shell.name = *av;
	shell.line = NULL;

	if (isatty(STDIN_FILENO))
		interactive(&shell);
	else
		non_interactive(&shell);

	return (shell.status);
}
