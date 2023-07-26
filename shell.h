#ifndef SHELL_H
#define SHELL_H

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>

#define MISUSAGE	2
#define EX_BADUSAGE	2
#define EX_NOTFOUND	127
#define EX_CMDFAIL 2
#define EX_SUCCESS 0

extern char **environ;

/**
 * struct shell_data - contains all most used variables for the shell
 * @name: name of the program
 * @process: counts the process
 * @status: exit status of the program
 * @tokens: tokenized string
 * @line: pointer input string
 *
 * Description: struct data
 */
typedef struct shell_data
{
	char *name;
	int process;
	int status;
	char **tokens;
	char *line;
} sh_data;
/**
 * struct builtin_s - buit in functions struct
 * @builtin: builtin function string
 * @fun_p: function pointer
 *
 * Description: struct data
 */
typedef struct builtin_s
{
	char *builtin;
	int (*fun_p)(sh_data *);
} builtin_f;

/*Prototypes*/
void interactive(sh_data *shell);
void non_interactive(sh_data *shell);
void removeNewline(char *str);
char *find_path(char *cmd);
int execCmd(sh_data *shell);
int calc_tokens(char *lineptr);
char **tokenize(char *lineptr);
void free_array(char **ptr);

/*_builtins.c*/
int builtins(sh_data *shell);
int shell_exit(sh_data *shell);
int print_env(sh_data *shell);
int change_directory(sh_data *shell);

/*string.c*/
int _strcmp(const char *str1, const char *str2);
size_t _strlen(const char *str);
char *_strdup(const char *src);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);

/*atoi.c*/
int _atoi(char *s);

/*enviroment.c*/
int setenv_command(sh_data *shell);
int unsetenv_command(sh_data *shell);
char *_getenv(const char *name);

/*_getline.c*/
void *_memcpy(void *dest, const void *src, size_t n);
ssize_t refillBuffer(FILE *stream, char buf[],
		size_t *buf_index, ssize_t *bytes_remaining);
char *resizeLineBuffer(char *lineptr, size_t *n, ssize_t bytes_read);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif
