#ifndef SHELL_H
#define SHELL_H

#define MAX_PATH_LENGTH 1024


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * struct command_info - command information
 * @line: line of command
 * @path: command path
 * @argc: number of arguments
 * @argv: arguments
 * @line_len: length of line
 * @char_len: length of char in line
 * @is_built_in: return value of built-in
 */
typedef struct command_info
{
	char *line;
	int argc;
	char **argv;
	char *path;

	size_t line_len;
	ssize_t char_len;

	int is_built_in;
} cmd_info;


/**
 * struct tbt - builtin table
 * @type: type of builtin
 * @func: function to call
 */
typedef struct tbt
{
	char *type;
	int (*func)(cmd_info *);
} builtin_table;

/* environment */
extern char **environ;

/* run_shell */
void run_shell(void);
void find_executable(cmd_info **info);

/* executable_cmd */
void execute_command(cmd_info *);

/* string */
int split_str(char *, char ***, char *, int);
void free_args(char **);

/* string 2*/
char *_strcpy(char *, const char *);
int _strlen(char *);
char *_strdup(const char *);
char *_strchr(char *, char);
char *_strncpy(char *dest, const char *src, int n);

/* string 3*/
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char *_strcat(char *, const char *);

/* builtin */
int find_builtin(cmd_info **);


/* built_in */
int which_builtin(cmd_info *);
int exit_builtin(cmd_info *);
int env_builtin(cmd_info *info);

/* get_env */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* helper */
char *allocate_and_copy(const char *str, int length);
int count_words(const char *str, char *delim);
int is_delim(char, char *);

#endif /* SHELL_H */
