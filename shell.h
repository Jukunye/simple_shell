#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define MISUSAGE	2
#define EX_BADUSAGE	2
#define EX_NOTFOUND	127

extern char **environ;


typedef struct shell_data {
	char *name;
	int process;
	int status;
	char **tokens;
	char *line;
} sh_data;

typedef struct builtin_s {
	char *builtin;
	int (*fun_p)(sh_data *);
} builtin_f;

void interactive(sh_data *shell);
void non_interactive(sh_data *shell);
void removeNewline(char *str);
char *find_path(char *cmd);
int execCmd(sh_data *shell);
int calc_tokens(char *lineptr);
char **tokenize(char *lineptr);
void free_array(char **ptr);
int builtins(sh_data *shell);
int shell_exit(sh_data *shell);
int print_env(sh_data *shell);
