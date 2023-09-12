#ifndef SHELL_H
#define SHELL_H

#define MAX__LENGTH 1024
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
 * @env_list: linked list of environment variables
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
	int (*func)(info_t *, t_env **);
} builtin_table;

/* environment */
extern char **environ;

/* run_shell */
void run_shell(t_env **);
void find_executable(info_t **, t_env **);

/* _getline */
ssize_t _getline(char **, size_t *, FILE *);
void get_input(info_t *);
void *_realloc(void *, unsigned int, unsigned int);

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
int find_builtin(info_t *, t_env **);
void replace_env_var(info_t **, t_env *);
void replace_args(info_t **info);

/* built_in */
int which_builtin(info_t *, t_env **);
int exit_builtin(info_t *, t_env **);
int env_builtin(info_t *, t_env **);
int setenv_builtin(info_t *, t_env **);
int unsetenv_builtin(info_t *, t_env **);

/* get_env */
char *_getenv(const char *, t_env *);
int _setenv(const char *, const char *, int, t_env **);
int _unsetenv(const char *, t_env **);

/* helper */
char *allocate_and_copy(const char *, int);
int count_words(const char *, char *);
int is_delim(char, char *);
int _atoi(char *);
void exit_shell(info_t *, int);

/** helper 1*/
char **split_env(char *);
char *concat_path_and_cmd(const char *, const char *);

/* lists */
int create_env_list(t_env **);
int add_node_end(const char *, const char *, t_env **);
void free_env_list(t_env *);
int edit_node(char *, char *, t_env **);
int remove_node(char *, t_env **);

/* _strtok */
char *_strtok(char *str, const char *delim);

#endif /* SHELL_H */
