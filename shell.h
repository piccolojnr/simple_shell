#ifndef SHELL_H
#define SHELL_H

#define MAX__LENGTH 1024
#define BUFFER_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdarg.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
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

	int char_len;

	int is_built_in;
	int status;
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
int run_shell(t_env **, char *);
int start_process(info_t **, t_env **);
void find_executable(info_t **, t_env **);
char *filter_comments(const char *);
int handle_logical_operators(char *line, info_t **info, t_env **env_list);

/* _getline */
int _getline(char **, size_t *, int);
void get_input(info_t *, char **, size_t *, int);
void *_realloc(void *, unsigned int);
void *_malloc(unsigned int);
void *_realloc2(void *ptr, unsigned int old_size, unsigned int new_size);

/* executable_cmd */
int execute_command(info_t **);
void handle_execution_error(info_t **info);

/* string */
int split_str(char *, char ***, char *);
void free_args(char **);

/* string 2*/
char *_strcpy(char *, const char *);
int _strlen(char *);
char *_strdup(const char *);
char *_strndup(const char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, const char *, int n);

/* string 3*/
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);
char *_strcat(char *, const char *);
char *_strncat(char *, const char *, int);
int find_n_occ(char *, char *);
int replace_str(char **, char *, char *);
char *trimWhitespace(const char *str);

/* builtin */
int find_builtin(info_t *, t_env **);
void replace_env_var(info_t **, t_env *);
void replace_args(info_t **);

/* built_in */
int which_builtin(info_t *, t_env **);
int exit_builtin(info_t *, t_env **);
int env_builtin(info_t *, t_env **);
int setenv_builtin(info_t *, t_env **);
int unsetenv_builtin(info_t *, t_env **);

/* built_in_1 */
int chdir_builtin(info_t *, t_env **);

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
int is_line_empty(const char *line);
int isspace(int c);
char *int_to_string(int num);
int count_digits(int num);
int execute_logical_command(info_t **info, t_env **env_list, int and_operator);

/* lists */
int create_env_list(t_env **);
int add_node_end(const char *, const char *, t_env **);
void free_env_list(t_env *);
int edit_node(char *, char *, t_env **);
int remove_node(char *, t_env **);

/* _strtok */
char *_strtok(char *, const char *);

/* _puts */
int _putchar(char);
void _puts(char *);
int _printf(const char *, ...);

#endif /* SHELL_H */
