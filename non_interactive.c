#include "shell.h"
/**
 * run_shell_non_interactive - Runs the shell
 * @info: ...
 * @name: name of program
 *
 * Return: 0 for success, 1 for failure
 */
int run_shell_non_interactive(info_t *info, char *name)
{
int i;
char *line, **args = NULL;
size_t char_len = 0;
FILE *file = NULL;
file = fopen(name, "r");
if (file == NULL)
{
perror("failed to open file");
return (EXIT_FAILURE);
}
while (_fgets(info, &line, &char_len, file) != NULL)
{
split_str(line, &args, "\n");
free(line);
if (args != NULL)
{
for (i = 0; args[i] != NULL; i++)
{
if (run_shell(info, args[i]) == -2)
{
free_args(args);
free(args[i]);
return (EXIT_FAILURE);
}
free(args[i]);
}
free_args(args);
}
}
fclose(file);
return (EXIT_SUCCESS);
}
/**
 * run_shell - ...
 * @info: ...
 * @line: ...
 *
 * Return: ...
 */
int run_shell(info_t *info, char *line)
{
int i;
char *filtered_line, **args = NULL, *trimmed, *delim = ";";
if (is_line_empty(line))
return (1);
filtered_line = filter_comments(line);
if (filtered_line == NULL)
return (1);
split_str(filtered_line, &args, delim);
if (args == NULL)
return (1);
for (i = 0; args[i] != NULL; i++)
{
trimmed = trimWhitespace(args[i]);
free(args[i]);
args[i] = trimmed;
if (args[i] != NULL && !is_line_empty(args[i]))
{
if (handle_logical_operators(args[i], info) == -2)
return (-2);
}
}
free_args(args);
return (0);
}
