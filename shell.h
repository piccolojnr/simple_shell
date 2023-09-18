#ifndef SHELL_H
#define SHELL_H

#define MAX__LENGTH 1024
#define BUFFER_SIZE 1024
#define MAX_ALIASES 50
#define MAX_ALIAS_LEN 100

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
 * struct alias_list - linked list of aliases
 * @name: alias
 * @value: value of alias
 * @next: ...
 */
typedef struct alias_list
{
	char *name;
	char *value;
	struct alias_list *next;
} alias_t;

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
 * @status: status of process
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
	int (*func)(info_t *, t_env **, alias_t **);
} builtin_table;

/* environment */
extern char **environ;

/* run_shell */
int run_shell(t_env **, char *);
int start_process(info_t **, t_env **, alias_t **);
void find_executable(info_t **, t_env **, alias_t **);
char *filter_comments(const char *);
int handle_logical_operators(char *line, info_t **info,
							t_env **env_list, alias_t **);

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
char *_strcpy(char *, const char *);
char *_strncpy(char *, const char *, int n);
int _strlen(char *);

/* string 2*/
char *_strdup(const char *);
char *_strndup(const char *, int);
char *_strchr(char *, char);
int _strcmp(char *, char *);
int _strncmp(char *, char *, int);

/* string 3*/
char *_strcat(char *, const char *);
char *_strncat(char *, const char *, int);
int find_num_sub(char *, char *);
int replace_str(char **, char *, char *);
char *trimWhitespace(const char *str);

/* builtin */
int find_builtin(info_t *, t_env **, alias_t **);
void replace_env_var(info_t **, t_env *);
void replace_args(info_t **);
void replace_with_env_var(info_t **info, int index, const char *env_name,
							t_env *env_list);
void replace_with_status(info_t **info, int index);
void replace_with_pid(info_t **info, int index, pid_t shell_pid);



/* builtin_1 */
int which_builtin(info_t *, t_env **, alias_t **);
int exit_builtin(info_t *, t_env **, alias_t **);
int env_builtin(info_t *, t_env **, alias_t **);
int setenv_builtin(info_t *, t_env **, alias_t **);
int unsetenv_builtin(info_t *, t_env **, alias_t **);

/* builtin_2 */
int chdir_builtin(info_t *, t_env **, alias_t **);
int alias_builtin(info_t *, t_env **, alias_t **);

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

/* helper 2*/
int count_digits(int num);
int execute_logical_command(info_t **info,
		t_env **env_list, alias_t **, int and_operator);

/* env_lists */
int create_env_list(t_env **);
int add_env_node_end(const char *, const char *, t_env **);
void free_env_list(t_env *);
int edit_env_node(char *, char *, t_env **);
int remove_env_node(char *, t_env **);

/* _strtok */
char *_strtok(char *, const char *);

/* _puts */
int _putchar(char);
void _puts(char *);
int _printf(const char *, ...);

/* alias */
void print_aliases(alias_t *);
void print_specific_alias(alias_t *, char *);
int define_alias(info_t *, int, alias_t **);
alias_t *get_alias(alias_t *, char *);

/* alias_lists */
int add_alias_node_end(const char *, const char *, alias_t **);
int edit_alias_node(char *, char *, alias_t **);
int remove_alias_node(char *, alias_t **);

/* chdir */
int change_directory(const char *, t_env **);
int handle_dash(info_t *, t_env **);

#endif /* SHELL_H */
