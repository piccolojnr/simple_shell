#include "shell.h"

/**
 * chdir_builtin - Change the current working directory.
 * @info: Pointer to the info_t struct containing command info.
 *
 * Return: 0 on success, 1 on failure.
 */
int chdir_builtin(info_t **info)
{
char *target_directory;
if ((*info)->argc != 2)
{
_printf("Usage: cd <directory>\n");
return (1); /* Return an error code */
}
target_directory = (*info)->argv[1];
if (_strcmp(target_directory, "-") == 0)
{
return (handle_dash(*info, &(*info)->env));
}
else
{
return (change_directory(target_directory, &(*info)->env));
}
}
/**
 * alias_builtin - Define or display aliases.
 * @info: Pointer to the info_t struct containing command info.
 *
 * Return: 0 on success, 1 on failure.
 */
int alias_builtin(info_t **info)
{
int i, num;
if ((*info)->argc == 1)
{
print_aliases((*info)->aliases);
}
else if ((*info)->argc > 1)
{
for (i = 1; i < (*info)->argc; i++)
{
num = find_num_sub((*info)->argv[i], "=");
if (num == 1)
define_alias(*info, i, &(*info)->aliases);
else if (num == 0)
print_specific_alias((*info)->aliases, (*info)->argv[i]);
else
{
perror("alias");
return (1);
}
}
}
return (0);
}
/**
 * replace_args - Replaces $n references in argv with their
 * @info: Pointer to the info_t structure
 */
void replace_args(info_t **info)
{
int i, j, k, new_argc = 0;
char **new_argv;
for (i = 0; i < (*info)->argc; i++)
{
if ((*info)->argv[i])
new_argc++;
}
new_argv = malloc(sizeof(char *) * new_argc);
if (!new_argv)
{
perror("Memory allocation failed");
exit(EXIT_FAILURE);
}
for (j = 0, k = 0; k < (*info)->argc; k++)
{
if ((*info)->argv[k])
{
new_argv[j++] = (*info)->argv[k];
}
}
/* Free the old argv array */
new_argv[j] = NULL;
free((*info)->argv);
(*info)->argv = new_argv;
(*info)->argc = new_argc;
}
/**
 * custom_fgets - Reads from a file stream.
 * @str: String to read from.
 * @size: Size of string.
 * @stream: File stream.
 *
 * Return: String read from stream.
 */
char *custom_fgets(char *str, int size, FILE *stream)
{
int bytesRead = read(fileno(stream), str, size);
if (bytesRead == -1)
{
return (NULL);
}
str[bytesRead] = '\0';
return (str);
}
