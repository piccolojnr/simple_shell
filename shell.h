#ifndef SHELL_H
#define SHELL_H

#define MAX_PATH_LENGTH 1024
#define BUFFER_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

/**
 * struct env_list - linked list of environment variables
 * @name: name of environment variable
 * @value: value of environment variable
 * @next: pointer to next node
 */
typedef struct env_list
{
	char *name;
	char *value;
	struct env_list *next;
} t_env;

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
} info_t;

/**
 * struct tbt - builtin table
 * @type: type of builtin
 * @func: function to call
 */
typedef struct tbt
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* environment */
extern char **environ;
extern t_env *env_list;

t_env *env_list = NULL;

/* run_shell */
void run_shell(void);
void find_executable(info_t **info);

/* _getline */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void get_input(info_t *info);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* executable_cmd */
void execute_command(info_t *);

/* string */
int split_str(char *str, char ***args, char *delim);
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
int find_builtin(info_t **);
void replace_env_var(info_t **info);

/* built_in */
int which_builtin(info_t *);
int exit_builtin(info_t *);
int env_builtin(info_t *info);
int setenv_builtin(info_t *info);
int unsetenv_builtin(info_t *info);

/* get_env */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/* helper */
char *allocate_and_copy(const char *str, int length);
int count_words(const char *str, char *delim);
int is_delim(char, char *);
int _atoi(char *s);
void exit_shell(info_t *info, int exit_status);

/** helper 1*/
char **split_env(char *str);
char *concat_path_and_cmd(const char *path, const char *cmd);

/* lists */
int create_env_list();
int add_node_end(const char *name, const char *value);
void free_env_list(t_env *head);
int edit_node(char *name, char *new_value);
int remove_node(char *name);

#endif /* SHELL_H */
