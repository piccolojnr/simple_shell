#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

/* for convert_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define INFO_INIT                             \
	{                                         \
		NULL, 0, NULL, 0, NULL, 0, NULL, NULL \
	}

/* functions return */
#define SUCCESS 0
#define FAILURE 1
#define EXIT -2

/* builtin returns */
#define BUILTIN_NOT_FOUND -1
#define BUILTIN_SUCCESS 0
#define BUILTIN_FAILURE 1
#define BUILTIN_EXIT -2

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
 * struct info - information about the shell
 * @argv: ...
 * @argc: ...
 * @path: ...
 * @status: ...
 * @cmds: ...
 * @cmds_len: ...
 * @env: ...
 * @filename: ...
 */
typedef struct info
{
	char **argv;
	int argc;
	char *path;
	int status;

	char **cmds;
	int cmds_len;

	char **env;
	char *filename;
} t_info;

/* shell */
void run_interactive_shell(t_info *);
void run_non_interactive_shell(t_info *);
void run_file(t_info *);
int start_process(t_info *);
int fork_command(t_info *info);

/* getline */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
int get_input(char **lineptr, size_t *n, FILE *stream, t_info *info);

/* string parser */
int parse_string(char *str, const char *del, char ***args);

/* helper functions 1*/
int is_interactive(void);
int is_delim(char c, const char *delim);

/* string manipulation 1*/
char *trimm_str(char *str);
int _strlen(const char *s);
int count_substrings(char *str, const char *delim);
char *_strdup(const char *s);
char *_strcpy(char *dest, const char *src);

/* string manipulation 2*/
void replace_char(char *str, char oldChar, char newChar);
int find_num_sub(char *str, char *sub);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, int n);
int _strcmp(char *s1, char *s2);

/* string manipulation 3 */
int _strncmp(char *s1, char *s2, int n);
char *_strchr(char *s, char c);
char *_strndup(const char *str, int n);
char *_strncpy(char *dest, const char *src, int n);

/* _puts */
void _puts(char *str);
int _putchar(char c);

/* memory */
void ffree(char **ar);

#endif /* SHELL_H */
