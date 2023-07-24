#include "_shell.h"

int main(int ac, char **av)
{
	sh_data shell;
	(void)ac;

	shell.status = 0;
	shell.name = *av;
	shell.line = NULL;

	if (isatty(STDIN_FILENO))
		interactive(&shell);
	else
		non_interactive(&shell);

	return (shell.status);
}
